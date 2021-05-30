#include <iostream>
#include <cstdio>
#include <memory>
#include <thread>
#include <mutex>
#include <future>
#include <cards.h>

static cards::CardRefs card;
static std::mutex mtx;
static unsigned int drawCount = 0, shuffleCount = 0;

void InitDeck(std::unique_ptr<cards::CCardDeck>& deckPtr)
{
	std::lock_guard<std::mutex> lg(mtx);
	deckPtr->Init();
	deckPtr->Shuffle();
	shuffleCount++;
}

void DrawCard(std::unique_ptr<cards::CCardDeck>& deckPtr)
{
	if(card != cards::EMPTY_DECK)
	{
		mtx.lock();
		card = deckPtr->Draw();
		drawCount++;
		mtx.unlock();

		std::printf("Dealed card: %s\n", deckPtr->CardToStr(card).c_str());
		std::printf("With value: %d\n", deckPtr->CardValue(card));

		return;
	}
}

void ShuffleDeck(std::unique_ptr<cards::CCardDeck>& deckPtr)
{
	std::lock_guard<std::mutex> lg(mtx);
	deckPtr->Shuffle();
	shuffleCount++;
}

int main()
{
	std::unique_ptr<cards::CCardDeck> cardDeck(new cards::CCardDeck);

	// Initialize the deck
	auto vf = std::async(std::launch::async, [&cardDeck]() {
																							InitDeck(cardDeck);
																							return true;
																						});
	vf.get();

	for(unsigned int idx = 0; idx < 60; idx++)
	{
		// Shuffle on every tenth itheration
		if(idx % 10 == 0) {
			auto wf = std::async(std::launch::async, [&cardDeck]() {
																									ShuffleDeck(cardDeck);
																									return true;
																								});
			wf.get();
		}
		else {	// Attempt to draw card
			auto wf = std::async(std::launch::async, [&cardDeck]() {
																									DrawCard(cardDeck);
																									return true;
																								});
			wf.get();
		}
	}

	//threads.join();

	std::printf("\nAttempted Draw Count: %d\nShuffle Count: %d\n", drawCount, shuffleCount);

	return 0;
}

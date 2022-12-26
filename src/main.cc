#include <iostream>
#include <cstdio>
#include <future>
#include <cards.h>

static cards::CardRefs card = cards::CardRefs::CLUBS2;
static std::mutex mtx;
static unsigned int drawCount = 0u; 
static unsigned int shuffleCount = 0u;

static void InitDeck(std::unique_ptr<cards::CCardDeck>&& deckPtr)
{
	std::lock_guard<std::mutex> lg(mtx);
	deckPtr->Init();
	deckPtr->Shuffle();
	shuffleCount++;
}

static void DrawCard(std::unique_ptr<cards::CCardDeck>&& deckPtr)
{
	if(card != cards::CardRefs::EMPTY_DECK)
	{
		mtx.lock();
		card = std::move(deckPtr->Draw());
		drawCount++;
		mtx.unlock();

		std::printf("Dealed card: %s\n", deckPtr->CardToStr(card).c_str());
		std::printf("With value: %d\n", deckPtr->CardValue(card));
	}
}

static void ShuffleDeck(std::unique_ptr<cards::CCardDeck>&& deckPtr)
{
	std::lock_guard<std::mutex> lg(mtx);
	deckPtr->Shuffle();
	shuffleCount++;
}

int main() {
	auto cardDeck = std::make_unique<cards::CCardDeck>();

	// Initialize the deck
	auto vf = std::async(std::launch::async, [&cardDeck]() {
                            InitDeck(std::move(cardDeck));
                            return true;
                        });
	vf.get();

	for(unsigned int idx = 0; idx < 60; idx++) {
		// Shuffle on every tenth iteration
		if(idx % 10 == 0) {
			auto wf = std::async(std::launch::async, [&cardDeck]() {
                                    ShuffleDeck(std::move(cardDeck));
                                    return true;
                                });
			wf.get();
		}
		else {	// Attempt to draw card
			auto wf = std::async(std::launch::async, [&cardDeck]() {
                                    DrawCard(std::move(cardDeck));
                                    return true;
                                });
			wf.get();
		}
	}

	std::printf("\nAttempted Draw Count: %d\nShuffle Count: %d\n", drawCount, shuffleCount);

	return 0;
}

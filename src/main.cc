#include <iostream>
#include <cstdio>
#include <future>
#include <functional>
#include <cards.h>

static cards::CardRefs card = cards::CardRefs::CLUBS2;
static std::mutex mtx;
static unsigned int drawCount = 0u; 
static unsigned int shuffleCount = 0u;

static void InitDeck(std::unique_ptr<cards::CCardDeck>&& deckPtr)
{
	std::lock_guard<std::mutex> lg(mtx);
	deckPtr->Init();
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

	using funcWrap = std::function<void(std::unique_ptr<cards::CCardDeck>&&)>;

	// Initialize the deck
	funcWrap f = std::bind(&InitDeck, std::placeholders::_1);
	f(std::move(cardDeck));

	// Shuffle on every tenth iteration
	f = std::bind(&ShuffleDeck, std::placeholders::_1);
	f(std::move(cardDeck));

	// Attempt to draw card
	f = std::bind(&DrawCard, std::placeholders::_1);
	f(std::move(cardDeck));

	std::printf("\nAttempted Draw Count: %d\nShuffle Count: %d\n", drawCount, shuffleCount);

	return 0;
}

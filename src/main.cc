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
	std::function<void(std::unique_ptr<cards::CCardDeck>&&)> cardFunc;

	// Initialize the deck
	cardFunc = InitDeck;
	cardFunc(std::move(cardDeck));

	// Shuffle on every tenth iteration
	cardFunc = ShuffleDeck;
	cardFunc(std::move(cardDeck));

	// Attempt to draw card
	cardFunc = DrawCard;
	cardFunc(std::move(cardDeck));

	std::printf("\nAttempted Draw Count: %d\nShuffle Count: %d\n", drawCount, shuffleCount);

	return 0;
}

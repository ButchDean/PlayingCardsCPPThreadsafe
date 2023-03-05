#include <iostream>
#include <cstdio>
#include <future>
#include <functional>
#include <vector>
#include <cards.h>

static cards::CardRefs card = cards::CardRefs::CLUBS2;
static std::mutex mtx;
static unsigned int drawCount = 0u; 
static unsigned int shuffleCount = 0u;

int main() {
	using funcWrap = std::function<void(std::unique_ptr<cards::CCardDeck>&&)>;

	const std::vector<funcWrap> fw = {
		// Initialize deck
		std::bind([](std::unique_ptr<cards::CCardDeck>&& deckPtr) {
			std::lock_guard<std::mutex> lg(mtx);
			deckPtr->Init();
		}, std::placeholders::_1),
		// Shuffle deck
		std::bind([](std::unique_ptr<cards::CCardDeck>&& deckPtr) {
			std::lock_guard<std::mutex> lg(mtx);
			deckPtr->Shuffle();
			shuffleCount++;
		}, std::placeholders::_1),
		// Draw card
		std::bind([](std::unique_ptr<cards::CCardDeck>&& deckPtr) {
			if(card != cards::CardRefs::EMPTY_DECK)
			{
				std::lock_guard<std::mutex> lg(mtx);
				card = std::move(deckPtr->Draw());
				drawCount++;

				std::printf("Dealt card: %s\n", deckPtr->CardToStr(card).c_str());
				std::printf("With value: %d\n", deckPtr->CardValue(card));
			}
		}, std::placeholders::_1)
	};

	auto cardDeck = std::make_unique<cards::CCardDeck>();

	// Initialize the deck
	fw[0](std::move(cardDeck));

	// Shuffle the deck
	fw[1](std::move(cardDeck));

	// Attempt to draw card
	fw[2](std::move(cardDeck));

	std::printf("\nAttempted Draw Count: %d\nShuffle Count: %d\n", drawCount, shuffleCount);

	return 0;
}

#include <iostream>
#include <cstdio>
#include <thread>
#include <functional>
#include <vector>
#include <cards.h>

static cards::CardRefs card = cards::CardRefs::CLUBS2;
static std::mutex mtx;
static unsigned int drawCount = 0u; 
static unsigned int shuffleCount = 0u;

int main() {
	using funcWrap = std::function<void(std::unique_ptr<cards::CCardDeck>&)>;

	const std::vector<funcWrap> fw = {
		// Initialize deck [0]
		std::bind([](std::unique_ptr<cards::CCardDeck>& deckPtr) {
			std::lock_guard<std::mutex> lg(mtx);
			deckPtr->Init();
		}, std::placeholders::_1),
		// Shuffle deck [1]
		std::bind([](std::unique_ptr<cards::CCardDeck>& deckPtr) {
			std::lock_guard<std::mutex> lg(mtx);
			deckPtr->Shuffle();
			shuffleCount++;
		}, std::placeholders::_1),
		// Draw card [2]
		std::bind([](std::unique_ptr<cards::CCardDeck>& deckPtr) {
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

	// Events:
	// 0 -> Initialize deck
	// 1 -> Shuffle deck
	// 2 -> Draw card
	std::vector<int> events = {0, 1, 2, 2, 2, 2, 1, 2, 2, 0, 2, 2, 2, 1, 2, 2};

	for(auto i : events) {
		i = i % 3; // Ensure operations fall in range
		std::thread e(fw[i], std::ref(cardDeck));

		if(i == 3)
			e.detach();
		else
			e.join();
	}

	std::printf("\nAttempted Draw Count: %d\nShuffle Count: %d\n", drawCount, shuffleCount);

	return 0;
}

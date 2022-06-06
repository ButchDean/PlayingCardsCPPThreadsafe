#include <iostream>
#include <cstdio>
#include <cards.h>
#include <functional.h>

extern unsigned int drawCount; 
extern unsigned int shuffleCount;

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
		// Shuffle on every tenth iteration
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

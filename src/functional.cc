#include <cards.h>
#include <functional.h>

static cards::CardRefs card;
static std::mutex mtx;
unsigned int drawCount = 0, shuffleCount = 0;

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
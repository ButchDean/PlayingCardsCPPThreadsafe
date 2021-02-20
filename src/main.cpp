#include <cstdio>
#include <memory>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <cards.h>

static cards::CardRefs card;
static std::mutex mtx;
static unsigned int drawCount = 0, shuffleCount = 0;

void InitDeck(std::unique_ptr<cards::CCardDeck>& deckPtr)
{
	mtx.lock();
	deckPtr->Init();
	deckPtr->Shuffle();
	shuffleCount++;
	mtx.unlock();
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
	mtx.lock();
	deckPtr->Shuffle();
	shuffleCount++;
	mtx.unlock();
}


int main()
{
	boost::asio::thread_pool threads(4);

	std::unique_ptr<cards::CCardDeck> cardDeck(new cards::CCardDeck);

	for(unsigned int idx = 0; idx < 60; idx++)
	{
		if(idx == 0)
			boost::asio::post(threads, [&cardDeck, idx](){ InitDeck(cardDeck); });

		if(idx % 10 == 0)
			boost::asio::post(threads, [&cardDeck, idx](){ ShuffleDeck(cardDeck); });
		else
			boost::asio::post(threads, [&cardDeck, idx](){ DrawCard(cardDeck); });
	}

	threads.join();

	std::printf("\nAttempted Draw Count: %d\nShuffle Count: %d\n", drawCount, shuffleCount);

	return 0;
}

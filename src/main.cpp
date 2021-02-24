#include <cstdio>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <cards.h>

static cards::CardRefs card;
static std::mutex mtx;
static unsigned int drawCount = 0, shuffleCount = 0;

// Unit Test
static std::vector<cards::CardRefs> drawnCards;

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
		if(card != cards::EMPTY_DECK)
			drawnCards.push_back(card);		// Record card drawn
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

	drawnCards.clear();

	for(unsigned int idx = 0; idx < 100; idx++)
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

	std::printf("Total cards drawn: %zu\n", drawnCards.size());

	for(auto c : drawnCards)
	{
		std::printf("%s ", cardDeck->CardToStr(c).c_str());
	}

	return 0;
}

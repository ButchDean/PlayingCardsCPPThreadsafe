#include <cstdio>
#include <chrono>
#include <random>
#include <cmath>
#include <functional>
#include <cards.h>
#include <progbar.h>

namespace cards
{
	void CCardDeck::Init()
	{
		std::puts("Initializing default sorted deck...");

		deck.clear();

		for(const auto& c : cardspecs) {
			deck.push_back(c.card);
		}

		std::printf("Deck size: %lu\n", deck.size());

		// Populate card values and other details key-value pairs.
		cardDetail.clear();
		for(auto c : cardspecs) {
			cardDetail.insert({c.card, c.cd});
		}
	}

	int CCardDeck::_GetRandomCardPos()
	{
		std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
		std::chrono::system_clock::duration periods = tp.time_since_epoch();

		// Seed 64-bit Mersenne Twister
		std::mt19937_64::result_type seed = periods.count();

		// Generate rand.
		auto deckPos = std::bind(std::uniform_int_distribution<int>(0, deck.size() - 1), std::mt19937_64(seed));

		return deckPos();
	}

	void CCardDeck::Shuffle()
	{
		// Do we need to shuffle?
		auto deckSize = deck.size();

		if(deckSize == 0)
		{
			std::puts("Deck size is empty, so there isn't anything to shuffle.");
			return;
		}
		else
		if(deckSize == 1)
		{
			std::puts("Deck only contains one card, so no need to shuffle.");
			return;
		}

		// We continue with shuffling.

		CardRefs cardValA, cardValB;

		auto randIterations = std::pow(deckSize, 3);

		for(int j = 0; j < randIterations; j++)
		{
			int posA = _GetRandomCardPos();
			cardValA = deck[posA];

			int posB = _GetRandomCardPos();
			cardValB = deck[posB];

			// Swap values
			deck[posA] = cardValB;
			deck[posB] = cardValA;

			// Update the progress bar
			const int PROG_DONE = j / randIterations * 100;
			UpdateProgress(PROG_DONE, deckSize);
		}
	}

	CardRefs CCardDeck::Draw()
	{
		if(deck.empty())
		{
			std::puts("Attempted to deal but deck is empty.");
			return CardRefs::EMPTY_DECK;
		}

		std::puts("\nDealing card...");
		CardRefs currentCard = deck[0];

		// Remove top card from deck.
		deck.pop_front();

		return currentCard;
	}

	std::string CCardDeck::CardToStr(const CardRefs card) const
	{
		auto cardSearch = cardDetail.find(card);

		if(cardSearch == cardDetail.end())
			return "Card string not found!";

		return cardSearch->second.cardStr;
	}

	int CCardDeck::CardValue(const CardRefs card) const
	{
		auto cardSearch = cardDetail.find(card);

		if(cardSearch == cardDetail.end())
		{
			std::puts("Card value not found!");
			return -1;
		}

		return cardSearch->second.cardVal;
	}
}

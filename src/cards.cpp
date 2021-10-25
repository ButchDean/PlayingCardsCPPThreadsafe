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

		for(int i = SPADES_A; i != EMPTY_DECK; i++)
		{
			deck.push_back(static_cast<CardRefs>(i));
		}

		std::printf("Deck size: %lu\n", deck.size());

		// Set up strings and values for card enums.
		cardDetail.clear();

		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES_A, {"SPADES_A", 21}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES2, {"SPADES2", 2}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES3, {"SPADES3", 3}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES4, {"SPADES4", 4}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES5, {"SPADES5", 5}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES6, {"SPADES6", 6}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES7, {"SPADES7", 7}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES8, {"SPADES8", 8}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES9, {"SPADES9", 9}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES10, {"SPADES10", 10}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES_J, {"SPADES_J", 11}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES_Q, {"SPADES_Q", 12}));
		cardDetail.insert(std::make_pair<int, CardDetail>(SPADES_K, {"SPADES_K", 13}));

		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS_A, {"CLUBS_A", 21}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS2, {"CLUBS2", 2}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS3, {"CLUBS3", 3}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS4, {"CLUBS4", 4}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS5, {"CLUBS5", 5}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS6, {"CLUBS6", 6}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS7, {"CLUBS7", 7}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS8, {"CLUBS8", 8}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS9, {"CLUBS9", 9}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS10, {"CLUBS10", 10}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS_J, {"CLUBS_J", 11}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS_Q, {"CLUBS_Q", 12}));
		cardDetail.insert(std::make_pair<int, CardDetail>(CLUBS_K, {"CLUBS_K", 13}));

		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS_A, {"HEARTS_A", 21}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS2, {"HEARTS2", 2}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS3, {"HEARTS3", 3}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS4, {"HEARTS4", 4}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS5, {"HEARTS5", 5}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS6, {"HEARTS6", 6}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS7, {"HEARTS7", 7}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS8, {"HEARTS8", 8}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS9, {"HEARTS9", 9}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS10, {"HEARTS10", 10}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS_J, {"HEARTS_J", 11}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS_Q, {"HEARTS_Q", 12}));
		cardDetail.insert(std::make_pair<int, CardDetail>(HEARTS_K, {"HEARTS_K", 13}));

		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS_A, {"DIAMONDS_A", 21}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS2, {"DIAMONDS2", 2}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS3, {"DIAMONDS3", 3}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS4, {"DIAMONDS4", 4}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS5, {"DIAMONDS5", 5}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS6, {"DIAMONDS6", 6}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS7, {"DIAMONDS7", 7}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS8, {"DIAMONDS8", 8}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS9, {"DIAMONDS9", 9}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS10, {"DIAMONDS10", 10}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS_J, {"DIAMONDS_J", 11}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS_Q, {"DIAMONDS_Q", 12}));
		cardDetail.insert(std::make_pair<int, CardDetail>(DIAMONDS_K, {"DIAMONDS_K", 13}));
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
			UpdateProgress(PROG_DONE + 1);
		}

		std::printf("\nShuffled deck size: %lu\n", deckSize);
	}

	CardRefs CCardDeck::Draw()
	{
		if(deck.empty())
		{
			std::puts("Attempted to deal but deck is empty.");
			return EMPTY_DECK;
		}

		std::puts("Dealing card...");
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

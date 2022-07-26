#ifndef _CARDS_MECHANIC_
#define _CARDS_MECHANIC_

#include <deque>
#include <unordered_map>
#include <array>
#include <string>

#include <common.h>

namespace cards
{
	enum class CardRefs { SPADES_A = 0, SPADES2, SPADES3, SPADES4, SPADES5, SPADES6, SPADES7, SPADES8, SPADES9, SPADES10, SPADES_J, SPADES_Q, SPADES_K,
			CLUBS_A, CLUBS2, CLUBS3, CLUBS4, CLUBS5, CLUBS6, CLUBS7, CLUBS8, CLUBS9, CLUBS10, CLUBS_J, CLUBS_Q, CLUBS_K,
			HEARTS_A, HEARTS2, HEARTS3, HEARTS4, HEARTS5, HEARTS6, HEARTS7, HEARTS8, HEARTS9, HEARTS10, HEARTS_J, HEARTS_Q, HEARTS_K,
			DIAMONDS_A, DIAMONDS2, DIAMONDS3, DIAMONDS4, DIAMONDS5, DIAMONDS6, DIAMONDS7, DIAMONDS8, DIAMONDS9, DIAMONDS10, DIAMONDS_J, DIAMONDS_Q, DIAMONDS_K,
			EMPTY_DECK };
			
	struct CardDetail {
	    std::string cardStr;
	    int cardVal;
	};	

	struct cardSpecs {
		CardRefs card;
		CardDetail cd;
	};
	
	class CCardDeck
	{
		public:
			CCardDeck(){
				// Set card values
				cardspecs[0] = {CardRefs::SPADES_A, {"SPADES_A", 1}};
				cardspecs[1] = {CardRefs::SPADES2, {"SPADES2", 2}};
				cardspecs[2] = {CardRefs::SPADES3, {"SPADES3", 3}};
				cardspecs[3] = {CardRefs::SPADES4, {"SPADES4", 4}};
				cardspecs[4] = {CardRefs::SPADES5, {"SPADES5", 5}};
				cardspecs[5] = {CardRefs::SPADES6, {"SPADES6", 6}};
				cardspecs[6] = {CardRefs::SPADES7, {"SPADES7", 7}};
				cardspecs[7] = {CardRefs::SPADES8, {"SPADES8", 8}};
				cardspecs[8] = {CardRefs::SPADES9, {"SPADES9", 9}};
				cardspecs[9] = {CardRefs::SPADES10, {"SPADES10", 10}};
				cardspecs[10] = {CardRefs::SPADES_J, {"SPADES_J", 11}};
				cardspecs[11] = {CardRefs::SPADES_Q, {"SPADES_Q", 12}};
				cardspecs[12] = {CardRefs::SPADES_K, {"SPADES_K", 13}};

				cardspecs[13] = {CardRefs::CLUBS_A, {"CLUBS_A", 1}};
				cardspecs[14] = {CardRefs::CLUBS2, {"CLUBS2", 2}};
				cardspecs[15] = {CardRefs::CLUBS3, {"CLUBS3", 3}};
				cardspecs[16] = {CardRefs::CLUBS4, {"CLUBS4", 4}};
				cardspecs[17] = {CardRefs::CLUBS5, {"CLUBS5", 5}};
				cardspecs[18] = {CardRefs::CLUBS6, {"CLUBS6", 6}};
				cardspecs[19] = {CardRefs::CLUBS7, {"CLUBS7", 7}};
				cardspecs[20] = {CardRefs::CLUBS8, {"CLUBS8", 8}};
				cardspecs[21] = {CardRefs::CLUBS9, {"CLUBS9", 9}};
				cardspecs[22] = {CardRefs::CLUBS10, {"CLUBS10", 10}};
				cardspecs[23] = {CardRefs::CLUBS_J, {"CLUBS_J", 11}};
				cardspecs[24] = {CardRefs::CLUBS_Q, {"CLUBS_Q", 12}};
				cardspecs[25] = {CardRefs::CLUBS_K, {"CLUBS_K", 13}};

				cardspecs[26] = {CardRefs::HEARTS_A, {"HEARTS_A", 1}};
				cardspecs[27] = {CardRefs::HEARTS2, {"HEARTS2", 2}};
				cardspecs[28] = {CardRefs::HEARTS3, {"HEARTS3", 3}};
				cardspecs[29] = {CardRefs::HEARTS4, {"HEARTS4", 4}};
				cardspecs[30] = {CardRefs::HEARTS5, {"HEARTS5", 5}};
				cardspecs[31] = {CardRefs::HEARTS6, {"HEARTS6", 6}};
				cardspecs[32] = {CardRefs::HEARTS7, {"HEARTS7", 7}};
				cardspecs[33] = {CardRefs::HEARTS8, {"HEARTS8", 8}};
				cardspecs[34] = {CardRefs::HEARTS9, {"HEARTS9", 9}};
				cardspecs[35] = {CardRefs::HEARTS10, {"HEARTS10", 10}};
				cardspecs[36] = {CardRefs::HEARTS_J, {"HEARTS_J", 11}};
				cardspecs[37] = {CardRefs::HEARTS_Q, {"HEARTS_Q", 12}};
				cardspecs[38] = {CardRefs::HEARTS_K, {"HEARTS_K", 13}};

				cardspecs[39] = {CardRefs::DIAMONDS_A, {"DIAMONDS_A", 1}};
				cardspecs[40] = {CardRefs::DIAMONDS2, {"DIAMONDS2", 2}};
				cardspecs[41] = {CardRefs::DIAMONDS3, {"DIAMONDS3", 3}};
				cardspecs[42] = {CardRefs::DIAMONDS4, {"DIAMONDS4", 4}};
				cardspecs[43] = {CardRefs::DIAMONDS5, {"DIAMONDS5", 5}};
				cardspecs[44] = {CardRefs::DIAMONDS6, {"DIAMONDS6", 6}};
				cardspecs[45] = {CardRefs::DIAMONDS7, {"DIAMONDS7", 7}};
				cardspecs[46] = {CardRefs::DIAMONDS8, {"DIAMONDS8", 8}};
				cardspecs[47] = {CardRefs::DIAMONDS9, {"DIAMONDS9", 9}};
				cardspecs[48] = {CardRefs::DIAMONDS10, {"DIAMONDS10", 10}};
				cardspecs[49] = {CardRefs::DIAMONDS_J, {"DIAMONDS_J", 11}};
				cardspecs[50] = {CardRefs::DIAMONDS_Q, {"DIAMONDS_Q", 12}};
				cardspecs[51] = {CardRefs::DIAMONDS_K, {"DIAMONDS_K", 13}};							
			}
			~CCardDeck() = default;

			CCardDeck(const CCardDeck &) = delete;
			CCardDeck(CCardDeck &&) = delete;
			CCardDeck &operator=(const CCardDeck &) = delete;
			CCardDeck &operator=(CCardDeck &&) = delete;
			
			void Init();
			void Shuffle();
			CardRefs Draw();
			std::string CardToStr(const CardRefs card) const;
			
			int CardValue(const CardRefs card) const;

			int DeckSize() {
				return deck.size();
			}
			
		private:
			std::deque<CardRefs> deck;
			std::unordered_map<CardRefs, CardDetail> cardDetail;
			std::array<cardSpecs, CARDDECKSIZE> cardspecs;
			
			int _GetRandomCardPos();	
	};
}

#endif
#ifndef _CARDS_MECHANIC_
#define _CARDS_MECHANIC_

#include <deque>
#include <unordered_map>
#include <vector>
#include <string>

namespace cards
{
	enum CardRefs { SPADES_A = 0, SPADES2, SPADES3, SPADES4, SPADES5, SPADES6, SPADES7, SPADES8, SPADES9, SPADES10, SPADES_J, SPADES_Q, SPADES_K,
			CLUBS_A, CLUBS2, CLUBS3, CLUBS4, CLUBS5, CLUBS6, CLUBS7, CLUBS8, CLUBS9, CLUBS10, CLUBS_J, CLUBS_Q, CLUBS_K,
			HEARTS_A, HEARTS2, HEARTS3, HEARTS4, HEARTS5, HEARTS6, HEARTS7, HEARTS8, HEARTS9, HEARTS10, HEARTS_J, HEARTS_Q, HEARTS_K,
			DIAMONDS_A, DIAMONDS2, DIAMONDS3, DIAMONDS4, DIAMONDS5, DIAMONDS6, DIAMONDS7, DIAMONDS8, DIAMONDS9, DIAMONDS10, DIAMONDS_J, DIAMONDS_Q, DIAMONDS_K,
			EMPTY_DECK };
			
	struct CardDetail {
	    std::string cardStr;
	    int cardVal;
	};	

	struct cardSpecs {
		int card;
		CardDetail cd;
	};
	
	class CCardDeck
	{
		public:
			CCardDeck(){
				// Set card values
				cardspecs.push_back({SPADES_A, {"SPADES_A", 1}});
				cardspecs.push_back({SPADES2, {"SPADES2", 2}});
				cardspecs.push_back({SPADES3, {"SPADES3", 3}});
				cardspecs.push_back({SPADES4, {"SPADES4", 4}});
				cardspecs.push_back({SPADES5, {"SPADES5", 5}});
				cardspecs.push_back({SPADES6, {"SPADES6", 6}});
				cardspecs.push_back({SPADES7, {"SPADES7", 7}});
				cardspecs.push_back({SPADES8, {"SPADES8", 8}});
				cardspecs.push_back({SPADES9, {"SPADES9", 9}});
				cardspecs.push_back({SPADES10, {"SPADES10", 10}});
				cardspecs.push_back({SPADES_J, {"SPADES_J", 11}});
				cardspecs.push_back({SPADES_Q, {"SPADES_Q", 12}});
				cardspecs.push_back({SPADES_K, {"SPADES_K", 13}});

				cardspecs.push_back({CLUBS_A, {"CLUBS_A", 1}});
				cardspecs.push_back({CLUBS2, {"CLUBS2", 2}});
				cardspecs.push_back({CLUBS3, {"CLUBS3", 3}});
				cardspecs.push_back({CLUBS4, {"CLUBS4", 4}});
				cardspecs.push_back({CLUBS5, {"CLUBS5", 5}});
				cardspecs.push_back({CLUBS6, {"CLUBS6", 6}});
				cardspecs.push_back({CLUBS7, {"CLUBS7", 7}});
				cardspecs.push_back({CLUBS8, {"CLUBS8", 8}});
				cardspecs.push_back({CLUBS9, {"CLUBS9", 9}});
				cardspecs.push_back({CLUBS10, {"CLUBS10", 10}});
				cardspecs.push_back({CLUBS_J, {"CLUBS_J", 11}});
				cardspecs.push_back({CLUBS_Q, {"CLUBS_Q", 12}});
				cardspecs.push_back({CLUBS_K, {"CLUBS_K", 13}});

				cardspecs.push_back({HEARTS_A, {"HEARTS_A", 1}});
				cardspecs.push_back({HEARTS2, {"HEARTS2", 2}});
				cardspecs.push_back({HEARTS3, {"HEARTS3", 3}});
				cardspecs.push_back({HEARTS4, {"HEARTS4", 4}});
				cardspecs.push_back({HEARTS5, {"HEARTS5", 5}});
				cardspecs.push_back({HEARTS6, {"HEARTS6", 6}});
				cardspecs.push_back({HEARTS7, {"HEARTS7", 7}});
				cardspecs.push_back({HEARTS8, {"HEARTS8", 8}});
				cardspecs.push_back({HEARTS9, {"HEARTS9", 9}});
				cardspecs.push_back({HEARTS10, {"HEARTS10", 10}});
				cardspecs.push_back({HEARTS_J, {"HEARTS_J", 11}});
				cardspecs.push_back({HEARTS_Q, {"HEARTS_Q", 12}});
				cardspecs.push_back({HEARTS_K, {"HEARTS_K", 13}});

				cardspecs.push_back({DIAMONDS_A, {"DIAMONDS_A", 1}});
				cardspecs.push_back({DIAMONDS2, {"DIAMONDS2", 2}});
				cardspecs.push_back({DIAMONDS3, {"DIAMONDS3", 3}});
				cardspecs.push_back({DIAMONDS4, {"DIAMONDS4", 4}});
				cardspecs.push_back({DIAMONDS5, {"DIAMONDS5", 5}});
				cardspecs.push_back({DIAMONDS6, {"DIAMONDS6", 6}});
				cardspecs.push_back({DIAMONDS7, {"DIAMONDS7", 7}});
				cardspecs.push_back({DIAMONDS8, {"DIAMONDS8", 8}});
				cardspecs.push_back({DIAMONDS9, {"DIAMONDS9", 9}});
				cardspecs.push_back({DIAMONDS10, {"DIAMONDS10", 10}});
				cardspecs.push_back({DIAMONDS_J, {"DIAMONDS_J", 11}});
				cardspecs.push_back({DIAMONDS_Q, {"DIAMONDS_Q", 12}});
				cardspecs.push_back({DIAMONDS_K, {"DIAMONDS_K", 13}});							
			}
			~CCardDeck(){}
			
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
			std::unordered_map<int, CardDetail> cardDetail;
			std::vector<cardSpecs> cardspecs;
			
			int _GetRandomCardPos();	
	};
}

#endif
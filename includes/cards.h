#ifndef _CARDS_MECHANIC_
#define _CARDS_MECHANIC_

#include <deque>
#include <unordered_map>
#include <vector>
#include <string>

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
				cardspecs.push_back({CardRefs::SPADES_A, {"SPADES_A", 1}});
				cardspecs.push_back({CardRefs::SPADES2, {"SPADES2", 2}});
				cardspecs.push_back({CardRefs::SPADES3, {"SPADES3", 3}});
				cardspecs.push_back({CardRefs::SPADES4, {"SPADES4", 4}});
				cardspecs.push_back({CardRefs::SPADES5, {"SPADES5", 5}});
				cardspecs.push_back({CardRefs::SPADES6, {"SPADES6", 6}});
				cardspecs.push_back({CardRefs::SPADES7, {"SPADES7", 7}});
				cardspecs.push_back({CardRefs::SPADES8, {"SPADES8", 8}});
				cardspecs.push_back({CardRefs::SPADES9, {"SPADES9", 9}});
				cardspecs.push_back({CardRefs::SPADES10, {"SPADES10", 10}});
				cardspecs.push_back({CardRefs::SPADES_J, {"SPADES_J", 11}});
				cardspecs.push_back({CardRefs::SPADES_Q, {"SPADES_Q", 12}});
				cardspecs.push_back({CardRefs::SPADES_K, {"SPADES_K", 13}});

				cardspecs.push_back({CardRefs::CLUBS_A, {"CLUBS_A", 1}});
				cardspecs.push_back({CardRefs::CLUBS2, {"CLUBS2", 2}});
				cardspecs.push_back({CardRefs::CLUBS3, {"CLUBS3", 3}});
				cardspecs.push_back({CardRefs::CLUBS4, {"CLUBS4", 4}});
				cardspecs.push_back({CardRefs::CLUBS5, {"CLUBS5", 5}});
				cardspecs.push_back({CardRefs::CLUBS6, {"CLUBS6", 6}});
				cardspecs.push_back({CardRefs::CLUBS7, {"CLUBS7", 7}});
				cardspecs.push_back({CardRefs::CLUBS8, {"CLUBS8", 8}});
				cardspecs.push_back({CardRefs::CLUBS9, {"CLUBS9", 9}});
				cardspecs.push_back({CardRefs::CLUBS10, {"CLUBS10", 10}});
				cardspecs.push_back({CardRefs::CLUBS_J, {"CLUBS_J", 11}});
				cardspecs.push_back({CardRefs::CLUBS_Q, {"CLUBS_Q", 12}});
				cardspecs.push_back({CardRefs::CLUBS_K, {"CLUBS_K", 13}});

				cardspecs.push_back({CardRefs::HEARTS_A, {"HEARTS_A", 1}});
				cardspecs.push_back({CardRefs::HEARTS2, {"HEARTS2", 2}});
				cardspecs.push_back({CardRefs::HEARTS3, {"HEARTS3", 3}});
				cardspecs.push_back({CardRefs::HEARTS4, {"HEARTS4", 4}});
				cardspecs.push_back({CardRefs::HEARTS5, {"HEARTS5", 5}});
				cardspecs.push_back({CardRefs::HEARTS6, {"HEARTS6", 6}});
				cardspecs.push_back({CardRefs::HEARTS7, {"HEARTS7", 7}});
				cardspecs.push_back({CardRefs::HEARTS8, {"HEARTS8", 8}});
				cardspecs.push_back({CardRefs::HEARTS9, {"HEARTS9", 9}});
				cardspecs.push_back({CardRefs::HEARTS10, {"HEARTS10", 10}});
				cardspecs.push_back({CardRefs::HEARTS_J, {"HEARTS_J", 11}});
				cardspecs.push_back({CardRefs::HEARTS_Q, {"HEARTS_Q", 12}});
				cardspecs.push_back({CardRefs::HEARTS_K, {"HEARTS_K", 13}});

				cardspecs.push_back({CardRefs::DIAMONDS_A, {"DIAMONDS_A", 1}});
				cardspecs.push_back({CardRefs::DIAMONDS2, {"DIAMONDS2", 2}});
				cardspecs.push_back({CardRefs::DIAMONDS3, {"DIAMONDS3", 3}});
				cardspecs.push_back({CardRefs::DIAMONDS4, {"DIAMONDS4", 4}});
				cardspecs.push_back({CardRefs::DIAMONDS5, {"DIAMONDS5", 5}});
				cardspecs.push_back({CardRefs::DIAMONDS6, {"DIAMONDS6", 6}});
				cardspecs.push_back({CardRefs::DIAMONDS7, {"DIAMONDS7", 7}});
				cardspecs.push_back({CardRefs::DIAMONDS8, {"DIAMONDS8", 8}});
				cardspecs.push_back({CardRefs::DIAMONDS9, {"DIAMONDS9", 9}});
				cardspecs.push_back({CardRefs::DIAMONDS10, {"DIAMONDS10", 10}});
				cardspecs.push_back({CardRefs::DIAMONDS_J, {"DIAMONDS_J", 11}});
				cardspecs.push_back({CardRefs::DIAMONDS_Q, {"DIAMONDS_Q", 12}});
				cardspecs.push_back({CardRefs::DIAMONDS_K, {"DIAMONDS_K", 13}});							
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
			std::vector<cardSpecs> cardspecs;
			
			int _GetRandomCardPos();	
	};
}

#endif
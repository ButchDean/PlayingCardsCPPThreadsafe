#ifndef _CARDS_MECHANIC_
#define _CARDS_MECHANIC_

#include <deque>
#include <unordered_map>
#include <string>

namespace cards
{
	enum CardRefs { SPADES_A = 0, SPADES2, SPADES3, SPADES4, SPADES5, SPADES6, SPADES7, SPADES8, SPADES9, SPADES10, SPADES_J, SPADES_Q, SPADES_K,
			CLUBS_A, CLUBS2, CLUBS3, CLUBS4, CLUBS5, CLUBS6, CLUBS7, CLUBS8, CLUBS9, CLUBS10, CLUBS_J, CLUBS_Q, CLUBS_K,
			HEARTS_A, HEARTS2, HEARTS3, HEARTS4, HEARTS5, HEARTS6, HEARTS7, HEARTS8, HEARTS9, HEARTS10, HEARTS_J, HEARTS_Q, HEARTS_K,
			DIAMONDS_A, DIAMONDS2, DIAMONDS3, DIAMONDS4, DIAMONDS5, DIAMONDS6, DIAMONDS7, DIAMONDS8, DIAMONDS9, DIAMONDS10, DIAMONDS_J, DIAMONDS_Q, DIAMONDS_K,
			EMPTY_DECK };
			
	struct CardDetail
	{
	    std::string cardStr;
	    int cardVal;
	};	
	
	class CCardDeck
	{
		public:
			CCardDeck(){}
			~CCardDeck(){}
			
			void Init();
			void Shuffle();
			CardRefs Draw();
			std::string CardToStr(const CardRefs card) const;
			
			int CardValue(const CardRefs card) const;
			
		private:
			std::deque<CardRefs> deck;
			std::unordered_map<int, CardDetail> cardDetail;
			
			int _GetRandomCardPos();	
	};
}

#endif
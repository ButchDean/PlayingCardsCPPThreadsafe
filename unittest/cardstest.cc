#include <gtest/gtest.h>
#include <progbar.h>
#include <cards.h>
#include <functional.h>

#define CARDDECKSIZE 52

namespace cards {

TEST(PlayingCardsTest, InitDeckSize) {
    CCardDeck cardDeck;

    cardDeck.Init();

    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE);
}

TEST(PlayingCardsTest, Draw1CardDeckSize) {
    CCardDeck cardDeck;

    cardDeck.Init();

    cardDeck.Draw();
    
    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE - 1);
}

}
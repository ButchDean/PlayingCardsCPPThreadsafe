#include <gtest/gtest.h>
#include <progbar.h>
#include <cards.h>
#include <functional.h>

#include <vector>

#define CARDDECKSIZE 52

namespace cards {

TEST(PlayingCardsTest, InitDeckSize) {
    CCardDeck cardDeck;

    cardDeck.Init();

    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE);
}

TEST(PlayingCardsTest, DrawSingleCardDeckSize) {
    CCardDeck cardDeck;

    cardDeck.Init();

    cardDeck.Draw();
    
    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE - 1);
}

TEST(PlayingCardsTest, DrawToEmptyDeckWithZeroCardsRemaining) {
    CCardDeck cardDeck;

    cardDeck.Init();

    CardRefs cr = cardDeck.Draw();

    while(cr != CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
    }

    EXPECT_EQ(cardDeck.DeckSize(), 0);
}

TEST(PlayingCardsTest, CheckEachCardUniqueUnshuffled) {
    CCardDeck cardDeck;

    cardDeck.Init();

    CardRefs cr = CardRefs::SPADES_A;
    std::vector<CardRefs> cardVec;
    int same = 0;

    while(cr != CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
        cardVec.push_back(cr);
    }

    for(int i = 0; i < cardVec.size() - 1; i++) {
        for(int j = 0; j < cardVec.size() - 1; j++) {
            if(cardVec[i] == cardVec[j]) {
                same++;
            }
        }
    }

    EXPECT_EQ(same, CARDDECKSIZE);
}

TEST(PlayingCardsTest, CheckEachCardUniqueShuffled) {
    CCardDeck cardDeck;

    cardDeck.Init();

    CardRefs cr = CardRefs::SPADES_A;
    std::vector<CardRefs> cardVec;
    int same = 0;

    cardDeck.Shuffle();

    while(cr != CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
        cardVec.push_back(cr);
    }

    for(int i = 0; i < cardVec.size() - 1; i++) {
        for(int j = 0; j < cardVec.size() - 1; j++) {
            if(cardVec[i] == cardVec[j]) {
                same++;
            }
        }
    }

    EXPECT_EQ(same, CARDDECKSIZE);
}

TEST(PlayingCardsTest, CanReinitializeEmptyDeck) {
    CCardDeck cardDeck;

    cardDeck.Init();

    CardRefs cr = cardDeck.Draw();

    while(cr != CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
    }

    cardDeck.Init();

    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE);    
}

TEST(PlayingCardsTest, CanDoubleInitializeDeckToRemainSameSize) {
    CCardDeck cardDeck;

    cardDeck.Init();
    cardDeck.Init();

    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE);   
}

TEST(PlayingCardsTest, CanDoubleInitializeDeckToRemainSameSizeEachCardUnique) {
    CCardDeck cardDeck;

    cardDeck.Init();
    cardDeck.Init();

    CardRefs cr = CardRefs::SPADES_A;
    std::vector<CardRefs> cardVec;
    int same = 0;

    while(cr != CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
        cardVec.push_back(cr);
    }

    for(int i = 0; i < cardVec.size() - 1; i++) {
        for(int j = 0; j < cardVec.size() - 1; j++) {
            if(cardVec[i] == cardVec[j]) {
                same++;
            }
        }
    }

    EXPECT_EQ(same, CARDDECKSIZE);    
}

}
#ifndef _FUNCTIONAL_H_
#define _FUNCTIONAL_H_

#include <thread>
#include <mutex>
#include <future>
#include <memory>

void InitDeck(std::unique_ptr<cards::CCardDeck>& deckPtr);
void DrawCard(std::unique_ptr<cards::CCardDeck>& deckPtr);
void ShuffleDeck(std::unique_ptr<cards::CCardDeck>& deckPtr);

#endif
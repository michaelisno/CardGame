#pragma once
#include <vector>
#include "Card.h"
#include "Player.h"

using namespace std;

class Game
{
private:
	vector<Card> deck;
	Player player;
	Player dealer;

	void InitialiseDeck(bool isBlackJack);
	void ShuffleDeck();
	Card DealCard();

	void War();
	void BlackJack();

public:
	void Play();

};
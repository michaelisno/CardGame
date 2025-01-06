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

	void InitialiseDeck();
	void ShuffleDeck();
	Card DealCard();

public:
	Game();

	void Play();

};
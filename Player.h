#pragma once
#include <vector>
#include "Card.h"

class Player
{
public:
	std::vector<Card> hand;

	void ReceiveCard(const Card& card);
	void ShowHand();
	int CalculateHandValue();

};
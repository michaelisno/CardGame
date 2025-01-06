#include <iostream>
#include "Player.h"

using namespace std;

void Player::ReceiveCard(const Card& card)
{
	hand.push_back(card);
}

void Player::ShowHand()
{
	for (Card card : hand)
	{
		cout << card.GetRank() << " of " << card.GetSuit() << ", ";
	}

	cout << endl;
}

int Player::CalculateHandValue()
{
	int value = 0;
	int aceCount = 0;

	for (Card& card : hand)
	{
		value += card.GetValue();
		
		if (card.GetRank() == "Ace")
			aceCount++;
	}

	while (value > 21 && aceCount > 0)
	{
		value -= 10;
		aceCount--;
	}

	return value;
}
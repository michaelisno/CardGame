#include <iostream>
#include <algorithm>
#include "Game.h"

Game::Game()
{
	InitialiseDeck();
	ShuffleDeck();
}

void Game::InitialiseDeck()
{
	string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
	int values[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

	for (string& suit : suits)
	{
		for (int i = 0; i < 13; i++)
		{
			deck.push_back(Card(suit, ranks[i], values[i]));
		}
	}
}

void Game::ShuffleDeck()
{
	srand(time(0));
	random_shuffle(deck.begin(), deck.end());
}

Card Game::DealCard()
{
	Card card = deck.back();
	deck.pop_back();
	return card;
}

void Game::Play()
{
	player.ReceiveCard(DealCard());
	dealer.ReceiveCard(DealCard());
	player.ReceiveCard(DealCard());
	dealer.ReceiveCard(DealCard());

	cout << "Player's Hand: ";
	player.ShowHand();
	
	cout << "Dealer's visible card: " << dealer.hand[0].GetRank() << " of " << dealer.hand[0].GetSuit() << endl;

	while (true)
	{
		cout << "Player's current hand value: " << player.CalculateHandValue() << endl;
		if (player.CalculateHandValue() > 21)
		{
			cout << "Player Busts! Dealer Wins." << endl;
			return;
		}

		cout << "Hit or Stand? (h/s): ";

		char choice;
		cin >> choice;

		if (choice == 'h')
		{
			player.ReceiveCard(DealCard());
			cout << "Player's Hand: ";
			player.ShowHand();
		}
		else
		{
			break;
		}
	}

	cout << "Dealer's Hand: ";
	dealer.ShowHand();

	while (dealer.CalculateHandValue() < 17)
	{
		dealer.ReceiveCard(DealCard());
		cout << "Dealer draws a card." << endl;
		cout << "Dealer's Hand: ";
		dealer.ShowHand();
	}

	if (dealer.CalculateHandValue() > 21)
	{
		cout << "Dealer Busts! Player Wins." << endl;
		return;
	}

	int playerValue = player.CalculateHandValue();
	int dealerValue = dealer.CalculateHandValue();

	cout << "Player's Hand Value: " << playerValue << endl;
	cout << "Dealer's Hand Value: " << dealerValue << endl;


	if (playerValue > dealerValue)
	{
		cout << "Player Wins!" << endl;
	}
	else if (playerValue < dealerValue)
	{
		cout << "Dealer Wins!" << endl;
	}
	else
	{
		cout << "Its a Tie!" << endl;
	}
}
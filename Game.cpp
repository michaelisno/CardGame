#include <iostream>
#include <algorithm>
#include "Game.h"

int main()
{
	cout << "Welcome to the Card Game!" << endl;

	Game game;
	game.Play();

	return 0;
}

void Game::InitialiseDeck(bool isBlackJack)
{
	string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
	int values[13];

	if (isBlackJack) 
	{
		int temp[]  = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

	}
	else
	{
		int temp[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1 };
		copy(begin(temp), end(temp), values);
	}

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
	cout << "Do you want to play War (w) or Black Jack (b)?" << endl << ">>";

	char option;
	cin >> option;

	if (option == 'w')
	{
		War();
	}
	else if (option == 'b')
	{
		BlackJack();
	}
	else
	{
		cout << "Error: Please enter a valid option." << endl;
		Play();
	}
}

void Game::War()
{
	cout << endl << "Welcome to War!" << endl << endl;

	InitialiseDeck(false);
	ShuffleDeck();

	for (int i = 0; i < 26; i++)
		player.ReceiveCard(DealCard());

	for (int i = 0; i < 26; i++)
		dealer.ReceiveCard(DealCard());

	while (true)
	{
		if (player.hand.empty())
		{
			cout << "Player has no Cards left, Dealer Wins!" << endl;
			return;
		}

		if (dealer.hand.empty())
		{
			cout << "Dealer has no Cards left, Player Wins!" << endl;
			return;
		}

		cout << "Enter any character to start the round." << endl;
		char a;
		cin >> a;


		cout << "---------------------" << endl;

		cout << "Player has: " << player.hand.size() << " cards." << endl << "Dealer has: " << dealer.hand.size() << " cards." << endl << endl;

		Card playerTopCard = player.RemoveTopCard();
		Card dealerTopCard = dealer.RemoveTopCard();

		cout << "Player's drawn card: " << playerTopCard.GetName() << endl;
		cout << "Dealer's drawn card: " << dealerTopCard.GetName() << endl;

		if (playerTopCard.GetValue() == dealerTopCard.GetValue())
		{
			cout << "Players Cards are the same value, a war has begun!" << endl << "Enter any character to draw your four cards." << endl;

			char a;
			cin >> a;

			bool isWarOver = false;

			vector<Card> cardsInPlay;

			cardsInPlay.push_back(playerTopCard);
			cardsInPlay.push_back(dealerTopCard);

			while (!isWarOver)
			{
				if (player.hand.size() <= 3)
				{
					cout << "Player doesn't have enough cards for War, dealer Wins!" << endl;
					return;
				}

				if (dealer.hand.size() <= 3)
				{
					cout << "Dealer doesn't have enough cards for War, player Wins!" << endl;
					return;
				}

				for (int i = 0; i < 3; i++)
				{
					cardsInPlay.push_back(player.hand[0]);
					cardsInPlay.push_back(dealer.hand[0]);

					player.RemoveTopCard();
					dealer.RemoveTopCard();
				}

				Card playerFourthCard = player.RemoveTopCard();
				Card dealerFourthCard = dealer.RemoveTopCard();

				cout << "Player's Fourth Face Up Card: " << playerFourthCard.GetName() << endl;
				cout << "Dealers's Fourth Face Up Card: " << dealerFourthCard.GetName() << endl;

				if (playerFourthCard.GetValue() == dealerFourthCard.GetValue())
				{
					cout << "Players Cards are the same value, war-ing (?) again..." << endl;

					cardsInPlay.push_back(playerFourthCard);
					cardsInPlay.push_back(dealerFourthCard);
					
					cout << "Enter any character to draw another four cards." << endl;
					char a;
					cin >> a;

					break;
				}
				else if (playerFourthCard.GetValue() > dealerFourthCard.GetValue())
				{
					cout << "Player's Card has a higher value. Player Wins Round and all cards in play!" << endl;
					player.ReceiveCard(playerFourthCard);
					player.ReceiveCard(dealerFourthCard);

					for (Card card : cardsInPlay)
					{
						player.ReceiveCard(card);
					}

					isWarOver = true;
				}
				else
				{
					cout << "Dealers's Card has a higher value. Dealer Wins Round and all cards in play!" << endl;
					dealer.ReceiveCard(playerFourthCard);
					dealer.ReceiveCard(dealerFourthCard);

					for (Card card : cardsInPlay)
					{
						dealer.ReceiveCard(card);
					}

					isWarOver = true;
				}
			}

			cardsInPlay.clear();
		}
		else if (playerTopCard.GetValue() > dealerTopCard.GetValue())
		{
			cout << "Player's Card has a higher value, so player wins round." << endl << "---------------------" << endl << endl;

			player.ReceiveCard(playerTopCard);
			player.ReceiveCard(dealerTopCard);
		}
		else
		{
			cout << "Dealers's card has a higher value, so dealer wins the round." << endl << "---------------------" << endl << endl;

			dealer.ReceiveCard(playerTopCard);
			dealer.ReceiveCard(dealerTopCard);
		}
	}
}

void Game::BlackJack()
{
	InitialiseDeck(true);
	ShuffleDeck();

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
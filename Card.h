#pragma once
#include <string>

class Card
{
private:
	std::string m_suit;
	std::string m_rank;
	int m_value;

public:
	Card(std::string suit, std::string rank, int value) { m_suit = suit; m_rank = rank; m_value = value; }

	std::string GetSuit() const { return m_suit; }
	std::string GetRank() const { return m_rank; }
	std::string GetName() const { return m_rank + " of " + m_suit; }
	int GetValue() const { return m_value; }
};
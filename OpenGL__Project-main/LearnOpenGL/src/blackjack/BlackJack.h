#pragma once
#include <vector>
#include <string>
#include <random>

enum GameResult
{
	DRAW,
	BUST,
	WIN,
	BLACKJACK,
};
enum CardType
{
	CLUB = 0,
	DIAMOND,
	HEART,
	SPADE,
	HIDDEN,
};
enum CardValue
{
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6,
	SEVEN = 7,
	EIGHT = 8,
	NINE = 9,
	TEN = 10,
	JACK = 11,
	QUEEN = 12,
	KING = 13,
	ACE = 14,
	HIDDEN = 99
};
struct Card
{
	CardType type;
	CardValue value;
	int Value01; // Possible value needed for aces
	int Value02;
};
typedef std::vector<Card> Hand;

namespace CardUtil
{
	inline int AddCardValue(Card)
	{

	}
	inline int GetHandValue(Hand const& hand)
	{
		int high = 0;
		int low = 0;

		for (auto it : hand)
		{
			low += it.Value01;
			high += it.Value02;
		}

		if (high > 21)
			return low;
		return (low < high) ? high : low;
	}
	inline std::string BuildCardRscName(Card card)
	{
		std::string fileName;
		switch (card.type)
		{
		case CardType::CLUB:
			fileName.append("club");
			break;
		case CardType::DIAMOND:
			fileName.append("diamond");
			break;
		case CardType::HEART:			
			fileName.append("heart");
			break;
		case CardType::SPADE:
			fileName.append("spade");
			break;
		case CardType::HIDDEN:
			return "hidden.png";
		}
		switch (card.value)
		{
		case TWO:
			fileName.append("_2.png");
			break;
		case THREE:
			fileName.append("_3.png");
			break;
		case FOUR:
			fileName.append("_4.png");
			break;
		case FIVE:
			fileName.append("_5.png");
			break;
		case SIX:
			fileName.append("_6.png");
			break;
		case SEVEN:
			fileName.append("_7.png");
			break;
		case EIGHT:
			fileName.append("_8.png");
			break;
		case NINE:
			fileName.append("_9.png");
			break;
		case TEN:
			fileName.append("_10.png");
			break;
		case JACK:
			fileName.append("_jack.png");
			break;
		case QUEEN:
			fileName.append("_queen.png");
			break;
		case KING:
			fileName.append("_king.png");
			break;
		case ACE:
			fileName.append("_ace.png");
			break;
		default:
			break;
		}

		return fileName;
	};
}
class BlackJack
{
private:
	Hand dealerHand;
	Hand playerHand;
	int wins = 0;
	int losses = 0;
private:
	int GenRandomNumber(int min, int max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(min, max);
		return distribution(gen);
	}
	Card DrawCard(bool dealer); // true = dealer
	int GetHandValue(bool dealer) const;
	bool IsBust();
public:
	void StartNewRound(); // Empties both hands
	std::string Hit(bool dealer); // Return name of the card (file)
};
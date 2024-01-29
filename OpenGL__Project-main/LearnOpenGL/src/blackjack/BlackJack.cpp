#include "BlackJack.h"
#include <string>
Card BlackJack::DrawCard(bool dealer)
{
	// Generate random numbers for card
	Card card;
	card.type = (CardType)GenRandomNumber(0, 3);
	card.value = (CardValue)GenRandomNumber(1, 14);
	
}
int BlackJack::GetHandValue(bool dealer) const
{
	return dealer ? CardUtil::GetHandValue(dealerHand) : CardUtil::GetHandValue(playerHand);
}
bool BlackJack::IsBust()
{
	return GetHandValue(false) > 21;
}

void BlackJack::StartNewRound()
{
	dealerHand.clear();
	playerHand.clear();
}

std::string BlackJack::Hit(bool dealer) // Return name of the card
{
	Card newCard = DrawCard(dealer); // Draw card for player
	dealer ? dealerHand.push_back(newCard) : playerHand.push_back(newCard);
	return "";
}

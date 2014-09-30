#include <iostream>
#include <vector>
#include <functional>
#include "GameCards.h"

GameCard::GameCard( GameCardType const type, EffectType const effect ) :
	m_type(type), m_effect(effect)
{
	//only need init. list
}

GameCard* GameCard::CreateCard()
{
	new GameCard(Knight, NONE);
}
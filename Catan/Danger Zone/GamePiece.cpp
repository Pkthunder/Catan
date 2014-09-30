#include <iostream>
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "GameCards.h"
#include "GamePiece.h"

//////////////////////////////////////////////////////////////////////////////
//Statics
Cost const GamePiece::m_price[4] = { Cost( 1, 0, 0, 0, 1 ), //Road
								Cost( 1, 1, 1, 0, 1 ), //Settlement
								Cost( 0, 0, 2, 3, 0 ), //City
								Cost( 0, 1, 1, 1, 0 ) }; //Card

GamePiece::GamePiece() : m_type(Card), 
	m_coords(sf::Vector2f(0.0f,0.0f)) {} //Default

GamePiece::GamePiece( GamePieceType const type, sf::Vector2f const coords ) :
	m_type(type), m_coords(coords)
{
	//only need init. list
}

GamePieceType GamePiece::getPieceType() const
{
	return m_type;
}

sf::Vector2f GamePiece::getScreenCoords() const
{
	return m_coords;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

PieceCard::PieceCard() : m_card(GameCard::CreateCard())
{
	//only need init. list
}

GameCardType PieceCard::getCardType() const
{
	return m_card->m_type;
}

GameCard* PieceCard::getCard() const
{
	return m_card;
}

bool PieceCard::isEffect() const
{
	return m_card->m_effect == NONE;
}

void PieceCard::AssignFunc()
{
	return; //deal with later
}
#ifndef GAMEPIECE_H_
#define GAMEPIECE_H_

#include <SFML\Graphics.hpp>
#include "GameCards.h"

enum GamePieceType { Card, Road, Settlement, City };

//Abstract class of all game pieces
class GamePiece {
private:
	GamePieceType const m_type;
	sf::Vector2f const m_coords;
	//PlayerOBJ *const m_owner;
	
	static const Cost m_price[4];
public:
	GamePiece();
	GamePiece( GamePieceType const type, sf::Vector2f const coords );
	static Cost& getCost( GamePieceType const type );
	
	virtual GamePieceType getPieceType() const;
	virtual sf::Vector2f getScreenCoords() const;
};

//Actual game piece classes
class PieceCard : public GamePiece {
private:
	GameCard *const m_card;

public:
	PieceCard();
	GameCardType getCardType() const;
	GameCard *getCard() const;
	bool isEffect() const;
	void AssignFunc();
};

class PieceRoad : public GamePiece {
private:
	sf::Vector2f m_start;
	sf::Vector2f m_end;
public:
	PieceRoad();
	sf::Vector2f getStart() const;
	sf::Vector2f getEnd() const;
};

class PieceSettlement : public GamePiece {

};

class PieceCity : public GamePiece {

};

#endif
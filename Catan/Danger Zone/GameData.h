#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "GamePiece.h"
#include "GameGui.h"
#include "GameCards.h"

//initialize as "PlayerData x = {0};" to preset all data memebers to zero
struct ResourceBank {
	int num_wood;
	int num_shep;
	int num_whet;
	int num_stone;
	int num_clay;
	int num_vp;
	int num_knights;
	int num_roads;
	int num_settlements;
	int num_city;
	ResourceBank();
	//ResourceBank operator+( ResourceBank const& rhs );
	ResourceBank operator+( Cost const &rhs );
};

class PlayerOBJ {
private:
	mutable bool m_update; //check to see if the screen needs to be updated with new data
	const int m_id; //Player's id number, aka "Player 1" or "Player 2" or etc...
	ResourceBank m_bank;
	PlayerGui *const m_ui; //constant pointer to player's ui for easy access to gui layer
	//vector<vector<GamePiece*>> m_pieceList; //2D vector to store Player's game pieces
	vector<Cost*> m_payout; //a list of resource payout indexed by dice roll value
public:
	PlayerOBJ( GameGui &the_gui, const int id_);
	int const getId() const;
	void Trade( PlayerOBJ &other );
	void Buy( GamePieceType piece );
	int const getTotalVP() const;
	int const getTotalKnights() const;
	int const getTotalRoads() const;
	PlayerGui& getPlayerGui() const;
	//int getSpecificResource( BankType rtype ) const; //Dont need this function?
	ResourceBank getBank() const;
	Cost getWallet() const; //returns resource data inside 'Cost' struct for easy price comparisons
	void add_to_bank( Cost &payout );
	//TODO: flesh out add_to_bank and begin writing test functions
};
//
////Stores all game related data. Use 'New' to place object on the heap
////for easy passing of data via pointers
//class GameData {
//private:
//	PlayerOBJ m_player_data[4];
//	vector<GameCard*> m_deck[52]; //TODO: look up total num of cards
//public:
//	GameData();
//	PlayerOBJ getPlayerObject( int const id ) const;
//	GameCard *DrawCard();
//};

#endif
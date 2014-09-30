#include <iostream>
#include "Globals.h"
#include "GameGui.h"
#include "GamePiece.h"
#include "GameCards.h"
#include "GameData.h"

ResourceBank::ResourceBank()
{
	num_wood = 0;
	num_shep = 0;
	num_whet = 0;
	num_stone = 0;
	num_clay = 0;
	num_vp = 0;
	num_knights = 0;
	num_roads = 0;
	num_settlements = 0;
	num_city = 0;
}

ResourceBank ResourceBank::operator+( Cost const &rhs )
{
	ResourceBank newBank;
	newBank.num_wood = this->num_wood + rhs.wood;
	newBank.num_shep = this->num_shep + rhs.shep;
	newBank.num_whet = this->num_whet + rhs.whet;
	newBank.num_stone = this->num_stone + rhs.stone;
	newBank.num_clay = this->num_clay + rhs.clay;
	newBank.num_vp = this->num_vp;
	newBank.num_knights = this->num_knights;
	newBank.num_roads = this->num_roads;
	newBank.num_settlements = this->num_settlements;
	newBank.num_city = this->num_city;
	return newBank;
}

//////////////////////////////////////////////////////////////////////////////////////
//PlayerOBJ Definition

PlayerOBJ::PlayerOBJ( GameGui &the_gui, const int id_) :
	m_id(id_), m_ui(the_gui.getPlayerGui(id_))
{
	m_update = false;
	//for testing purposes:
	
	//NOTE: pass payout vector?
	//skip for now

	//create vector of length 4 for each game piece
	//NOTE: change to array of vectors of game pieces?

}

int const PlayerOBJ::getId() const
{
	return m_id;
}

int const PlayerOBJ::getTotalVP() const
{
	return m_bank.num_vp;
}

int const PlayerOBJ::getTotalKnights() const
{
	return m_bank.num_knights;
}

int const PlayerOBJ::getTotalRoads() const
{
	return m_bank.num_roads;
}

PlayerGui& PlayerOBJ::getPlayerGui() const
{
	return *m_ui;
}

ResourceBank PlayerOBJ::getBank() const
{
	return m_bank;
}

Cost PlayerOBJ::getWallet() const
{
	return Cost( m_bank.num_wood, m_bank.num_shep, m_bank.num_whet,
				m_bank.num_stone, m_bank.num_clay );
}

void PlayerOBJ::add_to_bank( Cost &payout )
{
	/*m_bank = m_bank + payout;*/
	*m_bank.num_wood += payout.wood;
	m_bank.num_shep += payout.shep;
	m_bank.num_whet += payout.whet;
	m_bank.num_stone += payout.stone;
	m_bank.num_clay += payout.clay;*/
}

void PlayerOBJ::Trade( PlayerOBJ &other )
{
	//temp
	return;
}

void PlayerOBJ::Buy( GamePieceType piece )
{
	//temp
	return;
}
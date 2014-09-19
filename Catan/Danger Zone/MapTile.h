#ifndef MAP_TILE_H_
#define MAP_TILE_H_

#include <string>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

#include "Globals.h"

using namespace std;

class MapTile {

public:
	MapTile( unsigned int value, ResourceType type, sf::Vector2f pos, const unsigned int in );

	//Getters
	sf::CircleShape getTile();
	sf::Text getLabel();
	unsigned int getValue();
	ResourceType getType();

	sf::Vector2f getCenter(); //returns the pixel position of the center of the tile
	sf::Vector2f getPoint( const unsigned int pt ); //returns a specific point of the hexagonal tile

	//Setters
	void setTexture( const sf::Texture* img ); //sets the background of the tile to given image
	void set_to_desert();

	static bool loadStatics();
	static bool staticsLoaded;
	static const string typeNames[6];
	static vector<sf::Text*> valueList;
	static sf::Font font;
	static sf::Texture tileGraphic[6];
private:
	const unsigned int index;
	sf::CircleShape tile;
	sf::Text label;
	unsigned int value;
	ResourceType type;
};

class Map {
private:
	vector<MapTile*> mapVec;

public:
	Map(unsigned int limit = 4);

	void createTile(sf::Vector2f pos);
	void drawMap(sf::RenderWindow& Win);

	static mt19937 generator;
	static uniform_int_distribution<unsigned int> valDist;
	static uniform_int_distribution<unsigned int> typeDist;
	static unsigned int count;
	static vector<ResourceType> typeList;
};

#endif
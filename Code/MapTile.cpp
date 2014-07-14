#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "MapTile.h"

using namespace std;

const string MapTile::typeNames[6] = { "Wood", "Sheep", "Wheat", "Stone", "Clay", "Desert" };
vector<sf::Text*> MapTile::valueList;
sf::Font MapTile::font;
sf::Texture MapTile::tileGraphic[6];
bool MapTile::staticsLoaded = false;

bool MapTile::loadStatics()
{
	if (!font.loadFromFile("resources/sansation.ttf")) return false;
	if (!tileGraphic[0].loadFromFile("resources/wood.png")) return false;
	if (!tileGraphic[1].loadFromFile("resources/shep.png")) return false;
	if (!tileGraphic[2].loadFromFile("resources/whet.png")) return false;
	if (!tileGraphic[3].loadFromFile("resources/stone.png")) return false;
	if (!tileGraphic[4].loadFromFile("resources/clay.png")) return false;
	if (!tileGraphic[5].loadFromFile("resources/desert.png")) return false;

	return true; //success
}

MapTile::MapTile() {}

MapTile::MapTile( unsigned int value, ResourceType type, sf::Vector2f pos ) : tile(sf::CircleShape(radius, 6))
{
	if ( !staticsLoaded ) {
		if (loadStatics()) {
			cout << "Statics Loaded Successfully" << endl << endl;
			staticsLoaded = true;
		}
		else {
			cout << "Problem Loading Statics....Exiting" << endl << endl;
			return;
		}
	}

	this->value = value;
	this->type = type;

	tile.setTexture(&tileGraphic[type]);
	//tile.setOutlineColor(sf::Color::White);
	//tile.setOutlineThickness(2);
	//sets the origin(center) to be the true center of the shape
	sf::FloatRect sRect = tile.getLocalBounds();
	tile.setOrigin( (sRect.width/2.0f) + sRect.left, (sRect.height/2.0f) + sRect.top );
	//positions the shape
	tile.setPosition(pos);
	tile.rotate(90);

	label.setString( sf::String( to_string(value) ) );
	label.setFont(font);
	label.setCharacterSize(45);
	label.setColor(sf::Color::Black);
	sRect = label.getLocalBounds();
	label.setOrigin( (sRect.width/2.0f) + sRect.left, (sRect.height/2.0f) + sRect.top );
	label.setPosition(pos);
	valueList.push_back(&label);
}

sf::CircleShape MapTile::getTile() { return tile; }

sf::Text MapTile::getLabel() { return label; }

unsigned int MapTile::getValue() { return value; }

ResourceType MapTile::getType() { return type; }

sf::Vector2f MapTile::getCenter() { return tile.getPosition(); }

sf::Vector2f MapTile::getPoint( const unsigned int pt ) { return tile.getPoint(pt); }

void MapTile::setTexture( const sf::Texture* img ) { tile.setTexture(img); }

void MapTile::set_to_desert()
{
	type = Desert;
	tile.setFillColor(sf::Color::White);
	tile.setTexture(&tileGraphic[type]);
	label.setColor(sf::Color::Transparent);
	value = 0;
}

//********************************************************************************************************************************//

//Map Helper Function
sf::CircleShape createReferenceTile(unsigned int tier) 
{
	cout << "Generating Reference Hexagon for tier   " << tier << endl << endl;
	sf::CircleShape shape((radius-5.0f)*(tier*2), 6);
	//shape.setOutlineThickness(2);
	sf::FloatRect sRect = shape.getLocalBounds();
	shape.setOrigin( (sRect.width/2.0f) + sRect.left, (sRect.height/2.0f) + sRect.top );
	shape.setPosition(SCRNWIDTH/2, SCRNHEIGHT/2);
	return shape;
}

mt19937 Map::generator(static_cast<int>(time(0)));
uniform_int_distribution<unsigned int> Map::valDist(2, 11);
uniform_int_distribution<unsigned int> Map::typeDist(0, 4);
Map::Map(unsigned int limit)
{
	cout << "Creating Map..." << endl << endl;

	//create lone "tier 0" tile
	createTile(sf::Vector2f(SCRNWIDTH/2, SCRNHEIGHT/2));

	for ( unsigned int tier=1; tier<limit; tier++ )
	{
		sf::CircleShape ref = createReferenceTile(tier);

		//Creates 6 hexagons, one at each of the 6 points of the reference hexagon
		for ( unsigned int i=0; i<6; i++ ) 
		{
			sf::Vector2f pt = ref.getTransform().transformPoint(ref.getPoint(i));
			createTile(pt);
		
			//Draw reference lines between each point - this is done at the same time as the 6 "point hexagons"
			//to avoid re-drawing the same lines or revisiting the same coords (improves performance)
			sf::Vector2f endPt = ( i == 5 ) ? ref.getTransform().transformPoint(ref.getPoint(0)) :
						ref.getTransform().transformPoint(ref.getPoint(i+1));
			
			//NOTE: These "reference lines" dont actually need to be drawn (on screen or off) because I solved the 
			//problem with vector mathematics, however code is below to render if needed in future

			/*sf::VertexArray line(sf::Lines, 2);
			line[0].position = pt;
			line[1].position = endPt;*/

			//Creates the "inbetween hexagons" which are in between the "point hexagons"
			//Additional for-loop is used because there may be multiple "inbetween hexagons" in between 2 points (at higher tiers)
			for ( unsigned int j=0; j<tier-1; j++ ) 
			{
				float ratio = (float)(j+1) / tier; //cast to float to maintain decimal value
				float inverse = 1.0f - ratio; //Inverse of the ratio
				sf::Vector2f newPt = (inverse*pt) + (ratio*endPt); //Formula to find a vector that is a percentage between 2 vectors
				createTile(newPt);
			}
		}
	}

	cout << "Creating Random Desert Tile..." << endl << endl;
	mapVec[ (generator() % mapVec.size()) ]->set_to_desert();
}

void Map::createTile(sf::Vector2f pos)
{
	unsigned int randVal;
	do { randVal = valDist(generator); } while ( randVal == 7 ); //eliminates 7 from the range
	unsigned int randType = typeDist(generator);
	mapVec.push_back(new MapTile(randVal, getResourceType(randType), pos));
}

void Map::drawMap(sf::RenderWindow& Win)
{
	for ( unsigned int i=0; i<mapVec.size(); i++ )
	{
		Win.draw(mapVec[i]->getTile());
	}
	for ( unsigned int i=0; i<mapVec.size(); i++ )
	{
		Win.draw(*(MapTile::valueList[i]));
	}
}
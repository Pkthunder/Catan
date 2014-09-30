#ifndef GLOBALS_H_
#define GLOBALS_H_

using namespace std;

enum ResourceType { Error = -1, Wood, Shep, Whet, Stone, Clay, Desert }; //Desert is ONLY for MapTile

ResourceType getResourceType( unsigned int index );

const int SCRNWIDTH = 1250;
const int SCRNHEIGHT = 725;
const float radius = 55.0f;

//Cost of the game piece, overloaded comparsion operator for easy "afford-checking"
struct Cost {
	int wood;
	int shep;
	int whet;
	int stone;
	int clay;
	Cost( int c[5] );
	Cost ( int w, int s, int wh, int st, int c );
	bool operator==( Cost &other ) const;
	bool operator!=( Cost &other ) const;
};

#endif
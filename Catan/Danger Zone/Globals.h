#ifndef GLOBALS_H_
#define GLOBALS_H_

using namespace std;

enum ResourceType { Error = -1, Wood, Shep, Whet, Stone, Clay, Desert }; //Desert is ONLY for MapTile

ResourceType getResourceType( unsigned int index );

const int SCRNWIDTH = 1100;
const int SCRNHEIGHT = 725;
const float radius = 55.0f;


#endif
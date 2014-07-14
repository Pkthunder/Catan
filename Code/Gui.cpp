#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Gui.h"

using namespace std;

cGuiElement::cGuiElement() {}

//////////////////////////////////////////////////////////////////////////////////////

Gui::Gui() {}

void Gui::add_to_Gui(cGuiElement* ele)
{
	guiVec.push_back(ele);
}

void Gui::drawGui(sf::RenderWindow &Win)
{
	for ( unsigned int i=0; i<guiVec.size(); i++ )
	{
		guiVec[i]->drawElement(Win);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
sf::Font PlayerGui::font;
bool PlayerGui::loadStatics = false;

PlayerGui::PlayerGui( int playerId )
{
	cout << "Creating GUI for Player " << playerId 
		<< "....." << endl << endl;

	if ( !loadStatics ) {
		if ( !font.loadFromFile("resources/sansation.ttf")) {
			cout << "Font Loading Error in PlayerGui..." << endl << endl;
			return;
		}
		loadStatics = true;
	}

	this->playerId = playerId;

	outline.setSize(sf::Vector2f(200,150));
	outline.setFillColor(sf::Color::White);
	outline.setOutlineColor(sf::Color::Red);
	outline.setOutlineThickness(3);
	switch(playerId) {
	case TopLeft:
		outline.setPosition(30.0f, 30.0f);
		break;
	case TopRight:
		outline.setOrigin(200.0f, 0.0f);
		outline.setPosition(SCRNWIDTH - 30.0f, 30.0f);
		break;
	case BottomRight:
		outline.setOrigin(200.0f, 150.0f);
		outline.setPosition(SCRNWIDTH - 30.0f, SCRNHEIGHT - 30.0f);
		break;
	case BottomLeft:
		outline.setOrigin(0.0f, 150.0f);
		outline.setPosition(30.0f, SCRNHEIGHT - 30.0f);
		break;
	default: break;
	};
	renderQueue.push_back((sf::Drawable*)&outline);

	//set the center of the  gui area
	sf::FloatRect outlineRect = outline.getLocalBounds();
	baseCoord = sf::Vector2f( (outlineRect.width/2.0f), (outlineRect.height/2.0f));

	//Setting the 'Player X' label
	label.setString("Player " + playerId);
	label.setFont(font);
	label.setColor(sf::Color::Black);
	sf::FloatRect sRect = label.getLocalBounds();
	label.setOrigin((sRect.width/2.0f) + sRect.left, (sRect.height/2.0f) + sRect.top );
	label.setPosition( baseCoord.x, outlineRect.top + 5.0f );
	renderQueue.push_back((sf::Drawable*)&label);

}

void PlayerGui::drawElement(sf::RenderWindow &Win)
{
	for ( unsigned int i=0; i<renderQueue.size(); i++ )
		Win.draw(*renderQueue[i]);
}
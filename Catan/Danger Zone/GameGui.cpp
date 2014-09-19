#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Button.h"
#include "GameGui.h"

using namespace std;

cGuiElement::cGuiElement() {}

//////////////////////////////////////////////////////////////////////////////////////

GameGui::GameGui(vector<ButtonTracker*>& rBtnVec) : btnVec(rBtnVec)
{
	//this->btnVec = btnVec;
	add_to_Gui((cGuiElement*)new PlayerGui(1));
	add_to_Gui((cGuiElement*)new PlayerGui(2));
	add_to_Gui((cGuiElement*)new PlayerGui(3));
	add_to_Gui((cGuiElement*)new PlayerGui(4));
}

void GameGui::add_to_Gui(cGuiElement* ele)
{
	guiVec.push_back(ele);
}

void GameGui::drawGui(sf::RenderWindow &Win)
{
	for ( unsigned int i=0; i<guiVec.size(); i++ )
	{
		guiVec[i]->drawElement(Win);
	}
}

PlayerGui* GameGui::getPlayerGui( const int playerId )
{
	return (PlayerGui*)guiVec[playerId-1];
}

//////////////////////////////////////////////////////////////////////////////////////

//Static Members
sf::Font PlayerGui::font;
sf::Texture PlayerGui::iconList[5];
bool PlayerGui::loadStatics = false;

//Constructor
PlayerGui::PlayerGui( int playerId )
{
	cout << "Creating GUI for Player " << playerId 
		<< "....." << endl << endl;

	if ( !loadStatics ) {
		if ( !font.loadFromFile("resources/calibri.ttf")) {
			cout << "Font Loading Error in PlayerGui..." << endl << endl;
			return;
		}
		if (!iconList[0].loadFromFile("resources/clay-icon.png")) return;
		if (!iconList[1].loadFromFile("resources/shep-icon.png")) return;
		if (!iconList[2].loadFromFile("resources/stone-icon.png")) return;
		if (!iconList[3].loadFromFile("resources/whet-icon.png")) return;
		if (!iconList[4].loadFromFile("resources/wood-icon.png")) return;

		loadStatics = true;
	}

	this->playerId = playerId;

	//defines the square gui area
	outline.setSize(sf::Vector2f(225,150));
	outline.setFillColor(sf::Color::White);
	outline.setOutlineColor(sf::Color::Red);
	outline.setOutlineThickness(3);
	switch(playerId) {
	case TopLeft:
		outline.setPosition(25.0f, 25.0f);
		break;
	case TopRight:
		outline.setOrigin(225.0f, 0.0f);
		outline.setPosition(SCRNWIDTH - 25.0f, 25.0f);
		break;
	case BottomRight:
		outline.setOrigin(225.0f, 150.0f);
		outline.setPosition(SCRNWIDTH - 25.0f, SCRNHEIGHT - 25.0f);
		break;
	case BottomLeft:
		outline.setOrigin(0.0f, 150.0f);
		outline.setPosition(25.0f, SCRNHEIGHT - 25.0f);
		break;
	default: break;
	};
	renderQueue.push_back((sf::Drawable*)&outline);

	//set the center of the gui area
	sf::FloatRect outlineRect = outline.getGlobalBounds();
	baseCoord = sf::Vector2f( outlineRect.left + (outlineRect.width/2.0f), outlineRect.top + (outlineRect.height/2.0f) );

	//Setting the 'Player X' label
	label.setString(std::string("Player ").append(to_string(playerId)));
	label.setFont(font);
	label.setColor(sf::Color::Black);
	label.setCharacterSize(22);
	sf::FloatRect sRect = label.getLocalBounds();
	label.setOrigin((sRect.width/2.0f) + sRect.left, (sRect.height/2.0f) + sRect.top );
	label.setPosition( baseCoord.x, outlineRect.top + label.getCharacterSize()/2 + 5.0f );
	sRect = label.getGlobalBounds();
	renderQueue.push_back((sf::Drawable*)&label);

	//Set Resource Icons and Value Labels

	//Clay
	clayIcon.setTexture(iconList[0]);
	sf::FloatRect clayRect = clayIcon.getLocalBounds();
	clayVal.setString("x 0");
	clayVal.setFont(font);
	clayVal.setColor(sf::Color::Black);
	clayVal.setCharacterSize(16);
	clayVal.setOrigin(0.0f, clayVal.getLocalBounds().top + (clayVal.getLocalBounds().height/2.0f) );
	//Calculate Intervals for Even Spacing
	float iconWidth = clayRect.width + clayVal.getLocalBounds().width + 2.5f;
	float spacingInterval = (outlineRect.width - (iconWidth*3.0f)) / 4.0f;
	//Set ClayIcon position in accordance to interval
	clayIcon.setPosition( outlineRect.left + spacingInterval, sRect.top + sRect.height + 5.0f );
	clayRect = clayIcon.getGlobalBounds(); //update position
	clayVal.setPosition( clayRect.left + clayRect.width + 2.5f, clayRect.top + (clayRect.height/2.0f));
	renderQueue.push_back((sf::Drawable*)&clayIcon);
	renderQueue.push_back((sf::Drawable*)&clayVal);

	//Shep
	shepIcon.setTexture(iconList[1]);
	sf::FloatRect shepRect = shepIcon.getLocalBounds();
	shepIcon.setPosition(outlineRect.left + (spacingInterval*2.0f) + iconWidth, clayRect.top);
	shepRect = shepIcon.getGlobalBounds(); //update position
	shepVal.setString("x 0");
	shepVal.setFont(font);
	shepVal.setColor(sf::Color::Black);
	shepVal.setCharacterSize(16);
	shepVal.setOrigin(0.0f, shepVal.getLocalBounds().top + (shepVal.getLocalBounds().height/2.0f) );
	shepVal.setPosition( shepRect.left + shepRect.width + 2.5f, shepRect.top + (shepRect.height/2.0f));
	renderQueue.push_back((sf::Drawable*)&shepIcon);
	renderQueue.push_back((sf::Drawable*)&shepVal);

	//Stone
	stoneIcon.setTexture(iconList[2]);
	sf::FloatRect stoneRect = stoneIcon.getLocalBounds();
	stoneIcon.setPosition(outlineRect.left + (spacingInterval*3.0f) + (iconWidth*2.0f), clayRect.top);
	stoneRect = stoneIcon.getGlobalBounds(); //update position
	stoneVal.setString("x 0");
	stoneVal.setFont(font);
	stoneVal.setColor(sf::Color::Black);
	stoneVal.setCharacterSize(16);
	stoneVal.setOrigin(0.0f, stoneVal.getLocalBounds().top + (stoneVal.getLocalBounds().height/2.0f) );
	stoneVal.setPosition( stoneRect.left + stoneRect.width + 2.5f, stoneRect.top + (stoneRect.height/2.0f));
	renderQueue.push_back((sf::Drawable*)&stoneIcon);
	renderQueue.push_back((sf::Drawable*)&stoneVal);

	//Whet
	whetIcon.setTexture(iconList[3]);
	sf::FloatRect whetRect = whetIcon.getLocalBounds();
	whetIcon.setOrigin((whetRect.width/2.0f) + whetRect.left, 0.0f );
	whetIcon.setPosition( ((clayRect.left + clayRect.width) + shepRect.left) / 2.0f, 
		clayRect.top + clayRect.height + 5.0f);
	whetRect = whetIcon.getGlobalBounds(); //update position
	whetVal.setString("x 0");
	whetVal.setFont(font);
	whetVal.setColor(sf::Color::Black);
	whetVal.setCharacterSize(16);
	whetVal.setOrigin(0.0f, whetVal.getLocalBounds().top + (whetVal.getLocalBounds().height/2.0f) );
	whetVal.setPosition( whetRect.left + whetRect.width + 2.5f, whetRect.top + (whetRect.height/2.0f));
	renderQueue.push_back((sf::Drawable*)&whetIcon);
	renderQueue.push_back((sf::Drawable*)&whetVal);

	//Wood
	woodIcon.setTexture(iconList[4]);
	sf::FloatRect woodRect = woodIcon.getLocalBounds();
	woodIcon.setOrigin((woodRect.width/2.0f) + woodRect.left, 0.0f );
	woodIcon.setPosition( ((shepRect.left + shepRect.width) + stoneRect.left) / 2.0f, 
		clayRect.top + clayRect.height + 5.0f);
	woodRect = woodIcon.getGlobalBounds(); //update position
	woodVal.setString("x 0");
	woodVal.setFont(font);
	woodVal.setColor(sf::Color::Black);
	woodVal.setCharacterSize(16);
	woodVal.setOrigin(0.0f, woodVal.getLocalBounds().top + (woodVal.getLocalBounds().height/2.0f) );
	woodVal.setPosition( woodRect.left + woodRect.width + 2.5f, woodRect.top + (woodRect.height/2.0f));
	renderQueue.push_back((sf::Drawable*)&woodIcon);
	renderQueue.push_back((sf::Drawable*)&woodVal);

	//Sets Victory Point and Knight Counters
	victoryCount.setString("Victory Points: 0");
	victoryCount.setFont(font);
	victoryCount.setCharacterSize(17);
	victoryCount.setColor(sf::Color::Black);
	sf::FloatRect vicRect = victoryCount.getLocalBounds();
	victoryCount.setOrigin( 0.0f, vicRect.top + vicRect.height );
	victoryCount.setPosition( outlineRect.left + 5.0f, outlineRect.top + outlineRect.height - 5.0f );
	vicRect = victoryCount.getGlobalBounds(); //update position
	renderQueue.push_back((sf::Drawable*)&victoryCount);

	knightCount.setString("Knights: 0");
	knightCount.setFont(font);
	knightCount.setCharacterSize(17);
	knightCount.setColor(sf::Color::Black);
	sf::FloatRect knightRect = knightCount.getLocalBounds();
	knightCount.setOrigin( knightRect.left + knightRect.width , knightRect.top + knightRect.height );
	knightCount.setPosition( outlineRect.left + outlineRect.width - 5.0f, outlineRect.top + outlineRect.height - 5.0f );
	knightRect = knightCount.getGlobalBounds(); //update position
	renderQueue.push_back((sf::Drawable*)&knightCount);
}

void PlayerGui::drawElement(sf::RenderWindow &Win)
{
	for ( unsigned int i=0; i<renderQueue.size(); i++ )
		Win.draw(*renderQueue[i]);
}

void PlayerGui::updateVictoryCount(const unsigned int value)
{
	victoryCount.setString( std::string("Victory Points: ").append(to_string(value)) );
}

void PlayerGui::updateKnightCount(const unsigned int value)
{
	knightCount.setString( std::string("Knights: ").append(to_string(value)) );
}

void PlayerGui::updateResourceCount(const ResourceType type, const int value)
{
	sf::Text text;

	switch( type ) {
	case Clay:		text = clayVal;		break;
	case Shep:		text = shepVal;		break;
	case Stone:		text = stoneVal;	break;
	case Whet:		text = whetVal;		break;
	case Wood:		text = woodVal;		break;
	case Desert:
	case Error:
	default:		return;
	}
	text.setString( std::string("x ").append(to_string(value)) );
}
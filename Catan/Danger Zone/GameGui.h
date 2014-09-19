#ifndef GAMEGUI_H_
#define GAMEGUI_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Button.h"

class cGuiElement {
public:
	cGuiElement();
	virtual void drawElement(sf::RenderWindow &Win) = 0;
};

//////////////////////////////////////////////////////////////////////

class PlayerGui : public cGuiElement {
private:
	int playerId;
	sf::Vector2f baseCoord;
	vector<sf::Drawable*> renderQueue;

	sf::RectangleShape outline;
	sf::Text label;
	sf::Text victoryCount;
	sf::Text knightCount;
	sf::Sprite clayIcon;
	sf::Sprite shepIcon;
	sf::Sprite stoneIcon;
	sf::Sprite whetIcon;
	sf::Sprite woodIcon;
	sf::Text clayVal;
	sf::Text shepVal;
	sf::Text stoneVal;
	sf::Text whetVal;
	sf::Text woodVal;

public:
	enum GuiPos { TopLeft = 1, TopRight, BottomRight, BottomLeft };

	static sf::Font font;
	static sf::Texture iconList[5];
	static bool loadStatics;

	PlayerGui(int playerId);
	virtual void drawElement(sf::RenderWindow &Win);
	void updateVictoryCount(const unsigned int value);
	void updateKnightCount(const unsigned int value);
	void updateResourceCount(const ResourceType type, const int value);

};

//////////////////////////////////////////////////////////////////////

class GameGui {
private:
	vector<cGuiElement*> guiVec;
	vector<ButtonTracker*>& btnVec;
public:
	GameGui(vector<ButtonTracker*>& rBtnVec);
	void add_to_Gui(cGuiElement* ele);
	void drawGui(sf::RenderWindow &Win);
	PlayerGui* getPlayerGui( const int playerId );
};

#endif
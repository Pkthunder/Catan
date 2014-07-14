#ifndef GUI_H_
#define GUI_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "Globals.h"

class cGuiElement {
public:
	cGuiElement();
	virtual void drawElement(sf::RenderWindow &Win) = 0;
};

//////////////////////////////////////////////////////////////////////

class Gui {
private:
	vector<cGuiElement*> guiVec;
public:
	Gui();
	void add_to_Gui(cGuiElement* ele);
	void drawGui(sf::RenderWindow &Win);
};

//////////////////////////////////////////////////////////////////////

class PlayerGui : public cGuiElement{
private:
	int playerId;
	sf::RectangleShape outline;
	sf::Vector2f baseCoord;
	sf::Text label;
	vector<sf::Drawable*> renderQueue;
public:
	enum GuiPos { TopLeft = 1, TopRight, BottomRight, BottomLeft };

	static sf::Font font;
	static bool loadStatics;

	PlayerGui(int playerId);
	virtual void drawElement(sf::RenderWindow &Win);
	//sf::Vector2f getActualPosition();
};

#endif
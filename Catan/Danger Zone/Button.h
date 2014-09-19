#ifndef BUTTON_H_
#define BUTTON_H_

#include <functional>
#include <SFML/Graphics.hpp>

//TODO: Add Button State to handle Enter and Leave?

enum ButtonEvent { MouseEnter, MouseLeave, Click };

class ButtonTracker
{
private:
	sf::Drawable & obj;
	const sf::FloatRect rect;
	bool mouseOver; //is mouse on the button?
	bool runningHandler; //is click event on button already processing - to prevent double clicks re-running handler
	const std::function<void(sf::Drawable&, const ButtonEvent)> mOver_CB;
	const std::function<int(sf::Drawable&)> mClick_CB;
	const int id;
	static int currId;

public:
	//ButtonTracker();
	ButtonTracker(sf::Drawable &obj, const sf::FloatRect r, 
		const std::function<void(sf::Drawable&, const ButtonEvent)> overCB,
		const std::function<int(sf::Drawable& )> clickCB);
	const sf::FloatRect getRect();
	bool isMouseOver();
	void setMouseOver(bool m);
	bool isHandlerRunning();
	void setHandlerRunning(bool r);
	int HandleEvents(sf::Event &event);

};


#endif
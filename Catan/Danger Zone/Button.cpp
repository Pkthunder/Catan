#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Button.h"

//Statics
int ButtonTracker::currId = 1;

//ButtonTracker::ButtonTracker():id(0){};

ButtonTracker::ButtonTracker( sf::Drawable &obj, const sf::FloatRect r, 
							 const std::function<void(sf::Drawable&, const ButtonEvent)> overcb,
							 const std::function<int(sf::Drawable&)> clickcb) :
	obj(obj), id(currId), rect(r), mOver_CB(overcb), mClick_CB(clickcb)
{
	mouseOver = false;
	runningHandler = false;
	currId++;
}

const sf::FloatRect ButtonTracker::getRect()
{
	return rect;
}

bool ButtonTracker::isMouseOver()
{
	return mouseOver;
}

void ButtonTracker::setMouseOver( bool m )
{
	mouseOver = m;
}

bool ButtonTracker::isHandlerRunning()
{
	return runningHandler;
}

void ButtonTracker::setHandlerRunning(bool r)
{
	runningHandler = r;
}

//returns -2 if it does nothing
int ButtonTracker::HandleEvents( sf::Event &event )
{
	switch ( event.type ) {
	
	//Mouse Click Handler
	case sf::Event::MouseButtonPressed:
		//Check if click is inside button and left click
		if ( event.mouseButton.button == sf::Mouse::Left && isMouseOver() ) {
			setMouseOver(false);
			return mClick_CB(obj);
		}
		//click outside button
		break;

	//MouseEnter & MouseLeave Handler
	case sf::Event::MouseMoved:
		//Check Mouse Location
		if ( rect.contains( static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)) ) {
			if ( !isMouseOver() ) { //check for MouseEnter
				setMouseOver(true);
				mOver_CB(obj, MouseEnter);
			}
			//else = Mouse moved but remained inside button - do nothing
		}
		//else below = mouse moved and is outside button
		else if ( isMouseOver() ) { // check for MouseLeave
			setMouseOver(false);
			mOver_CB(obj, MouseLeave);
		}
		//else = button moved and never involved button - do nothing
		break;
	};
	return (-2); //means do nothing
}
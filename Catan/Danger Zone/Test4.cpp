//#include <iostream>
//#include <vector>
//#include <SFML/Graphics.hpp>
//
//using namespace std;
//
//const int SRCNWIDTH = 900;
//const int SRCNHEIGHT = 725;
//const float radius = 55.0f;
//sf::Vector2f center = sf::Vector2f(SRCNWIDTH/2, SRCNHEIGHT/2);
//
//vector<sf::CircleShape> tileList;
//const sf::Color colorList[4] = { sf::Color::Blue, sf::Color::Yellow, sf::Color::Red,
//	sf::Color::Magenta};
//const string colorName[4] = {"Blue", "Yellow", "Red", "Magenta"};
//vector<sf::VertexArray> idList;
//sf::Font font;
//
//void createTile( sf::Vector2f pos, sf::Color color)
//{
//	//creates a hexagon
//	sf::CircleShape shape(radius, 6);
//	shape.setFillColor(color);
//	shape.setOutlineColor(sf::Color::White);
//	shape.setOutlineThickness(2);
//	//sets the origin(center) to be the true center of the shape
//	sf::FloatRect sRect = shape.getLocalBounds();
//	shape.setOrigin( (sRect.width/2.0f) + sRect.left, (sRect.height/2.0f) + sRect.top );
//	//positions the shape
//	shape.setPosition(pos);
//	shape.rotate(90);
//	//add shape to master list of map tilesa
//	tileList.push_back(shape);
//}
//
//sf::CircleShape createReferenceTile(unsigned int tier) {
//
//	sf::CircleShape shape((radius)*(tier*2), 6);
//	shape.setFillColor(sf::Color::Magenta);
//	shape.setOutlineColor(sf::Color::White);
//	shape.setOutlineThickness(2);
//	//sets the origin(center) to be the true center of the shape
//	sf::FloatRect sRect = shape.getLocalBounds();
//	shape.setOrigin( (sRect.width/2.0f) + sRect.left, (sRect.height/2.0f) + sRect.top );
//	//positions the shape
//	shape.setPosition(center);
//	//add shape to master list of map tiles
//	//tileList.push_back(shape); // for debugging
//	return shape;
//}
//
//void createNewTier( unsigned int tier, unsigned int limit )
//{
//
//	if ( tier == (limit) ) { //base case
//		return;
//	}
//
//	cout << "Tier " << tier << " is " << colorName[tier-1] << endl << endl;
//
//	sf::CircleShape ref = createReferenceTile(tier); //Not rendered, only for reference to place other hexagons
//	
//	//Creates shapes ON the reference Hexagon points
//	for ( unsigned int i=0; i<(6); i++ ) {
//		sf::Vector2f pt = ref.getTransform().transformPoint(ref.getPoint(i));
//		createTile(pt, colorList[tier-1]);
//
//		//Draw reference lines between each point
//		sf::Vector2f endPt = ( i == 5 ) ? ref.getTransform().transformPoint(ref.getPoint(0)) :
//					ref.getTransform().transformPoint(ref.getPoint(i+1));
//		sf::VertexArray line(sf::Lines, 2);
//		line[0].position = pt;
//		line[1].position = endPt;
//
//		for ( unsigned int j=0; j<tier-1; j++ ) {
//			float ratio = (float)(j+1) / tier; //cast to float to maintain decimal value
//			float inverse = 1.0f - ratio; //Inverse of the ratio
//			sf::Vector2f newPt = (inverse*pt) + (ratio*endPt); //Formula to find a vector that is a percentage between 2 vectors
//			createTile(newPt, colorList[tier-1]);
//		}
//	}
//
//
//	return createNewTier(tier+1, limit);
//}
//
//void Test4() 
//{
//    sf::RenderWindow window(sf::VideoMode(SRCNWIDTH, SRCNHEIGHT), "Settlers of Catan");
//
//	if (!font.loadFromFile("resources/sansation.ttf"))
//		return;
//
//	//creates center tile
//	createTile(center, sf::Color::Green);
//	center = tileList[0].getPosition();
//	createNewTier(1, 5);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed) {
//				window.close();
//			}
//			if (event.type == sf::Event::KeyPressed) {
//				switch(event.key.code) {
//				case sf::Keyboard::Q:
//				case sf::Keyboard::Space:
//					window.close();
//					break;
//				default: break;
//				}
//			}
//		}
//		window.clear();
//		for ( unsigned int i = 0; i < tileList.size(); i++ ) {
//			window.draw( tileList[i] );
//		}
//		for ( unsigned int j = 0; j < idList.size(); j++ ) {
//			window.draw( idList[j] );
//		}
//		window.display();
//	}
//
//    return;
//}
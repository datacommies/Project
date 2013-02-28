#include "InputManager.h"
#include <iostream>
using namespace std;

int main()
{
	InputManager context;
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    	/* Will hold the positon of the rectangle shapes. */
    	sf::FloatRect rect1;
	sf::FloatRect rect2;
    	sf::FloatRect rect3;
    
    	/* The Rectangle shapes */
    	sf::RectangleShape button1;
    	sf::RectangleShape button2;
    	sf::RectangleShape button3;
    	/* Setting up buttons */
    	button1.setSize(sf::Vector2f(100, 50));
    	button1.setOutlineColor(sf::Color::Red);
    	button1.setOutlineThickness(5);
    	button1.setPosition(10, 20);
    
    	button2.setSize(sf::Vector2f(100, 50));
    	button2.setOutlineColor(sf::Color::Blue);
    	button2.setOutlineThickness(5);
    	button2.setPosition(10, 100);
    
    	button3.setSize(sf::Vector2f(100, 50));
    	button3.setOutlineColor(sf::Color::Green);
    	button3.setOutlineThickness(5);
    	button3.setPosition(10, 200);

	/* Global Bounds takes into account the transformations like
        setPosition()
    	*/
    	rect1 = button1.getGlobalBounds();
    	rect2 = button2.getGlobalBounds();
    	rect3 = button3.getGlobalBounds();
    	
    	while (window.isOpen())
    	{
    	    sf::Event event;
    	    while (window.pollEvent(event))
    	    {
    	        if (event.type == sf::Event::Closed)
    	        {
    	            window.close();
    	        }
    	        else if(event.type == sf::Event::MouseButtonPressed)
    	        {
    	            if(event.mouseButton.button == sf::Mouse::Left)
    	            {
    	                context.onClickContext(event, rect1, rect2, rect3);
			cout << "Current context value is now " << context.getCurrentContext() << endl; 
    	            }
    	        }
    	    }
        window.clear();
        window.draw(button1); // Draws stuff
        window.draw(button2);
        window.draw(button3);
        window.display();
	}
	return 0;

}

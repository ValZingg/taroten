#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"

#define WINDOW_HEIGHT 1280
#define WINDOW_WIDTH 720


int main()
{
    //========== WINDOW
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "SFML works!");
    window.setFramerateLimit(60);
    //=================

    std::array<Card,23> allcards = LoadCards();

    for(unsigned int k = 1;k < allcards.size();k++)
    {
        std::cout << "=============================" << std::endl;
        std::cout << allcards[k].name << std::endl;
    }

    //=============================================================================== MAIN LOOP ====================================================================================
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //==================DRAWING==================
        window.clear();
        //====STUFFTODRAW======

        //=================
        window.display();
    }

    //================================================================================= END ======================================================================================
    return 0;
}

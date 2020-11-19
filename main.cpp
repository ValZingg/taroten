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

    //========= CARD SETUP
    std::array<Card,23> allcards = LoadCards();
    for(unsigned int k = 1;k < allcards.size();k++) //reload all the card textures once, otherwise white squares !
    {
        allcards[k].Reload_texture();
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
        float currentx = 0;
        float currenty = 0;
        for(unsigned int g = 1;g < allcards.size();g++)
        {
            if(currentx >= 1200)
            {
                currentx = 0;
                currenty += 200;
            }
            allcards[g].image_spr.setPosition(sf::Vector2f(currentx,currenty));
            window.draw(allcards[g].image_spr);
            currentx += 125;

        }
        //=================
        window.display();
    }

    //================================================================================= END ======================================================================================
    return 0;
}

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menu.h"

#define WINDOW_HEIGHT 1600
#define WINDOW_WIDTH 900


int main()
{
    //========== FENETRE
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "SFML works!");
    window.setFramerateLimit(60);
    //=================

    //========= SETUP DES CARTES ============
    std::array<Card,23> allcards = LoadCards(); //Toutes les cartes du jeu
    for(unsigned int k = 1;k < allcards.size();k++) //Recharge toutes les textures des cartes pour �viter les carr�s blancs
    {
        allcards[k].Reload_texture();
    }

    //============== LOOP DU MENU ============
    MenuLoop(&window);
    window.clear(); //nettoie les �l�ments restant du menu
    //=============================================================================== LOOP DU JEU ====================================================================================
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //==================Affichage des �l�ments==================
        window.clear();//nettoie la fen�tre
        //====Choses � afficher======
        float currentx = 125;
        float currenty = 100;
        for(unsigned int g = 1;g < allcards.size();g++)
        {
            if(currentx >= 1200)
            {
                currentx = 125;
                currenty += 200;
            }
            allcards[g].image_spr.setPosition(sf::Vector2f(currentx,currenty));
            window.draw(allcards[g].image_spr);
            currentx += 125;

            if(allcards[g].image_spr.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
            {
                allcards[g].image_spr.setScale(sf::Vector2f(1.5f,1.5f));
            }
            else allcards[g].image_spr.setScale(sf::Vector2f(1.0f,1.0f));

        }
        //=================
        window.display();
    }

    //================================================================================= END ======================================================================================
    return 0;
}

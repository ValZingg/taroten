#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menu.h"
#include "pre_game.h"
#include "explore.h"
#include "Seed.h"

#define WINDOW_HEIGHT 1600
#define WINDOW_WIDTH 900


int main()
{
    //========== FENETRE
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Taroten");
    window.setFramerateLimit(60);
    //=================


    //POUR LE JEU
    bool is_seed_set = false;
    int seed = 0;
    //============== LOOP DU MENU ============
    bool game_active = true;
    int choixmenu;
    while(game_active)
    {
        if(!window.isOpen())return 999; //si l'utilisateur ferme la fenêtre avec le X rouge, fermer le programme
        //envoie l'utilsateur dans menu.h, et décide de la suite suivant le chiffre renvoyé
        switch(choixmenu)
        {
            default:
                choixmenu = MenuLoop(&window);
                break;

            case 1: //"Pré-jeu", là ou l'utilisateur va choisir son personnage et autres options
                choixmenu = PreGame(&window);
                break;

            case 2: //Le vrai jeu cette fois
                if(!is_seed_set)seed = getRandomNumber(100,999999,10);
                choixmenu = Explore(&window, seed);
                break;

            case 99:
                return EXIT_SUCCESS;
                break;
        }
    }

    //=============================================================================== LOOP DU JEU ====================================================================================
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //==================Affichage des éléments==================
        window.clear();//nettoie la fenêtre
        /*
        //====Choses à afficher======
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

        }*/
        //=================
        window.display();
    }

    //================================================================================= END ======================================================================================
    return 0;
}

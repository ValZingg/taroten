#ifndef PRE_GAME_H_INCLUDED
#define PRE_GAME_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menu.h"
#include "menuelements.h"
#include "characters.h"

#include "GUI_Manager.h"

int PreGame(sf::RenderWindow *window)
{
    //=============== charge la police d'écriture pour les éléments de l'interface======
    sf::Font police; //charge la police d'écriture
    police.loadFromFile("fonts/Timeless.ttf");
    //============== MESURAGE DE TEMPS ==========================
    sf::Clock clock; //utilisée pour empèchecher le programme de lire trop d'inputs en même temps
    clock.restart();
    //=============== définitions des éléments du menu ===========
    std::vector<GUI_Element*> menu_elements; //stocke tout les éléments du menu dans un vecteur pour les dessiner plus facilemtn après

    //FOND DU MENU
    GUI_Element Background(1600.0f,900.0f,0.0f,0.0f);
    menu_elements.push_back(&Background);

    //BOUTON DU CHOIX DU PERSO NUMERO 1
    GUI_Button_with_image testen(&police,"Perso1","choose_char1",400.0f,300.0f,50.0f,50.0f,"img/characters/char_1_portrait.png");
    menu_elements.push_back(&testen);
    //============================================================
    while(window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        //======================================





        //===========Dessinage=================
        window->clear();
        //=====
        int returnedvalue = GUIMANAGER(window,menu_elements,clock); //affiche l'interface et gère les clics
        if(returnedvalue != 0)return returnedvalue;
        //=====
        window->display();
    }
    return 0;
}


#endif // PRE_GAME_H_INCLUDED

#ifndef EXPLORE_H_INCLUDED
#define EXPLORE_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menu.h"
#include "menuelements.h"
#include "characters.h"

int Explore(sf::RenderWindow *window)
{
    sf::Clock clock;
    //============ vecteur des éléments graphiques ============
    std::vector<GUI_Element*> menu_elements;

    GUI_Element caca("caca",500.0f,500.0f,200.0f,100.0f);
    menu_elements.push_back(&caca);
    //============================================================
    while(window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window->close();
        }
        //===========================================================


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


#endif // EXPLORE_H_INCLUDED

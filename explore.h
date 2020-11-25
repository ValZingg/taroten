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
    //=============== charge la police d'�criture pour les �l�ments de l'interface======
    sf::Font police; //charge la police d'�criture
    police.loadFromFile("fonts/Timeless.ttf");
    //========= SETUP DES CARTES ============
    std::array<Card,23> allcards = LoadCards(); //Toutes les cartes du jeu
    for(unsigned int k = 1;k < allcards.size();k++)allcards[k].Reload_texture(); //Recharge toutes les textures des cartes pour �viter les carr�s blancs

    player.LoadDefaultCards(allcards);
    for(unsigned int k = 1;k < player.Deck.size();k++)player.Deck[k].Reload_texture();
    //============ vecteur des �l�ments graphiques ============
    std::vector<GUI_Element*> menu_elements;



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
        int returnedvalue = GUIMANAGER(window,menu_elements,clock); //affiche l'interface et g�re les clics
        if(returnedvalue != 0)return returnedvalue;
        //=====
        window->display();
    }
    return 0;
}



#endif // EXPLORE_H_INCLUDED

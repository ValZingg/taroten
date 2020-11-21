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
    GUI_Element Background("background",1600.0f,900.0f,0.0f,0.0f);
    menu_elements.push_back(&Background);

    //IMAGE DU CHOIX PERSO (VIDE AU DEPART)
    GUI_Image chosen_character_img("empty_char_image",400.0f,500.0f,80.0f,350.0f,"empty");
    menu_elements.push_back(&chosen_character_img);

    //DESCRIPTION DU CHOIX PERSO (VIDE AU DEPART)
    GUI_TextBox chosen_character_desc("character_desc",&police,"Cliquez sur la tête d'un personnage pour le selectionner...",1000.0f,500.0f,500.0f,350.0f);
    menu_elements.push_back(&chosen_character_desc);

    //BOUTON DU CHOIX DU PERSO NUMERO 1
    GUI_Button_with_image testen("choose_maya_button",&police,"Maya","choose_maya",400.0f,300.0f,80.0f,50.0f,"img/characters/Maya_portrait.png");
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

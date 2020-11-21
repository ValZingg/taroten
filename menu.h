#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menuelements.h"
#include "GUI_Manager.h"

/*
    MENULOOP
    --------
    Cette boucle sert � afficher le menu principal,
    l� ou le joueur choisira son personnage, la seed de la partie
    et les diverses actions.
*/
int MenuLoop(sf::RenderWindow *window)
{
    //=============== charge la police d'�criture pour les �l�ments de l'interface======
    sf::Font police; //charge la police d'�criture
    police.loadFromFile("fonts/Timeless.ttf");
    //============== MESURAGE DE TEMPS ==========================
    sf::Clock clock; //utilis�e pour emp�checher le programme de lire trop d'inputs en m�me temps
    clock.restart();
    //=============== d�finitions des �l�ments du menu ===========
    std::vector<GUI_Element*> menu_elements; //stocke tout les �l�ments du menu dans un vecteur pour les dessiner plus facilemtn apr�s

    //Fond d'�cran
    GUI_Element Background("background",1600.0f,900.0f,0.0f,0.0f);
    menu_elements.push_back(&Background);

    //Bouton pour lancer la partie
    GUI_Button button_startgame("startgamebutton",&police,"Nouvelle partie","newgame",400.0f,100.0f,600.0f,400.0f);
    menu_elements.push_back(&button_startgame);

    //Bouton pour les options
    GUI_Button button_options("optionsbutton",&police,"Options","options",400.0f,100.0f,600.0f,550.0f);
    menu_elements.push_back(&button_options);

    //Bouton pour quitter
    GUI_Button button_quit("quitbutton",&police,"Quitter","quit",400.0f,100.0f,600.0f,700.0f);
    menu_elements.push_back(&button_quit);
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



        //=====dessinage des choses======
        window->clear();
        //======
        int returnedvalue = GUIMANAGER(window,menu_elements,clock); //affiche l'interface et g�re les clics
        if(returnedvalue != 0)return returnedvalue; //si un autre int que 0 est re�u, cela veux dire qu'il y a eu un clic sur un bouton
        //======
        window->display();
    }

    return 1;
}


#endif // MENU_H_INCLUDED

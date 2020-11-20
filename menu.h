#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menuelements.h"


/*
    MENULOOP
    --------
    Cette boucle sert à afficher le menu principal,
    là ou le joueur choisira son personnage, la seed de la partie
    et les diverses actions.
*/
void MenuLoop(sf::RenderWindow *window)
{
    //=============== charge la police d'écriture pour les éléments de l'interface======
    sf::Font police; //charge la police d'écriture
    police.loadFromFile("fonts/Timeless.ttf");
    //=============== définitions des éléments du menu ===========
    std::vector<GUI_Element*> menu_elements; //stocke tout les éléments du menu dans un vecteur pour les dessiner plus facilemtn après
    GUI_Button button1("Test button",600.0f,300.0f,&police);
    menu_elements.push_back(&button1);
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
        for(unsigned int k = 0;k < menu_elements.size();k++)
        {
            window->draw(menu_elements[k]->e_sprite); //dessine tout les éléments de l'interface

            //!!! Le vecteur menu_elements est fait de la classe parente GUI_element,
            //!!! donc quand nous voulons dessiner par exemple le texte d'un bouton,
            //!!! le programme va crasher car GUI_element ne contient pas d'attribut Texte,
            //!!! c'est GUI_Button qui a un attribut texte. Donc pour y remédier, nous
            //!!! crééons une classe bouton temporaire, puis nous checkons si elle possède
            //!!! un texte à afficher, si oui, on l'affiche, sinon, on passe.
            //crée un bouton temporaire pour vérifier si l'élément actuel est un bouton
            //avec du texte à afficher
            GUI_Button *tempbutton = static_cast<GUI_Button*>(menu_elements[k]);
            if(tempbutton->b_text.getString().getSize() > 0)
            {
                window->draw(tempbutton->b_text);
            }
        }
        //======
        window->display();
    }
}


#endif // MENU_H_INCLUDED

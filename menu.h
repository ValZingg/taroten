#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menuelements.h"

/*
    MENULOOP
    --------
    Cette boucle sert � afficher le menu principal,
    l� ou le joueur choisira son personnage, la seed de la partie
    et les diverses actions.
*/
int MenuLoop(sf::RenderWindow *window)
{
    bool in_menu = true;
    //=============== charge la police d'�criture pour les �l�ments de l'interface======
    sf::Font police; //charge la police d'�criture
    police.loadFromFile("fonts/Timeless.ttf");
    //============== MESURAGE DE TEMPS ==========================
    sf::Clock clock; //utilis�e pour emp�checher le programme de lire trop d'inputs en m�me temps
    clock.restart();
    //=============== d�finitions des �l�ments du menu ===========
    std::vector<GUI_Element*> menu_elements; //stocke tout les �l�ments du menu dans un vecteur pour les dessiner plus facilemtn apr�s

    //Bouton pour lancer la partie
    GUI_Button button_startgame(&police,"Nouvelle partie","newgame",400.0f,100.0f,600.0f,400.0f);
    menu_elements.push_back(&button_startgame);

    //Bouton pour les options
    GUI_Button button_options(&police,"Options","options",400.0f,100.0f,600.0f,550.0f);
    menu_elements.push_back(&button_options);

    //Bouton pour quitter
    GUI_Button button_quit(&police,"Quitter","quit",400.0f,100.0f,600.0f,700.0f);
    menu_elements.push_back(&button_quit);
    //============================================================
    while(window->isOpen() && in_menu == true)
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
            window->draw(menu_elements[k]->e_sprite); //dessine tout les �l�ments de l'interface

            //!!! Le vecteur menu_elements est fait de la classe parente GUI_element,
            //!!! donc quand nous voulons dessiner par exemple le texte d'un bouton,
            //!!! le programme va crasher car GUI_element ne contient pas d'attribut Texte,
            //!!! c'est GUI_Button qui a un attribut texte. Donc pour y rem�dier, nous
            //!!! cr��ons une instance de classe GUI_Button temporaire, puis nous checkons si elle poss�de
            //!!! un texte � afficher, si oui, on l'affiche, sinon, on passe.
            //cr�e un bouton temporaire pour v�rifier si l'�l�ment actuel est un bouton
            //avec du texte � afficher
            GUI_Button *tempbutton = static_cast<GUI_Button*>(menu_elements[k]);
            if(tempbutton->b_text.getString().getSize() > 0)window->draw(tempbutton->b_text);
            std::string button_action = tempbutton->b_action; //essaie de r�cuperer l'action du bouton


            //======== gestion de la d�t�ction des clics sur les boutons ========
            //si la souris survole un bouton
            if(menu_elements[k]->e_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y))
            {
                //montre qu'on le survole en changeant le texte en jaune
                menu_elements[k]->e_sprite.setColor(sf::Color::Yellow);
                //et qu'on clique dessus
                //Il faut qu'au moins une seconde soit pass�e depuis le d�but de la boucle pour pouvoir cliquer.
                //Cela sert � empecher le programme de register les clics entre changement d'interface
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asSeconds() > 1)
                {
                    std::cout << "action bouton = "<< button_action << std::endl;
                    //on d�cide ensuite l'action avec le contenu de button_action
                    //Oblig� de faire des if..elses..if...elses parce que impossible de faire
                    // des switchs avec des strings :(
                    if(button_action == "quit")
                    {
                        //on stop le loop du menu, et on quitte le jeu
                        in_menu = false;
                        return EXIT_SUCCESS;
                    }

                    if(button_action == "newgame")
                    {
                        in_menu = false;
                        return 1; //envoie l'utilisateur au choix du personnage
                    }
                }
            }
            else
            {
                //si la souris ne survole plus un bouton, on le remet dans sa couleur normale
                if(menu_elements[k]->e_sprite.getColor() == sf::Color::Yellow)
                {
                    menu_elements[k]->e_sprite.setColor(sf::Color::White);
                }
            }
        }
        //======
        window->display();
    }

    return 1;
}


#endif // MENU_H_INCLUDED

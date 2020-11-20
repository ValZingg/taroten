#ifndef PRE_GAME_H_INCLUDED
#define PRE_GAME_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menu.h"
#include "menuelements.h"

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
    GUI_Button button_test(&police,"Test","test",400.0f,100.0f,600.0f,300.0f);
    menu_elements.push_back(&button_test);
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
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //!!! Pour la documentation de cette boucle, se référer à la même boucle dans menu.h!!!
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        for(unsigned int k = 0;k < menu_elements.size();k++)
        {
            window->draw(menu_elements[k]->e_sprite); //dessine tout les éléments de l'interface

            GUI_Button *tempbutton = static_cast<GUI_Button*>(menu_elements[k]);
            if(tempbutton->b_text.getString().getSize() > 0)window->draw(tempbutton->b_text);
            std::string button_action = tempbutton->b_action; //essaie de récuperer l'action du bouton

            //======== gestion de la détéction des clics sur les boutons ========
            //si la souris survole un bouton
            if(menu_elements[k]->e_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y))
            {
                //montre qu'on le survole en changeant le texte en jaune
                menu_elements[k]->e_sprite.setColor(sf::Color::Yellow);
                //et qu'on clique dessus
                //Il faut qu'au moins une seconde soit passée depuis le début de la boucle pour pouvoir cliquer.
                //Cela sert à empecher le programme de register les clics entre changement d'interface
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asSeconds() > 1)
                {
                    std::cout << "action bouton = "<< button_action << std::endl;
                    //on décide ensuite l'action avec le contenu de button_action
                    //Obligé de faire des if..elses..if...elses parce que impossible de faire
                    // des switchs avec des strings :(
                    if(button_action == "test")
                    {
                        return 0;
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
        //=====
        window->display();
    }
    return 0;
}


#endif // PRE_GAME_H_INCLUDED

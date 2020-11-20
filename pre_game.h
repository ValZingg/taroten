#ifndef PRE_GAME_H_INCLUDED
#define PRE_GAME_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menu.h"
#include "menuelements.h"

int PreGame(sf::RenderWindow *window)
{
    //=============== charge la police d'�criture pour les �l�ments de l'interface======
    sf::Font police; //charge la police d'�criture
    police.loadFromFile("fonts/Timeless.ttf");
    //============== MESURAGE DE TEMPS ==========================
    sf::Clock clock; //utilis�e pour emp�checher le programme de lire trop d'inputs en m�me temps
    clock.restart();
    //=============== d�finitions des �l�ments du menu ===========
    std::vector<GUI_Element*> menu_elements; //stocke tout les �l�ments du menu dans un vecteur pour les dessiner plus facilemtn apr�s
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
        //!!! Pour la documentation de cette boucle, se r�f�rer � la m�me boucle dans menu.h!!!
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        for(unsigned int k = 0;k < menu_elements.size();k++)
        {
            window->draw(menu_elements[k]->e_sprite); //dessine tout les �l�ments de l'interface

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

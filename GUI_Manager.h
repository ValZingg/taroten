#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menu.h"
#include "menuelements.h"
#include "characters.h"

int GUIMANAGER(sf::RenderWindow *window, std::vector<GUI_Element*> menu_elements, sf::Clock clock)
{
    for(unsigned int k = 0;k < menu_elements.size();k++)
    {
        window->draw(menu_elements[k]->e_sprite); //dessine tout les éléments de l'interface

        //!!! Le vecteur menu_elements est fait de la classe parente GUI_element,
        //!!! donc quand nous voulons dessiner par exemple le texte d'un bouton,
        //!!! le programme va crasher car GUI_element ne contient pas d'attribut Texte,
        //!!! c'est GUI_Button qui a un attribut texte. Donc pour y remédier, nous
        //!!! crééons une instance de classe GUI_Button temporaire, puis nous checkons si elle possède
        //!!! un texte à afficher, si oui, on l'affiche, sinon, on passe.
        GUI_Button *tempbutton = static_cast<GUI_Button*>(menu_elements[k]);
        std::string button_action; //si c'est un bouton
        if(tempbutton->has_text) //détermine si il y a du texte à afficher
        {
            window->draw(tempbutton->b_text);
            //Seul les boutons on du texte, donc on sais que c'est un bouton si il y a du texte
        }

        //même chose qu'au dessus, mais cette fois si on détecte si c'est un bouton avec image
        // et si une image est trouvée, on la dessine
        GUI_Button_with_image *tempbuttonwithimg = static_cast<GUI_Button_with_image*>(menu_elements[k]);
        if(tempbuttonwithimg->has_an_image)window->draw(tempbuttonwithimg->bi_sprite);

        //======== gestion de la détéction des clics sur les boutons ========
        //si la souris survole un bouton
        if(menu_elements[k]->e_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y))
        {
            //montre qu'on le survole en changeant le texte en jaune si il est défini pour
            if(menu_elements[k]->highlight_on)menu_elements[k]->e_sprite.setColor(sf::Color::Yellow);
            //et qu'on clique dessus
            //Il faut qu'au moins une seconde soit passée depuis le début de la boucle pour pouvoir cliquer.
            //Cela sert à empecher le programme de register les clics entre changement d'interface
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asSeconds() > 1)
            {
                if(tempbutton->is_clickable)
                {
                    button_action = tempbutton->b_action; //essaie de récuperer l'action du bouton si c'est un bouton
                    std::cout << "action bouton = "<< button_action << std::endl;
                }
                //on décide ensuite l'action avec le contenu de button_action
                //Obligé de faire des if..elses..if...elses parce que impossible de faire
                // des switchs avec des strings :(
                if(button_action == "quit")
                {
                    //on stop le loop du menu, et on quitte le jeu
                    return 99;
                }

                if(button_action == "newgame")
                {
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

    return 0; //si 0 est renvoyé, la boucle d'affichage continuera
}



#endif // GUI_MANAGER_H_INCLUDED

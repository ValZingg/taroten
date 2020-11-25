#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cards.h"
#include "menu.h"
#include "menuelements.h"
#include "characters.h"

//Instance globale du personnage choisi
Character player("Maya"); //charge maya par défaut
bool chose_character = false; //a choisi un personnage

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
        if(tempbutton->has_text)window->draw(tempbutton->b_text); //détermine si il y a du texte, si oui, on le dessine

        //même chose qu'au dessus, mais cette fois si on détecte si c'est un bouton avec image
        // et si une image est trouvée, on la dessine
        GUI_Button_with_image *tempbuttonwithimg = static_cast<GUI_Button_with_image*>(menu_elements[k]);
        if(tempbuttonwithimg->has_an_image && tempbuttonwithimg->is_clickable)window->draw(tempbuttonwithimg->bi_sprite);

        //Pour les simples images:
        GUI_Image *tempimage = static_cast<GUI_Image*>(menu_elements[k]);
        if(tempimage->has_an_image && tempimage->is_clickable == false)window->draw(tempimage->i_sprite);


        //======== gestion de la détéction des clics sur les boutons ========
        //si la souris survole un bouton
        if(menu_elements[k]->e_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y))
        {
            //montre qu'on le survole en changeant le texte en jaune si il est défini pour
            if(menu_elements[k]->highlight_on)menu_elements[k]->e_sprite.setColor(sf::Color::Blue);
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
                    return 99;//on stop le loop du menu, et on quitte le jeu

                if(button_action == "newgame")
                    return 1; //envoie l'utilisateur au choix du personnage

                if(button_action == "startgame" && chose_character)
                {
                    return 2;
                }



                    //=========CHOIX DE PERSONNAGES===========
                if(button_action == "choose_maya")
                {
                    player.LoadCharacter("Maya");
                    chose_character = true;
                    for(unsigned int i = 0;i < menu_elements.size();i++) //cherche dans tout les éléments pour trouver le bon
                    {
                        //change l'image du personnage choisi par celui de Maya ou le joueur viens de cliquer dessus
                        if(menu_elements[i]->unique_identifier == "empty_char_image")
                        {
                            tempimage = static_cast<GUI_Image*>(menu_elements[i]);
                            tempimage->Change_Image("img/characters/Maya.png");
                        }

                        if(menu_elements[i]->unique_identifier == "character_desc")
                        {
                            GUI_TextBox *temptextbox = static_cast<GUI_TextBox*>(menu_elements[i]);
                            temptextbox->b_text.setString(player.description);
                        }

                    }
                    clock.restart();
                }
            }
        }
        else
        {
            //si la souris ne survole plus un bouton, on le remet dans sa couleur normale
            if(menu_elements[k]->e_sprite.getColor() == sf::Color::Blue)
            {
                menu_elements[k]->e_sprite.setColor(sf::Color::White);
            }
        }
    }

    return 0; //si 0 est renvoyé, la boucle d'affichage continuera
}



#endif // GUI_MANAGER_H_INCLUDED

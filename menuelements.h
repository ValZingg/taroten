#ifndef MENUELEMENTS_H_INCLUDED
#define MENUELEMENTS_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#define PATH_TO_DEFAULT_TEXTURE "img/gui/buttontexture1.png"


/* MENUELEMENTS.H
    ------------
    Ce fichier stock différentes classes
    qui représentent des éléments de l'interface utilisateur.
    Par exemple des boutons, des fonds, etc...
*/


//GUI_ELEMENT : Classe parente de tout les éléments de l'interface
class GUI_Element
{
    public:
        sf::Texture e_texture; //texture de l'élément
        sf::Sprite e_sprite; //sprite de l'élément

        GUI_Element()
        {

        }
};

//GUI_BUTTON : un bouton qui éxécute du code quand cliqué
class GUI_Button : public GUI_Element
{
    public:
        sf::Text b_text; //représentation graphique du texte
        std::string b_action; //L'action que fera le bouton quand on clique dessus

        GUI_Button(sf::Font *font,std::string text, std::string action, float width, float height, float locationx, float locationy)
        {
            b_text.setFont(*font);   //assigne la police
            b_text.setString(text); //assigne le texte au graphisme
            b_text.setCharacterSize(50);
            b_text.setFillColor(sf::Color::White);

            b_action = action; //assigne l'action

            //=== positionnement du sprite du bouton et textures
            e_texture.loadFromFile(PATH_TO_DEFAULT_TEXTURE); //charge la texture
            e_sprite.setTexture(e_texture); //assigne la texture au sprite
            e_sprite.setPosition(sf::Vector2f(locationx,locationy)); //position du bouton
            // === Conversions
            float scalex = width / e_sprite.getGlobalBounds().width;
            float scaley = height / e_sprite.getGlobalBounds().height;
            e_sprite.setScale(sf::Vector2f(scalex,scaley)); //le rend rectangulaire

            //Aligne le texte au centre du bouton
            float xPos = (locationx + e_sprite.getLocalBounds().width / 2) - (b_text.getLocalBounds().width / 2);
            b_text.setPosition(xPos, e_sprite.getPosition().y);
        }

        void Reload_texture()
        {
            e_sprite.setTexture(e_texture);
        }
};


#endif // MENUELEMENTS_H_INCLUDED

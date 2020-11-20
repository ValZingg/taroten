#ifndef MENUELEMENTS_H_INCLUDED
#define MENUELEMENTS_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#define PATH_TO_DEFAULT_TEXTURE "img/gui/temp.png"


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

        GUI_Button(std::string text, float width, float height,sf::Font *font)
        {
            b_text.setFont(*font);   //assigne la police
            b_text.setString(text); //assigne le texte au graphisme
            b_text.setCharacterSize(35);
            b_text.setFillColor(sf::Color::Red);
            b_text.setPosition(sf::Vector2f(50.0f,400.0f));

            e_texture.loadFromFile(PATH_TO_DEFAULT_TEXTURE); //charge la texture
            e_sprite.setTexture(e_texture); //assigne la texture au sprite

            // === Conversions
            float scalex = width / e_sprite.getGlobalBounds().width;
            float scaley = height / e_sprite.getGlobalBounds().height;
            e_sprite.setScale(sf::Vector2f(scalex,scaley)); //le rend rectangulaire
        }

        void SetOriginInMiddle() //met le point d'origine de l'image au centre de l'image
        {
            e_sprite.setOrigin(sf::Vector2f(e_sprite.getGlobalBounds().height/2,e_sprite.getGlobalBounds().width/2));
        }

        void Reload_texture()
        {
            e_sprite.setTexture(e_texture);
            this->SetOriginInMiddle();
        }
};


#endif // MENUELEMENTS_H_INCLUDED

#ifndef MENUELEMENTS_H_INCLUDED
#define MENUELEMENTS_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#define PATH_TO_DEFAULT_TEXTURE "img/gui/buttontexture1.png"


/* MENUELEMENTS.H
    ------------
    Ce fichier stock diff�rentes classes
    qui repr�sentent des �l�ments de l'interface utilisateur.
    Par exemple des boutons, des fonds, etc...
*/


//GUI_ELEMENT : Classe parente de tout les �l�ments de l'interface
class GUI_Element
{
    public:
        sf::Texture e_texture; //texture de l'�l�ment
        sf::Sprite e_sprite; //sprite de l'�l�ment

        GUI_Element()
        {

        }
};

//GUI_BUTTON : un bouton qui �x�cute du code quand cliqu�
class GUI_Button : public GUI_Element
{
    public:
        sf::Text b_text; //repr�sentation graphique du texte
        std::string b_action; //L'action que fera le bouton quand on clique dessus
        bool has_an_image = false; //permet de sauter cet �l�ment dans la fonction de dessinage si il n'a pas d'image

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

//m�me chose qu'un bouton mais avec une image
class GUI_Button_with_image : public GUI_Button
{
    public: //bi = button with image
        sf::Texture bi_texture;
        sf::Sprite bi_sprite;

        //c'est tr�s long et tr�s moche, mais je sais pas comment faire autrement
        GUI_Button_with_image(sf::Font *font,std::string text, std::string action, float width, float height, float locationx, float locationy,std::string imagepath) : GUI_Button(font,text,action,width,height,locationx,locationy)
        {
            //chargement et assignations
            if(!bi_texture.loadFromFile(imagepath))std::cout << "Failed loading image :" << imagepath << std::endl;
            bi_sprite.setTexture(bi_texture);

            has_an_image = true; //confirme qu'on a bien une image, sers � savoir si on doit afficher qqch

            //positionnement de l'image
            bi_sprite.setOrigin(sf::Vector2f(bi_sprite.getGlobalBounds().width/2, bi_sprite.getGlobalBounds().height/2));

            float scalex = width / bi_sprite.getGlobalBounds().width;
            float scaley = height / bi_sprite.getGlobalBounds().height;
            bi_sprite.setScale(sf::Vector2f(scalex * 0.7,scaley * 0.7)); //d�finis la taille de l'image � 70% de la taille du bouton,pour faire que l'image ne cache pas le texte
            //d�finis la position de l'image au centre du bouton, mais aussi un petit peu d�cal� en bas, pour laisse appara�tre le texte du bouton en haut
            bi_sprite.setPosition(sf::Vector2f(e_sprite.getPosition().x + (e_sprite.getGlobalBounds().width / 2), e_sprite.getPosition().y + (e_sprite.getGlobalBounds().height / 1.8)));
        }

        void Reload_image()
        {
            bi_sprite.setTexture(bi_texture);
        }

};


#endif // MENUELEMENTS_H_INCLUDED

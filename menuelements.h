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

        std::string unique_identifier; //utile si on veux retrouver une instance spécifique

        bool has_an_image = false; //permet de sauter cet élément dans la fonction de dessinage si il n'a pas d'image
        bool has_text = false; //même chose mais pour le texte
        bool highlight_on = false; //change de couleur si on le survole avec le curseur
        bool is_clickable = false;


        GUI_Element(std::string Identifier,float width, float height, float locationx, float locationy)
        {
            unique_identifier = Identifier; //assigne l'identifiant
            //=== positionnement du sprite du bouton et textures
            e_texture.loadFromFile(PATH_TO_DEFAULT_TEXTURE); //charge la texture
            e_sprite.setTexture(e_texture); //assigne la texture au sprite
            e_sprite.setPosition(sf::Vector2f(locationx,locationy)); //position du bouton
            // === Conversions
            float scalex = width / e_sprite.getGlobalBounds().width;
            float scaley = height / e_sprite.getGlobalBounds().height;
            e_sprite.setScale(sf::Vector2f(scalex,scaley)); //le rend rectangulaire
        }

        void Reload_texture()
        {
            e_sprite.setTexture(e_texture);
        }
};

//GUI_BUTTON : un bouton qui éxécute du code quand cliqué
class GUI_Button : public GUI_Element
{
    public:
        sf::Text b_text; //représentation graphique du texte
        std::string b_action; //L'action que fera le bouton quand on clique dessus

        GUI_Button(std::string Identifier,sf::Font *font,std::string text, std::string action, float width, float height, float locationx, float locationy) : GUI_Element(Identifier,width,height,locationx,locationy)
        {
            is_clickable = true;
            highlight_on = true;

            b_text.setFont(*font);   //assigne la police
            b_text.setString(text); //assigne le texte au graphisme
            b_text.setCharacterSize(50);
            b_text.setFillColor(sf::Color::White);
            has_text = true;

            b_action = action; //assigne l'action

            //Aligne le texte au centre du bouton
            float xPos = (locationx + e_sprite.getLocalBounds().width / 2) - (b_text.getLocalBounds().width / 2);
            b_text.setPosition(xPos, e_sprite.getPosition().y);
        }

};

//même chose qu'un bouton mais avec une image
class GUI_Button_with_image : public GUI_Button
{
    public: //bi = button with image
        sf::Texture bi_texture;
        sf::Sprite bi_sprite;

        //c'est très long et très moche, mais je sais pas comment faire autrement
        GUI_Button_with_image(std::string Identifier, sf::Font *font,std::string text, std::string action, float width, float height, float locationx, float locationy,std::string imagepath) : GUI_Button(Identifier,font,text,action,width,height,locationx,locationy)
        {
            is_clickable = true;
            //chargement et assignations
            if(!bi_texture.loadFromFile(imagepath))std::cout << "Failed loading image :" << imagepath << std::endl;
            bi_sprite.setTexture(bi_texture);

            has_an_image = true; //confirme qu'on a bien une image, sers à savoir si on doit afficher qqch

            //positionnement de l'image
            bi_sprite.setOrigin(sf::Vector2f(bi_sprite.getGlobalBounds().width/2, bi_sprite.getGlobalBounds().height/2));

            float scalex = width / bi_sprite.getGlobalBounds().width;
            float scaley = height / bi_sprite.getGlobalBounds().height;
            bi_sprite.setScale(sf::Vector2f(scalex * 0.7,scaley * 0.7)); //définis la taille de l'image à 70% de la taille du bouton,pour faire que l'image ne cache pas le texte
            //définis la position de l'image au centre du bouton, mais aussi un petit peu décalé en bas, pour laisse apparaître le texte du bouton en haut
            bi_sprite.setPosition(sf::Vector2f(e_sprite.getPosition().x + (e_sprite.getGlobalBounds().width / 2), e_sprite.getPosition().y + (e_sprite.getGlobalBounds().height / 1.8)));
        }

        void Reload_image()
        {
            bi_sprite.setTexture(bi_texture);
        }

        void New_Image(std::string filepath) //change l'image actuelle
        {
            bi_texture.loadFromFile(filepath);
            bi_sprite.setTexture(bi_texture);
        }

};

//GUI_TEXTBOX : pratiquement pareil qu'un bouton dans la structure, à la différence que vous ne pouvez pas cliquer dessus
class GUI_TextBox : public GUI_Element
{
    public:
        sf::Text b_text; //représentation graphique du texte

        GUI_TextBox(std::string Identifier,sf::Font *font,std::string text, float width, float height, float locationx, float locationy) : GUI_Element(Identifier,width,height,locationx,locationy)
        {
            is_clickable = false;
            highlight_on = false;

            b_text.setFont(*font);   //assigne la police
            b_text.setString(text); //assigne le texte au graphisme
            b_text.setCharacterSize(30);
            b_text.setFillColor(sf::Color::White);
            has_text = true;

            //Aligne le texte
            b_text.setPosition((e_sprite.getPosition().x + e_sprite.getLocalBounds().width/6), (e_sprite.getPosition().y + e_sprite.getLocalBounds().height/15));
        }

};

//même chose que bouton avec image, mais sans texte et sans action
class GUI_Image : public GUI_Element
{
    public:
        sf::Texture i_texture;
        sf::Sprite i_sprite;

        GUI_Image(std::string Identifier, float width, float height, float locationx, float locationy,std::string filepath) : GUI_Element(Identifier,width,height,locationx,locationy)
        {
            is_clickable = false;
            has_an_image = false;
            //chargement et assignations
            if(filepath != "empty")
            {
                if(!i_texture.loadFromFile(filepath))std::cout << "Failed loading image :" << filepath << std::endl;
                else has_an_image = true;
                i_sprite.setTexture(i_texture);

                //positionnement de l'image
                i_sprite.setOrigin(sf::Vector2f(i_sprite.getGlobalBounds().width/2, i_sprite.getGlobalBounds().height/2));

                float scalex = width / i_sprite.getGlobalBounds().width;
                float scaley = height / i_sprite.getGlobalBounds().height;
                i_sprite.setScale(sf::Vector2f(scalex,scaley ));
                i_sprite.setPosition(sf::Vector2f(e_sprite.getPosition().x + (e_sprite.getGlobalBounds().width / 2), e_sprite.getPosition().y + (e_sprite.getGlobalBounds().height)));
            }
        }

        void Change_Image(std::string filepath) //change l'image actuelle
        {
            if(!i_texture.loadFromFile(filepath))std::cout << "Failed loading image :" << filepath << std::endl;
            this->i_sprite.setTexture(i_texture);
            has_an_image = true;

            //réduire légèrement la taille
            i_sprite.setScale(sf::Vector2f(0.8f,0.8f));

            //repositionnement de l'image
            i_sprite.setPosition(sf::Vector2f((e_sprite.getGlobalBounds().width/2), e_sprite.getPosition().y + (e_sprite.getLocalBounds().height/6)));
        }

};


#endif // MENUELEMENTS_H_INCLUDED

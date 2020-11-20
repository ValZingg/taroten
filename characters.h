#ifndef CHARACTERS_H_INCLUDED
#define CHARACTERS_H_INCLUDED
#include "Cards.h"
#include <iostream>

/*
    CHARACTERS.h
    ------------
    Ce fichier contient la classe "Character" qui sert à
    définir les différents personnages que le joueur pourra
    jouer.
*/


class Character
{
    public:
        std::string name; //nom du personnage
        std::vector<Card> Deck; //deck du personnage
        int hp; //points de vies actuels hp = "health points"
        int max_hp; //points de vies maximums

        //!!!TODO : Relics/items vector

        //graphisme pour le portrait du personnage
        sf::Texture portrait_text;
        sf::Sprite portrait_spr;

        //graphisme pour le corps entier du personnage
        sf::Texture body_text;
        sf::Texture body_spr;

        //On transmet au constructeur le chemin d'accès du fichier du personnage.
        //Le programme charge ensuite les données du personnage dans l'instance de classe
        //en lisant le fichier trouvé.
        Character(std::string filepath_to_load)
        {

        }


};



#endif // CHARACTERS_H_INCLUDED

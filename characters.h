#ifndef CHARACTERS_H_INCLUDED
#define CHARACTERS_H_INCLUDED
#include "Cards.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>

/*
    CHARACTERS.h
    ------------
    Ce fichier contient la classe "Character" qui sert à
    définir les différents personnages que le joueur pourra
    jouer.
*/

#define DEFAULT_CARD_AMOUNT 5

//Remplace toutes les instances d'un caractère dans un string par un autre.
//Don généreux d'un inconnu sur StackOverflow.com.
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

class Character
{
    public:
        std::string name; //nom du personnage
        std::string description;
        std::string default_cards;
        std::vector<Card> Deck; //deck du personnage
        int hp; //points de vies actuels hp = "health points"
        int max_hp; //points de vies maximums

        //!!!TODO : Relics/items vector

        //graphisme pour le portrait du personnage
        sf::Texture portrait_text;
        sf::Sprite portrait_spr;

        //graphisme pour le corps entier du personnage
        sf::Texture body_text;
        sf::Sprite body_spr;

        //On transmet au constructeur le chemin d'accès du fichier du personnage.
        //Le programme charge ensuite les données du personnage dans l'instance de classe
        //en lisant le fichier trouvé.
        Character(std::string Name)
        {
            LoadCharacter(Name);
        }

        void LoadCharacter(std::string Name)
        {
                //==Récupération des graphismes ==
            //on récupère le nom du personnage, et grâce à celui-ci,
            //on peut charger tout les graphismes
            name = Name;
            //d'abord les graphismes du corps
            std::string filepath = "img/characters/" + name + ".png";
            body_text.loadFromFile(filepath);
            body_spr.setTexture(body_text);
            //puis le portrait
            filepath = "img/characters/" + name + "_portrait.png";
            portrait_text.loadFromFile(filepath);
            portrait_spr.setTexture(portrait_text);

                //==Récupération des données et statistiques ==
            filepath = "character_data/" + name + ".txt";
            std::ifstream file_to_read;
            std::string line;
            int counter = 0; //pour savoir à quelle ligne on est
            file_to_read.open(filepath);
            Deck.clear(); //Nettoie le deck de toutes les cartes avant d'en recharger
            while(std::getline(file_to_read,line))//tant qu'on lit le fichier
            {
                //====DONNEES DES LIGNES====
                switch(counter)//case 0 = ligne 0, case 1 = ligne 1, etc...
                {
                    case 0:
                        line.erase(0,12); //efface les 12 premiers charactères "description=" pour qu'il ne reste que le texte
                        line.erase(line.size(),1); //supprime le dernier charactère "\n"
                        line = ReplaceAll(line,"|","\n"); //change les | dans le fichier par des sauts de ligne.
                        description = line;
                        break;

                    case 1: //points de vies max
                        line.erase(0,6); //efface les 6 premiers charactères "maxhp=" pour qu'il ne reste que le chiffre
                        line.erase(line.size(),1); //supprime le dernier charactère "\n"
                        max_hp = std::stoi(line);//convertir le string en int
                        hp = max_hp; //le personnage commence toujours avec tout ses points de vies
                        break;

                    case 2: //cartes de départ
                        line.erase(0,14);
                        line.erase(line.size(),1); //supprime le dernier charactère "\n"
                        default_cards = line;


                        break;
                }
                //==========================
                //========prochaine ligne
                counter++;
            }
            file_to_read.close();
        }

        void LoadDefaultCards(std::array<Card,23> allcards)
        {
            //On récupère les TAGS des cartes
            std::string delimiter = ",";
            std::replace( default_cards.begin(),default_cards.end(), ',' , '\n');

            std::istringstream finalresult(default_cards);
            std::string line;
            //Grâce aux tags, on cherche dans les cartes
            while(std::getline(finalresult,line))
            {
                for(unsigned int i = 1;i < allcards.size();i++) //on cherche dans toutes les cartes
                {
                    if(allcards[i].tag == line)Deck.push_back(allcards[i]);
                }
            }

        }
};



#endif // CHARACTERS_H_INCLUDED

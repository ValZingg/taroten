#ifndef EXPLORE_H_INCLUDED
#define EXPLORE_H_INCLUDED
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <sys/stat.h>
#include <unistd.h>
#include "Cards.h"
#include "Seed.h"
#include "menu.h"
#include "menuelements.h"
#include "characters.h"

#define ROOM_SIZE 9

inline bool check_if_file_exists (const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}


void DumpTrash(std::vector<GUI_Element*> menushit)
{
    std::string filepath = "runs/MERDE.txt";
    std::ofstream fichier(filepath); //crée le fichier vide
    fichier.close();

    fichier.open(filepath);
    for(unsigned int k = 0;k < menushit.size();k++)
    {
        fichier << "OBJET " << k << std::endl;
        fichier << menushit[k]->unique_identifier << std::endl;
        fichier << "----------------------" << std::endl;
    }
    std::cout << "Dump successful." << std::endl;
    fichier.close();
}

int Explore(sf::RenderWindow *window, int seed)
{
    //====Création du fichier seed si pas déjà fait
    std::string filepath = "runs/" + std::to_string(seed) + ".tRUN";
    if(!check_if_file_exists(filepath))CreateRunFile(seed);

    //====Horloge
    sf::Clock clock;

    //=============== charge la police d'écriture pour les éléments de l'interface======
    sf::Font police; //charge la police d'écriture
    police.loadFromFile("fonts/Timeless.ttf");

    //========= SETUP DES CARTES ============
    std::array<Card,23> allcards = LoadCards(); //Toutes les cartes du jeu
    for(unsigned int k = 1;k < allcards.size();k++)allcards[k].Reload_texture(); //Recharge toutes les textures des cartes pour éviter les carrés blancs

    //Recharge les textures du deck du joueur
    for(unsigned int k = 1;k < player.Deck.size();k++)player.Deck[k].Reload_texture();

    //============ vecteur des éléments graphiques ============
    std::vector<GUI_Element*> menu_elements;
    //menu_elements = GetAllSquares(police,filepath);

    for(unsigned int k = 0; k < ROOM_SIZE;k++)
    {
        GUI_Button tempbutton = ReadRunSquare(filepath,k,police);
        menu_elements.push_back(&tempbutton);
    }
    for(unsigned int k = 0;k < menu_elements.size();k++)
    {
        std::cout << "Nom avant de changer = " << menu_elements[k]->unique_identifier << std::endl;
        menu_elements[k]->unique_identifier = "square" + std::to_string(k);
        std::cout << "Nom après avoir = " << menu_elements[k]->unique_identifier << std::endl;
        std::cout << k << " | Recharge la texture de : " << menu_elements[k]->unique_identifier << std::endl;
        menu_elements[k]->Reload_texture();
    }
    for(unsigned int k = 0;k < menu_elements.size();k++)std::cout << menu_elements[k]->unique_identifier << std::endl;
    DumpTrash(menu_elements);

    //GUI_TextBox seedbu("seedbox",&police,std::to_string(seed),200.0f,200.0f,200.0f,200.0f);
    //menu_elements.push_back(&seedbu);



    //============================================================
    while(window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window->close();
        }
        //===========================================================


        //===========Dessinage=================
        window->clear();
        //=====
        int returnedvalue = GUIMANAGER(window,menu_elements,clock); //affiche l'interface et gère les clics
        if(returnedvalue != 0)return returnedvalue;
        //=====
        window->display();
    }
    return 0;
}



#endif // EXPLORE_H_INCLUDED

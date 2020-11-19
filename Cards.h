#ifndef CARDS_H_INCLUDED
#define CARDS_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <fstream>

class Card
{
    public:
        std::string name;
        std::string desc;

        sf::Texture image_text;
        sf::Sprite image_spr;

        Card()
        {

        }

};

std::array<Card,23> LoadCards()
{
    std::cout << "Loading cards..." << std::endl;
    std::array<Card,23> all_cards; //define array to return

    //==== GETTING ALL THE PATHS TO THE FILES =====
    std::string line;
    std::ifstream all_cards_file; //file containing paths to all cards to read
    std::array<std::string,23> cards_to_load; //creates an array of paths
    int counter = 0; //tracker
    all_cards_file.open("card_data/ALL_CARDS.txt");
    while(std::getline(all_cards_file, line))
    {
        counter++;
        line = "card_data/" + line;
        cards_to_load[counter] = line;
    }
    all_cards_file.close();

    //===== LOADING THE ACTUAL DATA =====
    std::ifstream file_to_read;
    for(unsigned int i = 0;i < cards_to_load.size();i++)
    {
        Card Temp_card;// create instance
        file_to_read.open(cards_to_load[i]);
        counter = 0;
        while(std::getline(file_to_read, line))
        {
            //==========DATA==========
            switch(counter)
            {
                case 0: //name of card
                    Temp_card.name = line;
                    break;
            }

            counter++;
        }
        all_cards[i] = Temp_card; //put in array
        file_to_read.close();
    }


    return all_cards;
}

#endif // CARDS_H_INCLUDED

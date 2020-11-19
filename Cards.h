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
        std::string tag;

        std::string path_to_img;
        sf::Texture image_text;
        sf::Sprite image_spr;

        Card()
        {

        }

        void Reload_texture()
        {
            image_spr.setTexture(image_text);
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

                case 1: //card TAG (short version of name in 3 letters)
                    Temp_card.tag = line;
                    break;
            }

            //LOADING THE IMAGE OF THE CARD
                //cleaning the string to find picture =====
            std::string clean_image_name = cards_to_load[i].substr(0, cards_to_load[i].size()-4);
            clean_image_name.erase(0,10);
            Temp_card.path_to_img = "img/cards/" + clean_image_name + ".png";
                //========================================
            //assigning images, textures.
            Temp_card.image_text.loadFromFile(Temp_card.path_to_img);
            Temp_card.image_spr.setTexture(Temp_card.image_text);
            counter++;
        }
        all_cards[i] = Temp_card; //put in array
        file_to_read.close();
    }


    return all_cards;
}

#endif // CARDS_H_INCLUDED

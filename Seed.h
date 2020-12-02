#ifndef SEED_H_INCLUDED
#define SEED_H_INCLUDED
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <chrono>
#include <unistd.h>

#include "menuelements.h"

#define LEVEL_SPOTS 9

//Pour créer la seed
int getRandomNumber(int minimum, int maximum,int moreseed)
{
    std::random_device rd;
            std::mt19937::result_type seed = rd() ^ (
                (std::mt19937::result_type)
                std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
                (std::mt19937::result_type)
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() + moreseed);

            std::mt19937 gen(seed);
            std::uniform_int_distribution<unsigned> distrib(minimum, maximum);

            int rando = distrib(gen);
            return rando;
}

void CreateRunFile(int seed)
{
    //crée le fichier qui va storer la partie
    std::string filepath = "runs/" + std::to_string(seed) + ".tRUN";
    std::ofstream fichier(filepath); //crée le fichier vide
    fichier.close();

    //génère ensuite tout les trucs à voir dans la partie

    fichier.open(filepath);
    for(unsigned int i = 0;i < LEVEL_SPOTS;i++) //crée 9 cases du niveau
    {
        /*
                Les types de cases :
                -----------------------
                1 = emplacement du joueur au départ
                2 = Ennemi
                3 = Trésor
        */

        int typeofspot = 0; //type de case
        if(i == 4)typeofspot = 1;
        else typeofspot = getRandomNumber(2,3,seed);
        usleep(100000); //pour laisser le temps de randomiser
        std::cout << typeofspot << std::endl;

        fichier << std::to_string(typeofspot) << ",notdone"<< std::endl;
        //rajoute "notdone" après la case, pour signifier qu'elle n'est pas completée (not done)
        //Quand le joueur aura visité cette case, cela se changera en "done"

    }
    fichier.close();

}

//Lit une seule "case" d'un fichier seed
//Et renvoie le tout en un GUI_Button
GUI_Button ReadRunSquare(std::string filepath, int index,sf::Font police)
{
    GUI_Button button_to_send_back("square" + std::to_string(index),&police,std::to_string(index),"square" + std::to_string(index),100.0f,100.0f,index * 7,index * 7);
    std::ifstream fichier(filepath);
    std::string line;
    int counter = 0;

    while(std::getline(fichier,line))
    {
        if(counter == index) //ligne trouvée
        {
            std::string saveline = line; //sauvegarde de l'état initial de la ligne

            //obtention de l'action
            line.erase(1,line.size()+1); //Efface  tout sauf le premier caractère ( le chiffre )
            int typeofaction = std::stoi(line);
            switch(typeofaction)
            {
                case 1:
                    button_to_send_back.b_text.setString("entrance");
                    button_to_send_back.b_action = "entrance";
                    break;

                case 2:
                    button_to_send_back.b_text.setString("battle");
                    button_to_send_back.b_action = "battle";
                    break;

                case 3:
                    button_to_send_back.b_text.setString("loot");
                    button_to_send_back.b_action = "loot";
                    break;
            }

        }
        counter++;
    }

    fichier.close();
    return button_to_send_back;
}

std::vector<GUI_Element*> GetAllSquares(sf::Font police,std::string filepath)
{
    std::vector<GUI_Element*> Toreturn;

    //Compte le nombre de lignes dans le fichier du niveau, pour pouvoir savoir combien de cases il y a
    std::ifstream fichier(filepath);
    std::string line;
    int nblines = 0;
    while(std::getline(fichier,line))nblines++;
    fichier.close();

    for(int k = 0;k < nblines;k++)
    {
        GUI_Button tempbutton = ReadRunSquare(filepath,k,police);
        Toreturn.push_back(&tempbutton);
    }


    return Toreturn;
}



#endif // SEED_H_INCLUDED

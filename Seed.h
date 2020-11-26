#ifndef SEED_H_INCLUDED
#define SEED_H_INCLUDED
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <chrono>
#include <unistd.h>

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

        fichier << std::to_string(typeofspot) << std::endl;

    }
    fichier.close();

}



#endif // SEED_H_INCLUDED

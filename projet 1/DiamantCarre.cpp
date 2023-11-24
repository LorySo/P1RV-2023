#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include <cstdlib> //rand()

using namespace std;

// fonction pour générer un nombre aléatoire qui a pour valeur maximale le paramètre max 
int genererNombreAleatoire(int max) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int nombreAleatoire = std::rand() % (max + 1);
    return nombreAleatoire;
}

void diamantCarre(vector<vector<float>>& t) {
    int h = t.size();
    int maxh = 50; //hauteur max de la map
    /*time_t currentTime = time(nullptr);
    srand(static_cast<unsigned int>(currentTime));
    int randomNumber = rand();*/
    int randomNumber = genererNombreAleatoire(maxh);


    t[0][0] = static_cast<float>(randomNumber % (2 * maxh));      //coins
    /*currentTime = time(nullptr);
    srand(static_cast<unsigned int>(currentTime));
    randomNumber = rand();*/
    randomNumber = genererNombreAleatoire(maxh);

    t[0][h - 1] = static_cast<float>(randomNumber % (2 * maxh));
    /*currentTime = time(nullptr);
    srand(static_cast<unsigned int>(currentTime));
    randomNumber = rand();*/
    randomNumber = genererNombreAleatoire(maxh);

    t[h - 1][h - 1] = static_cast<float>(randomNumber % (2 * maxh));
    /*currentTime = time(nullptr);
      srand(static_cast<unsigned int>(currentTime));
      randomNumber = rand();*/
    randomNumber = genererNombreAleatoire(maxh);

    t[h - 1][0] = static_cast<float>(randomNumber % (2 * maxh));

    int s = h - 1;

    while (s > 1) {
        int id = s / 2;

        //diamant
        for (int i = id; i + id < h; i += s) {
            for (int j = id; j + id < h; j += s) {
                float moy = (t[i - id][j - id] + t[i - id][j + id] + t[i + id][j + id] + t[i + id][j - id]) / 4.0f;
                /*currentTime = time(nullptr);
    srand(static_cast<unsigned int>(currentTime));
    randomNumber = rand();*/
                randomNumber = genererNombreAleatoire(maxh);
                t[i][j] = moy + static_cast<float>(randomNumber % (2 * id) - id);
            }
        }

        int bruit = 0;

        //carré
        for (int i = 0; i < h; i += id) {
            if (bruit == 0) {
                bruit = id;
            }
            else {
                bruit = 0;
            }

            for (int y = bruit; y < h; y += s) {
                float som = 0.0f;
                int n = 0;

                if (i >= id) {
                    som += t[i - id][y];
                    n++;
                }

                if (i + id < h) {
                    som += t[i + id][y];
                    n++;
                }

                if (y >= id) {
                    som += t[i][y - id];
                    n++;
                }

                if (y + id < h) {
                    som += t[i][y + id];
                    n++;
                }
                time_t currentTime = time(nullptr);

                /*currentTime = time(nullptr);
     srand(static_cast<unsigned int>(currentTime));
     randomNumber = rand();*/
                randomNumber = genererNombreAleatoire(maxh);

                t[i][y] = som / n + static_cast<float>(randomNumber % (2 * id) - id);
            }
        }
        s = id;
    }
    // pour ne pas avoir de pics vers le bas, on enlève les valeurs en dessous de 0
   /* for (int i = 0; i<h; i++) {
        for (int j = 0; j < h; j++) {
            if (t[i][j] < 0) {
                t[i][j] = 0;
            }
        }
    }*/
}

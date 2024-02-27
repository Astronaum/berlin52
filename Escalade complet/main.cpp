#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <cmath>
#include <ctime>
using namespace std;

//Instance de berlin52
vector<pair<int, int>> berlin52 = {
    {565, 575}, {25, 185}, {345, 750}, {945, 685}, {845, 655}, {880, 660},
    {25, 230}, {525, 1000}, {580, 1175}, {650, 1130}, {1605, 620},
    {1220, 580}, {1465, 200}, {1530, 5}, {845, 680}, {725, 370},
    {145, 665}, {415, 635}, {510, 875}, {560, 365}, {300, 465},
    {520, 585}, {480, 415}, {835, 625}, {975, 580}, {1215, 245},
    {1320, 315}, {1250, 400}, {660, 180}, {410, 250}, {420, 555},
    {575, 665}, {1150, 1160}, {700, 580}, {685, 595}, {685, 610},
    {770, 610}, {795, 645}, {720, 635}, {760, 650}, {475, 960},
    {95, 260}, {875, 920}, {700, 500}, {555, 815}, {830, 485},
    {1170, 65}, {830, 610}, {605, 625}, {595, 360}, {1340, 725},
    {1740, 245}
};

// Calcul la distance d'un circuit
double total_distance(const vector<int>& route, const vector<pair<int, int>>& tsp_instance) {
    int n = route.size();
    double total_dist = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        auto city_i = tsp_instance[route[i]];
        auto city_j = tsp_instance[route[j]];
        total_dist += sqrt(pow(city_i.first - city_j.first, 2) + pow(city_i.second - city_j.second, 2));
    }
    return total_dist;
}

// Fonction d'escalade complet
vector<int> hill_climbing(vector<int> route, const vector<pair<int, int>>& tsp_instance, int max_iterations) {
    // Initialisation avec la route donnée en entrée
    vector<int> current_route = route;
    // Calcul de la distance totale de la route courante
    double current_distance = total_distance(current_route, tsp_instance);
    // Variable pour suivre si une amélioration a été trouvée
    bool improved = true;
    // Compteur pour le nombre d'itérations effectuées
    int iteration_count = 0;
    // Initialisation de la meilleure route et de la meilleure distance
    vector<int> best_route = current_route;
    double best_distance = current_distance;

    // Boucle jusqu'à ce qu'aucune amélioration ne soit trouvée ou que le nombre maximal d'itérations soit atteint
    while (improved && iteration_count < max_iterations) {
        // Réinitialisation du booléen pour l'itération en cours
        improved = false;

        // Boucle à travers chaque paire de villes dans la route courante
        for (int i = 0; i < current_route.size() - 1; i++) {
            for (int j = i + 1; j < current_route.size(); j++) {
                // Création d'une nouvelle route en inversant l'ordre des villes entre les indices i et j
                vector<int> neighbor = current_route;
                reverse(neighbor.begin() + i, neighbor.begin() + j + 1); //2opt
                // Calcul de la distance totale de la nouvelle route
                double neighbor_distance = total_distance(neighbor, tsp_instance);

                // Si la nouvelle route est meilleure que la route courante
                if (neighbor_distance < current_distance) {
                    // Mise à jour de la route courante et de la distance totale
                    current_distance = neighbor_distance;
                    current_route = neighbor;
                    // Indiquer qu'une amélioration a été trouvée pour cette itération
                    improved = true;
                }
            }
        }

        // Si la distance de la route courante est meilleure que la meilleure distance trouvée jusqu'à présent
        if (current_distance < best_distance) {
            // Mettre à jour la meilleure route et la meilleure distance
            best_distance = current_distance;
            best_route = current_route;
        }

        // Incrémenter le compteur d'itérations
        iteration_count++;
    }

    // Retourner la meilleure route trouvée
    return best_route;
}


int main() {

    srand(time(nullptr));
    cout << "\033[32mAlgorithme ESCALADE COMPLET (COMPLETE HILL CLIMBING)\n\033[0m" << endl;
    cout << "\033[32m-------------------Berlin52----------------------\n\033[0m" << endl;
    // Generate a random initial route
    vector<int> route(berlin52.size());
    for (int i = 0; i < route.size(); i++) {
        route[i] = i;
    }
    std::random_shuffle(route.begin(), route.end());

    // Call the hill climbing function
    int max_iterations = 1000;
    std::vector<int> solution = hill_climbing(route, berlin52, max_iterations);

    // Print the best route found
    std::cout << "Best route found:";
    for (int i : solution) {
        std::cout << " " << i;
    }
    std::cout << "\n";
    std::cout << "Total distance: \033[32m" << total_distance(solution, berlin52) << "\033[0m\n";

    return 0;
}

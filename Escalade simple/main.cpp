#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// Définition de l'instance du problème
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

//Calcul la distance totale d'un circuit
double total_distance(const vector<int>& route, const vector<pair<int, int>>& tsp_instance) {
    int n = route.size();
    double total_dist = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        pair<int, int> city_i = tsp_instance[route[i]];
        pair<int, int> city_j = tsp_instance[route[j]];
        total_dist += sqrt(pow(city_i.first - city_j.first, 2) + pow(city_i.second - city_j.second, 2));
    }
    return total_dist;
}

// La fct algo escalade simple
vector<int> simple_hill_climbing(const vector<int>& route, const vector<pair<int, int>>& tsp_instance) {
    vector<int> current_route = route;
    double current_distance = total_distance(current_route, tsp_instance);
    vector<int> best_route = current_route;
    double best_distance = current_distance;
    bool improved = true;

    while (improved) {
        improved = false;

        for (int i = 0; i < current_route.size() - 1; i++) {
            for (int j = i + 1; j < current_route.size(); j++) {
                vector<int> neighbor = current_route;
                reverse(neighbor.begin() + i, neighbor.begin() + j + 1); //2opt
                double neighbor_distance = total_distance(neighbor, tsp_instance);

                if (neighbor_distance < current_distance) {
                    current_distance = neighbor_distance;
                    current_route = neighbor;
                    improved = true;
                    break; // Retenir la première route améliorante
                }
            }
            if (improved) {
                break; // Vérifie si une amélioration est trouvé
            }
        }

        if (current_distance < best_distance) {
            best_distance = current_distance;
            best_route = current_route;
        }
    }
    return best_route; // Retourne la première route améliorante
}


int main() {

    srand(time(nullptr));
    cout << "\033[32mAlgorithme ESCALADE SIMPLE (SIMPLE HILL CLIMBING)\n\033[0m" << endl;
    cout << "\033[32m-------------------Berlin52----------------------\n\033[0m" << endl;
    // Generate a random initial route
    vector<int> route(berlin52.size());
    std::iota(route.begin(), route.end(), 0);
    std::random_shuffle(route.begin(), route.end());

    // Call the hill climbing function
    std::vector<int> solution = simple_hill_climbing(route, berlin52);

    // Print the best route found
    std::cout << "Best route found:";
    for (int i : solution) {
        std::cout << " " << i;
    }
    std::cout << "\n";
    std::cout << "Total distance: \033[32m" << total_distance(solution, berlin52) << "\033[0m\n";

    return 0;
}

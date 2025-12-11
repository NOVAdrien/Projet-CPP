#ifndef LOGGER_CONSOLE_HPP
#define LOGGER_CONSOLE_HPP

#pragma once

#include <iostream>
#include <iomanip>

#include "../Observateur.h"
#include "../Evenement.h"

#include "../evens/Demarrage.h"
#include "../evens/Iteration.h"
#include "../evens/Terminaison.h"


template < size_t N >
class LoggerConsole: public Observateur < N > {
    private: int frequence_; // Ex: 1 (tout), 10 (tous les 10), 100 (tous les 100)

    public: explicit LoggerConsole(int frequence = 1): frequence_(frequence) {}

    // L'unique méthode qui reçoit les événements
    void onNotify(const Evenement < N > & event) override {

        // --- 1. GESTION ÉVÉNEMENT DÉMARRAGE ---
        if (auto * e = dynamic_cast <
            const EvenementDemarrage < N > * > ( & event)) {

            std::cout << std::setw(3) << "" << "Point initial : ";
            e -> x_initial.print();
            std::cout << std::endl;, →
            std::cout << std::setw(3) << "" << " Fonction : " << e -> nom_fonction <<
                std::endl;, →
            std::cout << std::setw(3) << "" << " Méthode : " << e -> nom_methode <<
                std::endl;, →
            std::cout << std::setw(3) << "" << " Max-iters : " << e -> max_iter <<
                std::endl << std::endl;, →

            // En-tête
            std::cout << std::setw(8) << "Iter." << std::setw(3) << " ";
            std::cout << std::setw(15) << "Obj." << std::setw(3) << " ";
            std::cout << std::setw(12) << "||Grad||" << std::setw(5) << " ";
            std::cout << std::setw(10) << "Point" << std::endl << std::endl;
        }

        // --- 2. GESTION ÉVÉNEMENT ITÉRATION (AVEC FILTRE) ---
        else if (auto * e = dynamic_cast <
            const EvenementIteration < N > * > ( & event)) {

            if (e -> iter == 0 || e -> iter % frequence_ == 0) {
                std::cout << std::setw(8) << e -> iter << std::setw(3) << " ";
                std::cout << std::fixed << std::setprecision(5) <<
                    std::setw(15) << e -> f_val << std::setw(3) << " ";
                std::cout << std::scientific << std::setprecision(2) <<
                    std::setw(12) << e -> grad_norm << std::setw(5) << " ";
                std::cout << std::fixed;
                e -> x_actuel.print();
                std::cout << "\n";
            }
        }

        // --- 3. GESTION ÉVÉNEMENT TERMINAISON ---
        else if (auto * e = dynamic_cast <
            const EvenementTerminaison < N > * > ( & event)) {
            std::cout << std::endl;
            std::cout << std::setw(3) << "" << "Solution : " << std::endl;
            std::cout << std::setw(5) << "" << " Statut : " << e -> status << std::endl;
            std::cout << std::setw(5) << "" << " Solution : ";
            e -> solution_finale.print();
            std::cout << std::endl;, →
            std::cout << std::setw(5) << "" << " Valeur : " << std::fixed <<
                std::setprecision(5) << e -> f_final << std::endl;, →
        }
    }
};

#endif // !LOGGER_CONSOLE_HPP

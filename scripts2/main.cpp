#include <vector>
#include <array>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

#include "FonctionObjective.hpp"

using namespace std;

float f_(std::array<float, 2> x) {
    return x[0]*x[0] + 2*x[1]*x[1];
}

std::array<float,2> gradf_(std::array<float,2> x) {
    std::array<float,2> gradfx = {0, 0};

    gradfx[0] = 2*x[0];
    gradfx[0] = 4*x[1];

    return gradfx;
}

std::array<float,2> direction_realisable(const std::array<float,2>& xk)
{
    std::array<float,2> g = gradf_(xk);
    for (float& v : g) v = -v;
    return g;
}

std::array<float,2> direction_deplacement(const std::array<float,2>& xk) 
{
    return direction_realisable(xk);
}

int main (int argc, char *argv[]) {

    FonctionObjective<2> f(
        f_,
        gradf_,
        "x0² + 2*x1²"
    );

    int maxIters_ = 1000;
    std::array<float,2> x0 = {2, 5};

    // cout << f.f_(x0) << endl;

    float epsilon_ = 0.000001;
    float alpha_ = 0.1;

    std::array<float,2> xk = x0;
    int k = 0;

    std::vector<std::array<float,2>> points_;
    std::vector<float> valeurs_;
    std::vector<float> normes_grad_;

    while (k < maxIters_)
    {
        float fx = f.f_(xk);
        std::array<float,2> gk = f.gradf_(xk);

        float ng = 0;

        for (float v : gk)
        {
            ng += v * v;
        }

        ng = sqrt(ng);

        points_.push_back(xk);
        valeurs_.push_back(fx);
        normes_grad_.push_back(ng);

        if (ng <= epsilon_)
        {
            break;
        }

        std::array<float,2> dk = direction_deplacement(xk);
        float lambda = alpha_;

        for (size_t i = 0; i < xk.size(); ++i)
        {
            xk[i] += lambda * dk[i];
        }

        ++k;
    }




    const string margin = "   ";

    cout << "\n---\n";
    cout << "--- Descente de Gradient (Pas Fixe)\n";
    cout << "---\n\n";

    // ---------- SECTION INITIALE ----------
    const int labelWidth = 14;
    const int solLabelWidth = 20;

    cout << margin << right << setw(labelWidth) << "Point initial" << " :  (";

    for (size_t i = 0; i < points_[0].size(); ++i)
    {
        cout << fixed << setprecision(2) << points_[0][i];

        if (i != points_[0].size() - 1)
        {
            cout << ", ";
        }
    }
    
    cout << ")\n";

    cout << margin << right << setw(labelWidth) << "Fonction" << " : " << f.getNom() << "\n";
    cout << margin << right << setw(labelWidth+1) << "Méthode" << " : Descente Gradient\n";
    cout << margin << right << setw(labelWidth) << "Max-iters" << " : " << maxIters_ << "\n\n";

    // ---------- EN-TÊTES ITÉRATIONS ----------
    cout << margin << right;
    cout << setw(12) << "Iter.";
    cout << setw(16) << "Obj.";
    cout << setw(18) << "||Grad||";
    cout << setw(20) << "Point";
    cout << "\n";

    // ---------- LIGNES D’ITÉRATIONS ----------
    for (size_t k = 0; k < points_.size(); ++k)
    {
        if (k % 10 == 0)
        {
            cout << margin << setw(12) << k;
            cout << setw(16) << fixed << setprecision(5) << valeurs_[k];
            cout << setw(18) << scientific << setprecision(2) << normes_grad_[k];

            ostringstream pt;
            pt << "(";

            for (size_t i = 0; i < points_[k].size(); ++i)
            {
                pt << fixed << setprecision(2) << points_[k][i];
                if (i != points_[k].size() - 1)
                {
                    pt << ", ";
                }
            }

            pt << ")";
            cout << setw(20) << pt.str() << "\n";
        }
    }

    cout << endl;

    // ---------- SECTION SOLUTION ----------
    cout << "\n" << margin << "Solution : \n";
    bool convergence = normes_grad_.back() <= epsilon_;

    if (convergence)
    {
        cout << margin << setw(solLabelWidth) << right << "Statut :"
                  << " CONVERGENCE (Tolérance atteinte)\n";
    }
    else
    {
        cout << margin << setw(solLabelWidth) << right << "Statut :"
                  << " ECHEC (Max itérations atteintes)\n";
    }

    cout << margin << setw(solLabelWidth) << right << "Solution :" << " (";

    for (size_t i = 0; i < points_.back().size(); ++i)
    {
        cout << fixed << setprecision(2) << points_.back()[i];
        if (i != points_.back().size() - 1)
        {
            cout << ", ";
        }
    }

    cout << ")\n";

    cout << margin << setw(solLabelWidth) << right << "Valeur :"
              << " " << fixed << setprecision(2)
              << valeurs_.back() << "\n";
       

    return 0;
}

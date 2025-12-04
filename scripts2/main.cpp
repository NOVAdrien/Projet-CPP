#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

float f_(std::vector<float> x) {
    return x[0]*x[0] + 2*x[1]*x[1];
}

std::vector<float> grad_(std::vector<float> x) {
    std::vector<float> gradfx;

    gradfx.push_back(2*x[0]);
    gradfx.push_back(4*x[1]);

    return gradfx;
}

std::vector<float> direction_realisable(const std::vector<float>& xk)
{
    std::vector<float> g = grad_(xk);
    for (float& v : g) v = -v;
    return g;
}

std::vector<float> direction_deplacement(const std::vector<float>& xk) 
{
    return direction_realisable(xk);
}

int main (int argc, char *argv[]) {

    int maxIters_ = 1000;
    std::vector<float> x0 = {2, 5};

    float epsilon_ = 0.000001;
    float alpha_ = 0.1;

    std::vector<float> xk = x0;
    int k = 0;

    std::vector<std::vector<float>> points_;
    std::vector<float> valeurs_;
    std::vector<float> normes_grad_;

    while (k < maxIters_)
    {
        float fx = f_(xk);
        std::vector<float> gk = grad_(xk);

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

        std::vector<float> dk = direction_deplacement(xk);
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

    cout << margin << right << setw(labelWidth) << "Fonction" << " : vla la fonction\n";
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

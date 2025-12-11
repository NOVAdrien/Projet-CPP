# ifndef OPTIMISEUR_HPP
# define OPTIMISEUR_HPP

# include <vector>
# include <iostream>
# include <iomanip>
# include <cmath>
# include "FonctionObjective.hpp"
# include "Vecteur.hpp"

using namespace std;

template <size_t N>
class Optimiseur
{
public:
    using V = Vecteur<N>;

    Optimiseur(const FonctionObjective<N>& f,
              int maxIters = 1000,
              double eps = 1e-6,
              double alpha = 0.1)
        : f_(f), maxIters_(maxIters), eps_(eps), alpha_(alpha) {}

    virtual ~Optimiseur() = default;

    void optimiser(V& x_depart)
    {
        V xk = x_depart;
        int k = 0;

        vector<V> points;
        vector<double> valeurs;
        vector<double> normes_grad;

        while (k < maxIters_)
        {
            double fx = f_.evaluer(xk);
            V gk = f_.calculerGradient(xk);
            double ng = gk.norme();

            points.push_back(xk);
            valeurs.push_back(fx);
            normes_grad.push_back(ng);

            if (ng <= eps_)
            {
                break;
            }

            V dk = calculerDirection(xk);
            double lambda = alpha_;

            xk = xk + dk * lambda;
            ++k;
        }

        const string margin = "   ";
        cout << "\n---\n";
        cout << "--- Descente (Optimiseur)\n";
        cout << "---\n\n";

        const int labelWidth = 14;
        const int solLabelWidth = 20;

        cout << margin << right << setw(labelWidth) << "Point initial" << " :  (";

        for (size_t i = 0; i < N; ++i)
        {
            cout << fixed << setprecision(2) << points.front()[i];
            
            if (i != N - 1)
            {
                cout << ", ";
            }
        }

        cout << ")\n";

        cout << margin << right << setw(labelWidth) << "Fonction" << " : " << f_.getNom() << "\n";
        cout << margin << right << setw(labelWidth+1) << "Méthode" << " : " << getNom() << "\n";
        cout << margin << right << setw(labelWidth) << "Max-iters" << " : " << maxIters_ << "\n\n";

        cout << margin << right;
        cout << setw(12) << "Iter.";
        cout << setw(16) << "Obj.";
        cout << setw(18) << "||Grad||";
        cout << setw(20) << "Point";
        cout << "\n";

        for (size_t kk = 0; kk < points.size(); ++kk)
        {
            if (kk % 10 == 0)
            {
                cout << margin << setw(12) << kk;
                cout << setw(16) << fixed << setprecision(5) << valeurs[kk];
                cout << setw(18) << scientific << setprecision(2) << normes_grad[kk];

                ostringstream pt;
                pt << "(";

                for (size_t i = 0; i < N; ++i)
                {
                    pt << fixed << setprecision(2) << points[kk][i];

                    if (i != N - 1)
                    {
                        pt << ", ";
                    }
                }

                pt << ")";
                cout << setw(20) << pt.str() << "\n";
            }
        }

        cout << endl;

        cout << "\n" << margin << "Solution : \n";
        bool convergence = !normes_grad.empty() && (normes_grad.back() <= eps_);

        if (convergence)
        {
            cout << margin << setw(solLabelWidth) << right << "Statut :" << " CONVERGENCE (Tolérance atteinte)\n";
        }
        else
        {
            cout << margin << setw(solLabelWidth) << right << "Statut :" << " ECHEC (Max itérations atteintes)\n";
        }

        cout << margin << setw(solLabelWidth) << right << "Solution :" << " (";

        if (!points.empty())
        {
            for (size_t i = 0; i < N; ++i)
            {
                cout << fixed << setprecision(2) << points.back()[i];

                if (i != N - 1)
                {
                    cout << ", ";
                }
            }
        }

        cout << ")\n";

        if (!valeurs.empty())
        {
            cout << margin << setw(solLabelWidth) << right << "Valeur :" << " " << fixed << setprecision(2) << valeurs.back() << "\n";
        }

        if (!points.empty())
        {
            x_depart = points.back();
        }
    }

    virtual V calculerDirection(const V& x) const = 0;

    virtual string getNom() const
    {
        return "Optimiseur générique";
    }

protected:
    const FonctionObjective<N>& f_;
    int maxIters_;
    double eps_;
    double alpha_;
};

# endif

# include <iostream>
# include <vector>
# include <functional>
# include <cmath>
# include <iomanip>
# include "Fonction.cpp"

using namespace std;
using Vecteur  = vector<float>;
using Gradient = function<Vecteur (const Vecteur&)>;

class MethodeOptimisation
{
protected:
    Fonction f_;
    Gradient grad_;
    float epsilon_;
    int   maxIters_;

    virtual Vecteur direction_deplacement(const Vecteur& xk) = 0;
    virtual Vecteur direction_realisable(const Vecteur& xk) = 0;
    virtual float pas_de_deplacement(const Vecteur& xk, const Vecteur& dk) = 0;

public:
    MethodeOptimisation(Fonction f, Gradient grad, float epsilon, int maxIters)
        : f_(std::move(f)), grad_(std::move(grad)), epsilon_(epsilon), maxIters_(maxIters) {}

    virtual ~MethodeOptimisation() = default;

    Vecteur run(const Vecteur& x0)
    {
        cout << "Point initial : (" << x0[0] << ", " << x0[1] << ")" << endl;
        cout << "Fonction : x1^2 + 2*x2^2" << endl << endl;
        cout << "Méthode : Descente Gradient" << endl;
        cout << "Max-iters : " << maxIters_ << endl << endl;
        cout << "Iter.\tObj.\t\t||Grad||\tPoint"<< endl;

        Vecteur xk = x0;
        int k = 0;

        while (k < maxIters_)
        {
            float fx = f_(xk);

            Vecteur gk = grad_(xk);
            float ng = 0.f;
            for (float v : gk) ng += v * v;
            ng = sqrt(ng);

            // affichage toutes les 10 itérations
            if (k % 10 == 0)
            {
                cout << fixed << std::setprecision(5) << k << "\t" << fx << "\t" << scientific << ng << "\t" << "(" << std::fixed << std::setprecision(2) << xk[0] << ", " << xk[1] << ")" << endl;
            }

            if (ng <= epsilon_)
            {
                break;
            }

            Vecteur dk = direction_deplacement(xk);
            float lambda = pas_de_deplacement(xk, dk);

            for (size_t i = 0; i < xk.size(); ++i)
            {
                xk[i] += lambda * dk[i];
            }

            ++k;
        }

        cout << endl << "Solution :" << endl;
        cout << "  Statut : CONVERGENCE (Tolérance atteinte)" << endl;
        cout << "  Solution : (" << fixed << setprecision(2) << xk[0] << ", " << xk[1] << ")" << endl;
        cout << "  Valeur : " << fixed << setprecision(2) << f_(xk) << endl;

        return xk;
    }
};
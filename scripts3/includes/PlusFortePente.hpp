# ifndef PLUSFORTEPENTE_HPP
# define PLUSFORTEPENTE_HPP

# include "Optimiseur.hpp"
# include "Vecteur.hpp"
# include <string>

using namespace std;

template <size_t N>
class PlusFortePente : public Optimiseur<N>
{
public:
    using V = Vecteur<N>;

    PlusFortePente(const FonctionObjective<N>& f,
                   int maxIters = 1000,
                   double eps = 1e-6,
                   double alpha = 0.1)
        : Optimiseur<N>(f, maxIters, eps, alpha) {}

    V calculerDirection(const V& x) const override
    {
        V g = this->f_.calculerGradient(x);
        double n = g.norme();

        if (n == 0.0)
        {
            return V();
        }

        return (-1.0) * (g / n);
    }

    string getNom() const override
    {
        return "Plus Forte Pente (direction normalisée)";
    }
};

# endif

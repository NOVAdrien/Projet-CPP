# ifndef DESCENTEGRADIENT_HPP
# define DESCENTEGRADIENT_HPP

# include "Optimiseur.hpp"
# include "Vecteur.hpp"
# include <string>

using namespace std;

template <size_t N>
class DescenteGradient : public Optimiseur<N>
{
public:
    using V = Vecteur<N>;

    DescenteGradient(const FonctionObjective<N>& f,
                     int maxIters = 1000,
                     double eps = 1e-6,
                     double alpha = 0.1)
        : Optimiseur<N>(f, maxIters, eps, alpha) {}

    V calculerDirection(const V& x) const override
    {
        V g = this->f_.calculerGradient(x);

        return (-1.0) * g;
    }

    string getNom() const override
    {
        return "Descente Gradient (pas fixe)";
    }
};

# endif

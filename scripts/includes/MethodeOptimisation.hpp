# ifndef METHODE_OPTIMISATION_HPP
# define METHODE_OPTIMISATION_HPP

# include <vector>
# include <functional>
# include "Fonction.hpp"

using namespace std;

using Vecteur  = vector<float>;
using Gradient = function<Vecteur(const Vecteur&)>;

class MethodeOptimisation
{
protected:
    Fonction f_;
    Gradient grad_;
    float epsilon_;
    int maxIters_;

    vector<Vecteur> points_;
    vector<float> valeurs_;
    vector<float> normes_grad_;

    virtual Vecteur direction_realisable(const Vecteur& xk) = 0;
    virtual Vecteur direction_deplacement(const Vecteur& xk) = 0;
    virtual float pas_de_deplacement(const Vecteur& xk, const Vecteur& dk) = 0;

public:
    MethodeOptimisation(Fonction f, Gradient grad, float epsilon, int maxIters);
    virtual ~MethodeOptimisation() = default;

    Vecteur run(const Vecteur& x0);
    
    void plot() const;
};

# endif

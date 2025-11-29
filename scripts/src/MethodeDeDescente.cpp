# include <vector>

# include "MethodeOptimisation.hpp"

using namespace std;

class MethodeDescente : public MethodeOptimisation
{
private:
    float alpha_;

public:
    MethodeDescente(Fonction f, Gradient g, float eps, int maxIters, float alpha)
        : MethodeOptimisation(move(f), move(g), eps, maxIters), alpha_(alpha) {}

    Vecteur direction_realisable(const Vecteur& xk) override
    {
        Vecteur g = grad_(xk);
        for (float& v : g) v = -v;
        return g;
    }

    Vecteur direction_deplacement(const Vecteur& xk) override
    {
        return direction_realisable(xk);
    }

    float pas_de_deplacement(const Vecteur&, const Vecteur&) override
    {
        return alpha_;
    }
};
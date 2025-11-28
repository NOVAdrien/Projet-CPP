# include <vector>
# include <functional>
# include <utility>
# include "MethodeOptimisation.cpp"

using namespace std;

using Vecteur  = std::vector<float>;
using Gradient = std::function<Vecteur (const Vecteur&)>;

class MethodeDescente : public MethodeOptimisation
{
public:

    MethodeDescente(Fonction f, Gradient grad, float epsilon, int maxIters, float alpha)
        : MethodeOptimisation(move(f), move(grad), epsilon, maxIters), alpha_(alpha) {}

    // 1) Direction réalisable = -grad(xk)
    Vecteur direction_realisable(const Vecteur& xk) override
    {
        Vecteur g = grad_(xk);

        for (float &v : g)
        {
            v = -v;
        }
        
        return g;
    }

    // 2) Direction de déplacement = direction réalisable
    Vecteur direction_deplacement(const Vecteur& xk) override
    {
        return direction_realisable(xk);
    }

    // 3) Pas de déplacement = alpha (pas fixe)
    float pas_de_deplacement(const Vecteur&, const Vecteur&) override
    {
        return alpha_;
    }

    // Optionnel : une itération complète si tu veux l’utiliser séparément
    Vecteur une_iteration(const Vecteur& xk)
    {
        Vecteur d  = direction_deplacement(xk);
        float lambda = pas_de_deplacement(xk, d);

        Vecteur xkp1 = xk;

        for (size_t i = 0; i < xkp1.size(); ++i) {
            xkp1[i] += lambda * d[i];
        }

        return xkp1;
    }

private:
    float alpha_;
};
#include <iostream>
#include <iostream>
#include <vector>
#include <utility>
#include "MethodeOptimisation.hpp"



class MethodeDescente : public MethodeOptimisation {
public:

    MethodeDescente(Fonction f, Gradient grad, double alpha)
        : f(std::move(f)), grad(std::move(grad)), alpha(alpha) {}

    // 1) Direction réalisable = -grad(xk)
    std::vector<float> direction_realisable(const std::vector<float>& xk) override {
        std::vector<float> g = grad(xk);
        for (float &v : g){
            v = -v;
        }
        return g;
    }

    // 2) Direction de déplacement = direction réalisable
    std::vector<float> direction_deplacement(const std::vector<float>& xk) override {
        return direction_realisable(xk);
    }

    // 3) Pas de déplacement = alpha (pas fixe)
    double pas_de_deplacement(const std::vector<float>&, const std::vector<float>&) override {
        return alpha;
    }

    // Optionnel : une itération complète
    std::vector<float> une_iteration(const std::vector<float>& xk) {
        std::vector<float> d  = direction_deplacement(xk);
        double lambda = pas_de_deplacement(xk, d);

        std::vector<float> xkp1 = xk;
        for (std::size_t i = 0; i < xkp1.size(); ++i) {
            xkp1[i] += static_cast<float>(lambda) * d[i];
        }

        return xkp1;
    }

private:
    Fonction f;
    Gradient grad;
    double alpha;
};

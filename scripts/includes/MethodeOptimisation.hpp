# ifndef METHODE_OPTIMISATION
# define METHODE_OPTIMISATION

# include "Fonction.hpp"
# include <vector>

// Contient les méthodes privées :
// - direction_descente_realisable())
// - pas_deplacement()
// - run()

class MethodeOptimisation
{
private:
    // Attributs
    float x;
    Fonction f;
    Fonction grad;
    std::vector<float> d;

    // Méthode virtuelle
        virtual void direction_descente_realisable(const std::vector<float>& xk);

        // Méthode virtuelle pure
        virtual float pas_deplacement(const std::vector<float>& xk) = 0;

public:

    // Constructeur
    MethodeOptimisation(float x0, Fonction fonction, Fonction gradient) ;

    // Fonction run
    float run();
};

# endif

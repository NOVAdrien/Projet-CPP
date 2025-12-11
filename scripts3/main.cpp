# include <iostream>
# include <array>
# include <cmath>
# include <string>
# include <iomanip>

# include "./includes/Vecteur.hpp"
# include "./includes/FonctionObjective.hpp"
# include "./includes/DescenteGradient.hpp"
# include "./includes/PlusFortePente.hpp"

using namespace std;

// q1(x) = x1^2 + 2*x2^2
class Q1 : public FonctionObjective<2>
{
public:
    using V = Vecteur<2>;
    Q1(const string& nom = "x1^2 + 2*x2^2")
        : FonctionObjective<2>(nom) {}

    double evaluer(const V& x) const override
    {
        return x[0]*x[0] + 2.0 * x[1]*x[1];
    }

    V calculerGradient(const V& x) const override
    {
        V g;
        g[0] = 2.0 * x[0];
        g[1] = 4.0 * x[1];

        return g;
    }
};

// q2(x) = x1^2 + 2*x2^2 + 3*x3^2
class Q2 : public FonctionObjective<3>
{
public:
    using V = Vecteur<3>;
    Q2(const string& nom = "x1^2 + 2*x2^2 + 3*x3^2")
        : FonctionObjective<3>(nom) {}

    double evaluer(const V& x) const override
    {
        return x[0]*x[0] + 2.0 * x[1]*x[1] + 3.0 * x[2]*x[2];
    }

    V calculerGradient(const V& x) const override
    {
        V g;
        g[0] = 2.0 * x[0];
        g[1] = 4.0 * x[1];
        g[2] = 6.0 * x[2];

        return g;
    }
};

// r(x) = (1 - x1)^2 + 100*(x2 - x1^2)^2
class R : public FonctionObjective<2>
{
public:
    using V = Vecteur<2>;
    R(const string& nom = "(1 - x1)^2 + 100*(x2 - x1^2)^2")
        : FonctionObjective<2>(nom) {}

    double evaluer(const V& x) const override
    {
        return (1 - x[0])*(1 - x[0]) + 100.0 * (x[1] - x[0]*x[0]) * (x[1] - x[0]*x[0]);
    }

    V calculerGradient(const V& x) const override
    {
        V g;
        g[0] = -2.0 * (1 - x[0]) - 400 * x[0] * (x[1] - x[0] * x[0]);
        g[1] = 200.0 * (x[1] - x[0] * x[0]);

        return g;
    }
};

int main()
{
    // Paramètres optimisation
    int maxIters = 100;
    double epsilon = 1e-6;
    double alpha = 0.1;
    
    using V2 = Vecteur<2>;
    using V3 = Vecteur<3>;





    // ==== Fonction q1 ==== #

    // Point initial
    V2 x1;
    x1[0] = 3.0;
    x1[1] = 5.0;

    // Fonctions
    Q1 q1("x0^2 + 2*x1^2");

    // Choisir l'optimiseur : DescenteGradient (pas fixe) ou PlusFortePente
    DescenteGradient<2> optim1(q1, maxIters, epsilon, alpha);
    // PlusFortePente<2> optim1(q1, maxIters, epsilon, alpha);

    // Lancer optimisation
    optim1.optimiser(x1);





    // ==== Fonction q2 ==== #

    // Point initial
    V3 x2;
    x2[0] = 3.0;
    x2[1] = 5.0;
    x2[2] = 2.0;

    // Fonctions
    Q2 q2("x1^2 + 2*x2^2 + 3*x3^2");

    // Choisir l'optimiseur : DescenteGradient (pas fixe) ou PlusFortePente
    DescenteGradient<3> optim2(q2, maxIters, epsilon, alpha);
    // PlusFortePente<3> optim2(q2, maxIters, epsilon, alpha);

    // Lancer optimisation
    optim2.optimiser(x2);





    // ==== Fonction r ==== #

    // Point initial
    V2 x3;
    x3[0] = 0.0;
    x3[1] = 0.0;

    // Fonctions
    R r("(1 - x1)^2 + 100*(x2 - x1^2)^2");

    // Choisir l'optimiseur : DescenteGradient (pas fixe) ou PlusFortePente
    DescenteGradient<2> optim3(r, maxIters, epsilon, alpha);
    // PlusFortePente<2> optim3(r, maxIters, epsilon, alpha);

    // Lancer optimisation
    optim3.optimiser(x3);

    return 0;
}

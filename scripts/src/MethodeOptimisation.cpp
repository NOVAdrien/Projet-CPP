# include "MethodeOptimisation.hpp"

// Constructeur
MethodeOptimisation::MethodeOptimisation(float x0, Fonction fonction, Fonction gradient)
    : x(x0), f(fonction), grad(gradient) {}

// Méthode virtuelle
vector<float> MethodeOptimisation::direction_descente_realisable(vector<float> xk)
{
    float y = grad(f(xk));

    if (y = 0)
        return xk;
    return -y;
}

// Fonction run
float MethodeOptimisation::run(Fonction f0, float eps, vector<float> x0)
{
    int k = 0;
    Fonction f = f0;
    vector<float> xk = x0, zk = x0;
    vector<float> dk = 0;
    float lk = 0;
    float y = grad(f(xk));

    while (y >= eps)
    {
        dk = DirectionDescenteDeplacement(xk, f);
        lk = PasDeplacement(xk, f, dk);
        k++;
    }

    z = xk;
    
}

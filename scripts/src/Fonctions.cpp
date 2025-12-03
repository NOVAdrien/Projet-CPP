# include "Fonctions.hpp"
# include <cmath>

// q1
float q1(const Vecteur& x)
{
    return x[0]*x[0] + 2 * x[1]*x[1];
}

Vecteur grad_q1(const Vecteur& x)
{
    return { 2*x[0], 4*x[1] };
}

// q2
float q2(const Vecteur& x)
{
    return x[0]*x[0] + 2*x[1]*x[1] + 3*x[2]*x[2];
}

Vecteur grad_q2(const Vecteur& x)
{
    return { 2*x[0], 4*x[1], 6*x[2] };
}

// r (Rosenbrock)
float r(const Vecteur& x)
{
    return (1 - x[0])*(1 - x[0]) + 100*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0]);
}

Vecteur grad_r(const Vecteur& x)
{
    float dx = -2*(1 - x[0]) - 400*x[0]*(x[1]-x[0]*x[0]);
    float dy = 200*(x[1]-x[0]*x[0]);
    
    return { dx, dy };
}

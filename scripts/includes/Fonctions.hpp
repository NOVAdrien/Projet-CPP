# ifndef FONCTIONS_HPP
# define FONCTIONS_HPP

# include <vector>

using namespace std;

using Vecteur = vector<float>;

// q1(x1,x2) = x1^2 + 2*x2^2
float q1(const Vecteur& x);
Vecteur grad_q1(const Vecteur& x);

// q2(x1,x2,x3) = x1^2 + 2*x2^2 + 3*x3^2
float q2(const Vecteur& x);
Vecteur grad_q2(const Vecteur& x);

// r(x1,x2) = (1-x1)^2 + 100*(x2-x1^2)^2
float r(const Vecteur& x);
Vecteur grad_r(const Vecteur& x);

# endif

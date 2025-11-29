# include "Fonction.hpp"

using namespace std;

Fonction::Fonction(int n, FuncType f) : n_(n), f_(move(f)) {}

float Fonction::operator()(const Vecteur& x) const
{
    return f_(x);
}

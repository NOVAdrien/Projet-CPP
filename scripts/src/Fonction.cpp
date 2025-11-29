# include "Fonction.hpp"

using namespace std;

Fonction::Fonction(int n, FuncType f, const string& nom)
    : n_(n), f_(move(f)), nom_(nom) {}

float Fonction::operator()(const Vecteur& x) const
{
    return f_(x);
}

string Fonction::getNom() const
{
    return nom_;
}
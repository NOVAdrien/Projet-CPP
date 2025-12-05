# ifndef FONCTIONOBJECTIVE_HPP
# define FONCTIONOBJECTIVE_HPP

# include <string>
# include "Vecteur.hpp"

using namespace std;

template <size_t N>
class FonctionObjective
{
public:
    using V = Vecteur<N>;

    FonctionObjective(const string& nom = "") : nom_(nom) {}
    virtual ~FonctionObjective() = default;

    virtual double evaluer(const V& x) const = 0;
    virtual V calculerGradient(const V& x) const = 0;

    string getNom() const
    {
        return nom_;
    }

private:
    string nom_;
};

# endif

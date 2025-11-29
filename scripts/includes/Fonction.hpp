# ifndef FONCTION_HPP
# define FONCTION_HPP

# include <functional>
# include <vector>
# include <string>

using namespace std;
using Vecteur = vector<float>;
using FuncType = function<float(const Vecteur&)>;

class Fonction
{
private:
    int n_;
    FuncType f_;
    string nom_;

public:
    Fonction(int n, FuncType f, const string& nom = "");
    Fonction() = default;
    float operator()(const Vecteur& x) const;

    string getNom() const;
};

# endif

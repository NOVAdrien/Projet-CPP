# ifndef FONCTION_HPP
# define FONCTION_HPP

# include <functional>
# include <vector>

using namespace std;
using Vecteur = vector<float>;
using FuncType = function<float(const Vecteur&)>;

class Fonction
{
private:
    int n_;
    FuncType f_;

public:
    Fonction(int n, FuncType f);
    Fonction() = default;
    float operator()(const Vecteur& x) const;
};

# endif

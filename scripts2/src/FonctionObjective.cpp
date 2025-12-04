# include "FonctionObjective.hpp"

using namespace std;

template <size_t N>
FonctionObjective<N>::FonctionObjective(
    function<float(const array<float, N>&)> f,
    function<array<float, N>(const array<float, N>&)> gradf,
    const string& nom
)
    : f_(move(f)), gradf_(move(gradf)), nom_(nom) {}

// float FonctionObjective::operator()(const Vecteur& x) const
// {
//     return f_(x);
// }

template <size_t N>
string FonctionObjective<N>::getNom() const
{
    return nom_;
}

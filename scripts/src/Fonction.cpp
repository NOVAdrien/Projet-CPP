#include "Fonction.hpp"

Fonction::Fonction(
    int argc,
    std::function<int (std::vector<int>)> f
    // vector<int> (*gradf)(vector<int> x)
):
    n(argc),
    f(f)
    // gradf(gradf)
{}

Fonction::~Fonction() {
}



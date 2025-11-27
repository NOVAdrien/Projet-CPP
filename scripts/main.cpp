#include "Fonction.hpp"

int f (std::vector<int> x) {
    return x[0];
}

std::vector<int> gradf (std::vector<int> x) {
    std::vector<int> v(2, 0);
    return v;
}

int main (int argc, char *argv[]) {

    Fonction f1(
        2,
        f
        // gradf
    );
    


    return 0;
}

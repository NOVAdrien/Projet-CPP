#ifndef FONCTION_HPP
#define FONCTION_HPP

#include <functional>
#include <vector>

class Fonction {
public:
    Fonction(
        int argc,
        std::function<int (std::vector<int>)> f
        // vector<int> (*gradf)(vector<int> x)
    );

    Fonction(Fonction &&) = default;
    Fonction(const Fonction &) = default;
    Fonction &operator=(Fonction &&) = default;
    Fonction &operator=(const Fonction &) = default;
    ~Fonction();

    std::function<int (std::vector<int>)> f;
    // int f(std::vector<int> x);
    // vector<int> gradf(vector<int> x);

private:
    int n;
};
#endif // !FONCTION_HPP

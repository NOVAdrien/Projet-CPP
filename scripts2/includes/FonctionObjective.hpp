# ifndef FONCTION_OBJECTIVE_HPP
# define FONCTION_OBJECTIVE_HPP

# include <functional>
# include <array>
# include <string>

using namespace std;

// template <size_t N>
// using array<float, N> = array<float, N>;
//
// template <size_t N>
// using function<float(const array<float, N>&)> = function<float(const array<float, N>&)>;
//
// template <size_t N>
// using function<array<float, N>(const array<float, N>&)> = function<array<float, N>(const array<float, N>&)>;

template <size_t N>
class FonctionObjective
{
private:
    string nom_;

public:
    FonctionObjective(
        function<float(const array<float, N>&)> f,
        function<array<float, N>(const array<float, N>&)> gradf,
        const string& nom = ""
    );
    FonctionObjective() = default;
    // float operator()(const array<float, N>& x) const;

    function<float(const array<float, N>&)> f_;
    function<array<float, N>(const array<float, N>&)> gradf_;

    string getNom() const;
};

# endif

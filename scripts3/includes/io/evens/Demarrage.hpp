# ifndef EVENEMENTDemarrage
# define EVENEMENTDemarrage

# include <string>
# include <iostream>
# include "../Evenement.hpp"
# include "../../FonctionObjective.hpp"

template <size_t N>
class EvenementDemarrage<N> : public Evenement<N>
{
private:
    int maxIt;
    double eps;
    FonctionObjective<2> func;

public:
    EvenementDemarrage <N>(FonctionObjective f, int maxIters, double epsilon) : func(f), maxIt(maxIters), eps(epsilon) {}

    void display()
    {
        cout << "Appel de EvenementDemarrage." << endl;
    }

    ~EvenementDemarrage() override = default;
    
};

# endif
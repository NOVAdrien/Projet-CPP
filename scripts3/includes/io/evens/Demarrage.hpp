# ifndef EVENEMENTDemarrage
# define EVENEMENTDemarrage

# include <string>
# include <iostream>
# include "../Evenement.hpp"
# include "FonctionObjective.hpp"

template <size_t N>
class EvenementDemarrage : public Evenement<N>
{
private:
    int maxIt;
    double eps;

public:
    EvenementDemarrage(int maxIters, double epsilon) : maxIt(maxIters), eps(epsilon) {}

    void display()
    {
        cout << "Appel de EvenementDemarrage." << endl;
    }

    ~EvenementDemarrage() override = default;
    
};

# endif
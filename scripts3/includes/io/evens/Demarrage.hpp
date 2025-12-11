# ifndef EVENEMENTDemarrage
# define EVENEMENTDemarrage

# include <string>
# include <iostream>
# include "../Evenement.hpp"
# include "FonctionObjective.hpp"

class EvenementDemarrage : public Evenement
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
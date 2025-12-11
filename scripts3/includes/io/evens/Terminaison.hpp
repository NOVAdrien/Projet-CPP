# ifndef EVENEMENTTerminaison
# define EVENEMENTTerminaison

# include <string>
# include <iostream>
# include "../Evenement.hpp"

template <size_t N>
class EvenementTerminaison : public Evenement<N>
{
private:
    int maxIt;
    double eps;

public:
    EvenementTerminaison(int maxIters, double epsilon) : maxIt(maxIters), eps(epsilon) {}

    void display()
    {
        cout << "Appel de EvenementTerminaison." << endl;
    }

    ~EvenementTerminaison() override = default;
    
};

# endif

# ifndef EVENEMENTIteration
# define EVENEMENTIteration

# include <string>
# include <iostream>
# include "../Evenement.hpp"

class EvenementIteration : public Evenement
{
private:

public:
    EvenementIteration() : {}

    void display()
    {
        cout << "Appel de EvenementIteration." << endl;
    }

    ~EvenementIteration() override = default;
    
};

# endif

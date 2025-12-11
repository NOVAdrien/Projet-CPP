# ifndef EVENEMENTTerminaison
# define EVENEMENTTerminaison

# include <string>
# include <iostream>
# include "../Evenement.hpp"

class EvenementTerminaison : public Evenement
{
private:

public:
    EvenementTerminaison() : {}

    void display()
    {
        cout << "Appel de EvenementTerminaison." << endl;
    }

    ~EvenementTerminaison() override = default;
    
};

# endif

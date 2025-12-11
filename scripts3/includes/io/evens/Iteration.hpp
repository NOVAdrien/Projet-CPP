# ifndef EVENEMENTIteration
# define EVENEMENTIteration

# include <string>
# include <iostream>
# include "../Evenement.hpp"

template <size_t N>
class EvenementIteration : public Evenement<N>
{
private:

public:
    EvenementIteration() {}

    void display()
    {
        cout << "Appel de EvenementIteration." << endl;
    }

    ~EvenementIteration() override = default;
    
};

# endif

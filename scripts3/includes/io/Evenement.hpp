# ifndef EVENEMENT
# define EVENEMENT

# include <string>
# include <iostream>
# include "FonctionObjective.hpp"

using namespace std;

template <size_t N>
class Evenement
{
public:
    virtual ~Evenement() = default;
};

# endif

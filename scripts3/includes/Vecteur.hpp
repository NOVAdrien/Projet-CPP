# ifndef VECTEUR_HPP
# define VECTEUR_HPP

# include <array>
# include <cmath>
# include <ostream>
# include <cstddef>

using namespace std;

template <size_t N>
class Vecteur : public array<double, N>
{
public:
    Vecteur()
    {
        for (size_t i = 0; i < N; ++i)
        {
            (*this)[i] = 0.0;
        }
    }

    Vecteur(const double (&vals)[N])
    {
        for (size_t i = 0; i < N; ++i)
        {
            (*this)[i] = vals[i];
        }
    }

    Vecteur<N> operator+(const Vecteur<N>& v) const
    {
        Vecteur<N> r;

        for (size_t i = 0; i < N; ++i)
        {
            r[i] = (*this)[i] + v[i];
        }
        
        return r;
    }

    Vecteur<N> operator-(const Vecteur<N>& v) const
    {
        Vecteur<N> r;
        
        for (size_t i = 0; i < N; ++i)
        {
            r[i] = (*this)[i] - v[i];
        }
        
        return r;
    }

    Vecteur<N> operator*(double a) const
    {
        Vecteur<N> r;

        for (size_t i = 0; i < N; ++i)
        {
            r[i] = (*this)[i] * a;
        }
        
        return r;
    }

    Vecteur<N> operator/(double a) const
    {
        Vecteur<N> r;
        
        for (size_t i = 0; i < N; ++i)
        {
            r[i] = (*this)[i] / a;
        }
        
        return r;
    }

    double norme() const
    {
        double s = 0.0;
        
        for (size_t i = 0; i < N; ++i)
        {
            s += (*this)[i]*(*this)[i];
        }
        
        return sqrt(s);
    }
};

template <size_t N>
Vecteur<N> operator*(double a, const Vecteur<N>& v)
{
    return v * a;
}

template <size_t N>
ostream& operator<<(ostream& os, const Vecteur<N>& v)
{
    os << "(";

    for (size_t i = 0; i < N; ++i)
    {
        os << v[i];

        if (i + 1 < N)
        {
            os << ", ";
        }
    }
    
    os << ")";
    
    return os;
}

# endif

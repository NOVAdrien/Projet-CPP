# include <iostream>
# include <array>
# include <cmath>
# include <string>
# include <iomanip>
# include <vector>

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

template <size_t N>
class FonctionObjective
{
public:
    using V = Vecteur<N>;

    FonctionObjective(const string& nom = "") : nom_(nom) {}
    virtual ~FonctionObjective() = default;

    virtual double evaluer(const V& x) const = 0;
    virtual V calculerGradient(const V& x) const = 0;

    string getNom() const
    {
        return nom_;
    }

private:
    string nom_;
};

// q1(x) = x1^2 + 2*x2^2
template <size_t N>
class Q1 : public FonctionObjective<N>
{
public:
    using V = Vecteur<N>;
    Q1(const string& nom = "x1^2 + 2*x2^2")
        : FonctionObjective<N>(nom) {}

    double evaluer(const V& x) const override
    {
        return x[0]*x[0] + 2.0 * x[1]*x[1];
    }

    V calculerGradient(const V& x) const override
    {
        V g;
        g[0] = 2.0 * x[0];
        g[1] = 4.0 * x[1];

        return g;
    }
};

// q2(x) = x1^2 + 2*x2^2 + 3*x3^2
template <size_t N>
class Q2 : public FonctionObjective<N>
{
public:
    using V = Vecteur<N>;
    Q2(const string& nom = "x1^2 + 2*x2^2 + 3*x3^2")
        : FonctionObjective<N>(nom) {}

    double evaluer(const V& x) const override
    {
        return x[0]*x[0] + 2.0 * x[1]*x[1] + 3.0 * x[2]*x[2];
    }

    V calculerGradient(const V& x) const override
    {
        V g;
        g[0] = 2.0 * x[0];
        g[1] = 4.0 * x[1];
        g[2] = 6.0 * x[2];

        return g;
    }
};

// r(x) = (1 - x1)^2 + 100*(x2 - x1^2)^2
template <size_t N>
class R : public FonctionObjective<N>
{
public:
    using V = Vecteur<N>;
    R(const string& nom = "(1 - x1)^2 + 100*(x2 - x1^2)^2")
        : FonctionObjective<N>(nom) {}

    double evaluer(const V& x) const override
    {
        return (1 - x[0])*(1 - x[0]) + 100.0 * (x[1] - x[0]*x[0]) * (x[1] - x[0]*x[0]);
    }

    V calculerGradient(const V& x) const override
    {
        V g;
        g[0] = -2.0 * (1 - x[0]) - 400 * x[0] * (x[1] - x[0] * x[0]);
        g[1] = 200.0 * (x[1] - x[0] * x[0]);

        return g;
    }
};

template <size_t N>
class Optimiseur
{
public:
    using V = Vecteur<N>;

    Optimiseur(const FonctionObjective<N>& f,
              int maxIters = 1000,
              double eps = 1e-6,
              double alpha = 0.1)
        : f_(f), maxIters_(maxIters), eps_(eps), alpha_(alpha) {}

    virtual ~Optimiseur() = default;

    void optimiser(V& x_depart)
    {
        V xk = x_depart;
        int k = 0;

        vector<V> points;
        vector<double> valeurs;
        vector<double> normes_grad;

        while (k < maxIters_)
        {
            double fx = f_.evaluer(xk);
            V gk = f_.calculerGradient(xk);
            double ng = gk.norme();

            points.push_back(xk);
            valeurs.push_back(fx);
            normes_grad.push_back(ng);

            if (ng <= eps_)
            {
                break;
            }

            V dk = calculerDirection(xk);
            double lambda = alpha_;

            xk = xk + dk * lambda;
            ++k;
        }

        const string margin = "   ";
        cout << "\n---\n";
        cout << "--- Descente (Optimiseur)\n";
        cout << "---\n\n";

        const int labelWidth = 14;
        const int solLabelWidth = 20;

        cout << margin << right << setw(labelWidth) << "Point initial" << " :  (";

        for (size_t i = 0; i < N; ++i)
        {
            cout << fixed << setprecision(2) << points.front()[i];
            
            if (i != N - 1)
            {
                cout << ", ";
            }
        }

        cout << ")\n";

        cout << margin << right << setw(labelWidth) << "Fonction" << " : " << f_.getNom() << "\n";
        cout << margin << right << setw(labelWidth+1) << "Méthode" << " : " << getNom() << "\n";
        cout << margin << right << setw(labelWidth) << "Max-iters" << " : " << maxIters_ << "\n\n";

        cout << margin << right;
        cout << setw(12) << "Iter.";
        cout << setw(16) << "Obj.";
        cout << setw(18) << "||Grad||";
        cout << setw(20) << "Point";
        cout << "\n";

        for (size_t kk = 0; kk < points.size(); ++kk)
        {
            if (kk % 10 == 0)
            {
                cout << margin << setw(12) << kk;
                cout << setw(16) << fixed << setprecision(5) << valeurs[kk];
                cout << setw(18) << scientific << setprecision(2) << normes_grad[kk];

                ostringstream pt;
                pt << "(";

                for (size_t i = 0; i < N; ++i)
                {
                    pt << fixed << setprecision(2) << points[kk][i];

                    if (i != N - 1)
                    {
                        pt << ", ";
                    }
                }

                pt << ")";
                cout << setw(20) << pt.str() << "\n";
            }
        }

        cout << endl;

        cout << "\n" << margin << "Solution : \n";
        bool convergence = !normes_grad.empty() && (normes_grad.back() <= eps_);

        if (convergence)
        {
            cout << margin << setw(solLabelWidth) << right << "Statut :" << " CONVERGENCE (Tolérance atteinte)\n";
        }
        else
        {
            cout << margin << setw(solLabelWidth) << right << "Statut :" << " ECHEC (Max itérations atteintes)\n";
        }

        cout << margin << setw(solLabelWidth) << right << "Solution :" << " (";

        if (!points.empty())
        {
            for (size_t i = 0; i < N; ++i)
            {
                cout << fixed << setprecision(2) << points.back()[i];

                if (i != N - 1)
                {
                    cout << ", ";
                }
            }
        }

        cout << ")\n";

        if (!valeurs.empty())
        {
            cout << margin << setw(solLabelWidth) << right << "Valeur :" << " " << fixed << setprecision(2) << valeurs.back() << "\n";
        }

        if (!points.empty())
        {
            x_depart = points.back();
        }
    }

    virtual V calculerDirection(const V& x) const = 0;

    virtual string getNom() const
    {
        return "Optimiseur générique";
    }

protected:
    const FonctionObjective<N>& f_;
    int maxIters_;
    double eps_;
    double alpha_;
};

template <size_t N>
class DescenteGradient : public Optimiseur<N>
{
public:
    using V = Vecteur<N>;

    DescenteGradient(const FonctionObjective<N>& f,
                     int maxIters = 1000,
                     double eps = 1e-6,
                     double alpha = 0.1)
        : Optimiseur<N>(f, maxIters, eps, alpha) {}

    V calculerDirection(const V& x) const override
    {
        V g = this->f_.calculerGradient(x);

        return (-1.0) * g;
    }

    string getNom() const override
    {
        return "Descente Gradient (pas fixe)";
    }
};

template <size_t N>
class PlusFortePente : public Optimiseur<N>
{
public:
    using V = Vecteur<N>;

    PlusFortePente(const FonctionObjective<N>& f,
                   int maxIters = 1000,
                   double eps = 1e-6,
                   double alpha = 0.1)
        : Optimiseur<N>(f, maxIters, eps, alpha) {}

    V calculerDirection(const V& x) const override
    {
        V g = this->f_.calculerGradient(x);
        double n = g.norme();

        if (n == 0.0)
        {
            return V();
        }

        return (-1.0) * (g / n);
    }

    string getNom() const override
    {
        return "Plus Forte Pente (direction normalisée)";
    }
};

int main()
{
    // Paramètres optimisation
    int maxIters = 100;
    double epsilon = 1e-6;
    double alpha = 0.1;
    
    using V2 = Vecteur<2>;
    using V3 = Vecteur<3>;





    // ==== Fonction q1 ==== #

    // Point initial
    V2 x1;
    x1[0] = 3.0;
    x1[1] = 5.0;

    // Fonctions
    Q1<2> q1("x0^2 + 2*x1^2");

    // Choisir l'optimiseur : DescenteGradient (pas fixe) ou PlusFortePente
    DescenteGradient<2> optim1(q1, maxIters, epsilon, alpha);
    // PlusFortePente<2> optim1(q1, maxIters, epsilon, alpha);

    // Lancer optimisation
    optim1.optimiser(x1);





    // ==== Fonction q2 ==== #

    // Point initial
    V3 x2;
    x2[0] = 3.0;
    x2[1] = 5.0;
    x2[2] = 2.0;

    // Fonctions
    Q2<3> q2("x1^2 + 2*x2^2 + 3*x3^2");

    // Choisir l'optimiseur : DescenteGradient (pas fixe) ou PlusFortePente
    DescenteGradient<3> optim2(q2, maxIters, epsilon, alpha);
    // PlusFortePente<3> optim2(q2, maxIters, epsilon, alpha);

    // Lancer optimisation
    optim2.optimiser(x2);





    // ==== Fonction r ==== #

    // Point initial
    V2 x3;
    x3[0] = 0.0;
    x3[1] = 0.0;

    // Fonctions
    R<2> r("(1 - x1)^2 + 100*(x2 - x1^2)^2");

    // Choisir l'optimiseur : DescenteGradient (pas fixe) ou PlusFortePente
    DescenteGradient<2> optim3(r, maxIters, epsilon, alpha);
    // PlusFortePente<2> optim3(r, maxIters, epsilon, alpha);

    // Lancer optimisation
    optim3.optimiser(x3);

    return 0;
}

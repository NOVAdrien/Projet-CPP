# include <iostream>
# include "src/MethodeDeDescente.cpp"

using namespace std;

// q1(x1,x2) = x1^2 + 2 x2^2
float q1_impl(const vector<float>& x)
{
    return x[0]*x[0] + 2.f * x[1]*x[1];
}

// grad(q1(x1,x2)) = (2*x1, 4*x2)
vector<float> grad_q1_impl(const vector<float>& x)
{
    return { 2.f * x[0], 4.f * x[1] };
}

int main()
{
    // Instanciation d'une fonction
    Fonction fq1(2, q1_impl);
    Gradient gq1 = grad_q1_impl;

    vector<float> x0 = {3.f, 5.f};

    // epsilon = 1e-6, maxIters = 100, alpha = 0.1
    MethodeDescente md(fq1, gq1, 1e-6f, 100, 0.1f);

    vector<float> sol = md.run(x0);

    cout << "Solution approchée : (" << sol[0] << ", " << sol[1] << ")" << endl;

    return 0;
}
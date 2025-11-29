# include <iostream>
# include "Fonction.hpp"
# include "MethodeOptimisation.hpp"
# include "src/MethodeDeDescente.cpp"

using namespace std;

float q1(const vector<float>& x)
{
    return x[0]*x[0] + 2.f * x[1]*x[1];
}

vector<float> grad_q1(const vector<float>& x)
{
    return { 2.f * x[0], 4.f * x[1] };
}

int main()
{
    Fonction fq1(2, q1);
    Gradient gq1 = grad_q1;

    vector<float> x0 = {3.f, 5.f};

    MethodeDescente md(fq1, gq1, 1e-6f, 100, 0.1f);

    md.run(x0);
    md.plot();

    return 0;
}

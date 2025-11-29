# include <iostream>
# include "Fonctions.hpp"
# include "src/MethodeDeDescente.cpp"

int main()
{
    using Vecteur = vector<float>;

    // Exemple q1
    Fonction fq1(2, q1, "x1^2 + 2*x2^2");
    Gradient gq1 = grad_q1;
    Vecteur x0 = {3, 5};
    MethodeDescente md1(fq1, gq1, 1e-6, 100, 0.1);
    Vecteur sol1 = md1.run(x0);
    md1.print();

    // Exemple q2
    Fonction fq2(3, q2, "x1^2 + 2*x2^2 + 3*x3^2");
    Gradient gq2 = grad_q2;
    Vecteur x02 = {3, 5, 2};
    MethodeDescente md2(fq2, gq2, 1e-6, 100, 0.1);
    Vecteur sol2 = md2.run(x02);
    md2.print();

    // Exemple r
    Fonction fr(2, r, "(1-x1)^2 + 100*(x2-x1^2)^2");
    Gradient gr = grad_r;
    Vecteur x03 = {0, 0};
    MethodeDescente md3(fr, gr, 1e-6, 100, 0.001);
    Vecteur sol3 = md3.run(x03);
    md3.print();

    return 0;
}

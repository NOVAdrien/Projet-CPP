# include <vector>
# include <functional>

using namespace std;

class Fonction
{
public:
    using FuncType = function<float (const vector<float>&)>;

    Fonction(int argc, FuncType f) : n(argc), f_(move(f)) {}

    Fonction() : n(0), f_() {}

    ~Fonction() = default;

    // permet de faire : f_obj(x)
    float operator()(const vector<float>& x) const
    {
        return f_(x);
    }

private:
    int n;        // dimension (info utile si besoin)
    FuncType f_;  // la vraie fonction
};
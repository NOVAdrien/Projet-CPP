#ifndef OBSERVATEUR_HPP
#define OBSERVATEUR_HPP

#include <vector>

template <size_t N>
class Observateur {
public:
    virtual ~Observateur() = default;
    // L'unique méthode de notification (pure event-based)
    virtual void onNotify(const Evenement<N>& event) = 0;
};

#endif // !OBSERVATEUR_HPP

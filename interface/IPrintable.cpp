#include "IPrintable.h"

std::ostream &operator<<(std::ostream &os, const IPrintable &p) {
    p.print(os);
    return os;
}

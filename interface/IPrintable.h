#ifndef HOTEL_IPRINTABLE_H
#define HOTEL_IPRINTABLE_H

#include <iostream>

class IPrintable {
    friend std::ostream &operator<<(std::ostream &os, const IPrintable &p);

public:
    virtual void print(std::ostream &os) const = 0;

    virtual ~IPrintable() = default;
};


#endif //HOTEL_IPRINTABLE_H

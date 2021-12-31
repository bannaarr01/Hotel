#ifndef HOTEL_ROOMTYPE_H
#define HOTEL_ROOMTYPE_H

#include <iostream>

//Abstract
class RoomType {
protected:
    // std::string roomTypeName;
    double price;
public:
    RoomType(double price = 0.0);

    virtual std::string getRoomTypeName() const = 0;

    virtual double getPrice() const = 0;

    virtual void setPrice(double) = 0;

    virtual ~RoomType() = default;
};


#endif //HOTEL_ROOMTYPE_H

#include "RoomTypeDouble.h"

RoomTypeDouble::RoomTypeDouble(double price)
        : RoomType(price) {

}

std::string RoomTypeDouble::getRoomTypeName() const {
    return roomTypeName;
}


double RoomTypeDouble::getPrice() const {
    return price;
}

void RoomTypeDouble::setPrice(double price) {
    this->price = price;
}



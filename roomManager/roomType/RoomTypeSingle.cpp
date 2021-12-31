#include "RoomTypeSingle.h"

RoomTypeSingle::RoomTypeSingle(double price)
        : RoomType(price) {

}

std::string RoomTypeSingle::getRoomTypeName() const {
    return roomTypeName;
}

double RoomTypeSingle::getPrice() const {
    return price;
}

void RoomTypeSingle::setPrice(double price) {
    this->price = price;
}


#include "RoomTypeVip.h"

RoomTypeVip::RoomTypeVip(double price)
        : RoomType(price) {

}

std::string RoomTypeVip::getRoomTypeName() const {
    return roomTypeName;
}

double RoomTypeVip::getPrice() const {
    return price;
}

void RoomTypeVip::setPrice(double price) {
    this->price = price;
}

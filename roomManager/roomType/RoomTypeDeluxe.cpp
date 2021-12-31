
#include "RoomTypeDeluxe.h"

RoomTypeDeluxe::RoomTypeDeluxe(double price)
        : RoomType(price) {

}

std::string RoomTypeDeluxe::getRoomTypeName() const {
    return roomTypeName;
}

double RoomTypeDeluxe::getPrice() const {
    return price;
}

void RoomTypeDeluxe::setPrice(double price) {
    this->price = price;
}



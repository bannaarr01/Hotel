#include "Room.h"

Room::Room(std::string roomNumber, Room::RoomAvailabilityStatus roomAvailabilityStatus, Room::BedType bedType,
           bool isWifiEnabled, std::shared_ptr<RoomType> &roomTypePtr)
        : roomNumber{roomNumber}, roomAvailabilityStatus{roomAvailabilityStatus}, bedType{bedType},
          isWifiEnabled{isWifiEnabled}, roomTypePtr{roomTypePtr} {

}

std::string Room::getRoomNumber() const {
    return roomNumber;
}

void Room::setRoomNumber(std::string roomNo) {
    roomNumber = roomNo;
}

Room::RoomAvailabilityStatus Room::getRoomAvailabilityStatus() const {
    return roomAvailabilityStatus;
}

Room::BedType Room::getBedType() const {
    return bedType;
}

bool Room::getWifiEnabled() const {
    return isWifiEnabled;
}

void Room::setWifiEnabled(bool isWifiEnabled) {
    this->isWifiEnabled = isWifiEnabled;
}

void Room::setRoomTypeSingle(double price) {
    roomTypePtr = std::make_unique<RoomTypeSingle>(price);

}

void Room::setRoomTypeDouble(double price) {
    roomTypePtr = std::make_shared<RoomTypeDouble>(price);
}

void Room::setRoomTypeDeluxe(double price) {
    roomTypePtr = std::make_shared<RoomTypeDeluxe>(price);
}

void Room::setRoomTypeVip(double price) {
    roomTypePtr = std::make_shared<RoomTypeVip>(price);
}


void Room::setRoomAvailabilityStatus(RoomAvailabilityStatus roomAvailabilityStatus) {
    this->roomAvailabilityStatus = roomAvailabilityStatus;
}

void Room::setBedType(BedType bedType) {
    this->bedType = bedType;
}


std::shared_ptr<RoomType> Room::getRoomType() const {
    return roomTypePtr;

}

std::string Room::roomAvailabilityStatusToString(Room::RoomAvailabilityStatus roomAvailabilityStatus) const {
    std::string result;
    switch (roomAvailabilityStatus) {
        case Room::RoomAvailabilityStatus::VACANT:
            result = "Vacant";
            break;
        case Room::RoomAvailabilityStatus::OCCUPIED:
            result = "Occupied";
            break;
        case Room::RoomAvailabilityStatus::RESERVED:
            result = "Reserved";
            break;
        case Room::RoomAvailabilityStatus::UNDER_MAINTENANCE:
            result = "Under Maintenance";
            break;
    };
    return result;
}


std::string Room::bedTypeToString(Room::BedType bedType) const {
    std::string result;
    switch (bedType) {
        case Room::BedType::SINGLE:
            result = "Single";
            break;
        case Room::BedType::DOUBLE:
            result = "Double";
            break;
        case Room::BedType::MASTER:
            result = "Master";
            break;
    };
    return result;
}


void Room::print(std::ostream &os) const {
    os << roomNumber << ","
       << roomAvailabilityStatusToString(roomAvailabilityStatus)
       << "," << bedTypeToString(bedType) << "," << ((isWifiEnabled == 0) ? "No" : "Yes")
       << "," << roomTypePtr->getRoomTypeName() << "," << roomTypePtr->getPrice();
}

bool Room::operator==(const Room &rhs) const {
    return this->roomNumber == rhs.roomNumber;
}

bool Room::operator<(const Room &rhs) const {
    return this->roomNumber < rhs.roomNumber;
}















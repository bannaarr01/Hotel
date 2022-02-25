#include "Room.h"

Room::Room(std::string roomNumber, Room::RoomAvailabilityStatus roomAvailabilityStatus, Room::BedType bedType,
           bool isWifiEnabled, std::shared_ptr<RoomType> &roomTypePtr,
           std::vector<rsd::ReservedDate> reservedDates)
        : roomNumber{roomNumber}, roomAvailabilityStatus{roomAvailabilityStatus}, bedType{bedType},
          isWifiEnabled{isWifiEnabled}, roomTypePtr{roomTypePtr}, reservedDates{reservedDates} {

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
//    int n{1};
//    os << roomNumber << ","
//       << roomAvailabilityStatusToString(roomAvailabilityStatus)
//       << "," << bedTypeToString(bedType) << "," << ((isWifiEnabled == 0) ? "No" : "Yes")
//       << "," << roomTypePtr->getRoomTypeName() << "," << roomTypePtr->getPrice() << "," << "{";
//    for (auto rsd: reservedDates) {
//        os << "chIn" << n << ":" << rsd.first << "," << "chOut" << n << ":" << rsd.second << ",";
//        ++n;
//    }

    json j;
    std::vector<json> jVec;

    //rsd::ReservedDate rsv;
    os << roomNumber << "|"
       << roomAvailabilityStatusToString(roomAvailabilityStatus)
       << "|" << bedTypeToString(bedType) << "|" << ((isWifiEnabled == 0) ? "No" : "Yes")
       << "|" << roomTypePtr->getRoomTypeName() << "|" << roomTypePtr->getPrice() << "|" << "[";
    for (auto &rsv: reservedDates) {
        j["checkInDate"] = rsv.checkInDate;
        j["checkOutDate"] = rsv.checkOutDate;
        jVec.push_back(j);
    }
//    for (auto &js: jVec) {
//        os << js;
//        os << ",";
//    }
    auto it = jVec.begin();
    while (it != jVec.end()) {
        os << *it;
        it++;
        if (!(it == jVec.end()))
            os << ",";
    }
    // os << jVec;
    os << "]" << "|";


}

bool Room::operator==(const Room &rhs) const {
    return this->roomNumber == rhs.roomNumber;
}

bool Room::operator<(const Room &rhs) const {
    return this->roomNumber < rhs.roomNumber;
}

std::vector<rsd::ReservedDate> Room::getReservedDates() const {
    return reservedDates;
}

void Room::setReservedDates(rsd::ReservedDate &rsvDate) {
//    std::map<std::string, std::string> m;
//    rsd::ReservedDate rsv{checkInDate, checkOutDate};
//    json j;
//    j["checkInDate"] = rsv.checkInDate;
//    j["checkOutDate"] = rsv.checkOutDate;
    reservedDates.emplace_back(rsvDate);
    // reservedDates.insert(std::make_pair(j["checkInDate"], j["checkOutDate"]));

//    reservedDates.emplace_back(m);
}

void Room::printJsonDate(const std::map<std::string, std::string> &rv) {
    int n;
    nlohmann::json json;


    json["reservedDates"] = {
            {rv}
    };
    json.dump(4);
}

void Room::addRoomsRsvDates(std::vector<rsd::ReservedDate> &rsvDates) {
    reservedDates.clear();
    reservedDates = rsvDates;

}

//template<typename T>
//std::map<std::string, typename T::mapped_type> Room::to_string_keyed_map(const T &input) const {
//
//    std::map<std::string, typename T::mapped_type> output;
//
//    for (auto const &pair: input) {
//        output.emplace(std::to_string(pair.first), pair.second);
//    }
//
//    return output;
//
//}

















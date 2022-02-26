#ifndef HOTEL_ROOM_H
#define HOTEL_ROOM_H

#include <iostream>
#include "../../interface/IPrintable.h"
#include "../roomType/RoomType.h"
#include "../roomType/RoomTypeSingle.h"
#include "../roomType/RoomTypeDouble.h"
#include "../roomType/RoomTypeDeluxe.h"
#include "../roomType/RoomTypeVip.h"
//#include "nlohmann/json.hpp"
#include "ReservedDate.h"
#include <memory>
#include <vector>
#include <map>
#include <iomanip>
//ReservedDate
//using namespace rsd;

class Room : public IPrintable {
    // friend std::ostream operator<<(std::ostream &os, const Room &r);
public:
    enum RoomAvailabilityStatus {
        VACANT = 1, OCCUPIED = 2, RESERVED = 3, UNDER_MAINTENANCE = 4
    };
    enum BedType {
        SINGLE = 1, DOUBLE = 2, MASTER = 3
    };

    Room() = default;

    Room(std::vector<Room> &room) {
    }

    Room(std::string roomNumber, RoomAvailabilityStatus roomAvailabilityStatus, BedType bedType,
         bool isWifiEnabled, std::shared_ptr<RoomType> &roomTypePtr,
         std::vector<rsd::ReservedDate>  = std::vector<rsd::ReservedDate>());

    std::string getRoomNumber() const;

    void setRoomNumber(std::string roomNo);

    RoomAvailabilityStatus getRoomAvailabilityStatus() const;

    void setRoomAvailabilityStatus(RoomAvailabilityStatus);

    BedType getBedType() const;

    void setBedType(BedType);

    bool getWifiEnabled() const;

    void setWifiEnabled(bool);

    void setRoomTypeSingle(double);

    void setRoomTypeDouble(double);

    void setRoomTypeDeluxe(double);

    void setRoomTypeVip(double);

    std::shared_ptr<RoomType> getRoomType() const;

    std::string roomAvailabilityStatusToString(RoomAvailabilityStatus roomAvailabilityStatus) const;


    std::string bedTypeToString(BedType bedType) const;

    void setReservedDates(rsd::ReservedDate &rsvDate);

    void addRoomsRsvDates(std::vector<rsd::ReservedDate> &rsvDates);

    std::vector<rsd::ReservedDate> getReservedDates() const;

    auto updateRoomDetails() {
        return [this](RoomAvailabilityStatus newRoomAvailabilityStatus, double price,
                      bool newIsWifiEnabled) {
            roomAvailabilityStatus = newRoomAvailabilityStatus;
            roomTypePtr->setPrice(price);
            isWifiEnabled = newIsWifiEnabled;
        };
    }

    auto updateReservationDate() {
        return [this](std::vector<rsd::ReservedDate> newReservedDates) {
            reservedDates = newReservedDates;
        };
    }

    virtual void print(std::ostream &os) const override;


    auto convertToJsonFormat() const {
        nlohmann::json j;
        j["Room"] = {{"room no",      roomNumber},
                     {"status",       roomAvailabilityStatusToString(roomAvailabilityStatus)},
                     {"wifi enabled", ((isWifiEnabled == 0) ? "No" : "Yes")},
                     {"room type",    roomTypePtr->getRoomTypeName()},
                     {"price",        roomTypePtr->getPrice()}
        };

        return j.dump(4);
    }

//    auto toCsv() {
//
//        return [this]() {
//            nlohmann::json j;
//            Room r;
//            std::cout << r.roomNumber = roomNumber << ","
//               << r.roomAvailabilityStatus = roomAvailabilityStatusToString(roomAvailabilityStatus)
//               << "," << bedTypeToString(bedType) << "," << ((isWifiEnabled == 0) ? "No" : "Yes")
//               << "," << roomTypePtr->getRoomTypeName() << "," << roomTypePtr->getPrice() << ",";
//            for (auto &rsv: reservedDates) {
//                j["checkInDate"] = rsv.checkInDate;
//                j["checkOutDate"] = rsv.checkOutDate;
//            }
//            os << ",";
//    return
//
//        };
//
//    }

//    template<typename T>
//    std::map<std::string, typename T::mapped_type> to_string_keyed_map(T const &input) const;
//=========
// Move variant
//    template <typename T>
//    std::map<std::string, typename T::mapped_type> to_string_keyed_map(T && input) {
//        std::map<std::string, typename T::mapped_type> output;
//
//        for (auto & pair : input) {
//            output.emplace(std::to_string(pair.first), std::move(pair.second));
//        }
//
//        return output;
//    }

    static void printJsonDate(const std::map<std::string, std::string> &rv);

    bool operator==(const Room &rhs) const;

    bool operator<(const Room &rhs) const;

    virtual ~Room() = default;

private:
    std::string roomNumber;
    RoomAvailabilityStatus roomAvailabilityStatus;
    BedType bedType;
    bool isWifiEnabled;
    std::shared_ptr<RoomType> roomTypePtr;
    //std::map<std::string, std::string> reservedDates;
    std::vector<rsd::ReservedDate> reservedDates;
};


#endif //HOTEL_ROOM_H

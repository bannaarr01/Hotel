#ifndef HOTEL_ROOMMANAGER_H
#define HOTEL_ROOMMANAGER_H

#include "../ui/UI.h"
#include "../ioManager/IoManager.h"
#include "room/Room.h"
#include "../hotelUtil/HotelUtil.h"
#include "../exception/AlreadyExistException.h"
#include "../exception/ErrorOpeningFileException.h"
#include "../exception/ErrorWritingToFileException.h"
//#include "../roomManager/RoomManager.h"
#include "../overallManager/OverallManager.h"
#include <set>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>

//#include <memory>

class RoomManager {
    IoManager ioManager;
    std::string fileName{"../data/rooms.csv"};
    std::vector<Room> roomsObjVec;
    std::set<Room> roomsObjSet;

public:
    // void initRoomManager(Reservation);

    void roomMenu();

    Room createRoom();

    auto obtainRoomType(std::string &roomTypeNameStr, double price);

    //  void setTodayRoomStatus(Reservation);

    //publish all rooms to room vec
    bool copyCSVtoRoomObjVec(std::vector<Room> &);

    std::vector<Room> findBySearchTerm(std::string &searchTerm, std::vector<Room> &roomsObjVec);


    void updateRoom();

    void findByRoomNumber();


};


#endif //HOTEL_ROOMMANAGER_H

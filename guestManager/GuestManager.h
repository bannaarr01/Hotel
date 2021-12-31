#ifndef HOTEL_GUESTMANAGER_H
#define HOTEL_GUESTMANAGER_H

#include "../ui/UI.h"
#include "../ioManager/IoManager.h"
#include "guest/Guest.h"
#include "../overallManager/OverallManager.h"
#include "../hotelUtil/HotelUtil.h"
#include "../exception/AlreadyExistException.h"
#include "../exception/ErrorOpeningFileException.h"
#include "../exception/ErrorWritingToFileException.h"
#include <set>
#include <cctype>
#include <vector>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>


class GuestManager {
private:
    IoManager ioManager;
    std::vector<Guest> guestObjList;
    std::set<Guest> guestObjSet;
public:

    void guestMenu();

    void updateMenu();

    void searchMenu();

    void createGuess();

    std::vector<Guest> getGuessObjList() {
        return guestObjList;
    }

    std::vector<Guest> findById(std::string searchTerm);

//    bool numberOfTimes(const std::string &searchName, const std::string &searchId, const std::string &line);
//


//    Guest &operator++();

    bool copyCSVtoGuestListVec();

};

#endif //HOTEL_GUESTMANAGER_H

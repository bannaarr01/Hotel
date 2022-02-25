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
#include <functional>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class GuestManager {
private:
    IoManager ioManager;
    std::string filename{"../data/guestLists.csv"};
    const char *filenameX{"../data/guestListsX.csv"};
    std::vector<Guest> guestObjList;
    std::set<Guest> guestObjSet;
public:

    void guestMenu();

    void updateMenu();

    Guest searchMenu();

    Guest createGuess();

    void showGuests();

    std::vector<Guest> getGuessObjList() {
        return guestObjList;
    }

    std::vector<Guest> findById(std::string &searchTerm);

//    bool numberOfTimes(const std::string &searchName, const std::string &searchId, const std::string &line);
//


//    Guest &operator++();

    bool copyCSVtoGuestObjSet(std::set<Guest> &guestObjSet);

};

#endif //HOTEL_GUESTMANAGER_H

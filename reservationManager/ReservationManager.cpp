#include "ReservationManager.h"

Reservation ReservationManager::createReservation(Room &room, Guest &guest) {
//    auto newReservation = ioManager.askInputToMakeReservation();
//    reservations.push_back(newReservation);
    // Room room = checkRoom()
    //  std::vector<Room> rooms;

    Reservation newReservation{room, "2022/04/21", "2022/05/02", 1, 1, guest};
    // va_end(args);


    // std::cout << newReservation << std::endl;
//    std::string searchGuestId{newReservation.getGuest().getId().getIdNumber()};
//    std::string searchCheckInDate{newReservation.getCheckInDate()};

    std::ifstream inFile{fileName, std::ios::in};
    std::ofstream outFile{fileName, std::ios::app};
    std::string line{};
    // bool result{false};
    try {
        if (!inFile) {
            throw ErrorOpeningFileException{};
        }
        if (!outFile) {
            throw ErrorWritingToFileException{};
        }
//        while (inFile >> line) {
//            //check if the name and id exist
//            if (numberOfTimes(searchCheckInDate, searchGuestId, line))
//                result = true;
//        }
//        if (result) {
//            //if exist throw an exception
//            throw AlreadyExistException{};
//        } else {
        //if not, dereference the pointer and insert the details
        outFile << newReservation << std::endl;
        //  std::cout << "🟢 Reservation successfully created ✅" << std::endl;
        //  }
//    } catch (const AlreadyExistException ex) {
//        std::cout << ex.what() << std::endl;
    } catch (const ErrorOpeningFileException ex) {
        std::cout << ex.what() << std::endl;
    } catch (const ErrorWritingToFileException ex) {
        std::cout << ex.what() << std::endl;
    }
    //closing both files
    inFile.close();
    outFile.close();

    return newReservation;
}

//std::vector<Reservation> ReservationManager::getReservation() const {
//    return reservations;
//}

void ReservationManager::reservationMenu() {
    reservationsObjSet.clear();
    copyCsvToReservationsObjSet(reservationsObjSet);
    //Accept valid range and UI to display
    int selection = ioManager.inputValidation(1, 6, UI::reservationMenuDisplay);

    switch (selection) {
        case 1: {
            std::cout << std::string(2, '\n');
            chooseAndDisplayRooms();
            break;
        }
        case 2: {
            std::cout << std::string(2, '\n');
            UI::reservationTabularDisplay(reservationsObjSet);
            //copyCsvToReservationsObjSet(reservationsObjSet);
            break;
        }
        case 3: {
            std::cout << std::endl;
            //   searchMenu();
            break;
        }
        case 4: {
            std::cout << std::string(2, '\n');
            OverallManager::mainMenu();
            break;
        }
        case 5: {
            std::cout << std::string(2, '\n');
            std::cout << "\033[1;31mQuitting. . .[0m️";
            break;
        }

    }


}

void ReservationManager::chooseAndDisplayRooms() {
    //when out of scope and func is recalled, clear to avoid duplicate data
    roomsObjVec.clear();
    //Make copy of the csv to roomsVec
    RoomManager roomManager;
    roomManager.copyCSVtoRoomObjVec(roomsObjVec);
    if (!(roomsObjVec.empty())) {
        bool done{false};
        do {
            int numOfRooms{0};
            char more{};
            Room room;
            Guest guest;
            //Accept valid range and UI to display
            int selection = ioManager.inputValidation(1, 7, UI::reservationSubMenuDisplay);
            switch (selection) {
                case 1: {
                    guest = existingGuest();
                    //since checkRoom func is returning a room, it's then assign to room directly
                    room = checkRoom("VIP", "Vacant");
                    //create room of this type 👆🏻, passed-in guest, if exists, manage no of room Reserved, bool 2 stop if...
                    createReservation(room, guest, numOfRooms, done);
                    break;//end of case 1 of selection
                }
                case 2: {
                    std::cout << std::string(2, '\n');
                    guest = existingGuest();
                    room = checkRoom("DELUXE", "Vacant");
                    createReservation(room, guest, numOfRooms, done);
                    break;

                }
                case 3: {
                    std::cout << std::endl;
                    guest = existingGuest();
                    room = checkRoom("DOUBLE", "Vacant");
                    createReservation(room, guest, numOfRooms, done);
                    break;
                }
                case 4: {
                    std::cout << std::string(2, '\n');
                    guest = existingGuest();
                    room = checkRoom("SINGLE", "Vacant");
                    createReservation(room, guest, numOfRooms, done);
                    break;
                }
                case 5: {
                    std::cout << std::string(2, '\n');
                    reservationMenu();
                    break;
                }
                case 6: {
                    std::cout << std::string(2, '\n');
                    OverallManager::mainMenu();
                    break;
                }
                case 7: {
                    std::cout << std::endl;
                    std::cout << "\033[1;31mQuitting. . .[0m️";
                    break;
                }
            }
            std::cout << "\nAdd More Reservation? Enter (Y or N): ";
            std::cin >> more;
            if (more == 'N' || more == 'n') {
                done = true;
                reservationMenu();
            }
        } while (!done);
    } else {
        std::cout << "\033[1;31m🚨 Sorry, Room Reservation is Unavailable...Please Try again later.[0m️" << std::endl;
        reservationMenu();
    }
}


std::vector<Room> ReservationManager::findAvailableRoom(std::string &roomType, std::string &roomAvailability) {
    std::vector<Room> result;
    //If found, copy the obj and insert into result vector
    std::copy_if(roomsObjVec.begin(), roomsObjVec.end(), std::back_inserter(result),
                 [&](const Room &room) {
                     return (room.getRoomType()->getRoomTypeName() == roomType &&
                             room.roomAvailabilityStatusToString(room.getRoomAvailabilityStatus()) == roomAvailability);
                 });
    return result;
}

Room ReservationManager::checkRoom(std::string &&roomType, std::string &&roomAvailability) {
    RoomManager roomManager;
    Room room;
    bool done{false};
    do {
        std::cout << std::string(2, '\n');
        //Result of available Room type from the current room objs (of d r-value args passed in)
        result = findAvailableRoom(roomType, roomAvailability);
        if (!result.empty()) {
            //display result in tabular form if not empty
            UI::tabularDisplay(result);

            //Set the initial range of room number to select to the first available room no display
            int rangeFrom = std::stod(result.at(0).getRoomNumber());
            //Set the range to last available room no i.e, if 3 rooms is available with room no 100,200,300
            //then available input the user should input should only be valid btw 100-300
            int to = std::stod(result.at(result.size() - 1).getRoomNumber());

            //inputValidationV2 accepts the range of available room no
            int selectRoom = ioManager.inputValidationV2(rangeFrom, to);
            //convert d integer to string
            std::string ss = std::to_string(selectRoom);

            //then check the room num (String) entered by the user is the room no is valid i.e, if the room no exist
            //in the available room display
            auto rm = roomManager.findBySearchTerm(ss, result);
            //if doesn't exist i.e, Invalid
            if (rm.empty()) {
                std::cout << "\n\033[1;31m💥 Please Enter the room number correctly...[0m" << std::endl;
            } else {
                //If exist n valid, display the room the user select in tabular form
                std::cout << "\n\033[1;36m YOU HAVE CHOSEN: [0m" << std::endl;
                //since findBySearchTerm return vec, user only select one, den it's set to vec.at(0)
                //n ds tabular also receive vec as arg
                UI::tabularDisplay(rm);
                //setting the result which is in vec.at(0) to room obj
                room = rm.at(0);
                done = true;
            }
        } else {
            std::cout
                    << "\033[1;31m🚨 Sorry, No Available " << roomType
                    << " Room at the moment, check different room type![0m"
                    << std::endl;
            done = true;
            chooseAndDisplayRooms();
        }
    } while (!done);
    //return d selected room
    return room;
}


void ReservationManager::subUpdateRoom(Room &room, int n) {
    try {
        std::ofstream outFile{fileName2, std::ios::trunc};
        std::string line{};
        Room::RoomAvailabilityStatus roomAvailabilityStatus = Room::RoomAvailabilityStatus(n);

        auto iterator = roomsObjVec.begin();
        while (iterator != roomsObjVec.end()) {
            if (*iterator == room) {
                roomsObjVec.erase(iterator);
                room.setRoomAvailabilityStatus(roomAvailabilityStatus);
                roomsObjVec.push_back(room);
                std::sort(roomsObjVec.begin(), roomsObjVec.end());
                if (!outFile) {
                    throw ErrorWritingToFileException{};
                }
                for (const auto &elem: roomsObjVec)
                    outFile << elem << std::endl;
                outFile.close();
                //  std::cout << "🟢 Room updated successfully ✅" << std::endl;
//                roomMenu();
            } else
                iterator++; //only increment the iterator if not erased
        }
    } catch (ErrorWritingToFileException ex) {
        // std::cout << ex.what() << std::endl;
//        roomMenu();
    }

}


void ReservationManager::updateReservation(Reservation &reservation) {
    try {
        std::ofstream outFile{fileName, std::ios::trunc};
        std::string line{};

        auto iterator = reservations.begin();
        while (iterator != reservations.end()) {
            if (*iterator == reservation) {
                reservations.erase(iterator);
                //reservations.push_back(reservation);
                reservations.emplace_back(reservation);
                // std::sort(begin(reservations), end(reservations));
                if (!outFile) {
                    throw ErrorWritingToFileException{};
                }
                for (const auto &elem: reservations)
                    outFile << elem << std::endl;
                outFile.close();
                //  std::cout << "🟢 Room updated successfully ✅" << std::endl;
//                roomMenu();
            } else
                iterator++; //only increment the iterator if not erased
        }
    } catch (ErrorWritingToFileException ex) {
        // std::cout << ex.what() << std::endl;
    }

}

Guest ReservationManager::existingGuest() {
    GuestManager gm;
    Guest guest;
    int existingGuest = ioManager.inputValidation(1, 5, UI::existingGuestDisplay);
    switch (existingGuest) {
        case 1: {
            if (gm.copyCSVtoGuestObjSet(guestObjSet)) {
                std::cout << "✅ Search Initiated Successfully...🚀" << std::endl;
                bool done{false};
                do {
                    std::vector<Guest> result;
                    char search{};
                    std::string searchTerm{};
                    std::cout << "Enter Guest Passport / Driving License: ";
                    std::cin >> searchTerm;
                    std::transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::toupper);
                    std::copy_if(guestObjSet.begin(), guestObjSet.end(), std::back_inserter(result),
                                 [searchTerm](const Guest &g) {
                                     return (g.getId().getIdNumber() == searchTerm);
                                 });
                    if (!std::empty(result)) {
                        guest = result.at(0);
                        std::cout << "🟢 Found" << std::endl;
                        //   std::cout << result << std::endl;
                    } else
                        std::cout << "🔴 Record NOT Found. 💥 SELECT N to enter guest details or Y to search again"
                                  << std::endl;
                    std::cout << "\nSearch Again? Enter (Y or N): ";
                    std::cin >> search;
                    if (search == 'N' || search == 'n') {
                        done = true;
                    }
                } while (!done);

                // return guest;
            } else {
                std::cout << "\n🚨 Sorry! Reservation is currently unavailable for Existing Guest. check back soon..."
                          << std::endl;
                std::cout << std::endl;
                reservationMenu();
            }
            break;
        }
    }
    return guest;
}

bool ReservationManager::copyCsvToReservationsObjSet(std::set<Reservation> &reservationsObjSet) {
    std::ifstream inFile{fileName};
    std::string line{};
    std::string temp{};
    std::string word{};

    //For Reservation
    std::string reservationNumber{}, checkInDate{}, checkOutDate{}, reservationStatus{};
    int adultCount{}, childrenCount{};
    bool isCreditCardBilled{}, hasPaid{};

    //For Guest
    std::string name{}, address{}, country{}, nationality{}, gender{}, contact{}, iDType{};
    std::string idNumber{}, iDExpiryDate{}, ccHolderName{}, ccNumber{}, ccExpiryDate{}, ccCVV{};

    //For room
    std::string roomNumber{}, roomTypeName{}, roomAvailabilityStatus{}, bedType{};
    bool isWifiEnabled{};
    double price{};

    // try {
    if (!inFile) {
        return false;
        // throw ErrorOpeningFileException{};
    }
    while (std::getline(inFile, line)) {

        std::stringstream s(line);
        std::vector<std::string> reservationStrVec;
        std::string word;
        while (std::getline(s, word, ',')) {
            reservationStrVec.push_back(word);
        }

        int idTypeNo{};
        reservationNumber = reservationStrVec[0], roomNumber = reservationStrVec[1],
        roomAvailabilityStatus = reservationStrVec[2], bedType = reservationStrVec[3],
        isWifiEnabled = reservationStrVec[4] == "Yes", roomTypeName = reservationStrVec[5],
        price = std::stod(reservationStrVec[6]),
        checkInDate = reservationStrVec[7], checkOutDate = reservationStrVec[8],
        reservationStatus = reservationStrVec[9], adultCount = std::stod(reservationStrVec[10]),
        childrenCount = std::stod(reservationStrVec[11]),

        name = reservationStrVec[12], address = reservationStrVec[13], country = reservationStrVec[14],
        nationality = reservationStrVec[15], gender = reservationStrVec[16], contact = reservationStrVec[17],
        iDType = reservationStrVec[18] == "Driving License" ? idTypeNo = 2 : idTypeNo = 1,
        idNumber = reservationStrVec[19], iDExpiryDate = reservationStrVec[20],
        ccHolderName = reservationStrVec[21], ccNumber = reservationStrVec[22], ccExpiryDate = reservationStrVec[23],
        ccCVV = reservationStrVec[24], isCreditCardBilled = reservationStrVec[25] == "1",
        hasPaid = reservationStrVec[26] == "1";


        IdDetails id2{IdDetails::IDType(idTypeNo), idNumber, iDExpiryDate};
        CreditCardDetails c3{ccHolderName, ccNumber, ccExpiryDate, ccCVV};
        std::unique_ptr<Guest> guest = std::make_unique<Guest>(name, address, country, nationality, gender, contact,
                                                               id2, c3);
        //Obtain the integer value of both enum specified
        int num1 = obtainRoomAvailabilityStatus(roomAvailabilityStatus);
        int num2 = obtainBedType(bedType);
        Room::RoomAvailabilityStatus roomAvailStatus = Room::RoomAvailabilityStatus(num1);
        Room::BedType bedType = Room::BedType(num2);
        //Retrieving a shared Pointer to RoomType
        RoomManager rm;
        std::shared_ptr<RoomType> roomType = rm.obtainRoomType(roomTypeName, price);
        std::unique_ptr<Room> obtainedRoom = std::make_unique<Room>(roomNumber, roomAvailStatus, bedType,
                                                                    isWifiEnabled, roomType);
        //
        int num3 = obtainReservationStatus(reservationStatus);
        Reservation::ReservationStatus reserveStatus = Reservation::ReservationStatus(num3);

        Reservation obtainedReservation{*obtainedRoom, checkInDate, checkOutDate, adultCount, childrenCount, *guest,
                                        isCreditCardBilled, hasPaid, reserveStatus, reservationNumber};
        //Store each of the reservation in reservationsObjSet
        reservationsObjSet.emplace(obtainedReservation);
    }

    return true;
}

std::set<Reservation>
ReservationManager::getGuestReservation(Guest &guest, std::set<Reservation> &reservationsObjSet) {
    std::set<Reservation> res;

    std::copy_if(reservationsObjSet.begin(), reservationsObjSet.end(), std::inserter(res, res.end()),
                 [&](const Reservation &r) {
                     return (r.getGuest() == guest);//this compare d guest ID as defined in guest class with overload==
                 });
    return res;
}

void ReservationManager::createReservation(Room &room, Guest &guest, int &numOfRooms, bool &done) {
    GuestManager gm;
    Reservation newReservation;
    //don't bother to create guest nor reservation if no available room for this room type
    if (!(room.getRoomNumber().empty())) {
        //If the guest exists, use the guest info in d system to create reservation : else input guest info
        (guest.getId().getIdNumber()).empty() ? guest = gm.createGuess() : guest;
        //
        //Even though err was made with selection of Exist guest or Not, this checking will still capture
        if (!(guest.getId().getIdNumber()).empty()) {
            auto rs = getGuestReservation(guest, reservationsObjSet);
            if (!std::empty(rs)) {
                for (const auto &r: rs) {
                    //If checking date yyyy-mm-dd minus today's date is > 1, increment d room number
                    if (differenceDatesInDays(r.getCheckInDate()) >= 1) {
                        numOfRooms += 1;
                    }
                }
            }
        }//check the guest reservation record for reserved room that has not been checked-In Yet
        //
        if (numOfRooms > 2) {
            std::cout << std::string(2, '\n');
            std::cout
                    << "\033[1;31mSorry! Unable to complete operation. Reservation limit has been reached....[0m"
                    << std::endl;
            done = true;
            reservationMenu();
        }
        //create a new reservation
        newReservation = createReservation(room, guest);
        if (!(newReservation.getReservationNumber().empty())) {
            //Update the reservation Set, In case of further reservation while new CopyFromCsv Not Updated Yet
            reservationsObjSet.emplace(newReservation);
            std::cout << "🟢 Reservation Created Successfully ✅" << std::endl;
            //update and override Room file
            subUpdateRoom(room);
        } else
            std::cerr << "Sorry! Your Reservation could not be completed ! Try again later..."
                      << std::endl;
    }
}





//TO ADD MORE ROOMS TO JUST MADE RESERVATION
/*
 *
//                bool done{false};
//                do {
//                    while (numOfRooms < 4) {
//                        int option = ioManager.inputValidation(1, 5, UI::reservationOptionDisplay);
////                        if (numOfRooms == 3) {
////                            std::cout << std::string(2, '\n');
////                            std::cout
////                                    << "\033[1;31mSorry! Cannot add room. Reservation limit has been reached....[0m"
////                                    << std::endl;
////                            reservationMenu();
////                        }
//                        switch (option) {
//                            case 1: {
//                                ++pos;
//                                //if user select add more rooms, then add ds and check the position if not Empty n create reservation
//                                rooms.emplace_back(checkRoom("VIP", "Vacant"));
//                                //if no available room, then don't create reservation nor guest
//                                if (!(rooms.at(pos).getRoomNumber().empty())) {
//                                    // guests.emplace_back(gm.createGuess());
////                            createReservation(rooms, guests);
//                                    // subUpdateRoom(rooms.at(pos));
//                                    newReservation.addRoom(rooms.at(pos));
//                                    std::cout << "🟢 " << newReservation << " ✅" << std::endl;
//                                    rsv = newReservation;
//                                    subUpdateRoom(rooms.at(pos));
//                                    updateReservation(rsv);
//                                    numOfRooms = rsv.getRooms().size();
//                                }
//                                break;
//                            }
//                            case 2: {
//                                std::cout << std::string(2, '\n');
//                            }
//                        }
//                    }
//                    done = true;
//                } while (!done);
 */




#include "ReservationManager.h"


void ReservationManager::createReservation(Room &room, Guest &guest) {
//    auto newReservation = ioManager.askInputToMakeReservation();
//    reservations.push_back(newReservation);
    // Room room = checkRoom()
    //  std::vector<Room> rooms;

    Reservation newReservation{room, "01/03/22", "01/05/22", 1, 1, guest};
    // va_end(args);


    std::cout << newReservation << std::endl;
    std::string searchGuestId{newReservation.getGuestDetails().getId().getIdNumber()};
    std::string searchCheckInDate{newReservation.getCheckInDate()};

    std::ifstream inFile{fileName, std::ios::in};
    std::ofstream outFile{fileName, std::ios::app};
    std::string line{};
    bool result{false};
    try {
        if (!inFile) {
            throw ErrorOpeningFileException{};
        }
        if (!outFile) {
            throw ErrorWritingToFileException{};
        }
        while (inFile >> line) {
            //check if the name and id exist
            if (numberOfTimes(searchCheckInDate, searchGuestId, line))
                result = true;
        }
        if (result) {
            //if exist throw an exception
            throw AlreadyExistException{};
        } else {
            //if not, dereference the pointer and insert the details
            outFile << newReservation << std::endl;
            std::cout << "🟢 Reservation successfully created ✅" << std::endl;
        }
    } catch (const AlreadyExistException ex) {
        std::cout << ex.what() << std::endl;
    } catch (const ErrorOpeningFileException ex) {
        std::cout << ex.what() << std::endl;
    } catch (const ErrorWritingToFileException ex) {
        std::cout << ex.what() << std::endl;
    }
    //closing both files
    inFile.close();
    outFile.close();
}

std::vector<Reservation> ReservationManager::getReservation() const {
    return reservations;
}

void ReservationManager::reservationMenu() {
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
            //   updateMenu();
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
            OverallManager::mainMenu();
            break;
        }

    }


}

void ReservationManager::chooseAndDisplayRooms() {
    //Make copy of the csv to roomsVec
    RoomManager roomManager;
    bool isRoomsAvailable = roomManager.copyCSVtoRoomObjVec(roomsObjVec);
    if (isRoomsAvailable == true) {
        GuestManager gm;
        Guest guest;
        Room room;
        //Accept valid range and UI to display
        int selection = ioManager.inputValidation(1, 7, UI::reservationSubMenuDisplay);
        switch (selection) {
            case 1: {
                room = checkRoom("VIP", "Vacant");
                if (!(room.getRoomNumber().empty())) {
                    guest = gm.createGuess();
                    createReservation(room, guest);
                }
                break;
            }
            case 2: {
                std::cout << std::string(2, '\n');
                room = checkRoom("DELUXE", "Vacant");
                if (!(room.getRoomNumber().empty())) {
                    guest = gm.createGuess();
                    createReservation(room, guest);
                }

            }
            case 3: {
                std::cout << std::endl;
                checkRoom("DOUBLE", "Vacant");
                break;
            }
            case 4: {
                std::cout << std::string(2, '\n');
                checkRoom("SINGLE", "Vacant");
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
    } else {
        std::cout << "🚨 Sorry, Room Reservation is unAvailable...Please Try again later." << std::endl;
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
        auto result = findAvailableRoom(roomType, roomAvailability);
        if (!result.empty()) {
            UI::tabularDisplay(result);

            int rangeFrom = std::stod(result.at(0).getRoomNumber());
            int to = std::stod(result.at(result.size() - 1).getRoomNumber());

            int selectRoom = ioManager.inputValidationV2(rangeFrom, to);
            std::string ss = std::to_string(selectRoom);

            auto rm = roomManager.findBySearchTerm(ss, result);
            if (rm.empty()) {
                std::cout << "\n\033[1;31m💥 Please Enter the room number correctly...[0m" << std::endl;
            } else {
                std::cout << "\n\033[1;36m YOU HAVE CHOSEN: [0m" << std::endl;
                UI::tabularDisplay(rm);
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
    return room;
}


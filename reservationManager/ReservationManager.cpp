#include "ReservationManager.h"

Reservation ReservationManager::createReservation(std::vector<Room> &rooms, std::vector<Guest> &guests) {
//    auto newReservation = ioManager.askInputToMakeReservation();
//    reservations.push_back(newReservation);
    // Room room = checkRoom()
    //  std::vector<Room> rooms;

    Reservation newReservation{rooms, "01/03/22", "01/05/22", 1, 1, guests};
    // va_end(args);


    std::cout << newReservation << std::endl;
    std::string searchGuestId{newReservation.getGuests()[0].getId().getIdNumber()};
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

    return newReservation;
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
    //when out of scope and func is recalled, clear to avoid duplicate data
    roomsObjVec.clear();
    //Make copy of the csv to roomsVec
    RoomManager roomManager;
    roomManager.copyCSVtoRoomObjVec(roomsObjVec);
    if (!(roomsObjVec.empty())) {
        GuestManager gm;
        Reservation newReservation;
        Reservation rsv;
        std::vector<Room> rooms;
        std::vector<Guest> guests;
        int pos{0};
//        std::string reservationNumber{};
        //Accept valid range and UI to display
        int selection = ioManager.inputValidation(1, 7, UI::reservationSubMenuDisplay);
        switch (selection) {
            case 1: {
                //since checkRoom func is returning a room, it's then insert to rooms vec directly
                rooms.emplace_back(checkRoom("VIP", "Vacant"));
                if (!(rooms.at(0).getRoomNumber().empty())) {
                    guests.emplace_back(gm.createGuess());
                    newReservation = createReservation(rooms, guests);
                    reservations.emplace_back(newReservation);
                    //update and override file
                    subUpdateRoom(rooms.at(0));
//                    reservationMenu();
                }
                size_t numOfRooms{};
                bool done{false};
                do {
                    if (numOfRooms == 3) {
                        done = true;
                        std::cout << "Sorry u can't add more rooms" << std::endl;
                        //x reservationMenu();
                    }
                    while (numOfRooms < 3) {
                        int option = ioManager.inputValidation(1, 5, UI::reservationOptionDisplay);
                        switch (option) {
                            case 1: {
                                std::cout << std::string(2, '\n');
                                ++pos;
                                //if user select add more rooms, then add ds and check the position if not Empty n create reservation
                                rooms.emplace_back(checkRoom("VIP", "Vacant"));
                                //if no available room, then don't create reservation nor guest
                                if (!(rooms.at(pos).getRoomNumber().empty())) {
                                    // guests.emplace_back(gm.createGuess());
//                            createReservation(rooms, guests);
                                    // subUpdateRoom(rooms.at(pos));
                                    newReservation.addRoom(rooms.at(pos));
                                    std::cout << "🟢 " << newReservation << " ✅" << std::endl;
                                    rsv = newReservation;
                                    subUpdateRoom(rooms.at(pos));
                                    updateReservation(rsv);
                                    numOfRooms = rsv.getRooms().size();
                                }
                                break;
                            }
                            case 2: {
                                std::cout << std::string(2, '\n');
                            }
                        }
                    }
                } while (!done);
                if (!(newReservation.getReservationNumber().empty()))
                    std::cout << "🟢 Reservation Created Successfully ✅" << std::endl;
                break;//end of case 1 of selection
            }
            case 2: {
                std::cout << std::string(2, '\n');
                rooms.emplace_back(checkRoom("DELUXE", "Vacant"));
                if (!(rooms.at(0).getRoomNumber().empty())) {
                    guests.emplace_back(gm.createGuess());
                    createReservation(rooms, guests);
                }
                break;

            }
            case 3: {
                std::cout << std::endl;
                rooms.emplace_back(checkRoom("DOUBLE", "Vacant"));
                if (!(rooms.at(0).getRoomNumber().empty())) {
                    guests.emplace_back(gm.createGuess());
                    createReservation(rooms, guests);
                }
                break;
            }
            case 4: {
                std::cout << std::string(2, '\n');
                rooms.emplace_back(checkRoom("SINGLE", "Vacant"));
                if (!(rooms.at(0).getRoomNumber().empty())) {
                    guests.emplace_back(gm.createGuess());
                    createReservation(rooms, guests);
                }
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
        std::cout << "\033[1;31m🚨 Sorry, Room Reservation is unAvailable...Please Try again later.[0m️" << std::endl;
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
                reservations.push_back(reservation);
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
//        roomMenu();
    }

}








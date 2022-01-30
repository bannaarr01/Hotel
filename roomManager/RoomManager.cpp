#include "RoomManager.h"

void RoomManager::roomMenu() {
    roomsObjVec.clear();
    copyCSVtoRoomObjVec(roomsObjVec);
    //Accept valid range and UI to display
    int selection = ioManager.inputValidation(1, 6, UI::roomMenuDisplay);
    //control the valid selection made
    switch (selection) {
        case 1: {
            //Create New Room
            std::cout << std::endl;
            createRoom();
            break;
        }
        case 2: {
            //Find a Room
            findByRoomNumber();
            std::cout << std::endl;

            break;
        }
        case 3: {
            //Show All Rooms
            bool done{false};
            try {
                do {
                    char select{};
                    std::cout << std::endl;
                    UI::tabularDisplay(roomsObjVec);
                    std::cout << "Enter Y to go back to Room Menu: ";
                    std::cin >> select;
                    if (select == 'Y' || select == 'y') {
                        done = true;
                        roomMenu();
                    } else {
                        throw InvalidEntryException{};
                    }
                } while (!done);
            } catch (InvalidEntryException ex) {
                std::cout << ex.what() << std::endl;
                roomMenu();
            }
        }
            break;
        case 4: {
            //Update a Room
            std::cout << std::endl;
            updateRoom();
            break;
        }
        case 5: {
            //Back to Main Menu
            std::cout << std::endl;
            OverallManager::mainMenu();
            break;
        }
        case 6: {
            std::cout << std::endl;
            std::cout << "\033[1;31mQuitting. . .[0m️";
            break;
        }
    }

}

Room RoomManager::createRoom() {
    auto newRoom = ioManager.askInputAndCreateNewRoom();
    std::string searchRoomNumber{newRoom.getRoomNumber()};
    //File Handling
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
            if (numberOfTimes(searchRoomNumber, line))
                result = true;
        }
        if (result) {
            //if exist throw an exception
            throw AlreadyExistException{};
        } else {
            //if not, dereference the pointer and insert the details
            outFile << newRoom << std::endl;
            std::cout << "🟢 Room successfully created ✅" << std::endl;
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

    return newRoom;
}

std::vector<Room> RoomManager::findBySearchTerm(std::string &searchTerm, std::vector<Room> &roomsObjVec) {
    std::vector<Room> result;
    //If found, copy the obj and insert into result vector
    std::copy_if(roomsObjVec.begin(), roomsObjVec.end(), std::back_inserter(result),
                 [searchTerm](const Room &room) {
                     return (room.getRoomNumber() == searchTerm);
                 });
    return result;
}


void RoomManager::updateRoom() {
    std::cout << "Enter Room Number: ";
    std::string roomNumber{};
    std::getline(std::cin, roomNumber);
    auto result = findBySearchTerm(roomNumber, roomsObjVec);
    if (!std::empty(result)) {
        Room foundRoom;
        std::cout << "🟢 Found Room " << roomNumber << ". Make your Selection ☑️" << std::endl;
        foundRoom = result.at(0);
        std::cout << foundRoom.convertToJsonFormat() << std::endl;

        int selection = ioManager.inputValidation(1, 4, UI::updateRoomMenuDisplay);
        switch (selection) {
            case 1: {
                try {
                    std::ofstream outFile{fileName, std::ios::trunc};
                    std::string line{};

                    auto iterator = roomsObjVec.begin();
                    while (iterator != roomsObjVec.end()) {
                        if (*iterator == foundRoom) {
                            roomsObjVec.erase(iterator);
                            Room::RoomAvailabilityStatus roomAvailabilityStatus = Room::RoomAvailabilityStatus(3);
                            auto update = foundRoom.updateRoomDetails();
                            update(roomAvailabilityStatus, 101.35, false);
                            roomsObjVec.push_back(foundRoom);
                            std::sort(roomsObjVec.begin(), roomsObjVec.end());
                            if (!outFile) {
                                throw ErrorWritingToFileException{};
                            }
                            for (const auto &elem: roomsObjVec)
                                outFile << elem << std::endl;
                            outFile.close();
                            std::cout << "🟢 Room updated successfully ✅" << std::endl;
                            roomMenu();
                        } else
                            iterator++; //only increment the iterator if not erased
                    }
                } catch (ErrorWritingToFileException ex) {
                    std::cout << ex.what() << std::endl;
                    roomMenu();
                }
                break;
            }
            case 2: {
                roomMenu();
                break;
            }
            case 3: {
                OverallManager::mainMenu();
                break;
            }
            case 4: {
                std::cout << "\033[1;31mQuitting. . .[0m️";
                break;
            }
        }
        //   foundRoom = result.at(0);
//            std::cout << foundRoom.convertToJsonFormat() << std::endl;
    } else {
        std::cout << "🔴 Room " << roomNumber << " NOT Found. Cannot UPDATE 💥" << std::endl;
        roomMenu();
    }

}


void RoomManager::findByRoomNumber() {
    bool done{false};
    do {
        char search{};
        std::cout << "Enter Room Number: ";
        std::string roomNumber{};
        std::getline(std::cin, roomNumber);
        auto result = findBySearchTerm(roomNumber, roomsObjVec);
        if (!std::empty(result)) {
            Room foundRoom;
            std::cout << "🟢 Found Room " << std::endl;
            foundRoom = result.at(0);
            std::cout << foundRoom.convertToJsonFormat() << std::endl;
        } else
            std::cout << "🔴 Room NOT Found!" << std::endl;
        std::cout << "Search Again? Enter (Y or N): ";
        std::cin >> search;
        std::cin.ignore();
        if (search == 'N' || search == 'n') {
            done = true;
            //End search and return to guest menu
            roomMenu();
        }
    } while (!done);

}


//Get Room type Name by returning a shared pointer to the room type
auto RoomManager::obtainRoomType(std::string &roomTypeNameStr, double price) {
    std::shared_ptr<RoomType> roomType;
    if (roomTypeNameStr == "VIP")
        roomType = std::make_shared<RoomTypeVip>(price);
    else if (roomTypeNameStr == "DELUXE")
        roomType = std::make_shared<RoomTypeDeluxe>(price);
    else if (roomTypeNameStr == "DOUBLE")
        roomType = std::make_shared<RoomTypeDouble>(price);
    else if (roomTypeNameStr == "SINGLE")
        roomType = std::make_shared<RoomTypeSingle>(price);

    return roomType;
}


bool RoomManager::copyCSVtoRoomObjVec(std::vector<Room> &roomsObjVec) {
    std::ifstream inFile{fileName};//RoomList csv
    std::string line{};
    std::string word{};

    std::string roomNumber{}, roomTypeName{}, roomAvailabilityStatus{}, bedType{}, isWifiEnabled{};
    std::string price{};

    if (!inFile) {
        return false;
    }
    //while reading line by line
    while (std::getline(inFile, line)) {
        std::stringstream s(line);
        //getting each word after comma ,and insert into the vector
        std::vector<std::string> roomStrVec;
        std::string word;
        while (std::getline(s, word, ',')) {
            roomStrVec.push_back(word);
        }
        //retrieving each line columns
        roomNumber = roomStrVec[0], roomAvailabilityStatus = roomStrVec[1], bedType = roomStrVec[2],
        isWifiEnabled = roomStrVec[3], roomTypeName = roomStrVec[4], price = roomStrVec[5];

        //Obtain the integer value of both enum specified
        int num1 = obtainRoomAvailabilityStatus(roomAvailabilityStatus);
        int num2 = obtainBedType(bedType);
        bool setWifi;
        //set wi-fi obtained string to bool
        isWifiEnabled == "Yes" ? setWifi = true : setWifi = false;

        Room::RoomAvailabilityStatus roomAvailabilityStatus = Room::RoomAvailabilityStatus(num1);
        Room::BedType bedType = Room::BedType(num2);

        //convert string to double
        double valueOfPrice = std::stod(price);

        //Retrieving a shared Pointer to RoomType
        auto roomType = obtainRoomType(roomTypeName, valueOfPrice);

        //Creating Capturing each room into a unique pointer
        std::unique_ptr<Room> newRoom = std::make_unique<Room>(roomNumber, roomAvailabilityStatus, bedType,
                                                               setWifi, roomType);

        //Insert into vector of Room Object
        roomsObjVec.emplace_back(std::move(*newRoom));
    }//destroy when out of scope, restart until end of all line
    return true;
}




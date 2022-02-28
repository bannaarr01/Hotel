#include "ReservationManager.h"

//Reservation
//ReservationManager::initReservation(Room &room, Guest &guest, std::string &checkInDate, std::string &checkOutDate,
//                                    int &adultCount, int &childrenCount) {
////    auto newReservation =ioManager.iskInputToMakeReservation();
//    Reservation newReservation{room, checkInDate, checkInDate, adultCount, childrenCount, guest};
//
//    std::ofstream outFile{fileName, std::ios::app};
//    std::string line{};
//    try {
//        if (!outFile) {
//            throw ErrorWritingToFileException{};
//        }
//        outFile << newReservation;
//    } catch (const ErrorWritingToFileException &ex) {
//        std::cout << ex.what() << std::endl;
//    }
//
//    outFile.close();
//
//    return newReservation;
//}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

void ReservationManager::reservationMenu() {
    if (!copyCsvToReservationsObjSet(reservationsObjSet)) {
        std::cout << "\033[1;31m🚨 An error has occurred...Please Try again later.[0m️" << std::endl;
        OverallManager::mainMenu();
    }

    //Accept valid range and UI to display
    int selection = ioManager.inputValidation(1, 6, UI::reservationMenuDisplay);

    switch (selection) {
        case 1: {
            std::cout << std::string(2, '\n');
            //Choose and Display Rooms and Additionally make a reservation
            chooseAndDisplayRooms();
            break;
        }
        case 2: {
            std::cout << std::string(2, '\n');
            //Display all active reservations in tabular form
            printReservations();
            break;
        }
        case 3: {
            std::cout << std::endl;
            //Manage Existing Reservation
            manageReservation();
            break;
        }
        case 4: {
            std::cout << std::string(2, '\n');
            //Payment Menu
            PaymentManager pm;
            pm.paymentMenu();
            break;
        }
        case 5: {
            std::cout << std::string(2, '\n');
            //Go back to Main Menu
            OverallManager::mainMenu();
            break;
        }
        case 6: {
            std::cout << std::endl << std::endl;
            //Stop and Exit the System
            std::cout << "\033[1;31mQuitting. . .[0m️";
            break;
        }
    }


}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

std::map<std::string, std::string> ReservationManager::checkRoomDates(Room &room) {
    std::map<std::string, std::string> dates;
    std::string checkInDate, checkOutDate;
    bool doneWithDate{false};
    do {
        checkInDate = ioManager.validateDate("CheckIn-Date");
        bool doneWithCOutDate{false};
        do {
            checkOutDate = ioManager.validateDate("CheckOut-Date");
            int diff = reservationDiffDatesInDays(checkInDate, checkOutDate);
            if (diff > 30)
                std::cout
                        << "\n\033[1;31mYou can only reserve a room for maximum 30 days. Enter another check out date"
                        << std::endl;
            else if (diff >= 1)
                doneWithCOutDate = true;
            else
                std::cout
                        << "\n\033[1;31mYour reservation must be for one (1) Night at least. Enter another check out date"
                        << std::endl;
            //std::cout << diff << " days" << std::endl;
        } while (!doneWithCOutDate);

        //If NOT overlap with any reserved date for the Room then insert d dates to the map
        if (checkOverlap(room, checkInDate, checkOutDate)) {
            doneWithDate = true;
            dates.insert(std::make_pair("checkInDate", checkInDate));
            dates.insert(std::make_pair("checkOutDate", checkOutDate));
        } else {
            std::cout
                    << "\nTherefore, the selected room is \033[1;31mUNAVAILABLE[0m on the chosen Date."
                    << std::endl << std::endl << std::endl;

            std::cout << "[1;36mMAKE A SELECTION[0m" << std::endl;
            std::cout << "1. Check Another Date For This Room" << std::endl;
            std::cout << "2. Go Back to Check Another Room" << std::endl;
            int selection = ioManager.inputValidationV2(1, 2);
            if (selection == 2) {
                chooseAndDisplayRooms();
            }


        }

    } while (!doneWithDate);


    return dates;
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
            Room room;
            Guest guest;
            //Accept valid range and UI to display
            int selection = ioManager.inputValidation(1, 7, UI::reservationSubMenuDisplay);
            switch (selection) {
                case 1: {
                    //since checkRoom func is returning a room, it's then assign to room directly
                    room = checkRoom(DEF_VIP, DEF_STATUS_VACANT);
                    std::cout << "\033[1;36mENTER DATE BELOW TO CHECK ROOM #" << room.getRoomNumber()
                              << " AVAILABILITY[0m \n" << std::endl;
                    // Transfer ⇢ control to check dates of the room passed in
                    auto checkedRoomDates = checkRoomDates(room);
                    //The selected cIn and cOut date returned
                    std::string checkInDate = checkedRoomDates[DEF_CHECK_IN_DATE];
                    std::string checkOutDate = checkedRoomDates[DEF_CHECK_OUT_DATE];
                    //check number of guest for this room
                    int adultCount = ioManager.guestCount(GuestCount::VIP_ADULT_MAX, DEF_ADULT);
                    int childrenCount = ioManager.guestCount(GuestCount::VIP_CHILDREN_MAX, DEF_CHILDREN);
                    //Check Guest if Exists or register new guest
                    guest = existingGuest();
                    //create reservation
                    createReservation(room, guest, numOfRooms, checkInDate, checkOutDate, adultCount, childrenCount,
                                      done);
                    //Add cIn and cOut dates to update this room
                    subUpdateRoom(room, checkInDate, checkOutDate);

                    break;//end of case 1 of selection
                }
                case 2: {
                    std::cout << std::endl;
                    //DELUXE ROOM
                    room = checkRoom(DEF_DELUXE, DEF_STATUS_VACANT);
                    std::cout << "\033[1;36mENTER DATE BELOW TO CHECK ROOM #" << room.getRoomNumber()
                              << " AVAILABILITY[0m \n" << std::endl;
                    auto checkedRoomDates = checkRoomDates(room);
                    std::string checkInDate = checkedRoomDates[DEF_CHECK_IN_DATE];
                    std::string checkOutDate = checkedRoomDates[DEF_CHECK_OUT_DATE];
                    int adultCount = ioManager.guestCount(GuestCount::DELUXE_ADULT_MAX, DEF_ADULT);
                    int childrenCount = ioManager.guestCount(GuestCount::DELUXE_CHILDREN_MAX, DEF_CHILDREN);
                    guest = existingGuest();
                    createReservation(room, guest, numOfRooms, checkInDate, checkOutDate, adultCount, childrenCount,
                                      done);
                    subUpdateRoom(room, checkInDate, checkOutDate);
                    break;

                }
                case 3: {
                    std::cout << std::endl;
                    //DOUBLE ROOM
                    room = checkRoom(DEF_DOUBLE, DEF_STATUS_VACANT);
                    std::cout << "\033[1;36mENTER DATE BELOW TO CHECK ROOM #" << room.getRoomNumber()
                              << " AVAILABILITY[0m \n" << std::endl;
                    auto checkedRoomDates = checkRoomDates(room);
                    std::string checkInDate = checkedRoomDates[DEF_CHECK_IN_DATE];
                    std::string checkOutDate = checkedRoomDates[DEF_CHECK_OUT_DATE];
                    int adultCount = ioManager.guestCount(GuestCount::DOUBLE_ADULT_MAX, DEF_ADULT);
                    int childrenCount = ioManager.guestCount(GuestCount::DOUBLE_CHILDREN_MAX, DEF_CHILDREN);
                    guest = existingGuest();
                    createReservation(room, guest, numOfRooms, checkInDate, checkOutDate, adultCount, childrenCount,
                                      done);
                    subUpdateRoom(room, checkInDate, checkOutDate);
                    break;
                }
                case 4: {
                    std::cout << std::endl;
                    //SINGLE ROOM
                    room = checkRoom(DEF_SINGLE, DEF_STATUS_VACANT);
                    std::cout << "\033[1;36mENTER DATE BELOW TO CHECK ROOM #" << room.getRoomNumber()
                              << " AVAILABILITY[0m \n" << std::endl;
                    auto checkedRoomDates = checkRoomDates(room);
                    std::string checkInDate = checkedRoomDates[DEF_CHECK_IN_DATE];
                    std::string checkOutDate = checkedRoomDates[DEF_CHECK_OUT_DATE];
                    int adultCount = ioManager.guestCount(GuestCount::SINGLE_ADULT_MAX, DEF_ADULT);
                    int childrenCount = ioManager.guestCount(GuestCount::SINGLE_CHILDREN_MAX, DEF_CHILDREN);
                    guest = existingGuest();
                    createReservation(room, guest, numOfRooms, checkInDate, checkOutDate, adultCount, childrenCount,
                                      done);
                    subUpdateRoom(room, checkInDate, checkOutDate);
                    break;
                }
                case 5: {
                    std::cout << std::endl;
                    reservationMenu();
                    //checkOverlap();
                    break;
                }
                case 6: {
                    std::cout << std::endl;
                    OverallManager::mainMenu();
                    break;
                }
                case 7: {
                    std::cout << std::endl;
                    std::cout << "\033[1;31mQuitting. . .[0m️";
                    break;
                }
            }

            std::cout << "\nAdd More Reservation ? " << std::endl;
            std::cout << "1. YES\n2. NO";
            int addMore = ioManager.inputValidationV2(1, 2);
            if (addMore == 2) {
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
    std::vector<Room> resultRm;
    //If found, copy the obj and insert into result vector
    std::copy_if(roomsObjVec.begin(), roomsObjVec.end(), std::back_inserter(resultRm),
                 [&](const Room &room) {
                     return (room.getRoomType()->getRoomTypeName() == roomType &&
                             room.roomAvailabilityStatusToString(room.getRoomAvailabilityStatus()) == roomAvailability);
                 });
    return resultRm;
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


void ReservationManager::subUpdateRoom(Room &room, std::string &checkInDate, std::string &checkOutDate) {
    try {
        std::ofstream outFile{fileName2, std::ios::trunc};
        std::string line{};
        auto iterator = roomsObjVec.begin();
        while (iterator != roomsObjVec.end()) {
            if (*iterator == room) {
                auto oldRsDates = room.getReservedDates();
                roomsObjVec.erase(iterator);
                //room.setReservedDates(checkInDate, checkOutDate);
                rsd::ReservedDate rsv{checkInDate, checkOutDate};
                oldRsDates.emplace_back(rsv);
                auto update = room.updateReservationDate();
                update(oldRsDates);
                roomsObjVec.push_back(room);
                std::sort(roomsObjVec.begin(), roomsObjVec.end());
                if (!outFile) {
                    throw ErrorWritingToFileException{};
                }
                for (const auto &elem: roomsObjVec)
                    outFile << elem << std::endl;
                outFile.close();
                iterator = roomsObjVec.end();
            } else {
                iterator++; //only increment the iterator if...
            }

        }
    } catch (ErrorWritingToFileException &ex) {
        // std::cout << ex.what() << std::endl;
//        roomMenu();
    }


}


bool ReservationManager::checkOverlap(Room &room, std::string &checkInDate, std::string &checkOutDate) {
    std::vector<mlp::Interval> reservedDates;
    double cInDate;
    double cOutDate;
    auto theSelectedRoomReservedDates = room.getReservedDates();
    if (!(theSelectedRoomReservedDates.empty())) {
        for (auto &rsvD: theSelectedRoomReservedDates) {
            cInDate = std::stod(rsvD.checkInDate);
            cOutDate = std::stod(rsvD.checkOutDate);
            reservedDates.emplace_back(mlp::Interval{static_cast<long>(cInDate), static_cast<long>(cOutDate)});
        }
    }
    cInDate = std::stod(checkInDate);
    cOutDate = std::stod(checkOutDate);
    reservedDates.emplace_back(mlp::Interval{static_cast<long>(cInDate), static_cast<long>(cOutDate)});
    //Display Conflicting
    if (!(mlp::displayConflicting(reservedDates))) {
        return true;
    }

    return false;
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
                    std::vector<Guest> resultGs;
                    char search{};
                    std::string searchTerm{};
                    std::cout << "Enter Guest Passport / Driving License: ";
                    std::cin >> searchTerm;
                    std::transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::toupper);
                    std::copy_if(guestObjSet.begin(), guestObjSet.end(), std::back_inserter(resultGs),
                                 [searchTerm](const Guest &g) {
                                     return (g.getId().getIdNumber() == searchTerm);
                                 });
                    if (!std::empty(resultGs)) {
                        auto dGuest = resultGs.at(0);
                        guest = dGuest;
                        std::cout << "🟢 Guest Record Found" << std::endl;
                        //   std::cout << result << std::endl;
                    } else
                        std::cout
                                << "\n\033[1;31m🔴 Record NOT Found.💥[0m" << std::endl;

                    std::cout << "\n\033[1;36mSEARCH AGAIN ? :[0m" << std::endl;
                    std::cout << "1. YES : Search Again\n2. INPUT New Guest Details\n3. GO Back to Previous Menu"
                              << std::endl;
                    int options = ioManager.inputValidationV2(1, 2);
                    if (options == 2) {
                        done = true;
                        //The create reservation function checks n create new Guest when this return null
                    }
                    if (options == 3) {
                        done = true;
                        reservationMenu();
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
        case 2: {
            //create new guest
            auto newGuestDetails = gm.createGuess();
            guest = newGuestDetails;
            break;
        }
        case 3: {
            //Go back to Reservation
            reservationMenu();
            break;
        }
        case 4: {
            //Go back to Main Menu
            OverallManager::mainMenu();
            break;
        }
        case 5: {
            std::cout << "\033[1;31mQuitting. . .[0m️" << std::endl;
            break;
        }
    }
    return guest;
}

bool ReservationManager::copyCsvToReservationsObjSet(std::set<Reservation> &reservationsObjSt) {
    std::ifstream inFile{fileName};
    std::string line{};
    std::string temp{};
    std::string word{};

    //For Reservation
    std::string reservationNumber{}, checkInDate{}, checkOutDate{}, reservationStatus{};
    double adultCount{}, childrenCount{};
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
        iDType = reservationStrVec[18],
        idNumber = reservationStrVec[19], iDExpiryDate = reservationStrVec[20],
        ccHolderName = reservationStrVec[21], ccNumber = reservationStrVec[22], ccExpiryDate = reservationStrVec[23],
        ccCVV = reservationStrVec[24], isCreditCardBilled = reservationStrVec[25] == "1",
        hasPaid = reservationStrVec[26] == "1";


        iDType == "Driving License" ? idTypeNo = 2 : idTypeNo = 1;
        IdDetails id2{IdDetails::IDType(idTypeNo), idNumber, iDExpiryDate};
        CreditCardDetails c3{ccHolderName, ccNumber, ccExpiryDate, ccCVV};
        std::unique_ptr<Guest> guest = std::make_unique<Guest>(name, address, country, nationality, gender, contact,
                                                               id2, c3);
        //Obtain the integer value of both enum specified
        int num1 = obtainRoomAvailabilityStatus(roomAvailabilityStatus);
        int num2 = obtainBedType(bedType);
        auto roomAvailStatus = Room::RoomAvailabilityStatus(num1);
        auto bedTyp = Room::BedType(num2);
        //Retrieving a shared Pointer to RoomType
        // RoomManager rm;
        std::shared_ptr<RoomType> roomType = RoomManager::obtainRoomType(roomTypeName, price);
        std::unique_ptr<Room> obtainedRoom = std::make_unique<Room>(roomNumber, roomAvailStatus, bedTyp,
                                                                    isWifiEnabled, roomType);
        //
        int num3 = obtainReservationStatus(reservationStatus);
        auto reserveStatus = Reservation::ReservationStatus(num3);
        Reservation obtainedReservation{*obtainedRoom, checkInDate, checkOutDate, static_cast<int>(adultCount),
                                        static_cast<int>(childrenCount), *guest, reservationNumber,
                                        isCreditCardBilled, hasPaid, reserveStatus};
        //Store each of the reservation in reservationsObjSet
        reservationsObjSt.emplace(obtainedReservation);
    }

    return true;
}

std::set<Reservation>
ReservationManager::getGuestReservation(Guest &guest, std::set<Reservation> &reservationsObjSt) {
    std::set<Reservation> res;

    std::copy_if(reservationsObjSt.begin(), reservationsObjSt.end(), std::inserter(res, res.end()),
                 [&](const Reservation &r) {
                     return (r.getGuest() == guest);//this compare d guest ID as defined in guest class with overload==
                 });
    return res;
}

void ReservationManager::createReservation(Room &room, Guest &guest, int &numOfRooms, std::string &checkInDate,
                                           std::string &checkOutDate,
                                           int &adultCount, int &childrenCount, bool &done) {

    std::ofstream outFile{fileName, std::ios::app};
    std::string line{};
    GuestManager gm;
    //Reservation newReservation;
    //don't bother to create guest nor reservation if no available room for this room type
    if (!(room.getRoomNumber().empty())) {
        //If the guest exists, use the guest info in d system to create reservation : else input guest info By calling
        //createGuest
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
            done = true; //END D LOOP of creating More rooms when number of Booked room is 3
            reservationMenu();
        }
        //create a new reservation
        // newReservation = initReservation(room, guest, checkInDate, checkOutDate, adultCount, childrenCount);

        // Generate reservation UUID
        boost::uuids::uuid u = boost::uuids::random_generator()();
        //Change the UUID to string
        std::string rsvNumber = boost::uuids::to_string(u);
        //Create New Reservation
        Reservation newReservation{room, checkInDate, checkOutDate, adultCount, childrenCount, guest, rsvNumber};


        if (!(newReservation.getReservationNumber().empty())) {
            try {
                if (!outFile) {
                    throw ErrorWritingToFileException{};
                }
                //Update the reservation Set, In case of further reservation while new CopyFromCsv Not Updated Yet
                reservationsObjSet.emplace(newReservation);
                std::cout << "\n🟢 Reservation Created Successfully ✅" << std::endl;
                std::cout << "Your Reservation Reference / ID: " << newReservation.getReservationNumber() << std::endl
                          << std::endl;
                outFile << newReservation;
            } catch (const ErrorWritingToFileException &ex) {
                std::cout << ex.what() << std::endl;
            }
            outFile.close();

            std::cout << "\033[1;33mReservation will be deleted if not Paid within 24 hours[0m\n" << std::endl;
            int select = ioManager.inputValidation(1, 2, UI::reservationPaymentOptionDisplay);
            if (select == 1) {
                PaymentManager m;
                m.processPayment(newReservation);
            } else if (select == 2) {
                reservationMenu();
            }
        } else
            std::cerr << "Sorry! Your Reservation could not be completed ! Try again later..."
                      << std::endl;
    }
}

void ReservationManager::manageReservation() {
    int selection = ioManager.inputValidation(1, 7, UI::reservationManagementDisplay);
    switch (selection) {
        case 1: {
            break;
        }
    }
}

std::vector<Reservation>
ReservationManager::findReservation(std::string &rsvId, std::unique_ptr<std::set<Reservation>> rsvObjSet) {
    if (rsvObjSet == nullptr)
        rsvObjSet = std::move(std::make_unique<std::set<Reservation>>(reservationsObjSet));

    auto reservationsObjSt = *rsvObjSet;
    std::vector<Reservation> resultRsv;
    std::copy_if(reservationsObjSt.begin(), reservationsObjSt.end(), std::back_inserter(resultRsv),
                 [&](const Reservation &rsv) {
                     return (rsv.getReservationNumber() == rsvId);
                 });
    return resultRsv;
}


//std::vector<Room> ReservationManager::findAvailableRoom(std::string &roomType, std::string &roomAvailability) {
//    std::vector<Room> resultRm;
//    //If found, copy the obj and insert into result vector
//    std::copy_if(roomsObjVec.begin(), roomsObjVec.end(), std::back_inserter(resultRm),
//                 [&](const Room &room) {
//                     return (room.getRoomType()->getRoomTypeName() == roomType &&
//                             room.roomAvailabilityStatusToString(room.getRoomAvailabilityStatus()) == roomAvailability);
//                 });
//    return resultRm;
//}

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
    } catch (ErrorWritingToFileException &ex) {
        // std::cout << ex.what() << std::endl;
    }

}

void ReservationManager::printReservations() {
    UI::reservationTabularDisplay(reservationsObjSet);
    std::cout << "[1;36mMAKE A SELECTION[0m" << std::endl;
    std::cout << "1. Go Back to Previous Menu" << std::endl;
    std::cout << "2. Go Back to Main Menu" << std::endl;
    int selection = ioManager.inputValidationV2(1, 2);
    if (selection == 1) {
        std::cout << std::endl << std::endl;
        reservationMenu();
    } else if (selection == 2) {
        std::cout << std::endl << std::endl;
        OverallManager::mainMenu();
    }
}

void ReservationManager::updateReservationCreditCard() {

}

void ReservationManager::updateReservationRoom() {

}

void ReservationManager::updateReservationGuestInfo() {

}

void ReservationManager::pintExpiredReservations() const {

}

void ReservationManager::confirmReservationStatus() {

}

void ReservationManager::changeReservationPaymentStatus() {

}












//TO ADD MORE ROOMS TO JUST MADE RESERVATION INSTEAD OF ONE RESERVATION AT A TIME
/*
 *
//                bool done{false};
//                do {
//                    while (numOfRooms < 4) {
//                        int option =ioManager.inputValidation(1, 5, UI::reservationOptionDisplay);
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




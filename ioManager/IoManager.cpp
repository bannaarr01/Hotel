#include "IoManager.h"
#include "../reservationManager/ReservationManager.h"

//Accept range of valid input and also accept a void function (UI) to display and return valid selection made
int IoManager::inputValidation(const int &rangeFrom, const int &to, const std::function<void()> &func) {
    int selection{};
    std::string entry{};
    bool done{false};
    do {
        try {
            func();//Void function that display menu
            std::cin >> entry;
            std::istringstream validator{entry};

            if (validator >> selection && (selection >= rangeFrom && selection <= to))
                done = true;
            else
                throw InvalidEntryException{};

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } catch (InvalidEntryException &ex) {
            std::cout << ex.what() << std::endl;
        }
    } while (!done);

    return selection; //return selection
}


int IoManager::inputValidationV2(const int &rangeFrom, const int &to) {
    int selection{};
    std::string entry{};
    bool done{false};
    do {
        try {
            std::cout << std::setw(30) << std::setfill('=') << "" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << "Enter " << rangeFrom << "-" << to << " to select: ";
            std::cin >> entry;
            std::istringstream validator{entry};

            if (validator >> selection && (selection >= rangeFrom && selection <= to))
                done = true;
            else
                throw InvalidEntryException{};

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } catch (InvalidEntryException &ex) {
            std::cout << ex.what() << std::endl;
        }
    } while (!done);

    return selection; //return selection
}

Guest IoManager::askInputToCreateNewGuest() {
    std::string name{"John Curly"};
//    std::string idNumber{"D2569095"};
    std::string idNumber{};
    std::cout << "Enter ID Number (Passport / Driving License): ";
    std::cin >> idNumber;
    std::string address{"301 Royal street"};
    std::string country{"London"};
    std::string nationality{"English"};
    std::string gender{"male"};
    std::string contact{"1234556950"};
    int iDType{2};
    // std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    std::transform(idNumber.begin(), idNumber.end(), idNumber.begin(), ::toupper);
    CreditCardDetails c{"Frank", "374245455400126", "2025", "567"};
    IdDetails id{IdDetails::IDType(iDType), idNumber, "9999"};

    Guest newGuest{name, address, country, nationality, gender, contact, id, c};

    return newGuest;
}

Room IoManager::askInputAndCreateNewRoom() {
    //to be modify for input request
    double price{95.57};
    std::string roomNumber{"106"};
    bool isWifiEnabled{false};
    int n{1};
    auto roomAvailabilityStatus = Room::RoomAvailabilityStatus(4);
    auto bedType = Room::BedType(3);
    std::shared_ptr<RoomType> rrr = std::make_shared<RoomTypeVip>(price);

    std::unique_ptr<Room> newRoom = std::make_unique<Room>(roomNumber, roomAvailabilityStatus, bedType, isWifiEnabled,
                                                           rrr);
//    std::cout << *rm << std::endl;
    return *newRoom;
}

Reservation IoManager::askInputToMakeReservation() {
    //to be modify for input request
    std::shared_ptr<RoomType> rrr = std::make_shared<RoomTypeVip>(93.55);
    Room rm{"123", Room::RoomAvailabilityStatus::VACANT, Room::BedType::MASTER, true,
            rrr};
    IdDetails id{IdDetails::IDType(1), "D2569090", "2025"};
    CreditCardDetails cc{"John", "443567890324567890", "05/25", "455"};
    std::unique_ptr<Guest> guest = std::make_unique<Guest>("John Doe", "12 Habebe str", "Kuala Lumpur", "Malaysia",
                                                           "male",
                                                           "0123994564", id, cc);

    // std::vector<Reservation> reservation;
    //Reservation rsv{rm, "01/03/22", "01/05/22", 1, 1, *guest};

    return Reservation();
}

std::string IoManager::validateDate(const std::string &title) {
    std::string validDateStr;
    std::string userInputDate;
    bool done{false};
    do {
        try {
            std::cout << "\033[1;35mEnter " << title << " format ex: "
                      << to_iso_extended_string(boost::gregorian::day_clock::universal_day()) << " (YYYY-MM-DD): [0m️";
            std::cin >> userInputDate;
            userInputDate.erase(remove(userInputDate.begin(), userInputDate.end(), '-'), userInputDate.end());
            boost::gregorian::date dateObj(boost::gregorian::from_undelimited_string(userInputDate));
//            if (differenceDatesInDays(userInputDate) < 0) {
            if ((dateObj - boost::gregorian::day_clock::universal_day()).days() < 0) {
                std::cout << "\033[1;31mDate cannot be in the past. Enter valid date[0m" << std::endl;
            } else {
                done = true;
                validDateStr = userInputDate;
                //  std::cout << "✅" << std::endl;
            }
        } catch (...) {
            std::cout << "\033[1;31mInvalid Date Entry. Follow the format given (YYYY-MM-DD) with valid Date[0m️"
                      << std::endl;
        }
    } while (!done);
    return validDateStr;
}

int IoManager::guestCount(const int &max, const std::string &name) {
    ReservationManager rm;
    int validFrom{1};
    int selection{};
    std::string entry{};
    bool done{false};
    do {
        std::cout << "\nEnter the TOTAL number of " << name << " for this reservation : ";
        std::cin >> entry;
        std::istringstream validator{entry};
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (validator >> selection && (selection >= validFrom && selection <= max))
            done = true;
        else {
            std::cout << "\n\033[1;31m🚨 Sorry, This room type ONLY allow Minimum of " << validFrom << " and Max of "
                      << max << " " << name << "[0m️"
                      << std::endl;


            std::cout << "\n1. Adjust the number of " << name << "\n2. Check another suitable room type"
                      << std::endl;
            int options = inputValidationV2(1, 2);
            if (options == 2) {
                done = true;
                rm.chooseAndDisplayRooms();
            }
        }

    } while (!done);

    return selection;
}






#include "IoManager.h"

//Accept range of valid input and also accept a void function (UI) to display and return valid selection made
int IoManager::inputValidation(const int rangeFrom, const int to, std::function<void()> func) {
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
        } catch (InvalidEntryException ex) {
            std::cout << ex.what() << std::endl;
        }
    } while (!done);

    return selection; //return selection
}


Guest IoManager::askInputToCreateNewGuest() {
    std::string name{"Moe Curly"};
    std::string idNumber{"D2569093"};
    std::string address{"301 Royal street"};
    std::string country{"London"};
    std::string nationality{"English"};
    std::string gender{"male"};
    std::string contact{"1234556950"};
    int iDType{2};
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
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
    Room::RoomAvailabilityStatus roomAvailabilityStatus = Room::RoomAvailabilityStatus(4);
    Room::BedType bedType = Room::BedType(3);
    std::shared_ptr<RoomType> rrr = std::make_shared<RoomTypeVip>(price);

    std::unique_ptr<Room> newRoom = std::make_unique<Room>(roomNumber, roomAvailabilityStatus, bedType, isWifiEnabled,
                                                           rrr);
//    std::cout << *rm << std::endl;
    return std::move(*newRoom);
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
    Reservation rsv{rm, "01/03/22", "01/05/22", 1, 1, *guest};

    return rsv;
}



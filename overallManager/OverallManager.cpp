#include "OverallManager.h"


void OverallManager::mainMenu() {
    IoManager ioManager;
    std::cout << "\033[1;46m \033[1;30m⭐️⭐️ WELCOME TO NEW DAWN INN 🏨 ⭐️⭐️\033[0m️" << std::endl;
    //Accepting Range of valid Input and UI to display
    int selection = ioManager.inputValidation(1, 6, UI::Launch);
    std::cout << std::string(2, '\n');
    switch (selection) {
        case 1: {
            //Initiate Guest Manager
            GuestManager guestManager;
            guestManager.guestMenu();
            break;
        }
        case 2: {
            //Initiate Reservation Manager
            ReservationManager reservationManager;
            reservationManager.reservationMenu();
            break;
        }
        case 3: {
            //Initiate Room Manager
            RoomManager roomManager;
            roomManager.roomMenu();
            break;
        }
//        case 4: {
//            //Check-In
//            RoomManager roomManager;
//            roomManager.roomMenu();
//            break;
//        }
//        case 5: {
//            //Check-Out
//            RoomManager roomManager;
//            roomManager.roomMenu();
//            break;
//        }
        case 6: {
            std::cout << "\033[1;31mQuitting. . .[0m️";
            break;

        }
    }


}

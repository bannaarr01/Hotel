#include "UI.h"

//=======================UI HEADER========================================================================
//Header - DRY [Don't repeat yourself]
//Accept width of == displayed, title of the menu and list of menu to display
void UI::header(const int totalWidth, const std::string title, const std::string range,
                std::vector<std::string> listToDisplay) {
    std::cout << std::setw(totalWidth) << std::setfill('=') << "" << std::endl;
    std::cout << std::setfill(' ');
    //Centre title amidst == based on total width given
    std::cout << std::setw((totalWidth - title.length()) / 2) << std::right << "" << "\033[1;36m" + title + "[0m️"
              << std::endl;
    std::cout << std::setw(totalWidth) << std::setfill('=') << "" << std::endl;
    std::cout << std::setfill(' ');
    //track number of list passed-in
    int count{};
    //Display the list passed-in and increment the count to be displayed in-front of each Menu list
    for (const auto lst: listToDisplay) {
        std::cout << ++count << ". " << lst << "\n";
    }
    std::cout << std::setw(totalWidth) << std::setfill('=') << "" << std::endl;
    std::cout << std::setfill(' ');
    //display the range passed-in
    std::cout << "Enter " + range + " to select: ";
}
//========================END OF UI HEADER=================================================================



//========================MAIN MENU UI=====================================================================
void UI::Launch() {
    const int totalWidth{35};
    std::vector<std::string> listsToDisplay{"MANAGE GUEST", "RESERVATION", "ROOM MANAGEMENT", "CHECK-IN",
                                            "CHECK-OUT", "\033[1;31mEXIT ➡️[0m️"};
    header(totalWidth, "MAIN MENU", "1-6", listsToDisplay);
}
//========================END OF MAIN MENU UI==============================================================




//========================GUEST UI=========================================================================
void UI::guestMenuDisplay() {
    const int totalWidth{30};
    std::vector<std::string> listsToDisplay{"Create Guest", "Update Guest", "Search Guest", "Delete Guest",
                                            "\033[1;36mMAIN MENU[0m️ ⬅"};
    header(totalWidth, "GUEST MENU", "1-5", listsToDisplay);
}

void UI::guestSubMenuDisplay() {
    const int totalWidth{30};
    std::vector<std::string> listsToDisplay{"Update Name", "Full Address and Contact", "Credit Card Details",
                                            "\033[1;36mGUEST MENU[0m️ ⬅", "\033[1;36mMAIN MENU[0m️ ⬅"};
    header(totalWidth, "UPDATE GUEST INFORMATION", "1-5", listsToDisplay);
}
//========================END OF GUEST UI==================================================================



//========================ROOM UI==========================================================================
void UI::roomMenuDisplay() {
    const int totalWidth{30};
    std::vector<std::string> listsToDisplay{"Create Room", "Find a Room", "Show All Rooms", "Update Room",
                                            "\033[1;36mMAIN MENU[0m️ ⬅", "\033[1;31mEXIT ➡️[0m️"};
    header(totalWidth, "ROOM MENU", "1-6", listsToDisplay);
}

void UI::updateRoomMenuDisplay() {
    const int totalWidth{30};
    std::vector<std::string> listsToDisplay{"Update Room Details and Status",
                                            "\033[1;36mROOM MENU[0m️ ⬅", "\033[1;36mMAIN MENU[0m️ ⬅",
                                            "\033[1;31mEXIT ➡️[0m️"};
    header(totalWidth, "UPDATE / DELETE ROOM", "1-4", listsToDisplay);
}

void UI::tabularDisplay(const std::vector<Room> &roomVec) {
    const int total_width{70};             //Total width of ruler
    const int field1_width{10};           //Room No
    const int field2_width{11};          //Room Type
    const int field3_width{11};         //Bed Type
    const int field4_width{16};        //Price
    const int field5_width{7};        //wifi
    const int field6_width{15};      //status

    std::string title{"ROOM(s) WITH PRICE PER NIGHT"};
    int title_length = title.length();
    std::cout << std::setw((total_width - title_length) / 2) << "" << "\033[1;36m" + title + "[0m️" << std::endl;

    std::cout << std::setw(total_width) << std::setfill('-') << "" << std::endl;   // display total_width dashes
    std::cout << std::setfill(' '); // reset set-fill to blank spaces

    std::cout << std::setw(field1_width) << std::left << "Room No."
              << std::setw(field2_width) << std::left << "Type"
              << std::setw(field3_width) << std::left << "Bed"
              << std::setw(field4_width) << std::left << "Price (＄)"
              << std::setw(field5_width) << std::left << "Wi-Fi❔"
              << std::setw(field6_width) << std::right << "Status"
              << std::endl;

    std::cout << std::setw(total_width) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::setprecision(2) << std::fixed; // for displaying the price with 2 decimal digits
    for (size_t i = 0; i < roomVec.size(); ++i) {
        std::cout << std::setw(field1_width) << std::left << roomVec.at(i).getRoomNumber()
                  << std::setw(field2_width) << std::left << roomVec.at(i).getRoomType()->getRoomTypeName()
                  << std::setw(field3_width) << std::left << roomVec.at(i).bedTypeToString(roomVec.at(i).getBedType())
                  << std::setw(field4_width) << std::left << roomVec.at(i).getRoomType()->getPrice()
                  << std::setw(field5_width) << std::left << ((roomVec.at(i).getWifiEnabled() == 0) ? "No" : "Yes")
                  << std::setw(field6_width) << std::right
                  << roomVec.at(i).roomAvailabilityStatusToString(roomVec.at(i).getRoomAvailabilityStatus())
                  << std::endl;
    }
    std::cout << std::setw(total_width) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::endl << std::endl;

}
//========================END OF ROOM UI===================================================================



//========================RESERVATION UI===================================================================
void UI::reservationMenuDisplay() {
    const int totalWidth{35};
    std::vector<std::string> listsToDisplay{"Make a New Reservation",
                                            "Show all Reservations",
                                            "Manage Existing Reservation",
                                            "\033[1;36mMAIN MENU[0m️ ⬅",
                                            "\033[1;31mEXIT ➡️[0m️"};
    header(totalWidth, "MANAGE RESERVATION", "1-4", listsToDisplay);
}

void UI::reservationManagementDisplay() {
    const int totalWidth{35};
    std::vector<std::string> listsToDisplay{"Search Guest Active Reservations",
                                            "Update A Reservation",
                                            "Delete Reservation",
                                            "\033[1;36mRESERVATION MENU[0m️ ⬅",
                                            "\033[1;36mMAIN MENU[0m️ ⬅",
                                            "\033[1;31mEXIT ➡️[0m️"};
    header(totalWidth, "MANAGE EXISTING RESERVATION", "1-7", listsToDisplay);
}

void UI::reservationSubMenuDisplay() {
    const int totalWidth{30};
    std::vector<std::string> listsToDisplay{"VIP Rooms", "DELUXE Rooms", "DOUBLE Rooms", "SINGLE Rooms",
                                            "\033[1;36mRESERVATION MENU[0m️ ⬅",
                                            "\033[1;36mMAIN MENU[0m️ ⬅",
                                            "\033[1;31mEXIT ➡️[0m️"};
    header(totalWidth, "CHOOSE ROOM TYPE", "1-7", listsToDisplay);

}

void UI::existingGuestDisplay() {
    const int totalWidth{35};
    std::vector<std::string> listsToDisplay{"YES - Existing Guest", "NO - New Guest",
                                            "\033[1;36mRESERVATION MENU[0m️ ⬅",
                                            "\033[1;36mMAIN MENU[0m️ ⬅",
                                            "\033[1;31mEXIT ➡️[0m️"};
    header(totalWidth, "EXISTING GUEST ?", "1-5", listsToDisplay);
}

void UI::reservationTabularDisplay(const std::set<Reservation> &reservationSet) {
    const int total_width{80};             //Total width of ruler
    const int field1_width{40};           //Reservation No
    const int field2_width{9};           //Room #
    const int field3_width{11};         //Room Type
    const int field4_width{11};        //Guest ID
    const int field5_width{9};        //Status
    //===============================//
    const int field6_width{37};     //
    const int field7_width{20};    //
    //============================//
    const int field8_width{34};  //
    const int field9_width{22}; //
    //======================== //


    std::string title{"RESERVATION(s)"};
    int title_length = title.length();
    std::cout << std::setw((total_width - title_length) / 2) << "" << "\033[1;36m" + title + "[0m️" << std::endl;

    std::cout << std::setw(total_width) << std::setfill('-') << "" << std::endl;   // display total_width dashes
    std::cout << std::setfill(' '); // reset set-fill to blank spaces

    std::cout << std::setw(field1_width) << std::left << "Reservation No."
              << std::setw(field2_width) << std::left << "Room #"
              << std::setw(field3_width) << std::left << "Room Type"
              << std::setw(field4_width) << std::left << "Guest ID"
              << std::setw(field5_width) << std::left << "Rs Status"
              << std::endl;

    std::cout << std::setw(total_width) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::setprecision(2) << std::fixed; // for displaying the price with 2 decimal digits
    for (const Reservation &reservation: reservationSet) {
        std::cout << std::setw(field1_width) << std::left << reservation.getReservationNumber()
                  << std::setw(field2_width) << std::left << reservation.getRoom().getRoomNumber()
                  << std::setw(field3_width) << std::left << reservation.getRoom().getRoomType()->getRoomTypeName()
                  << std::setw(field4_width) << std::left << reservation.getGuest().getId().getIdNumber()
                  << std::setw(field5_width) << std::left
                  << reservation.reservationStatusToString(reservation.getReservationStatus())
                  << std::endl;
        std::cout << std::setw(field6_width) << std::left << "\033[1;36mCheck-In Date: [0m"
                  << std::setw(field8_width) << std::left << reservation.getCheckInDate()
                  << std::setw(field7_width) << std::left << "\033[1;32mTotal $: [0m"
                  << std::setw(field5_width) << std::left
                  << "[1;36m" << reservation.getRoom().getRoomType()->getPrice() << "[0m"
                  << std::endl;
        std::cout << std::setw(field6_width) << std::left << "\033[1;32mCheck-Out Date: [0m"
                  << std::setw(field8_width) << std::left << reservation.getCheckOutDate()
                  << std::setw(field9_width) << std::left << "\033[1;36mPaid ?[0m"
                  << std::setw(field5_width) << std::left
                  << (reservation.getHasPaid() == 0 ? "\033[1;31mNOT YET[0m" : "\033[1;32mPAID ✅[0m")
                  << std::endl << std::endl;
    }//For Each Reservation

    std::cout << std::setw(total_width) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::endl << std::endl;
}

//========================END OF RESERVATION UI============================================================



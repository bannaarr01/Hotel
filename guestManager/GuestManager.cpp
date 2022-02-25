
#include "GuestManager.h"

void GuestManager::guestMenu() {
    int num{};
    UI::guestMenuDisplay();
    std::cin >> num;

    switch (num) {
        case 1: {
            std::cout << std::string(2, '\n');
            createGuess();
            guestMenu();
            break;
        }
        case 2: {
            std::cout << std::string(2, '\n');
            updateMenu();
            break;
        }
        case 3: {
            std::cout << std::endl;
            searchMenu();
            break;
        }
        case 4: {
            std::cout << std::string(2, '\n');
            OverallManager::mainMenu();
            break;
        }
        case 5: {
            std::cout << std::string(2, '\n');
            showGuests();
            //  OverallManager::mainMenu();
            break;
        }

    }
}

void GuestManager::updateMenu() {
    // UI::guestSubMenuDisplay();
    int selection = ioManager.inputValidation(1, 5, UI::guestSubMenuDisplay);
    Guest guest;
    switch (selection) {
        case 1: {
            std::string guestId{};
            if (copyCSVtoGuestObjSet(guestObjSet)) {
                std::cout << "🟢 Initiated Successfully...🚀" << std::endl;
                std::cout << "Enter ID of Guest to update: ";
                std::cin >> guestId;
                /// std::getline(std::cin, name);
                auto result = findById(guestId);
                if (!result.empty()) {
                    guest = result.at(0);
                    auto it = guestObjSet.find(guest);
                    if (it != guestObjSet.end()) {
                        std::cout << "🟢 FOUND" << std::endl;
                        guestObjSet.erase(it);
                        std::string newName{"NewMan"}, newAddress{}, newCountry{}, newContact{};
                        //std::cin.ignore();
                        std::cout << "Enter New Address: ";
                        std::getline(std::cin, newAddress);
                        std::cout << "Enter New Country: ";
                        std::getline(std::cin, newCountry);
                        std::cout << "Enter New Contact: ";
                        std::getline(std::cin, newContact);
                        guest.setName(newName);
                        auto changeGuestByNCC = guest.changeGuestDetails();
                        changeGuestByNCC(newAddress, newCountry, newContact);

                        std::string newHolderName{"Frank Wife"}, newCcNumber{"4467829012345678"},
                                newExpiryDate{"2025"}, newCVV{"478"};
                        auto changeGuestCCDetails = guest.changeGuestCcDetails();
                        changeGuestCCDetails(newHolderName, newCcNumber, newExpiryDate, newCVV);
                        guestObjSet.emplace(guest);
                        std::ofstream outFile{filename};//std::ios::app
                        std::string line{};
                        if (!outFile) {
                            std::cerr << "Error Writing Guest data to file...🚨️" << std::endl;
                            // return 1;
                        }
                        for (const auto &elem: guestObjSet)
                            outFile << elem << std::endl;
                        std::cout << "🟢 File Override Successfully ✅" << std::endl;
                        outFile.close();
                    } else
                        std::cout << "🔴 NOT FOUND" << std::endl;
                }
//                    std::cout << "[";
//                    for (const auto &elem: guestObjSet)
//                        std::cout << elem << " ";
//                    std::cout << "]" << std::endl;
            } else {
                std::cout << "\033[1;31m🔴 Sorry there's an error... try again later...\033[0m" << std::endl;
                guestMenu();
            }
            break;
        }//end of case 1

        case 4: {
            std::cout << std::endl;
            guestMenu();
            break;
        }
        case 5: {
            std::cout << std::endl;
            OverallManager::mainMenu();
            break;
        }

    }

}

Guest GuestManager::createGuess() {
    //Request input to create new guest
    auto g = ioManager.askInputToCreateNewGuest();
    //Making the guest a unique Guest smart pointer
    std::unique_ptr<Guest> guest = std::make_unique<Guest>(g);
    //Use the entered detail name and Id as search term to check existing file
    std::string searchName{guest->getName()};
    std::string searchId{guest->getId().getIdNumber()};
    //  g.save(*guest, filenameX);
    //File Handling
//    std::ifstream inFile{"../data/guestLists.csv", std::ios::in};
//    std::ofstream outFile{"../data/guestLists.csv", std::ios::app};
//    std::string line{};
//    bool result{false};
//    try {
//        if (!inFile) {
//            throw ErrorOpeningFileException{};
//        }
//        if (!outFile) {
//            throw ErrorWritingToFileException{};
//        }
//        while (inFile >> line) {
//            //check if the name and id exist
//            if (numberOfTimes(searchName, searchId, line))
//                result = true;
//        }
//        if (result) {
//            //if exist throw an exception
//            throw AlreadyExistException{
//                    "\033[1;31m 💥 Could Not save 🧨\n🔴 Guest Already Exists in the system 🚨\033[0m"};
//        } else {
//            //if not, dereference the pointer and insert the details
//            outFile << *guest << std::endl;
//            std::cout << "🟢 Guest successfully created ✅" << std::endl;
//        }
//    } catch (const AlreadyExistException ex) {
//        std::cout << ex.what() << std::endl;
//    } catch (const ErrorOpeningFileException ex) {
//        std::cout << ex.what() << std::endl;
//    } catch (const ErrorWritingToFileException ex) {
//        std::cout << ex.what() << std::endl;
//    }
//    //closing both files
//    inFile.close();
//    outFile.close();

    return *guest;

}

Guest GuestManager::searchMenu() {
    copyCSVtoGuestObjSet(guestObjSet);
    std::vector<Guest> searchResult;
    Guest guest;
//    std::ifstream inFile{filename};
//    std::vector<Guest> searchResult;
//    std::string line{};
//    std::string temp{};
//    std::string word{};
//
//    std::string name{}, address{}, country{}, nationality{}, gender{}, contact{};
//    std::string iDType{};
//    std::string idNumber{}, iDExpiryDate{}, ccHolderName{}, ccNumber{}, ccExpiryDate{}, ccCVV{};
//
//    if (!inFile) {
//        std::cerr << "Error Opening Guest file 🚨️" << std::endl;
//    }
//
//    while (std::getline(inFile, line)) {
//
//        std::stringstream s(line);
//        std::vector<std::string> guestStrVec;
//        std::string word;
//        while (std::getline(s, word, ',')) {
//            guestStrVec.push_back(word);
//        }
////        std::cout << "Tokenized line: ";
////        for (const auto &elem: words)
////            std::cout << "[" << elem << "]";
////        std::cout << std::endl;
//
//        name = guestStrVec[0], address = guestStrVec[1], country = guestStrVec[2],
//        nationality = guestStrVec[3], gender = guestStrVec[4], contact = guestStrVec[5],
//        idNumber = guestStrVec[7], iDExpiryDate = guestStrVec[8], ccHolderName = guestStrVec[9],
//        ccNumber = guestStrVec[10], ccExpiryDate = guestStrVec[11], ccCVV = guestStrVec[12];
//        int n{};
//        iDType = guestStrVec[6] == "Driving License" ? n = 2 : n = 1;
//
//        IdDetails id2{IdDetails::IDType(n), idNumber, iDExpiryDate};
//        CreditCardDetails c3{ccHolderName, ccNumber, ccExpiryDate, ccCVV};
//        std::unique_ptr<Guest> guest = std::make_unique<Guest>(name, address, country, nationality, gender, contact,
//                                                               id2, c3);
//
//        //guestObjList.push_back(*guest);
//        guestObjSet.emplace(*guest);
//    }
    std::cout << "✅ Search Initiated Successfully...🚀" << std::endl;

    bool done{false};
    do {
        char search{};
        std::string searchTerm{};
        std::cout << "Enter Guest Passport / Driving License: ";
        std::cin >> searchTerm;
        //std::getline(std::cin, searchTerm);
        std::transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::toupper);
        searchResult = findById(searchTerm);
        if (!searchResult.empty()) {
            guest = searchResult.at(0);
            std::cout << "🟢 Found" << std::endl;
            //for (auto &res: searchResult)
            std::cout << guest << std::endl;
        } else
            std::cout << "🔴 Record NOT Found" << std::endl;
        std::cout << "Search Again? Enter (Y or N): ";
        std::cin >> search;
        if (search == 'N' || search == 'n') {
            done = true;
            //End search and return to guest menu
            guestMenu();
        }
    } while (!done);

    return guest;
}


std::vector<Guest> GuestManager::findById(std::string &searchTerm) {
    std::vector<Guest> result;
    //If found, copy the obj and insert into result vector

    std::copy_if(guestObjSet.begin(), guestObjSet.end(), std::back_inserter(result),
                 [searchTerm](const Guest &g) {
                     return (g.getId().getIdNumber() == searchTerm || g.getName() == searchTerm);
                 });

    return result;
}


bool GuestManager::copyCSVtoGuestObjSet(std::set<Guest> &guestObjSet) {
    std::ifstream inFile{filename};
    std::string line{};
    std::string temp{};
    std::string word{};

    std::string name{}, address{}, country{}, nationality{}, gender{}, contact{};
    std::string iDType{};
    std::string idNumber{}, iDExpiryDate{}, ccHolderName{}, ccNumber{}, ccExpiryDate{}, ccCVV{};
    // try {
    if (!inFile) {
        return false;
        // throw ErrorOpeningFileException{};
    }
    while (std::getline(inFile, line)) {

        std::stringstream s(line);
        std::vector<std::string> guestStrVec;
        std::string word;
        while (std::getline(s, word, ',')) {
            guestStrVec.push_back(word);
        }
        name = guestStrVec[0], address = guestStrVec[1], country = guestStrVec[2],
        nationality = guestStrVec[3], gender = guestStrVec[4], contact = guestStrVec[5],
        idNumber = guestStrVec[7], iDExpiryDate = guestStrVec[8], ccHolderName = guestStrVec[9],
        ccNumber = guestStrVec[10], ccExpiryDate = guestStrVec[11], ccCVV = guestStrVec[12];
        int n{};
        iDType = guestStrVec[6] == "Driving License" ? n = 2 : n = 1;
        IdDetails id2{IdDetails::IDType(n), idNumber, iDExpiryDate};
        CreditCardDetails c3{ccHolderName, ccNumber, ccExpiryDate, ccCVV};
        std::unique_ptr<Guest> guest = std::make_unique<Guest>(name, address, country, nationality, gender, contact,
                                                               id2, c3);
        guestObjSet.emplace(*guest);
    }
//} catch (ErrorOpeningFileException ex) {
//    std::cout << ex.what() << std::endl;
//}

    return true;
}

void GuestManager::showGuests() {
    Guest gg;

//    if (copyCSVtoGuestObjSet(guestObjSet)) {
//        for (auto g: guestObjSet)
//            gg.restore(ar, g, filenameX);
//    }


}



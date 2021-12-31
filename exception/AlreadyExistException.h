
#ifndef HOTEL_ALREADYEXISTEXCEPTION_H
#define HOTEL_ALREADYEXISTEXCEPTION_H

class AlreadyExistException : public std::exception {
public:
    AlreadyExistException() noexcept = default;

    ~AlreadyExistException() = default;

    virtual const char *what() const noexcept {
        return "\033[1;31m 💥 Could Not save 🧨\n🔴 ID Already Exists in the system 🚨\033[0m";

    }
};


#endif //HOTEL_ALREADYEXISTEXCEPTION_H

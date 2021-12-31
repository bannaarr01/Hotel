#ifndef HOTEL_INVALIDENTRYEXCEPTION_H
#define HOTEL_INVALIDENTRYEXCEPTION_H


class InvalidEntryException : public std::exception {
public:
    InvalidEntryException() noexcept = default;

    ~InvalidEntryException() = default;

    virtual const char *what() const noexcept {
        return "\033[1;31m💥 Invalid Entry 🧨, Try again...\033[0m";
    }
};


#endif //HOTEL_INVALIDENTRYEXCEPTION_H

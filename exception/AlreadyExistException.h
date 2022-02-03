
#ifndef HOTEL_ALREADYEXISTEXCEPTION_H
#define HOTEL_ALREADYEXISTEXCEPTION_H

class AlreadyExistException : public std::exception {
public:
    explicit AlreadyExistException(const char *message) noexcept: msg{message} {}

    //copy constructor
    //  AlreadyExistException(AlreadyExistException const &) noexcept = default;

    //copy assignment
    //   AlreadyExistException &operator=(AlreadyExistException const &) noexcept = default;

    ~AlreadyExistException() override = default;

    virtual const char *what() const noexcept override {
        return msg;
    }

private:
    const char *msg;
};


#endif //HOTEL_ALREADYEXISTEXCEPTION_H

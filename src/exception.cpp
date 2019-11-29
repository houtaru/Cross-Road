#include "exception.hpp"

Exception::Exception(const char *msg) {
    this->msg = msg;
}

Exception::Exception() {
}

Exception::~Exception() {
}

const char*Exception:: what() const throw() {
    return this->msg;
}
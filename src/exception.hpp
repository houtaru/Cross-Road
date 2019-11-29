#pragma once
#include <exception>

class Exception: public std::exception {
    public:
        Exception();
        Exception(const char *msg);
        virtual ~Exception();
        const char* what() const throw();
    
    private:
        const char *msg;
};
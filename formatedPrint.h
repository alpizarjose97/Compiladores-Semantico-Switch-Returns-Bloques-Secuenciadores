//
// Created by Pablo Brenes on 22 abr 2018.
//

#ifndef LEXICO_FORMATEDPRINT_H
#define LEXICO_FORMATEDPRINT_H

#include <iostream>

void static printff(const char* s) {
    while (*s) {
        if (*s == '%' && *++s != '%')
            throw std::runtime_error("invalid format string: missing arguments");
        std::cout << *s++;
    }
}

template<typename T, typename... Args>
void static printff(const char* s, const T& value, const Args&... args) {
    while (*s) {
        if (*s == '%' && *++s != '%') {
            std::cout << value;
            return printff(++s, args...);
        }
        std::cout << *s++;
    }
    throw std::runtime_error("extra arguments provided to printf");
}

#endif //LEXICO_FORMATEDPRINT_H

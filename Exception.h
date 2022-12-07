#pragma once
#include <exception>
#include <iostream>

class file_not_opened : public std::exception{
public:
    const char* what(){
        return "Couldn't open the file.";
    }
};

class incompatible_dimensions : public std::exception{
public:
    const char* what(){
        return "Error: operation on matrices with incompatible dimensions";
    }
};

class out_of_bounds : public std::exception{
public:
    const char* what(){
        return "Out of bounds exception";
    }
};
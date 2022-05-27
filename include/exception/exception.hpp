#pragma once
#ifndef _EXCEPTION_HPP
#define _EXCEPTION_HPP

#include <string>

class exception : public std::exception
{
public:
    enum class TYPE {
        INDEX_ROW_ERROR = 1,
        NOT_SQUARE,
        NOT_INVERTIBLE,
        INDEX_COLLUMN_ERROR,
        INCOMPATIBLE_SIZE_ERROR,
        FILE_OPENING_ERROR,
        LITTLE_DATA_ERROR
    };

private:
    std::string _error_t;
public:
    explicit exception(const std::string& err)
        : _error_t(err) { }

    explicit exception(TYPE _type) {

        switch (_type)
        {
        case TYPE::INDEX_ROW_ERROR:
            _error_t = {  "accessing a non-existent matrix row"   };
            break;

        case TYPE::NOT_SQUARE:
            _error_t = {        "matrix must be square"           };
            break;

        case TYPE::NOT_INVERTIBLE:
            _error_t = {       "matrix is not invertible"         };
            break;

        case TYPE::INDEX_COLLUMN_ERROR:
            _error_t = { "accessing a non-existent matrix column" };
            break;

        case TYPE::INCOMPATIBLE_SIZE_ERROR:
            _error_t = {       "incompatible matrix sizes"        };
            break;

        case TYPE::FILE_OPENING_ERROR:
            _error_t = {            "there's no file"             };
            break;

        case TYPE::LITTLE_DATA_ERROR:
            _error_t = {  "there is not enough data in the file"  };
            break;

        default:
            _error_t = {     "no case for this type of error"     };
        }
    }

    const char* what() const noexcept { return _error_t.c_str(); }
};

#endif /// _EXCEPTION_HPP
#pragma once
#ifndef _EXCEPTION_HPP
#define _EXCEPTION_HPP

#include <string>

class exception : public std::exception
{
public:
    enum class TYPE {
        INDEX_COLLUMN_ERROR = 1
    };

private:
    std::string _error_t;
public:
    explicit exception(const std::string& err)
        : _error_t(err) { }

    explicit exception(TYPE _type) {

        switch (_type)
        {
        case TYPE::INDEX_COLLUMN_ERROR:
            _error_t = "accessing a non-existent matrix column";
            break;
        default:
            _error_t = "no case for this type of error";
        }
    }

    const char* what() const noexcept { return _error_t.c_str(); }
};

#endif /// _EXCEPTION_HPP
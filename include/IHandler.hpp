/**
 * IHandler.hpp
 */

#ifndef IHANDLER_HPP
#define IHANDLER_HPP

#include <cpprest/http_msg.h>

class IHandler {
    public:
        virtual ~IHandler() { std::cout << "DEAD\n"; }
        virtual bool invoke(const web::http::http_request& req) = 0;
        virtual std::string path() const = 0;
};

#endif // IHANDLER_HPP

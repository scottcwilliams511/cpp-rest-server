/**
 * IHandler.hpp
 */

#ifndef IHANDLER_HPP
#define IHANDLER_HPP

#include <cpprest/http_msg.h>

class IHandler {
    public:
        virtual ~IHandler() { }
        virtual bool invoke(web::http::http_request req) = 0;
};

#endif // IHANDLER_HPP

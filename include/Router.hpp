/**
 * Router.hpp
 */

#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <cpprest/http_msg.h>
#include "IHandler.hpp"

struct Route {
    std::string path;
    std::function<void(web::http::http_request)> method;
};

class Router : public IHandler {
    public:
        Router();

        bool invoke(web::http::http_request req);

        void get(std::string path, std::function<void(web::http::http_request)> callback);

    private:

        std::vector<Route> _getRoutes;
};

#endif // ROUTER_HPP

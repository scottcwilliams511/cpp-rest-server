/**
 * Router.cpp
 */

#include "Router.hpp"

Router::Router() {
    std::cout << "HELLO\n";
}

bool Router::invoke(web::http::http_request req) {
    utility::string_t path = req.relative_uri().path();

    for (Route route : _getRoutes) {
        if (route.path == path) {
            route.method(req);
            return true;
        }
    }

    return false;
}

void Router::get(std::string path, std::function<void(web::http::http_request)> callback) {
    Route route {
        path,
        callback,
    };

    _getRoutes.push_back(route);
}

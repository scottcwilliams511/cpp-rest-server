/**
 * Router.cpp
 */

#include "Router.hpp"

Router::Router() {
    std::cout << "HELLO\n";
    _path = "";
}

Router::Router(const std::string& path) {
    _path = path;
}

std::string Router::path() const {
    return _path;
}

bool Router::invoke(const web::http::http_request& req) {
    utility::string_t path = req.relative_uri().path();

    for (auto const& handler : _handlers) {
        std::string handlerPath = handler->path();
        // Matching path.
        if (path == handlerPath){
            return handler->invoke(req);
        }
        // Middleware.
        if (handlerPath.empty()) {
            handler->invoke(req);
        }  
    }

    return false;
}

void Router::get(const std::string& path, const std::function<void(const web::http::http_request&)>& method) {
    std::unique_ptr<IHandler> handler(new Route(path, method));
    _handlers.push_back(std::move(handler));
}

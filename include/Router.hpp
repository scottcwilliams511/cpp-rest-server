/**
 * Router.hpp
 */

#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <cpprest/http_msg.h>
#include "IHandler.hpp"

class Router : public IHandler {
    class Route : public IHandler {
        public:
            Route(const std::string& path, const std::function<void(const web::http::http_request&)>& method) {
                _path = path;
                _method = method;
            }

            bool invoke(const web::http::http_request& req) {
                _method(req);
                return true;
            }

            std::string path() const {
                return _path;
            }
        private:
            std::string _path;
            std::function<void(const web::http::http_request&)> _method;
    };

    public:
        Router();
        Router(const std::string& path);

        bool invoke(const web::http::http_request& req);
        void get(const std::string& path, const std::function<void(const web::http::http_request&)>& callback);
        std::string path() const;
    private:
        std::string _path;
        std::vector<std::unique_ptr<IHandler>> _handlers;
};

#endif // ROUTER_HPP

/**
 * Server.hpp
 */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <cpprest/http_listener.h>

#include "Router.hpp"

/**
 * Server object.
 */
class Server {
    public:
        Server(const std::string& host, const std::string& port);

        pplx::task<void> open();
        pplx::task<void> close();
        std::string endpoint() const;
        std::vector<utility::string_t> requestPath(const web::http::http_request& req) const;

        void get(const std::string& path, const std::function<void(const web::http::http_request&)>& callback);
    private:
        void _get(const web::http::http_request& req);
        void _post(const web::http::http_request& req);
        void _put(const web::http::http_request& req);
        void _delete(const web::http::http_request& req);

        web::http::experimental::listener::http_listener _listener;
        Router _router;
};

#endif // SERVER_HPP

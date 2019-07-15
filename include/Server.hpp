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
        std::vector<utility::string_t> requestPath(const web::http::http_request& req);

        void get(std::string path, std::function<void(web::http::http_request)> callback);
    private:
        void _get(web::http::http_request req);
        void _post(web::http::http_request req);
        void _put(web::http::http_request req);
        void _delete(web::http::http_request req);
        std::map<std::string, std::function<void(web::http::http_request req)>> _routes;

        web::http::experimental::listener::http_listener _listener;
        Router _router;
};

#endif // SERVER_HPP

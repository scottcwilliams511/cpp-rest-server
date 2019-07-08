#include <iostream>
#include "Server.hpp"

using namespace web;
using namespace utility;
using namespace web::http;
using namespace web::http::experimental::listener;

Server::Server(const std::string& host, const std::string& port) {
    uri_builder builder;

    builder.set_scheme("http")
        .set_host(host)
        .set_port(port)
        .set_path("api/v1");

    _listener = http_listener(builder.to_uri());

    // Expose endpoints.
    _listener.support(methods::GET, std::bind(&Server::_get, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&Server::_post, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&Server::_put, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&Server::_delete, this, std::placeholders::_1));
}

pplx::task<void> Server::open() {
    return _listener.open();
}

pplx::task<void> Server::close() {
    return _listener.close();
}

std::string Server::endpoint() const {
    return _listener.uri().to_string();
}

std::vector<utility::string_t> Server::requestPath(const http_request& req) {
    auto relativePath = uri::decode(req.relative_uri().path());
    return uri::split_path(relativePath);
}

/**
 * @brief Route get requests.
 */
void Server::_get(http_request req) {
    auto foo = uri::split_query(req.request_uri().query());
    for (auto it = foo.begin(); it != foo.end(); it++ ) {
        std::cout << it->first << ':' << it->second << "\n";
    }
    std::cout << "GET: " << req.to_string() << "\n";
    
    auto path = requestPath(req);
    if (!path.empty()) {
        if (path[0] == "test") {
            auto res = json::value::object();
            res["foo"] = json::value::string("bar");
            req.reply(status_codes::OK, res);
            return;
        }
    }

    req.reply(status_codes::NotFound);
}

void Server::_post(http_request req) {
    std::cout << "POST: " << req.to_string() << "\n";
    req.reply(status_codes::OK);
}

void Server::_put(http_request req) {
    std::cout << "PUT: " << req.to_string() << "\n";
    req.reply(status_codes::OK);
}

void Server::_delete(http_request req) {
    std::cout << "DELETE: " << req.to_string() << "\n";
    req.reply(status_codes::OK);
}

#ifndef SERVER_HPP
#define SERVER_HPP

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

using namespace web::http;
using namespace utility;
using namespace web::http::experimental::listener;

class Server {
    public:
        Server(const std::string& host, const std::string& port);

        pplx::task<void> open();
        pplx::task<void> close();
        std::string endpoint() const;
        std::vector<utility::string_t> requestPath(const http_request& req);
    private:
        void _get(http_request req);
        void _post(http_request req);
        void _put(http_request req);
        void _delete(http_request req);

        http_listener _listener;
};

#endif // SERVER_HPP

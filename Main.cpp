#include <iostream>
#include <condition_variable>
#include <mutex>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "Server.hpp"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

void makeRequest() {
    // Create http_client to send the request.
    http_client client(U("http://localhost:3000"));

    // Build request URI and start the request.
    uri_builder builder(U("/api/v1/test"));

    // Open stream to output file.
    pplx::task<void> requestTask = client.request(methods::GET, builder.to_string())
        // Handle response headers arriving.
        .then([=](http_response response) {
            printf("Received response status code:%u\n", response.status_code());

            // Extract json.
            return response.extract_json();
        })

        // Print json.
        .then([=](pplx::task<json::value> previousTask) {
            const json::value& value = previousTask.get();
            std::cout << "Value: " << value.serialize() << "\n";
        });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try {
        requestTask.wait();
    } catch (const std::exception& e) {
        printf("Error exception:%s\n", e.what());
    }
}

std::condition_variable condition;

int main(int argc, char* argv[]) {
    signal(SIGINT, [] (int signal) {
        if (signal == SIGINT) {
            std::cout << "\nSIGINT trapped...\n";
            condition.notify_one();
        }
    });

    string_t host = U("localhost");
    string_t port = U("3000");

    try {
        // Create server
        Server server(host, port);

        // Start server.
        server.open().wait();
        std::cout << "Listening at: " << server.endpoint() << "\n";

        // Test calling the server.
        makeRequest();

        // Keep server running until user kills it.
        std::mutex mutex;
        std::unique_lock<std::mutex> lock { mutex };
        condition.wait(lock);
        lock.unlock();

        std::cout << "Closing server...\n";
        server.close().wait();
    } catch (std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return -1;
    }

    return 0;
}

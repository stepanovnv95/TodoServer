#include <vector>

#include <proxygen/httpserver/HTTPServer.h>

#include "HelloHandlerFactory.h"


int main()
{
    std::vector<proxygen::HTTPServer::IPConfig> IPs = {
        {folly::SocketAddress("0.0.0.0", 2288), proxygen::HTTPServer::Protocol::HTTP},
    };

    proxygen::HTTPServerOptions options;
    options.threads = 1;
    options.idleTimeout = std::chrono::milliseconds(60 * 1000);
    options.handlerFactories =
            proxygen::RequestHandlerChain()
            .addThen<HelloHandlerFactory>()
            .build();

    proxygen::HTTPServer server(std::move(options));
    server.bind(IPs);
    server.start(
        []{ std::cout << "Success" << std::endl; },
        [](std::exception_ptr){ std::cout << "Fail" << std::endl; }
    );

    return 0;
}

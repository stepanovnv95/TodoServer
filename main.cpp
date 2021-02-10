#include <vector>

#include <fmt/core.h>
#include <proxygen/httpserver/HTTPServer.h>

#include "Arguments.h"
#include "HelloHandlerFactory.h"


void configureArguments(int argc, char* argv[])
{
    std::string usage = fmt::format("\nUsage:\n{} --port <value>", argv[0]);
    gflags::SetUsageMessage(usage);

    std::string version = fmt::format("0.1 {} {}", __DATE__, __TIME__);
    gflags::SetVersionString(version);

    gflags::ParseCommandLineFlags(&argc, &argv, true);
}


proxygen::HTTPServerOptions configureServerOptions()
{
    proxygen::HTTPServerOptions options;
    options.handlerFactories = proxygen::RequestHandlerChain()
                                .addThen<HelloHandlerFactory>()
                                .build();
    return options;
}


int main(int argc, char* argv[])
{
    configureArguments(argc, argv);

    proxygen::HTTPServerOptions options = configureServerOptions();
    proxygen::HTTPServer server(std::move(options));

    std::vector<proxygen::HTTPServer::IPConfig> IPs = {
        {folly::SocketAddress(FLAGS_host, FLAGS_port), proxygen::HTTPServer::Protocol::HTTP},
    };
    server.bind(IPs);

    int status = 0;
    auto onSuccess = []{
        std::cout << "Server successfully started" << std::endl;
    };
    auto onError = [&](std::exception_ptr ep) {
        status = 1;
        try {
            std::rethrow_exception(ep);
        }  catch (const std::exception& e) {
            std::cout << fmt::format("Server starting error, what(): {}", e.what()) << std::endl;
        } catch (...) {
            std::cout << fmt::format("Unknown server starting error") << std::endl;
        }
    };

    server.start(onSuccess, onError);

    return status;
}

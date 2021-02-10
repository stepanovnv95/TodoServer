#ifndef HELLOHANDLER_H
#define HELLOHANDLER_H

#include <proxygen/httpserver/RequestHandler.h>


class HelloHandler : public proxygen::RequestHandler
{
public:
    void onRequest(std::unique_ptr<proxygen::HTTPMessage> request) noexcept override;
    void onBody(std::unique_ptr<folly::IOBuf>) noexcept override;
    void onUpgrade(proxygen::UpgradeProtocol prot) noexcept override;
    void onEOM() noexcept override;
    void requestComplete() noexcept override;
    void onError(proxygen::ProxygenError err) noexcept override;

private:
    void sendHello() noexcept;
    void sendBadMethod() noexcept;
};

#endif // HELLOHANDLER_H

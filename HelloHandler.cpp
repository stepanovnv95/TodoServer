#include "HelloHandler.h"

#include <proxygen/httpserver/ResponseBuilder.h>


void HelloHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> request) noexcept
{
    if (request->getMethod() == proxygen::HTTPMethod::GET) {
        sendHello();
    } else {
        sendBadMethod();
    }
}

void HelloHandler::onBody(std::unique_ptr<folly::IOBuf> /*body*/) noexcept
{}

void HelloHandler::onUpgrade(proxygen::UpgradeProtocol /*prot*/) noexcept
{}

void HelloHandler::onEOM() noexcept
{}

void HelloHandler::requestComplete() noexcept
{}

void HelloHandler::onError(proxygen::ProxygenError /*err*/) noexcept
{}

void HelloHandler::sendHello() noexcept
{
    const char* html = "<html><body><h1>Hello, World!</h1></body></html>";
    proxygen::ResponseBuilder(downstream_)
            .status(200, "OK")
            .header(proxygen::HTTPHeaderCode::HTTP_HEADER_CONTENT_TYPE, "text/html; charset=utf-8")
            .body(html)
            .sendWithEOM();
}

void HelloHandler::sendBadMethod() noexcept
{
    proxygen::ResponseBuilder(downstream_)
            .status(400, "Bad method")
            .sendWithEOM();
}

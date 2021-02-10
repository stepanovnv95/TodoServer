#ifndef HELLOHANDLERFACTORY_H
#define HELLOHANDLERFACTORY_H

#include <proxygen/httpserver/RequestHandlerFactory.h>

#include "HelloHandler.h"


class HelloHandlerFactory : public proxygen::RequestHandlerFactory
{
public:
    void onServerStart(folly::EventBase* evb) noexcept override;
    void onServerStop() noexcept override;
    proxygen::RequestHandler* onRequest(proxygen::RequestHandler*, proxygen::HTTPMessage*) noexcept override;

private:
    HelloHandler handler;
};

#endif // HELLOHANDLERFACTORY_H

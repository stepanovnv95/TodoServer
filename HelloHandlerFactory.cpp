#include "HelloHandlerFactory.h"

#include "HelloHandler.h"


void HelloHandlerFactory::onServerStart(folly::EventBase */*evb*/) noexcept
{}

void HelloHandlerFactory::onServerStop() noexcept
{}

proxygen::RequestHandler *HelloHandlerFactory::onRequest(proxygen::RequestHandler *, proxygen::HTTPMessage *) noexcept
{
    return &handler;
}

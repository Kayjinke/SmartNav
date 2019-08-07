#include "DestinationInputStubImpl.hpp"

using namespace v1::commonapi;

DestinationInputStubImpl::DestinationInputStubImpl()  { }
DestinationInputStubImpl::~DestinationInputStubImpl() { }

void DestinationInputStubImpl::getAllStreets(const std::shared_ptr<CommonAPI::ClientId> _client, getAllStreetsReply_t _reply)
{
     DestinationInput::Stringlist streets;
     streets.push_back("renmin street");
     streets.push_back("jiading strret");
     _reply(streets);  
}

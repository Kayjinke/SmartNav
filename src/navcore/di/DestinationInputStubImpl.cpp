#include "DestinationInputStubImpl.hpp"

using namespace v1::commonapi;

DestinationInputStubImpl::DestinationInputStubImpl()  { }
DestinationInputStubImpl::~DestinationInputStubImpl() { }

void DestinationInputStubImpl::getAllStreets(const std::shared_ptr<CommonAPI::ClientId> _client, getAllStreetsReply_t _reply)
{
     DestinationInput::Stringlist streets;
     streets.push_back("Alta Street");
     streets.push_back("Altura Street");
     streets.push_back("Altura Walk");
     streets.push_back("Ashland Avenue");
     streets.push_back("Augustine Court");
     streets.push_back("Avenue 28");
     streets.push_back("Avenue 26");
     streets.push_back("Aylesworth Place");
     streets.push_back("Clifton Street");
     streets.push_back("Eastlake Avenue");
     streets.push_back("Emma Avenue");
     streets.push_back("Gates Street");
     streets.push_back("George Street");
     streets.push_back("Fonda Way");
     streets.push_back("Griffin Avenue");
     streets.push_back("Hancock Street");
     streets.push_back("Johnston Street");
     streets.push_back("Lincoln Park Avenue");
     streets.push_back("Minnesota Street");
     streets.push_back("North Broadway");
     streets.push_back("North Altura Street");
     streets.push_back("Pomona Street");
     streets.push_back("Prewett Street");
     streets.push_back("Thomas Street");
     streets.push_back("Terry Place");
     streets.push_back("Two Tree Avenue");
     _reply(streets);  
}

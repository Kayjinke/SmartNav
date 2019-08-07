// HelloWorldStubImpl.hpp
#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/DestinationInputStubDefault.hpp>

class DestinationInputStubImpl: public v1_0::commonapi::DestinationInputStubDefault {
public:
     DestinationInputStubImpl();
     virtual ~DestinationInputStubImpl();
     virtual void getAllStreets(const std::shared_ptr<CommonAPI::ClientId> _client, getAllStreetsReply_t _reply);
            
};
#endif /* HELLOWORLDSTUBIMPL_H_ */

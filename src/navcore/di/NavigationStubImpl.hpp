// HelloWorldStubImpl.hpp
#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/NavigationStubDefault.hpp>

class NavigationStubImpl: public v1_0::commonapi::NavigationStubDefault {
public:
     NavigationStubImpl();
     virtual ~NavigationStubImpl();
     virtual void foo(const std::shared_ptr<CommonAPI::ClientId> _client,
            int32_t _x1, std::string _x2, fooReply_t _reply); 
            
};
#endif /* HELLOWORLDSTUBIMPL_H_ */

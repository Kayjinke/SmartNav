// RouteInfoStubImpl.hpp
#ifndef ROUTEINFOSTUBIMPL_H_
#define ROUTEINFOSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/RouteInfoStubDefault.hpp>

class RouteInfoStubImpl: public v1_0::commonapi::RouteInfoStubDefault {
public:
     RouteInfoStubImpl();
     virtual ~RouteInfoStubImpl();
     virtual void displayRI(const std::shared_ptr<CommonAPI::ClientId> _client,
            int32_t _x1, std::string _x2, fooReply_t _reply); 
            
};
#endif /* ROUTEINFOSTUBIMPL_H_ */

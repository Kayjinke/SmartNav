// HelloWorldStubImpl.hpp
#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/RouteCalculationStubDefault.hpp>

using namespace v1::commonapi;

class RouteCalculationStubImpl: public v1_0::commonapi::RouteCalculationStubDefault {
public:
     RouteCalculationStubImpl();
     virtual ~RouteCalculationStubImpl();
     virtual void calcRoute(const std::shared_ptr<CommonAPI::ClientId> _client, RouteCalculation::Shapepoint _startPos, RouteCalculation::Shapepoint _endPos, calcRouteReply_t _reply); 
            
};
#endif /* HELLOWORLDSTUBIMPL_H_ */

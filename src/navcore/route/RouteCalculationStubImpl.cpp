// HelloWorldStubImpl.cpp
#include "RouteCalculationStubImpl.hpp"



RouteCalculationStubImpl::RouteCalculationStubImpl()  { }
RouteCalculationStubImpl::~RouteCalculationStubImpl() { }

void RouteCalculationStubImpl::calcRoute(const std::shared_ptr<CommonAPI::ClientId> _client, RouteCalculation::Shapepoint _startPos, RouteCalculation::Shapepoint _endPos, calcRouteReply_t _reply) {

    std::cout << "calcRoute called, setting new values." << std::endl;

    RouteCalculation::Shapepoints shapepoints;
    
    shapepoints.push_back(RouteCalculation::Shapepoint(300,100));
    shapepoints.push_back(RouteCalculation::Shapepoint(350,150));
    shapepoints.push_back(RouteCalculation::Shapepoint(400,250));
    shapepoints.push_back(RouteCalculation::Shapepoint(700,400));
    _reply(shapepoints);
    
};

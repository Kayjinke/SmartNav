// HelloWorldStubImpl.cpp
#include "RouteCalculationStubImpl.hpp"



RouteCalculationStubImpl::RouteCalculationStubImpl()  { }
RouteCalculationStubImpl::~RouteCalculationStubImpl() { }

void RouteCalculationStubImpl::calcRoute(const std::shared_ptr<CommonAPI::ClientId> _client, RouteCalculation::Shapepoint _startPos, RouteCalculation::Shapepoint _endPos, calcRouteReply_t _reply) {

    std::cout << "calcRoute called, setting new values." << std::endl;

    RouteCalculation::Shapepoints shapepoints;
    
    shapepoints.push_back(RouteCalculation::Shapepoint(5,5));
    shapepoints.push_back(RouteCalculation::Shapepoint(5,6));
    shapepoints.push_back(RouteCalculation::Shapepoint(5,7));
    shapepoints.push_back(RouteCalculation::Shapepoint(5,100));
    _reply(shapepoints);
    
};

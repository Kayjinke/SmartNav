#include "RouteCalculationStubImpl.hpp"
#include "dataacess.h"

RouteCalculationStubImpl::RouteCalculationStubImpl() { }

RouteCalculationStubImpl::~RouteCalculationStubImpl() { }

void RouteCalculationStubImpl::calcRoute(const std::shared_ptr<CommonAPI::ClientId> _client, RouteCalculation::Shapepoint _startPos, RouteCalculation::Shapepoint _endPos, calcRouteReply_t _reply) {

    std::cout << "calcRoute called, setting new values." << std::endl;

    RouteCalculation::Shapepoints shapepoints;

    if(_startPos.getLon() == 1)
    {

        Routeinput input;
        input.routeinput(3724830);
        const std::vector<Wgs84Pos>& roads = input.getRoute();
        for(std::vector<Wgs84Pos>::const_iterator iter = roads.begin(); iter != roads.end(); iter++ )
        {
            shapepoints.push_back(RouteCalculation::Shapepoint(iter->lon, iter->lat));
        }
    }
    

    if(_startPos.getLon() == 2)
    {
        Routeinput input;
        input.routeinput(3784001);
        const std::vector<Wgs84Pos>& roads = input.getRoute();
        for(std::vector<Wgs84Pos>::const_iterator iter = roads.begin(); iter != roads.end(); iter++ )
        {
            shapepoints.push_back(RouteCalculation::Shapepoint(iter->lon, iter->lat));
        }
    }
    cout << "RouteCalculationStubImpl over" << endl; 
    //shapepoints.push_back(RouteCalculation::Shapepoint(-118.2038679, 34.0751386));
    //shapepoints.push_back(RouteCalculation::Shapepoint(-118.2053329, 34.0754687));
    //shapepoints.push_back(RouteCalculation::Shapepoint(-118.2022890, 34.0745812));
    _reply(shapepoints);
    
    
    
};

#include "RouteCalculationStubImpl.hpp"
#include "dataacess.h"

 
 static DataRead dacalc;
    
class GlobalData
{
public:
    GlobalData()
    { 
       std::cout << "global data " << std::endl;
        dacalc.road_read("../data/routes.txt");
        std::cout << "RouteCalculationStubImpl end" << std::endl;
    }
}globalData;

RouteCalculationStubImpl::RouteCalculationStubImpl()
{ 

std::cout << "RouteCalculationStubImpl" << std::endl;


}
RouteCalculationStubImpl::~RouteCalculationStubImpl() { }

void RouteCalculationStubImpl::calcRoute(const std::shared_ptr<CommonAPI::ClientId> _client, RouteCalculation::Shapepoint _startPos, RouteCalculation::Shapepoint _endPos, calcRouteReply_t _reply) {

    std::cout << "calcRoute called, setting new values." << std::endl;

    RouteCalculation::Shapepoints shapepoints;
 
    const std::map<long, Route>& roads = dacalc.getAllRoads();
    cout << "iter size "  << roads.size() << endl; 

    for(std::map<long, Route>::const_iterator iter = roads.begin(); iter != roads.end(); iter++)
    {
         if(iter->first == 3784001)
         {
            for(std::vector<Wgs84Pos>::const_iterator iter1 = iter->second.shapePoints.begin(); iter1 != iter->second.shapePoints.end(); iter1++)
            {
                cout << "R lon: " << iter1->lon << endl; 
                shapepoints.push_back(RouteCalculation::Shapepoint(iter1->lon, iter1->lat));
            }
         }
    } 
   
    cout << "HHHHHHHHHHHHHHHHH" << endl; 
    //shapepoints.push_back(RouteCalculation::Shapepoint(-118.2038679, 34.0751386));
    //shapepoints.push_back(RouteCalculation::Shapepoint(-118.2053329, 34.0754687));
    //shapepoints.push_back(RouteCalculation::Shapepoint(-118.2022890, 34.0745812));
    _reply(shapepoints);
    
    
    
};

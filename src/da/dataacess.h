#ifndef dataacess_h
#define dataacess_h

#include <map>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;
struct Wgs84Pos
{
    Wgs84Pos(double a, double b)
    : lon(a), lat(b) {}
    double lon;
    double lat;
};

typedef std::vector<Wgs84Pos> Wgs84PosList;
typedef std::map<long, Wgs84Pos>::iterator Wgs84PosMapIter;

struct Road
{
   Road(long a, const Wgs84PosList& list)
   : id(a), shapePoints(list)
   {}
   
   long id;
   std::vector<Wgs84Pos> shapePoints;
};

typedef std::map<long, Road>::iterator RoadMapIter;


class DataAcess
{
public:
    DataAcess();
    bool open_database();
    
private:
    std::map<long, Wgs84Pos> m_ShapePoints;
    std::map<long, Road> m_Roads;  
};

struct Route
{
   Route(int a, const Wgs84PosList& list)
   : count(a), shapePoints(list)
   {}
   
   int count;
   std::vector<Wgs84Pos> shapePoints;
};

typedef std::map<long, Route>::iterator RouteMapIter;

class DataRead
{
public:
    DataRead();
    bool shapepoint_read(std::string filename);
    bool road_read(std::string filename);

    std::map<long, Route> getAllRoads() { return r_Roads; }

private:
    std::map<long, Wgs84Pos> r_ShapePoints;
    std::map<long, Route> r_Roads;
};


#endif /*dataacess_h*/

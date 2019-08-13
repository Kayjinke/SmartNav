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

static const int road_type_normal = 0x0001;
static const int road_type_area   = 0x0002;

struct Road
{
   Road(long a, int t, const Wgs84PosList& list)
   : id(a), type(t), shapePoints(list)
   {}
   
   long id;
   int  type;
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
   Route(int a, int t, const Wgs84PosList& list)
   : count(a), type(t), shapePoints(list)
   {}
   
   int count;
   int type;
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

class Routeinput
{
public:
    Routeinput();
    void routeinput(long id);
    std::vector<Wgs84Pos> getRoute() { return poslist; }
    
private:
    long                  id;
    std::map<long, Route> roads;
    std::vector<Wgs84Pos> poslist;
};

#endif /*dataacess_h*/

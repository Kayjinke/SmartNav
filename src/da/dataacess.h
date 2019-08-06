#ifndef dataacess_h
#define dataacess_h

#include <map>
#include <vector>
#include <string>

using namespace std;
struct Wgs84Pos
{
    Wgs84Pos(float a, float b)
    : lon(a), lat(b) {}
    float lon;
    float lat;
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

class DataRead
{
public:
    DataRead();
    bool shapepoint_read(std::string filename);
    bool road_read(std::string filename);

private:
    std::map<long, Wgs84Pos> r_ShapePoints;
    std::map<long, Road> r_Roads;
};


#endif /*dataacess_h*/

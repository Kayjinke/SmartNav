#ifndef dataacess_h
#define dataacess_h

#include <map>
#include <vector>

struct Wgs84Pos
{
    Wgs84Pos(int a, int b)
    : lon(a), lat(b) {}
    int lon;
    int lat;
};

typedef std::vector<Wgs84Pos> Wgs84PosList;
typedef std::map<long, Wgs84Pos>::iterator Wgs84PosMapIter;

struct Road
{
   Road(int a, const Wgs84PosList& list)
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

#endif /*dataacess_h*/

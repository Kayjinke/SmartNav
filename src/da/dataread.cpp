#include <iostream>
#include <fstream>
#include "dataacess.h"
#include <string>

using namespace std;

DataRead::DataRead()
{
}

bool DataRead::shapepoint_read(string filename)
{
    long id = 0;
    float lon = 0;
    float lat = 0;
    Wgs84Pos position(lon, lat);
    std::map<long, Wgs84Pos> r_ShapePoints;
    
    ifstream filestream;
    ifstream infile(filename, ios::in | ios::binary);
    if(filestream.fail())
    {
        cout << "read failed " << endl;
    }
    
    while(!infile.eof())
    {
        infile.read((char*)&id,sizeof(long));    
        infile.read((char*)&position,sizeof(position)); 
        r_ShapePoints.insert(make_pair(id, position));
    }
    cout << " starting...  The counter :" << r_ShapePoints.size() << " sizeof: " << sizeof(r_ShapePoints) << " bytes" << endl;
 
    for(Wgs84PosMapIter iter = r_ShapePoints.begin(); iter != r_ShapePoints.end(); iter++) 
    {
    cout << " Read node id : " << iter->first << "  lon: " << iter->second.lon << " lat: " << iter->second.lat << endl;
    } 
}
    

    // read method 2:
    /*ifstream filestream;
    ifstream infile(filename, ios::binary);
    if(filestream.fail())
    {
        cout << "read failed " << endl;
    }
    
    while (!infile.eof()) {
            long id;
            float lon;
            float lat;
            infile>>id;
            infile>>lon;
            infile>>lat;
            //r_ShapePoints.insert(std::pair<long, Wgs84Pos>(id, Wgs84Pos(lon, lat)));
            cout << "Read points,id = " << id << ", Lon: " << lon << ", Lat: " <<  lat << " " << endl;
        }*/
    
 
bool DataRead::road_read(string filename)
{
    long wayid = 0;
    long id = 0;
    Wgs84PosList poslist;
    std::map<long, Road> r_Roads;
    
    ifstream filestream;
    ifstream infile(filename, ios::in | ios::binary);
    if(filestream.fail())
    {
        cout << "road read failed " << endl;
    }
    
    while(!infile.eof())
    {
        infile.read((char*)&wayid,sizeof(long));   
        infile.read((char*)&id,sizeof(id)); 
        infile.read((char*)&poslist,sizeof(poslist)); 
        Road routes(id, poslist);
        r_Roads.insert(make_pair(wayid, routes));
    }
    cout << " reading roads...  The counter :" << r_Roads.size() << " sizeof: " << sizeof(r_Roads) << " bytes" << endl;
 
    for(RoadMapIter iter = r_Roads.begin(); iter != r_Roads.end(); iter++)
        {
         cout << "read road id : " << iter->second.id << " point count: " << iter->second.shapePoints.size() << endl;
        
    }
}

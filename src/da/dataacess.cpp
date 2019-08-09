#include <iostream>
#include <fstream>
#include "dataacess.h"
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

DataRead::DataRead()
{
}

bool DataRead::shapepoint_read(string filename)
{
    long   id = 0;
    double lon = 0;
    double lat = 0;
    double fnl_lon = 0;
    double fnl_lat = 0;
    double max_lon = 0;
    double max_lat = 0;
    double min_lon = 0;
    double min_lat = 0;
    double axis_xmin  = -118.21228;
    double axis_ymax = 34.07353;
    double axis_xmax = -118.19955; 
    double axis_ymin = 34.07951;

    
    double pos_y;
    double pos_x;
    double new_x;
    double new_y;
    // 所取地图的实际坐标范围

    
    //定义Qt上坐标轴的x和y范围以及地图信息的坐标范围；
    double x = 800;
    double y = 480;
    double axis_x ;
    double axis_y ;
    axis_x = axis_xmax - axis_xmin;
    axis_y = axis_ymax - axis_ymin;
        
    Wgs84Pos position(lon, lat);
    Wgs84Pos fnl_position(fnl_lon, fnl_lat);
    std::vector<double> AllLon; 
    std::vector<double> AllLat;
    std::map<long, Wgs84Pos> r_nShapePoints;
    
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
        AllLon.push_back(position.lon);
        AllLat.push_back(position.lat);
    }
    cout << " starting...  The counter :" << r_ShapePoints.size() << " sizeof: " << sizeof(r_ShapePoints) << " bytes" << endl;

 
    for(Wgs84PosMapIter iter = r_ShapePoints.begin(); iter != r_ShapePoints.end(); iter++) 
    {
        cout << fixed;
        cout << " Read node id : " << iter->first << "  lon: " << setprecision(7) << iter->second.lon << " lat: " << setprecision(7) << iter->second.lat << endl;
        pos_x = iter->second.lon;
        pos_y = iter->second.lat;   
        new_x = (pos_x - axis_xmin) * (x / axis_x); // x(lon) transformation succeed
        new_y = (-(pos_y - axis_ymax)) * (y / axis_y);   // y(lat) transformation succeed

        
        fnl_position.lon = new_x;
        fnl_position.lat = new_y;
        r_nShapePoints.insert(make_pair(iter->first, fnl_position));                   
    } 
    
    for(Wgs84PosMapIter iter = r_nShapePoints.begin(); iter != r_nShapePoints.end(); iter++) 
    {  
        cout << fixed;
        cout << setprecision(7)<< "Final read node id: " << iter->first << ", lon: " << iter->second.lon << ", Lat: " <<  iter->second.lat << endl;
    }

   
 // # calculate max&min longtitude and latitude;
   /*for(std::vector<double>::iterator iter_lon = AllLon.begin(); iter_lon != AllLon.end(); iter_lon++)
    {   
        max_lon = *max_element(AllLon.begin(), AllLon.end());
        min_lon = *min_element(AllLon.begin(), AllLon.end());            
    }
    cout << fixed;
    cout << "max_Lon: " << setprecision(7) << max_lon << ", min_Lon: " << setprecision(7) << min_lon << endl;  

   for(std::vector<double>::iterator iter_lat = AllLat.begin(); iter_lat != AllLat.end(); iter_lat++)
    {   
        max_lat = *max_element(AllLat.begin(), AllLat.end());
        min_lat = *min_element(AllLat.begin(), AllLat.end());  
    }   Mpa points lon: -118.2078319 , lat: 34.0755396
   Mpa points lon: -118.2090966 , lat: 34.0755199
   Mpa points lon: -118.2104038 , lat: 34.0754996
   Mpa points lon: -118.2117936 , lat: 34.0754780
   Mpa points lon: -118.2131035 , lat: 34.0754577

    cout << fixed;    
    cout << "max_Lat: " << setprecision(7) << max_lat << ", min_Lat: " << setprecision(7) << min_lat << endl;*/     


}
 

bool DataRead::road_read(string filename)
{   
    ifstream filestream;
    ifstream infile(filename, ios::in | ios::binary);
    if(filestream.fail())
    {
        cout << "road read failed " << endl;
    }
    
    while(!infile.eof())
    {
        long wayid = 0;
        int count = 0;
        double lon = 0;
        double lat = 0;    
        infile.read((char*)&wayid, 8);
        infile.read((char*)&count, 4);
        
        //cout << "wayid: " << wayid << ", count: " << count << endl;
        Wgs84PosList poslist;
        for(int i = 0; i < count; i++)
        {
            infile.read((char*)&lon, sizeof(double));
            infile.read((char*)&lat, sizeof(double));
            poslist.push_back(Wgs84Pos(lon, lat));
        }
        Route route(count, poslist);
        r_Roads.insert(make_pair(wayid, route));
    }
    
    //cout << " reading roads...  The counter :" << r_Roads.size() << " sizeof: " << sizeof(r_Roads) << " bytes" << endl;
    
    /*for(std::map<long, Route>::iterator iter = r_Roads.begin(); iter != r_Roads.end(); iter++)
    {
        cout << iter->first  << "  " << iter->second.count << endl;
        for(std::vector<Wgs84Pos>::iterator iter1 = iter->second.shapePoints.begin(); iter1 != iter->second.shapePoints.end(); iter1++)
        {
            cout << fixed;
            cout << ", vector lon:" << setprecision(7) << iter1->lon << ", lat: " << iter1->lat << endl;
        }
    }*/
}

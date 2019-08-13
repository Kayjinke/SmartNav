#include "dataacess.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/Exception.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


using Poco::XML::DOMParser;
using Poco::XML::InputSource;
using Poco::XML::Document;
using Poco::XML::NodeIterator;
using Poco::XML::NodeFilter;
using Poco::XML::Node;
using Poco::XML::NodeList;
using Poco::XML::NamedNodeMap;
using Poco::XML::AutoPtr;
using Poco::Exception;

using namespace std;

DataAcess::DataAcess()
{
}

bool DataAcess::open_database()
{
    ifstream in("../data/map_data.osm");
    Poco::XML::InputSource src(in);
    try  
    {  
        DOMParser parser; 
        AutoPtr<Document> pDoc = parser.parse(&src);
        
        {
            NodeList* nl = pDoc->getElementsByTagName("node");
            cout << "points count: " << nl->length() << endl;
            for (long i = 0; i < nl->length(); i++)
            {
                Node* node = nl->item(i);
                NamedNodeMap* nm = node->attributes();
                if(nm)
			    {
			        long id = 0;
			        double lon = 0;
			        double lat = 0;
				    for(int j = 0; j < nm->length() ; j++)
				    {
					    Node* attr = nm->item(j);
					    if (attr->nodeName() == "id")
					    {
					        id  = atol(attr->nodeValue().c_str());
                        }
					    if (attr->nodeName() == "lat")
					    {
					        lat = atof(attr->nodeValue().c_str());				        
                        }
                        if (attr->nodeName() == "lon")
					    {
					        lon = atof(attr->nodeValue().c_str());
                        }
				    }
				    cout << fixed;
				    cout << "Create points " << i << " id : " << id  <<" , Lon: " << setprecision(7) << lon << " , Lat: " << setprecision(7) << lat << endl;
				    m_ShapePoints.insert(std::pair<long, Wgs84Pos>(id, Wgs84Pos(lon, lat)));
			    }
            } 
        }      
        cout << "parse shape point OK" << endl;
        cout << " size : " << sizeof(m_ShapePoints) <<  endl; 
           
        ofstream outfile;
        outfile.open("../data/shapepoints.txt", ios::out | ios::binary);
        std::map<long, Wgs84Pos>::iterator iter;
        iter = m_ShapePoints.begin();
        while(iter!=m_ShapePoints.end())
        {
            outfile.write((char*)&iter->first,sizeof(long));
            outfile.write((char*)&iter->second, sizeof(Wgs84Pos));
            iter++;
        }
        outfile.close();
        cout << " ShapePoints write over " << endl; 
               
        {
            NodeList* nl = pDoc->getElementsByTagName("way");
            cout << "ways count: " << nl->length() << endl;
            for (int i = 0; i < nl->length(); i++)
            {
                long wayId = 0;
                Wgs84PosList points;                
                Node* node = nl->item(i);
                {
                    NamedNodeMap* nm = node->attributes();
                    if(nm)
                    {
                        int ref = 0;
	                    for(int k = 0; k < nm->length(); k++)
	                    {
		                    Node* attr = nm->item(k);
		                    if (attr->nodeName() == "id")
		                    {
		                        wayId  = atol(attr->nodeValue().c_str());
                            }
	                    }
	                }
	            }
				                           
    			cout << "create road " << wayId  << endl;
                NodeList* cnl = node->childNodes();
                if(cnl)
			    {		
			        long first_ref = 0, last_ref = 0;
			                
				    for(int j = 0; j < cnl->length() ; j++)
				    {
					    Node* cn = cnl->item(j);
					    if (cn->nodeName() == "nd")
					    {
                            NamedNodeMap* nm = cn->attributes();
                            if(nm)
			                {
			                    long ref = 0;
				                for(int k = 0; k < nm->length(); k++)
				                {
					                Node* attr = nm->item(k);
					                if (attr->nodeName() == "ref")
					                {
					                    ref  = atol(attr->nodeValue().c_str());
					                    if (first_ref == 0)
					                    {
					                        first_ref = ref;
					                    }
					                    last_ref = ref;
                                    }
				                }
				                cout << "ref: " << ref  << ", first ref: " << first_ref << "  last_ref: " << last_ref << endl;
				                Wgs84PosMapIter iter = m_ShapePoints.find(ref);
				                if (iter != m_ShapePoints.end())
				                {
				                     points.push_back(iter->second);
                                }

                                
				            }  
				       }
				    }
				   
                    if (first_ref != last_ref)
                    {
                         m_Roads.insert(std::pair<long, Road>(wayId, Road(wayId, road_type_normal, points)));
                    }
                    else
                    {
                         m_Roads.insert(std::pair<long, Road>(wayId, Road(wayId, road_type_area, points)));                    
                    }				    

			    }
            } 
        } 
 
        for(RoadMapIter iter = m_Roads.begin(); iter != m_Roads.end(); iter++)
        {
            cout << "Way id: " << iter->second.id << ", shape points count: " << iter->second.shapePoints.size() << ", type: " << iter->second.type << endl;
            for(std::vector<Wgs84Pos>::iterator iter_1 = iter->second.shapePoints.begin(); iter_1 != iter->second.shapePoints.end(); iter_1++)
            {
                cout << "   Map points lon: " << iter_1->lon << " , lat: " << iter_1->lat << endl;
            }
        }
          
        ofstream outfile1;
        outfile1.open("../data/routes.txt", ios::out | ios::binary);
        std::map<long, Road>::iterator iter1;
        iter1 = m_Roads.begin();
        while(iter1 != m_Roads.end())
        {
            int count = iter1->second.shapePoints.size();
            int roadtype = iter1->second.type;
            outfile1.write((char*)&iter1->second.id, 8);
            outfile1.write((char*)(&count), 4);
            outfile1.write((char*)(&roadtype), 4);
            for(std::vector<Wgs84Pos>::iterator iter_2 = iter1->second.shapePoints.begin(); iter_2 != iter1->second.shapePoints.end(); iter_2++)
            {
                outfile1.write((char*)&iter_2->lon, sizeof(iter_2->lon));
                outfile1.write((char*)&iter_2->lat, sizeof(iter_2->lat));
               cout << "  current lon=: "  << iter_2->lon << " , lat=: " << iter_2->lat << endl;
            }
            iter1++;
            cout <<  "Write wayid=: " << iter1->second.id << " ,  count=: " << count << endl;
           
        }
        outfile1.close();
        cout << " Roads write over " << endl;    

        }  
        catch (Exception& exc)  
        {  
            std::cerr << exc.displayText() << std::endl;  
        } 
        
}

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
    //m_ShapePoints.reserve(10000);
    //m_Roads.reserve(1000);
}

bool DataAcess::open_database()
{
    ifstream in("../data/map.osm");
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
			        int lon = 0;
			        int lat = 0;
				    for(int j = 0; j < nm->length() ; j++)
				    {
					    Node* attr = nm->item(j);
					    if (attr->nodeName() == "id")
					    {
					        id  = atol(attr->nodeValue().c_str());
                        }
					    if (attr->nodeName() == "lat")
					    {
					        lat  = atol(attr->nodeValue().c_str());
                        }
                        if (attr->nodeName() == "lon")
					    {
					        lon = atol(attr->nodeValue().c_str());
                        }
				    }
				    cout << "create points " << i << " " << id << endl;
				    m_ShapePoints.insert(std::pair<int, Wgs84Pos>(id, Wgs84Pos(lon, lat)));
			    }
            } 
        } 
        cout << "parse shape point OK" << endl;
        {
            NodeList* nl = pDoc->getElementsByTagName("way");
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
				                           
                NodeList* cnl = node->childNodes();
                if(cnl)
			    {		        
				    for(int j = 0; j < cnl->length() ; j++)
				    {
					    Node* cn = cnl->item(j);
					    if (cn->nodeName() == "nd")
					    {
                            NamedNodeMap* nm = cn->attributes();
                            if(nm)
			                {
			                    int ref = 0;
				                for(int k = 0; k < nm->length(); k++)
				                {
					                Node* attr = nm->item(k);
					                if (attr->nodeName() == "ref")
					                {
					                    ref  = atol(attr->nodeValue().c_str());
                                    }
				                }
				                Wgs84PosMapIter iter = m_ShapePoints.find(ref);
				                if (iter != m_ShapePoints.end())
				                {
				                     points.push_back(iter->second);
                                }
				            }
				       }
				    }
				    cout << "create road " << wayId << endl;
				    m_Roads.insert(std::pair<int, Road>(wayId, Road(wayId, points)));
			    }
            } 
        }       
 
    }  
    catch (Exception& exc)  
    {  
        std::cerr << exc.displayText() << std::endl;  
    } 
    
    for(RoadMapIter iter = m_Roads.begin(); iter != m_Roads.end(); iter++)
    {
         cout << "road id: " << iter->second.id << "shape points count: " << iter->second.shapePoints.size() << endl;
    }
}

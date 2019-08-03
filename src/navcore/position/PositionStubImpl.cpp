// PositionStubImpl.cpp
#include "PositionStubImpl.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

bool PositionStubImpl::m_IsStart = true;

PositionStubImpl::PositionStubImpl()
{
       m_DemoThread = new std::thread(PositionStubImpl::demo_thread_func, this);
}

PositionStubImpl::~PositionStubImpl() { }


void PositionStubImpl::demo_thread_func(void* data)
{
    PositionStubImpl* parent = (PositionStubImpl*)(data);
    while(m_IsStart)
    {
         cout << "I am working" << endl;
         sleep(1);
         ::v1::commonapi::Position::Shapepoint shapepoint;
         shapepoint.setLon(100);
         shapepoint.setLat(200);         
         parent->firePositionAttributeChanged(shapepoint);
    }
}

void PositionStubImpl::setRoute(const std::shared_ptr<CommonAPI::ClientId> _client, Position::Shapepoints _route, setRouteReply_t _reply){

    std::cout << "setRoute called, setting new values." << std::endl;

};

void PositionStubImpl::startDemo(const std::shared_ptr<CommonAPI::ClientId> _client, startDemoReply_t _reply)
{
       m_IsStart = true;

};

void PositionStubImpl::stopDemo(const std::shared_ptr<CommonAPI::ClientId> _client, stopDemoReply_t _reply)
{
	   m_IsStart = false;
	
};


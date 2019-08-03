// PositionStubImpl.cpp
#include "PositionStubImpl.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

bool PositionStubImpl::m_IsStart=false;

PositionStubImpl::PositionStubImpl()
{
}

PositionStubImpl::~PositionStubImpl() { }


void PositionStubImpl::demo_thread_func()
{
    while(m_IsStart)
    {
         cout << "I am working" << endl;
         sleep(1);
    }
}

void PositionStubImpl::setRoute(const std::shared_ptr<CommonAPI::ClientId> _client, Position::Shapepoints _route, setRouteReply_t _reply){

    std::cout << "setRoute called, setting new values." << std::endl;

};

void PositionStubImpl::startDemo(const std::shared_ptr<CommonAPI::ClientId> _client, startDemoReply_t _reply)
{
       m_IsStart = true;
       m_DemoThread = new std::thread(PositionStubImpl::demo_thread_func);
};

void PositionStubImpl::stopDemo(const std::shared_ptr<CommonAPI::ClientId> _client, stopDemoReply_t _reply)
{
	   m_IsStart = false;
	
};


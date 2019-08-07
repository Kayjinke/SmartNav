// PositionStubImpl.cpp
#include "PositionStubImpl.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

PositionStubImpl::PositionStubImpl()
{
}

PositionStubImpl::~PositionStubImpl() { }


void PositionStubImpl::demo_thread_func(void* data)
{
    PositionStubImpl* parent = (PositionStubImpl*)(data);
    while(!parent->isDone())
    {
         cout << "I am working" << endl;
         sleep(1);
         ::v1::commonapi::Position::Shapepoint shapepoint;
         shapepoint =  parent->getNextPoint();
         parent->firePositionAttributeChanged(shapepoint);
    }
}

void PositionStubImpl::setRoute(const std::shared_ptr<CommonAPI::ClientId> _client, Position::Shapepoints _route, setRouteReply_t _reply){

    std::cout << "setRoute called, setting new values." << std::endl;
    m_Route = _route;

}

void PositionStubImpl::startDemo(const std::shared_ptr<CommonAPI::ClientId> _client, startDemoReply_t _reply)
{
     m_DemoThread = new std::thread(PositionStubImpl::demo_thread_func, this);
}

void PositionStubImpl::stopDemo(const std::shared_ptr<CommonAPI::ClientId> _client, stopDemoReply_t _reply)
{
}

bool  PositionStubImpl::isDone()
{
    return m_CurrentIdx == m_Route.size() - 1;
}

Position::Shapepoint PositionStubImpl::getNextPoint()
{
    if (m_CurrentIdx < m_Route.size() -1)
    {
       return m_Route[++m_CurrentIdx];
    }
}


// PositionStubImpl.cpp
#include "PositionStubImpl.hpp"

PositionStubImpl::PositionStubImpl()  { }
PositionStubImpl::~PositionStubImpl() { }


void PositionStubImpl::setRoute(const std::shared_ptr<CommonAPI::ClientId> _client, Position::Shapepoints _route, setRouteReply_t _reply){

    std::cout << "setRoute called, setting new values." << std::endl;

};

void PositionStubImpl::startDemo(const std::shared_ptr<CommonAPI::ClientId> _client, startDemoReply_t _reply){
};

void PositionStubImpl::stopDemo(const std::shared_ptr<CommonAPI::ClientId> _client, stopDemoReply_t _reply){
};


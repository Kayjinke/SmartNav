// POSITIONStubImpl.hpp
#ifndef POSITIONSTUBIMPL_H_
#define POSITIONSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/PositionStubDefault.hpp>
#include <thread>

using namespace v1::commonapi;

class PositionStubImpl: public v1_0::commonapi::PositionStubDefault {
public:
    PositionStubImpl();
    virtual ~PositionStubImpl();
	virtual void setRoute(const std::shared_ptr<CommonAPI::ClientId> _client, Position::Shapepoints _route, setRouteReply_t _reply);
    virtual void startDemo(const std::shared_ptr<CommonAPI::ClientId> _client, startDemoReply_t _reply);
    virtual void stopDemo(const std::shared_ptr<CommonAPI::ClientId> _client, stopDemoReply_t _reply);
    
    Position::Shapepoint getNextPoint();
    bool  isDone();
private:
    static void demo_thread_func(void* data);

private:
     std::thread*           m_DemoThread;
     Position::Shapepoints  m_Route;
     int                    m_CurrentIdx;
            
};
#endif /* POSITIONSTUBIMPL_H_ */

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
private:
    static void demo_thread_func();

private:
     static bool     m_IsStart;
     std::thread*    m_DemoThread;
            
};
#endif /* POSITIONSTUBIMPL_H_ */

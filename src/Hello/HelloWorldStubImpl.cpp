// HelloWorldStubImpl.cpp
#include "HelloWorldStubImpl.hpp"

HelloWorldStubImpl::HelloWorldStubImpl()
: m_Counter(0),cnt(0) { }
HelloWorldStubImpl::~HelloWorldStubImpl() { }

void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
	std::string _name, sayHelloReply_t _reply)
{
    m_Counter++;

    std::stringstream messageStream;
    messageStream << "Hello " << _name << "!";
    std::cout << "sayHello('" << _name << "'): '" << messageStream.str() << m_Counter << "'\n";

    _reply(messageStream.str());
};

void HelloWorldStubImpl::incCounter() {
    cnt++;
    setXAttribute((int32_t)cnt);
    std::cout << "New counter value = " << cnt << "!" << std::endl;
}
;



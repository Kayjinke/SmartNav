// HelloWorldStubImpl.cpp
#include "NavigationStubImpl.hpp"

NavigationStubImpl::NavigationStubImpl()  { }
NavigationStubImpl::~NavigationStubImpl() { }

void NavigationStubImpl::foo(const std::shared_ptr<CommonAPI::ClientId> _client,
                int32_t _x1,
                std::string _x2,
                fooReply_t _reply) {

    std::cout << "foo called, setting new values." << std::endl;

    int32_t y1 = 86;
    std::string y2 = "xyz";
    _reply(y1, y2);
};

// HelloWorldClient.cpp
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/HelloWorldProxy.hpp>

using namespace v1_0::commonapi;

void recv_cb(const CommonAPI::CallStatus& callStatus, const int32_t& val) {
    std::cout << "Receive callback: " << val << std::endl;
}


int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<HelloWorldProxy<>> myProxy =
    	runtime->buildProxy<HelloWorldProxy>("local", "test");

    std::cout << "Checking availability!" << std::endl;
    
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;
    
   
    while(1)
    {

        
        int32_t value = 0;
        CommonAPI::CallInfo info(1000);
        
                
        CommonAPI::CallStatus callStatus;
        std::string returnMessage;
        myProxy->sayHello("Jinko", callStatus, returnMessage);
        std::cout << "Got message: '" << returnMessage << "'\n";
             
        
        std::cout << "Getting attribute value: " << value << std::endl;
        myProxy->getXAttribute().getValue(callStatus, value, &info);
        std::cout << "Got attribute value: " << value << std::endl;
        
                
        std::function<void(const CommonAPI::CallStatus&, int32_t)> fcb = recv_cb;
        myProxy->getXAttribute().setValueAsync(value, fcb, &info);
        
        sleep(1);
    }
    return 0;
}

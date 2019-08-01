// HelloWorldClient.cpp
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/NavigationProxy.hpp>

using namespace std;

using namespace v1_0::commonapi;

void recv_cb(const CommonAPI::CallStatus& callStatus, const int32_t& val) {
    std::cout << "Receive callback: " << val << std::endl;
}


int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<NavigationProxy<>> myProxy =
    	runtime->buildProxy<NavigationProxy>("local", "navigation");

    std::cout << "Checking availability!" << std::endl;
    
    if (!myProxy)
    {
        cout << "this is a null pointer" << endl;
        return -1;
    }
    
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;
    
   
    while(1)
    {
        int32_t value = 0;
        int32_t inX1 = 5;
        std::string inX2 = "abc";
        int32_t outY1;
        std::string outY2;
        
        CommonAPI::CallInfo info(1000);
        
                
        CommonAPI::CallStatus callStatus;
        std::string returnMessage;
             
        std::cout << "Call foo with synchronous semantics ..." << std::endl;
        myProxy->foo(inX1, inX2, callStatus, outY1, outY2);
        std::cout << "   Input values: x1 = " << inX1 << ", x2 = " << inX2 << std::endl;
        std::cout << "   Output values: y1 = " << outY1 << ", y2 = " << outY2 << std::endl;
        
        
        sleep(1);
    }
    return 0;
}

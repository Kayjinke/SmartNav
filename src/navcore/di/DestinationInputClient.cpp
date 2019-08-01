// HelloWorldClient.cpp
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/DestinationInputProxy.hpp>

using namespace std;

using namespace v1_0::commonapi;

//void recv_cb(const CommonAPI::CallStatus& callStatus, const int32_t& val) {
//    std::cout << "Receive callback: " << val << std::endl;
//}


int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<DestinationInputProxy<>> myProxy =
    	runtime->buildProxy<DestinationInputProxy>("local", "inputdestination");

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
        string streets;
        
        CommonAPI::CallInfo info(1000);
         
        CommonAPI::CallStatus callStatus;
                     
        std::cout << "Input your destination ..." << std::endl;
        cin >> streets;
        //myProxy->getAllStreets(streets, callStatus);
       
        
        
        
        sleep(1);
    }
    return 0;
}

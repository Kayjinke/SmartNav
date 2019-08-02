// HelloWorldService.cpp
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "DestinationInputStubImpl.hpp"

using namespace std;

int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<DestinationInputStubImpl> myService =
    	std::make_shared<DestinationInputStubImpl>();
    runtime->registerService("local", "inputdestination", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    while (true) {
        
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
 }

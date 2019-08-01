// HelloWorldService.cpp
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "NavigationStubImpl.hpp"

using namespace std;

int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<NavigationStubImpl> myService =
    	std::make_shared<NavigationStubImpl>();
    runtime->registerService("local", "navigation", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    while (true) {
        
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
 }

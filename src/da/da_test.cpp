#include "dataacess.h"
#include <iostream>

using namespace std;

int main()
{
    cout << " start read data1.1" << endl;
    DataRead dr;
    dr.shapepoint_read("../data/shapepoints_test.txt");
    dr.road_read("../data/routes_test.txt");
    
    return 0;
}

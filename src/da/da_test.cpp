#include "dataacess.h"
#include <iostream>

using namespace std;

int main()
{
    cout << " start read data1.1" << endl;
    DataRead dr;
    //dr.shapepoint_read("../data/shapepoints_data.txt");
    dr.road_read("routes.txt");
    
    return 0;
}

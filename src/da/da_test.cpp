#include "dataacess.h"
#include <iostream>

using namespace std;

int main()
{
    cout << " start read data1.1_____________" << endl;
    DataRead dr;
    dr.shapepoint_read("../data/shapepoints.txt");
    dr.road_read("../data/routes.txt");
    
    return 0;
}

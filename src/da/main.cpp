#include "dataacess.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "dataacess test application" << endl;
    DataAcess da;
    da.open_database();
       
    return 0;
}

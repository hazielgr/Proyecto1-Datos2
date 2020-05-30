#include <iostream>
#include "VsPointer.h"

int main() {
    VsPointer<string> myPtr = VsPointer<string>::New();
    VsPointer<string> myPtr2 = VsPointer<string>::New();
    VsPointer<string> myPtr3 = VsPointer<string>::New();
    *myPtr = "Haziel";
    myPtr2 = myPtr;
    string str = &myPtr;
    myPtr3 = "Haziel";
    cout<<str<<endl;
    cout<<myPtr.getData()<<endl;
    cout<<myPtr2.getData()<<endl;
    cout<<myPtr3.getData()<<endl;




return 0;
}

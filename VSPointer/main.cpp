#include <iostream>
#include "VsPointer.h"

int main() {
    VsPointer<string> myPtr = VsPointer<string>::New();
    VsPointer<string> myPtr2 = VsPointer<string>::New();
    *myPtr = "Haziel";
    myPtr2 = myPtr;
    cout<<&myPtr<<endl;
    cout<<myPtr.getData()<<endl;
    cout<<myPtr2.getData()<<endl;

return 0;
}

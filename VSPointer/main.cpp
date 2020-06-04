
#include "VsPointer.hpp"
int main() {
    VsPointer<int> haziel = VsPointer<int>::New();
    VsPointer<int> haziel2 = VsPointer<int>::New();
    haziel2 = 8;
    haziel = haziel2;

return 0;
}
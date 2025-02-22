

#include <iostream>
#include <ostream>
#include <vector>

using namespace std;


int main (int argc, char *argv[]) {
    std::vector<int*> list = {};
    list.push_back(new int{3});
    std::cout << "element: " << *list[0] << std::endl;
    list.clear();

    std::cout << "after release element: " << *list[0] << std::endl;
    return 0;
}

#include "matplotlibcpp.h"
#include <iostream>

using namespace std;
namespace plt = matplotlibcpp;

int main() {
    plt::plot({1,3,2,4});
    plt::show();
}

#include <array>
#include <vector>
#include <iostream>
#include "waltrDrawStructure.hpp"

int main(void) {
	// std::vector<int> vec = {0,0,0,0,0};
	// Waltr waltr = Waltr(vec);
	// for(int i =0;i<5;i++) {
	// 	vec[i] = i;
	// }
	// waltr.logVector(vec);
	// drawStructure(arr_c,5);
	// drawStructure(vec);

    std::vector<int> v;
    Waltr waltr = Waltr(v);
    for(int i=0;i<44;i++) {
        v.push_back(i*2);
    }
	waltr.logVector(v);
}

#include <array>
#include <vector>
#include <initializer_list>
#include "drawStructure.hpp"

int main(void) {
	std::array<int,5> arr_stl={0,1,2,3,4};
	int arr_c[5] = {0,1,2,3,4};
	std::vector<int> vec = {5,6,7,8,9};
	
	DrawStructure drawStructure = DrawStructure(arr_stl);
	// drawStructure(arr_c,5);
	// drawStructure(vec);
}

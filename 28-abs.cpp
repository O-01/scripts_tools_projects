#include <iostream>

template <typename T>
T abs(T x) {
	return x < 0 ? x * -1 : x;
}

int main(void) {
	int neg = -144;
	std::cout << "The absolute value of " << neg << "is " << abs(neg) << std::endl;
	return 0;
}

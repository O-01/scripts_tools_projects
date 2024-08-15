#include <iostream>
#include <string>

#define STRINGIFY(x) #x
#define STR(x) STRINGIFY(x)
#define STOI(x) (std::stoi((x)))

template <typename T>
T abs(T x) {
	return x < 0 ? x * -1 : x;
}

template <typename T>
T max(T x, T y) {
	return x > y ? x : y;
}

int main(int argc, char *argv[]) {
	if (argc < 2)
		return std::cout << "Usage: " << argv[0] << " `number` `comparison`" << std::endl, 1;
	std::cout << "\033[3J\033[H\033[2J";
	std::cout << "----------------------------------------------------------------" << std::endl
		<< "Absolute value of `" STR(argv[1]) "`(= " << argv[1] << ") is: " << abs(STOI(argv[1])) << std::endl
		<< "Absolute value of `" STR(argv[2]) "`(= " << argv[2] << ") is: " << abs(STOI(argv[2])) << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "`" STR(argv[1]) "`(= " << argv[1] << ")"
		<< (max(STOI(argv[1]), STOI(argv[2])) == STOI(argv[2]) ? " is less than " : " is greater than ")
		<< "`" STR(argv[2]) "`(= " << argv[2] << ")" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	int neg = -144, other = -1;
	std::cout << "Absolute value of `" << STR(neg) << "` is: " << abs(neg) << std::endl
		<< "Absolute value of `" << STR(other) << "` is: " << abs(other) << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "`" STR(neg) "`(= " << neg << ")"
		<< (max(neg, other) == other ? " is less than " : " is greater than ")
		<< "`" STR(other) "`(= " << other << ")" << std::endl;
	other = -4096;
	std::cout << "`" STR(other) "` changed to " << other << std::endl;
	std::cout << "`" STR(neg) "`(= " << neg << ")"
		<< (max(neg, other) == other ? " is less than " : " is greater than ")
		<< "`" STR(other) "`(= " << other << ")" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	return 0;
}

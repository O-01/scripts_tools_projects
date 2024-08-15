#include <iostream>
#include <string>

#define DIVIDER "------------------------------------------------"
#define STOI(x) (std::stoi((x)))
#define STRINGIFY(x) #x
#define STR(x) STRINGIFY(x)

template <typename T>
T abs(T x) {
	return x < 0 ? x * -1 : x;
}

template <typename T>
T max(T x, T y) {
	return x > y ? x : y;
}

template <typename T>
int cmp(T x, T y) {
	return x == y ? 0 : x < y ? -1 : 1;
}

int main(int argc, char *argv[]) {
	if (argc < 2)
		return std::cout << "Usage: " << argv[0] << " `number` `comparison`" << std::endl, 1;
	int out = 0;
	std::cout << "\033[3J\033[H\033[2J";
	try {
		std::cout
			<< "Absolute value of `" STR(argv[1]) "`(= " << argv[1] << ") is: " << abs(STOI(argv[1])) << std::endl
			<< "Absolute value of `" STR(argv[2]) "`(= " << argv[2] << ") is: " << abs(STOI(argv[2])) << std::endl
			<< DIVIDER << std::endl;
		std::cout << "`" STR(argv[1]) "`(= " << argv[1] << ")"
			<< (!(out = cmp(STOI(argv[1]), STOI(argv[2]))) ? " is equal to "
				: out < 0 ? " is less than " : " is greater than ")
			<< "`" STR(argv[2]) "`(= " << argv[2] << ")" << std::endl;
	}
	catch (std::invalid_argument const& ex) {
		std::cout << "\a\n \033[4;31m## std::invalid_argument::what():\033[0;39m " << ex.what() << std::endl;
	}
	catch (std::out_of_range const& ex) {
		std::cout << "\a\n \033[4;31m## std::out_of_range::what():\033[0;39m " << ex.what() << std::endl;
	}
	std::cout << DIVIDER << std::endl;
	int neg = -144, other = -1;
	std::cout
		<< "Absolute value of `" << STR(neg) << "` is: " << abs(neg) << std::endl
		<< "Absolute value of `" << STR(other) << "` is: " << abs(other) << std::endl
		<< DIVIDER << std::endl
		<< "`" STR(neg) "`(= " << neg << ")"
		<< (max(neg, other) == other ? " is less than " : " is greater than ")
		<< "`" STR(other) "`(= " << other << ")" << std::endl;
	other = -4096;
	std::cout
		<< "`" STR(other) "` changed to " << other << std::endl
		<< "`" STR(neg) "`(= " << neg << ")"
		<< (max(neg, other) == other ? " is less than " : " is greater than ")
		<< "`" STR(other) "`(= " << other << ")" << std::endl
		<< DIVIDER << std::endl;
	return 0;
}

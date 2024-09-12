#include <cstdlib>
#include <iostream>

#define FIZZ "Fizz"
#define BUZZ "Buzz"
#define NOTHING ""

#define MUL3(x) (!((x) % 3))
#define MUL5(x) (!((x) % 5))
#define MUL3OR5(x) (MUL3((x)) || MUL5((x)))

void fizzbuzz_odd(char *num);

int main(int argc, char **argv) {
	if (argc != 2 || !(std::atoi(argv[1])))
		return std::cout <<
			"\x1B[1;31m** PLEASE SUPPLY NUMBER\x1B[0;39m\n" <<
			"Usage: '" << argv[0] << " <number>'" << std::endl, 1;
	fizzbuzz_odd(argv[1]);
	return 0;
}

void fizzbuzz_odd(char *num) {
	for (int i = 1, num_int = std::atoi(num); i < num_int + 1; ++i)
		std::cout <<
			(MUL3(i) ? FIZZ : NOTHING) <<
			(MUL5(i) ? BUZZ : NOTHING) <<
			(!MUL3OR5(i) ? std::to_string(i) : NOTHING) << std::endl;
}

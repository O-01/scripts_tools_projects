#include "../pub04str_to_hex.c"

// gcc -Wall -Werror -Wextra -pedantic test/pub04str_to_hex-main.c -I. -o pub04str_to_hex-test
// Usage: ./pub04str_to_hex-test <public key>

// test public key string: "042835908c04f2b9a75153da5e4a4660222a5970cfdda92a1abb38c140a2d65f7ef6e55663284f8a5bbc7b6eb8e78f0b98cd2b2790df2b63c6551f7cb6a9fa9aeb"

int main(int argc, char **argv) {
	uint8_t test[EC_PUB_LEN] = {0};

	if (argc != 2)
		return (fprintf(stderr, "\x1b[1;31mUsage: %s <public key>\n\x1b[0m", argv[0]), 1);
	printf("\x1b[1;3;4;33mINPUT STR:\x1b[0m %s\n" "\x1b[1;3;4;35mCONVERTED:\x1b[0m ", argv[1]);
	pub04str_to_hex((uint8_t *)argv[1], test);
	print_hex_buf(test, EC_PUB_LEN), putchar('\n');
	puts("\x1b[1;3;32mSUCCESS!\x1b[0m");
	return (0);
}

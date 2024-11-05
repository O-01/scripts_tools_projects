#include <chrono>
#include <csignal>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>

#define MESSAGE "JUST ONE SMILE ON YOUR FACE WAS ALL IT TOOK TO CHANGE MY FORTUNE"

volatile bool loop = true;

void break_loop(int __attribute__((unused)) sig) { loop = false; }

int main(void) {
	int iter = 0, pid = getpid();
	std::string *display = new std::string {MESSAGE};
	std::cout << "\x1B[?47h\x1B[3J\x1B[H\x1B[2J" << "[ PID: " << pid << " ]" << std::endl;
	signal(SIGINT, break_loop);
	while (loop) {
		std::cout << pid << " : "
			<< "[" << std::setfill('_') << std::setw(4) << iter++ << "] : "
			<< display << " : " << *display << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1200));
	}
	delete display;
	std::cout << "\x1B[?47l";
	return (0);
}

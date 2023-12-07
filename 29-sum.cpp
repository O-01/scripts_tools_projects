#include <cstdio>

int sum(int x, int y) {
    return x + y;
}

int main() {
    int x = 12, y = 16;

    printf("The sum of %d and %d is %d.\n", x, y, sum(x, y));
}

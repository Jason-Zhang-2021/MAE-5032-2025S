#include <signal.h>
#include <stdio.h>

void handler(int sig) {
    printf("Received signal %d\n", sig);
}

int main() {
    signal(SIGINT, handler);  // 覆盖 Ctrl+C 的默认行为
    while (1) {}
}


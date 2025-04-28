#include <stdio.h>
#include <math.h>

void heavy_inner_loop() {
    double sum = 0.0;
    for (unsigned int i = 0; i < 20000000; ++i) {
        sum += sqrt(i);
    }
    printf("Sum in heavy_inner_loop: %f\n", sum);
}

void helper_func() {
    for (unsigned int i = 0; i < 1000; ++i) {
        sqrt(i);
    }
}

void compute_heavy() {
    printf("\nInside compute_heavy()\n");
    for (int j = 0; j < 3; ++j) {
        helper_func(); // light helper call
        heavy_inner_loop();
    }
}

void compute_light() {
    printf("\nInside compute_light()\n");
    double sum = 0.0;
    for (unsigned int i = 0; i < 100000; ++i) {
        sum += sqrt(i);
    }
    printf("Sum in compute_light: %f\n", sum);
}

void process_data() {
    printf("\nProcessing data...\n");
    compute_heavy();
    compute_light();
}

void init() {
    printf("\nInitializing...\n");
    for (unsigned int i = 0; i < 500000; ++i) {
        sqrt(i);
    }
}

void write_output() {
    printf("\nWriting output...\n");
    for (unsigned int i = 0; i < 200000; ++i) {
        sqrt(i);
    }
}

void cleanup() {
    printf("\nCleaning up...\n");
    for (unsigned int i = 0; i < 100000; ++i) {
        sqrt(i);
    }
}

void finalize() {
    printf("\nFinalizing...\n");
    write_output();
    cleanup();
}

int main() {
    printf("\nInside main()\n");
    init();
    process_data();
    finalize();
    return 0;
}

// EOF

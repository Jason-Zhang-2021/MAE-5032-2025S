// test_fftw.c
#include <stdio.h>
#include <fftw3.h>

int main() {
    int N = 8;
    fftw_complex in[N], out[N], inv[N];
    fftw_plan p_forward, p_backward;

    // Fill input with real values, imag = 0
    for (int i = 0; i < N; ++i) {
        in[i][0] = i + 1;  // real part
        in[i][1] = 0.0;    // imag part
    }

    // Create plans
    p_forward = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    p_backward = fftw_plan_dft_1d(N, out, inv, FFTW_BACKWARD, FFTW_ESTIMATE);

    // Execute forward FFT
    fftw_execute(p_forward);

    printf("FFT result:\n");
    for (int i = 0; i < N; ++i)
        printf("out[%d] = %.2f + %.2fi\n", i, out[i][0], out[i][1]);

    // Execute inverse FFT
    fftw_execute(p_backward);

    printf("\nInverse FFT (should recover input):\n");
    for (int i = 0; i < N; ++i)
        printf("inv[%d] = %.2f + %.2fi\n", i, inv[i][0] / N, inv[i][1] / N);

    // Cleanup
    fftw_destroy_plan(p_forward);
    fftw_destroy_plan(p_backward);
    fftw_cleanup();

    return 0;
}

// EOF

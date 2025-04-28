gcc -O0 -g heavy_sleep.c -o heavy_sleep
time ./heavy_sleep
rm -rf heavy_sleep

gcc -O0 -g heavy_compute.c -o heavy_compute
time ./heavy_compute
rm -rf heavy_compute

gcc -O0 -g heavy_syscall.c -o heavy_syscall
time ./heavy_syscall
rm -rf heavy_syscall

rm -rf *.dSYM

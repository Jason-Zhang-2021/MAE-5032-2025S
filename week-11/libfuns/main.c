#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>     // gettimeofday 
#include <sys/resource.h> // getrusage
#include <sys/times.h>    // times

int main()
{
  // Record start time using times()
  struct tms start_tms, end_tms;
  clock_t start_clock = times(&start_tms);

  // Record start resource usage using getrusage()
  struct rusage start_usage, end_usage;
  getrusage(RUSAGE_SELF, &start_usage);

  // Record start wall-clock time using gettimeofday()
  struct timeval start_wall, end_wall;
  gettimeofday(&start_wall, NULL);

  // === Perform heavy computation ===
  printf("Start heavy work...\n");
  volatile double dummy = 0;
  for (long long i = 0; i < 1e8; ++i)
    dummy += i * 0.000001;
  
  printf("Heavy work done!\n");

  // Record end times
  clock_t end_clock = times(&end_tms);
  getrusage(RUSAGE_SELF, &end_usage);
  gettimeofday(&end_wall, NULL);

  // === Print timing information ===
  // 1. Using times()
  long ticks_per_second = sysconf(_SC_CLK_TCK);
  printf("\n=== times() ===\n");
  printf("User time: %.4f seconds\n",
      (end_tms.tms_utime - start_tms.tms_utime) / (double)ticks_per_second);
  printf("System time: %.4f seconds\n",
      (end_tms.tms_stime - start_tms.tms_stime) / (double)ticks_per_second);

  // 2. Using getrusage()
  printf("\n=== getrusage() ===\n");
  double user_sec = (end_usage.ru_utime.tv_sec - start_usage.ru_utime.tv_sec) +
    (end_usage.ru_utime.tv_usec - start_usage.ru_utime.tv_usec) / 1e6;
  double sys_sec  = (end_usage.ru_stime.tv_sec - start_usage.ru_stime.tv_sec) +
    (end_usage.ru_stime.tv_usec - start_usage.ru_stime.tv_usec) / 1e6;
  printf("User time: %.4f seconds\n", user_sec);
  printf("System time: %.4f seconds\n", sys_sec);

  // Output memory usage (maximum resident set size)
  printf("Maximum resident set size: %ld KB\n", end_usage.ru_maxrss);

  // 3. Using gettimeofday()
  printf("\n=== gettimeofday() (wall clock) ===\n");
  double wall_sec = (end_wall.tv_sec - start_wall.tv_sec) +
    (end_wall.tv_usec - start_wall.tv_usec) / 1e6;
  printf("Elapsed wall clock time: %.4f seconds\n", wall_sec);

  return 0;
}

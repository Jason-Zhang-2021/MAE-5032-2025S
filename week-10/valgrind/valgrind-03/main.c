#include <iostream>
#include <cstring>

class Data 
{
  public:
    char* buffer;

    Data(size_t size) {
      buffer = new char[size];
      std::strcpy(buffer, "Valgrind tutorial");
    }

    ~Data() {
      // Intentionally missing delete[] buffer;
    }

    void corrupt() {
      delete[] buffer;     // Free here
      buffer[0] = 'X';     // Use-after-free
    }
};

void leak_indirect() 
{
  int ** indirect = new int*[2];
  indirect[0] = new int[10];  // Never deleted
  indirect[1] = new int[10];  // Never deleted
                              // No delete for indirect or indirect[i]
}

void still_reachable() 
{
  static int* reachable = new int[5];  // Only once, stays until program ends
  reachable[0] = 42;
}

int main() 
{
  Data* d1 = new Data(100);
  
  d1->corrupt();          // Triggers use-after-free

  leak_indirect();        // Causes indirect leak

  still_reachable();      // Will show as still reachable

  return 0;               // d1 not deleted (definitely lost)
}

// EOF

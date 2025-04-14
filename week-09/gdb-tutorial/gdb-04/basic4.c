#include <iostream>

int unknown(int &s)
{
  s += 1;
  return s;
}

void small(int &a)
{
  a /= 68;
}

int bar(int &p)
{
  p *= 3;
  return unknown(p);
}

void oof(int &n)
{
  n *= n - 20;
  n = n - bar(n);
}

void foo(int &z)
{
  z = bar(z);
  oof(z);
  small(z);
  ++z;
}

int main()
{
  int x = 10;
  foo(x);

  if(x != 0)
  {
    std::cerr<<" Error: x = "<<x<<", which is not 0.\n";
    return 3;
  }
}



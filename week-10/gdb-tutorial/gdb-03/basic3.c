#include <iostream>

int factorial(const int &n)
{
  if(n != 0) return n * factorial(n-1);
  else return 1;
}

int main()
{
  int n;
  std::cout<<"Please enter a positive integer: \n";
  if(std::cin>>n && n>=0)
    std::cout<<n<<"! = "<<factorial(n)<<std::endl;
  else
    std::cout<<"That is not a positive integer!\n";
}

// EOF

#include <bits/stdc++.h>

using namespace std;

class A
{
   int a;
   public:
       A()
       {
          a = 1;
       }
       // virtual void show() = 0;
       void show()
       {
          cout <<a<<endl;
       }
};

class B: public A
{
   int b;
   public:
       B()
       {
          b = 2;
       }
       // virtual void show()
       void show()
       {
          cout <<b<<endl;
       }
};

int main()
{
   A *pA;
   // B oB;
   // B *pB = new B;
   pA = new B;
   // pA = &oB;
   // pA = pB;
   pA->show();
   return 0;
}
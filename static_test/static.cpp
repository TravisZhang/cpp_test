#include <bits/stdc++.h>

using namespace std;

class A
{
   int a;
   static double s[3];
   public:
       A()
       {
          a = 1;
       }
       // virtual void show() = 0;
       // virtual void show()
       void show()
       {
          cout <<a<<endl;
       }
       virtual void print_s()
       // void print_s()
       {
       	  cout << "print s"<<endl;
          for(auto si: s)
          {
          	cout << si << endl;
          }
          cout << "print end" << endl;
       }
       virtual void print_s_addr() {
       	 cout << "s addr:" << s << endl;
       }
};

class B: public A
{
   int b;
   static constexpr double s[3] = {3.0, 4.0, 5.0}; // only available in c++17 or newer
   static constexpr int a0 = 3;
   static constexpr int a1 = a0*2;
   static constexpr double ss[a1] = {0.5};
   
   static constexpr int as[a1] = {0};
   // static double s[3];
   static void init_as() {
   		// ss = {8.0,9.0,10.0};
       	 int i = 0;
       	 // for(auto& ai: ss)
       	 // {
       	 // 	// ai = ++i; // still read only !!!!!!!
       	 // }
       }
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
       void print_s()
       {
       	  cout << "print s"<<endl;
          for(auto si: s)
          {
          	cout << si << endl;
          }
          cout << "print end" << endl;
       }
       void print_s_addr() {
       	 cout << "s addr:" << s << endl;
       }
       void init_ss() {
       	 double i = 6;
       	 for(auto& si: ss)
       	 {
       	 	// si = ++i; // read only !!!!!!
       	 }
       }
       void print_ss() {
       	 for(auto& si: ss)
       	 {
       	 	cout << "ss: " << si << endl;
       	 }
       }
       void init() {
       	init_as();
       }
       

};



double A::s[3] = {0.0, 1.0, 2.0};

// double B::s[3] = {3.0, 4.0, 5.0};

int main()
{
   A *pA;
   // B oB;
   B *pB = new B;
   pA = new B;
   // pA = new A;
   // pA = &oB;
   // pA = pB;
   A *pA1 = new A;
   pA->show();
   cout << "pA:" << pA << endl;
   pA->print_s_addr();
   pA->print_s();
   
   cout << "pB:" << pB << endl;
   pB->print_s_addr();
   pB->print_s();
   
   cout << "pA1:" << pA1 << endl;
   pA1->print_s_addr();
   pA1->print_s();
   pB->init_ss();
   pB->print_ss();
   pB->init();
   
   delete(pA);
   delete(pB);
   delete(pA1);
   return 0;
}
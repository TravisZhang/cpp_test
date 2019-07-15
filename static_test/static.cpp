#include <bits/stdc++.h>

using namespace std;

class A
{
   protected:
    int a;
    static double s[3];
    static constexpr int share[] = {12,34,56};
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

       void print_share()
       {
          cout << "print share"<<endl;
          for(auto si: share)
          {
            cout << si << endl;
          }
          cout << "print end" << endl;
       }
       void print_share_addr() {
         cout << "share addr:" << share << endl;
       }


       void init() {
       	init_as();
       }
       

};

void print_angle() {
	static double angle = 2;

	cout << "angle: " << ++angle << endl;

}


double A::s[3] = {0.0, 1.0, 2.0};

constexpr int A::share[];

// double B::s[3] = {3.0, 4.0, 5.0};

constexpr double B::s[3];

int main()
{
   A *pA;
   // B oB;
   B *pB = new B;
   pA = new B;

   // pA = new A;
   // pA = &oB;
   // pA = pB;
   pA->show();
   cout << "pA:" << pA << endl;
   pA->print_s_addr();
   pA->print_s();
   // pA->print_share_addr(); // error: A has no member
   // pA->print_share(); // error: A has no member
   cout << endl;
   
   cout << "pB:" << pB << endl;
   pB->print_s_addr();
   pB->print_s();
   pB->print_share_addr();
   pB->print_share();
   cout << endl;
   
   B *pB1 = new B;
   cout << "pB1:" << pB1 << endl;
   pB1->print_s_addr();
   pB1->print_s();
   pB1->print_share_addr();
   pB1->print_share();
   cout << endl;

   A *pA1 = new A;
   cout << "pA1:" << pA1 << endl;
   pA1->print_s_addr();
   pA1->print_s();
   cout << endl;
   
   A *pA2 = new A;
   cout << "pA2:" << pA2 << endl;
   pA2->print_s_addr();
   pA2->print_s();
   cout << endl;

   A A3;
   cout << "A3:" << &A3 << endl;
   A3.print_s_addr();
   A3.print_s();
   cout << endl;


   for(int i = 0; i < 3; ++i)
   		print_angle();
   
   delete(pA);
   delete(pB);
   delete(pB1);
   delete(pA1);
   delete(pA2);
   return 0;
}
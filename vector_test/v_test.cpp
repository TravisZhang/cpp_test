#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    vector<int> vect;   
    vect.push_back(1);
    vect.push_back(2);
    vect.push_back(3);
    vect.push_back(4);
    // vect.resize(10);    //新的空间不覆盖原有四个元素占有的空间，现在size和capacity都是10
    vect.resize(10,0); 
    cout<<"size "<<vect.size()<<endl;
    int i = 0;
    for (i = 0; i < vect.size(); i++)
    {
        cout<<"i: "<<i<<" v: "<<vect[i]<<endl; 
    }

	vector<int> vect1;       
    vect1.resize(10,1);    //分配100个空间
    // vect1.clear();
    vect1.resize(10);
    vect1.push_back(1);
    vect1.push_back(2);
    vect1.push_back(3);
    vect1.push_back(4);
	cout<<"size "<<vect1.size()<<endl; //现在size和capacity都是104
    for (i = 0; i < vect1.size(); i++)
    {
        cout<<"i: "<<i<<" v: "<<vect1[i]<<endl; 
    }

    // vector<int> vect2(vect1);
    vector<int> vect2;
    vect2.push_back(1);
    vect2.push_back(2);
    vect2.push_back(3);
    vect2.push_back(4);
    vect2.reserve(10);
    vect2.resize(6,1);
    cout<<"size "<<vect2.size()<<endl;  //size为4，但是capacity为10
    for (i = 0; i < vect2.size(); i++)
    {
        cout<<"i: "<<i<<" v: "<<vect2[i]<<endl; 
    }

    //从上面例子可以看出，不管是调用resize还是reserve，二者对容器原有的元素都没有影响。

    return 0;
}
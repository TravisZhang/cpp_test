#include "myvector.h"

using namespace myfun;

int main(int argc, char* argv[])
{

    vector<int> v_test;
    v_test.reserve(0);

    Myvector<int> v0(5,3);
    cout << "v0 capacity:" << v0.capacity() << endl;
    cout << "v0 size:" << v0.size() << endl;
    Myvector<int> v(v0);
    cout << "v capacity:" << v.capacity() << endl;
    v.reserve(10);
    cout << "v capacity after reserve:" << v.capacity() << endl;
    // v.pop_back();
    cout << "v size:" << v.size() << endl;

    print_myvec(v);

    for(size_t i = 0; i < v.size(); ++i)
    {
        v[i] = i;
    }
    print_myvec(v);

    cout << endl;

    /*resize & reserve test*/
    cout << "begin resize & reserve test" << endl;
    struct Point
    {
        // Point(){}
        Point(int a=111,int b=222):x(a),y(b){}
        int x,y;
    };
    Point p1[3];
    Myvector<Point> mypvec(3);
    cout << "mypvec size:" << mypvec.size() << endl;
    cout << "mypvec capacity:" << mypvec.capacity() << endl;
    mypvec.resize(5);
    cout << "mypvec size after resize:" << mypvec.size() << endl;
    cout << "mypvec capacity:" << mypvec.capacity() << endl;
    Point p2(1,2);
    mypvec.resize(10,p2);
    cout << "mypvec size after resize with input value:" << mypvec.size() << endl;
    cout << "mypvec capacity:" << mypvec.capacity() << endl;
    mypvec.reserve(20);
    cout << "mypvec capacity after reserve:" << mypvec.capacity() << endl;
    for(size_t i = 0; i < mypvec.size(); ++i)
    {
        cout << "mypvec[" << i << "].x:" << mypvec[i].x << endl;
    }
    cout << endl;

    /*Copy test*/
    cout << "begin copy test" << endl;
    Myvector<Point> mypvec1(mypvec);
    cout << "mypvec1 size:" << mypvec1.size() << endl;
    cout << "mypvec1 capacity:" << mypvec1.capacity() << endl;
    for(size_t i = 0; i < mypvec1.size(); ++i)
    {
        cout << "mypvec1[" << i << "].x:" << mypvec1[i].x << endl;
    }
    cout << endl;

    /* Move test*/
    cout << "begin move test" << endl;
    Myvector<Point> mypvec5(std::move(mypvec1));
    cout << "mypvec1 size:" << mypvec1.size() << endl;
    cout << "mypvec1 capacity:" << mypvec1.capacity() << endl;
    cout << "mypvec5 size:" << mypvec5.size() << endl;
    cout << "mypvec5 capacity:" << mypvec5.capacity() << endl;
    for(size_t i = 0; i < mypvec5.size(); ++i)
    {
        cout << "mypvec5[" << i << "].x:" << mypvec5[i].x << endl;
    }
    // cout << "mypvec1[" << "0" << "].x:" << mypvec1[0].x << endl;
    cout << endl;

    /*Insert test*/
    cout << "begin insert test" << endl;
    Myvector<Point>::myiterator it;
    it = mypvec.begin();
    Point p3(3,4);
    mypvec.insert(it+mypvec.size(),12,p3);
    // mypvec.insert(it+50,12,p3);
    cout << "mypvec size after insert:" << mypvec.size() << endl;
    cout << "mypvec capacity after insert:" << mypvec.capacity() << endl;
    for(size_t i = 0; i < mypvec.size(); ++i)
    {
        cout << "mypvec[" << i << "].x:" << mypvec[i].x << endl;
    }
    cout << endl;

    /*Pushback test*/
    Point p4(5,6);
    size_t origin_size = mypvec.size();
    size_t origin_cap = mypvec.capacity();
    size_t total_num = origin_cap-origin_size;
    cout << "begin push back test"<< total_num << " elements" << endl;
    for(size_t i = 0; i < total_num; ++i)
        mypvec.push_back(p4);
    cout << "mypvec size after push_back:" << mypvec.size() << endl;
    cout << "mypvec capacity after push_back:" << mypvec.capacity() << endl;
    for(size_t i = 0; i < mypvec.size(); ++i)
    {
        cout << "mypvec[" << i << "].x:" << mypvec[i].x << endl;
    }
    cout << endl;

    /* copy assignment test*/
    cout << "begin copy assignment test" << endl;
    Myvector<Point> mypvec2;
    cout << "mypvec2 size before:" << mypvec2.size() << endl;
    cout << "mypvec2 capacity before:" << mypvec2.capacity() << endl;
    mypvec2 = mypvec;
    cout << "mypvec2 size:" << mypvec2.size() << endl;
    cout << "mypvec2 capacity:" << mypvec2.capacity() << endl;
    for(size_t i = 0; i < mypvec2.size(); ++i)
    {
        cout << "mypvec2[" << i << "].x:" << mypvec2[i].x << endl;
    }
    cout << "mypvec size:" << mypvec.size() << endl;
    cout << endl;

    /* move assignment test*/
    cout << "begin move assignment test" << endl;
    Myvector<Point> mypvec3;
    cout << "mypvec3 size before:" << mypvec3.size() << endl;
    cout << "mypvec3 capacity before:" << mypvec3.capacity() << endl;
    mypvec3 = std::move(mypvec);
    cout << "mypvec size:" << mypvec.size() << endl;
    cout << "mypvec capacity:" << mypvec.capacity() << endl;
    cout << "mypvec3 size:" << mypvec3.size() << endl;
    cout << "mypvec3 capacity:" << mypvec3.capacity() << endl;
    for(size_t i = 0; i < mypvec3.size(); ++i)
    {
        cout << "mypvec3[" << i << "].x:" << mypvec3[i].x << endl;
    }
    cout << "mypvec size:" << mypvec.size() << endl;
    // cout << "mypvec[" << "0" << "].x:" << mypvec[0].x << endl;
    cout << endl;

    /* test multidimension vector */
    cout << "begin multidimension vector test" << endl;
    Myvector<Myvector<Point>> my2dpvec;
    my2dpvec.resize(10);
    for(size_t i = 0; i < 10; ++i)
    {
        Point p5(7,8);
        my2dpvec[i].resize(5);
        for(size_t j = 0; j < 5; ++j)
        {
            my2dpvec[i][j] = mypvec3[0];
        }
    }

    cout << "my2dpvec size: " << my2dpvec.size() << ", " << my2dpvec[0].size() << endl;
    cout << "my2dpvec[1][2].x:" <<  my2dpvec[1][2].x << " y:" << my2dpvec[1][2].y << endl;



    cout <<endl<< "end of test!!!" << endl;




    return 0;
}

#include <vector>
#include <memory.h>
#include <iostream>

namespace myfun
{
using namespace std;

template<class T>
class Myvector
{
public:

    /********************** types **********************/
    typedef T* myiterator;

    /********************* functions **********************/
    Myvector():pstart_(0),pend_(0),resSize_(0),actSize_(0){};

    Myvector(auto in)
    {
        in = in < 0 ? 0 : in;
        size_t n = static_cast<size_t>(in);
        if(n != 0)
        {
            size_t nn = 1;
            while(nn < n)
            {
                nn *= 2;
            }
            pstart_ = new (std::nothrow) T[nn];
            if (!pstart_) {
                // Handle error
                cout << "ERROR: memory allocation failed !!!!" << endl;
            }
            else
            {
                resSize_ = nn;
                actSize_ = n;
                pend_ = pstart_ + n;
            }
        }
    }

    Myvector(auto in, const T& v)
    {
        in = in < 0 ? 0 : in;
        size_t n = static_cast<size_t>(in);
        if(n != 0)
        {
            size_t nn = 1;
            while(nn < n)
            {
                nn *= 2;
            }
            pstart_ = new (std::nothrow) T[nn];
            // cout << "pstart_ established" << endl;
            if (!pstart_) {
                // Handle error
                cout << "ERROR: memory allocation failed !!!!" << endl;
            }
            else
            {
                resSize_ = nn;
                actSize_ = n;
                pend_ = pstart_ + n;
                myiterator p = pstart_;
                while(1)
                {
                    // cout << "assigning value, n:" << n << endl;
                    *p++ = v;
                    if(--n == 0)
                        break;
                }
            }
        }
    }

    /*Copy constructor*/
    Myvector(const Myvector& mv)
    {
        if(this == &mv)
        {
            cout << "same!!!" << endl;
            return;
        }
        if(mv.empty())
        {
            cout << "empty!!!" << endl;
            return;
        }
        else
        {
            size_t n = mv.size();
            size_t nn = mv.capacity();
            pstart_ = new (std::nothrow) T[nn];
            // cout << "pstart_ established" << endl;
            if (!pstart_) {
                // Handle error
                cout << "ERROR: memory allocation failed !!!!" << endl;
            }
            else
            {
                resSize_ = nn;
                actSize_ = n;
                pend_ = pstart_ + n;
                // myiterator p = pstart_;
                // while(1)
                // {
                //     // cout << "assigning value, n:" << n << endl;
                //     // cout << "mv:" << mv[actSize_-n] << endl;
                //     *p++ = mv[actSize_-n];
                //     // cout << "p:" << *(p-1) << endl;
                //     if(--n == 0)
                //         break;
                // }
                memcpy( pstart_, mv.pstart_, actSize_ * sizeof(T) );

            }
        }
    }

    /*Move constructor*/
    Myvector(Myvector&& mv)
    {
        pstart_ = mv.begin();
        pend_ = mv.end();
        resSize_ = mv.capacity();
        actSize_ = mv.size();
        // cout << "pstart_ established" << endl;
        mv.~Myvector();
        // cout << "mv deleted" << endl;
    }


    /*Element access overload*/
    T operator[] (auto&& in) // rvalue reference (can be used for lvalue too)
    {
        in = in < 0 ? 0 : in;
        in = in > actSize_ ? actSize_ : in;
        size_t n = static_cast<size_t>(in);
        return *(pstart_+n);
    }
    // T operator[] (auto& in) // lvalue reference
    // {
    //     in = in < 0 ? 0 : in;
    //     in = in > actSize_ ? actSize_ : in;
    //     size_t n = static_cast<size_t>(in);
    //     return *(pstart_+n);
    // }

    /*Array subscript operator overload for value assign*/
    T& operator[](size_t idx) 
    {   
        idx = idx < 0 ? 0 : idx;
        idx = idx >= actSize_ ? (actSize_-1) : idx;
        return pstart_[idx]; 
    }
    const T& operator[](size_t idx) const 
    { 
        idx = idx < 0 ? 0 : idx;
        idx = idx >= actSize_ ? actSize_-1 : idx;
        return pstart_[idx]; 
    }

    /*Copy Assignment Constructor*/
    Myvector& operator=(const Myvector& mv)
    {
        if(this != &mv)
        {
            size_t n = mv.size();
            size_t nn = 1;
            while(nn < n)
            {
                nn *= 2;
            }
            // cout << "deconstructing" << endl;
            for(myiterator p = pstart_; p < pend_; ++p)
            {
                // cout << "deconstructing element" << endl;
                p->~T();
            }
            // delete [] pstart_;
            pstart_ = new (std::nothrow) T[nn];
            // cout << "pstart_ established" << endl;
            if (!pstart_) {
                // Handle error
                cout << "ERROR: memory allocation failed !!!!" << endl;
            }
            else
            {
                memcpy( pstart_, mv.begin(), (mv.size()) * sizeof(T) ); 
                // memset( pstart_, 0, nn * sizeof(T) );
                actSize_ = mv.size();
                pend_ = pstart_ + actSize_;
                resSize_ = nn;
            }
        }
        return *this;
    }

    /*Move Assignment Constructor*/
    Myvector& operator=(Myvector&& mv)
    {
        if(this != &mv)
        {
            // cout << "deconstructing" << endl;
            for(myiterator p = pstart_; p < pend_; ++p)
            {
                // cout << "deconstructing element" << endl;
                p->~T();
            }
            // delete [] pstart_;
            pstart_ = mv.begin();
            pend_ = mv.end();
            resSize_ = mv.capacity();
            actSize_ = mv.size();
            // cout << "pstart_ established" << endl;
            mv.~Myvector();
            // cout << "mv deleted" << endl;
        }
        return *this;
    }

    /*Deconstructor*/
    ~Myvector()
    {
        // cout << "deconstructing" << endl;
        for(myiterator p = pstart_; p < pend_; ++p)
        {
            // cout << "deconstructing element" << endl;
            p->~T();
        }
        // cout << "destructing pstart_" << endl;
        // delete [] pstart_;
        pstart_ = NULL;
        pend_ = NULL;
        resSize_ = 0;
        actSize_ = 0;
        // cout << "destruction complete" << endl;

    }

    myiterator begin() const { return pstart_; }
    myiterator end() const { return pend_; }
    T front() const { return *pstart_; }
    T back() const { return *(pend_-1); }
    size_t capacity() const { return resSize_; }
    size_t size() const { return actSize_; }
    bool empty() const { return (pstart_ == pend_); }

    void insert(myiterator p, auto in, const T& v);
    void push_back(const T& v);
    void pop_back() {
        if (actSize_ > 0) {
            --pend_;
            pend_->~T();
            --actSize_;
        }
    }
    void reserve(auto in);
    void resize(auto in);
    void resize(auto in, const T& v);



    /********************** variables **********************/

protected:

    /********************** functions **********************/

    /********************** variables **********************/
    size_t resSize_ = 0; // reserved size
    size_t actSize_ = 0; // actual size
    myiterator pstart_ = 0;
    myiterator pend_ = 0;

    
};

/* insert in elements with value v before p */
template<class T>
void Myvector<T>::insert(myiterator p, auto in, const T& v)
{
    in = in < 1 ? 1 : in;
    size_t n = static_cast<size_t>(in);
    size_t delta_n = resSize_ - actSize_;
    size_t num_of_move = pend_ - p;
    
    if(num_of_move > 0 && num_of_move <= actSize_)
    {
        if(delta_n >= n)
        {
            myiterator pnew_end = pend_ + n;
            actSize_ += n;
            while(num_of_move-- != 0)
            {
                *(--pnew_end) = *(--pend_);
            }
            while(1)
            {
                *(--pnew_end) = v;
                if(--n == 0)
                    break;
            }
            pend_ = pstart_ + actSize_;
        }
        else
        {
            size_t nn = 1;
            while(nn < n+actSize_)
            {
                nn *= 2;
            }
            myiterator pnew_start = new (std::nothrow) T[nn];
            // cout << "pstart_ established" << endl;
            if (!pnew_start) {
                // Handle error
                cout << "ERROR: memory allocation failed !!!!" << endl;
            }
            else
            {  
                actSize_ += n;
                myiterator pnew_end = pnew_start + actSize_;
                while(num_of_move-- != 0)
                {
                    *(--pnew_end) = *(--pend_);
                }
                while(1)
                {
                    *(--pnew_end) = v;
                    if(--n == 0)
                        break;
                }
                memcpy( pnew_start, pstart_, (p-pstart_) * sizeof(T) );
                pend_ = pstart_ + actSize_ - n;

                // cout << "deconstructing" << endl;
                for(myiterator p = pstart_; p < pend_; ++p)
                {
                    // cout << "deconstructing element" << endl;
                    p->~T();
                }
                // delete [] pstart_;
                pstart_ = pnew_start;
                pend_ = pstart_ + actSize_;
                resSize_ = nn;
            }
        } 
    }
    else if(num_of_move == 0)
    {
        if(delta_n >= n)
        {
            while(1)
            {
                *(pend_) = v;
                ++pend_;
                if(--n == 0)
                    break;
            }
            actSize_ = pend_ - pstart_;
        }
        else
        {
            size_t nn = 1;
            while(nn < n+actSize_)
            {
                nn *= 2;
            }
            myiterator pnew_start = new (std::nothrow) T[nn];
            // cout << "pstart_ established" << endl;
            if (!pnew_start) {
                // Handle error
                cout << "ERROR: memory allocation failed !!!!" << endl;
            }
            else
            {
                memcpy( pnew_start, pstart_, actSize_ * sizeof(T) );
                pend_ = pnew_start + actSize_;
                while(1)
                {
                    *(pend_) = v;
                    ++pend_;
                    if(--n == 0)
                        break;
                }
                actSize_ = pend_ - pnew_start;
                
                // cout << "deconstructing" << endl;
                for(myiterator p = pstart_; p < pend_; ++p)
                {
                    // cout << "deconstructing element" << endl;
                    p->~T();
                }
                // delete [] pstart_;
                pstart_ = pnew_start;
                resSize_ = nn;
            }
        }
    }  
    else
    {
        cout << "ERROR: insert position not with in range !!!" << endl;
        exit(1);
    }
}

template<class T>
void Myvector<T>::push_back(const T& v)
{
    if(actSize_ < resSize_)
    {
        *(pend_) = v;
        ++actSize_;
        ++pend_;
    }
    else
    {
        insert(end(), 1, v);
    }
}

template<class T>
void Myvector<T>::resize(auto in)
{
    in = in < 0 ? 0 : in;
    size_t n = static_cast<size_t>(in);

    if(n > resSize_)
    {
        size_t nn = 1;
        while(nn < n)
        {
            nn *= 2;
        }
        myiterator pnew_start = new (std::nothrow) T[nn];
        // cout << "pstart_ established" << endl;
        if (!pnew_start) {
            // Handle error
            cout << "ERROR: memory allocation failed !!!!" << endl;
        }
        else
        {
            memset( pnew_start, 0, n * sizeof(T) );
            memcpy( pnew_start, pstart_, actSize_ * sizeof(T) );
            // cout << "deconstructing" << endl;
            for(myiterator p = pstart_; p < pend_; ++p)
            {
                // cout << "deconstructing element" << endl;
                p->~T();
            }
            // delete [] pstart_;
            actSize_ = n;
            pstart_ = pnew_start;
            pend_ = pstart_ + actSize_;
            resSize_ = nn;
        }
    }
}

template<class T>
void Myvector<T>::resize(auto in, const T& v)
{
    in = in < 0 ? 0 : in;
    size_t n = static_cast<size_t>(in);

    if(n > resSize_)
    {
        // cout << "n0:" << n << endl;
        size_t nn = 1;
        while(nn < n)
        {
            nn *= 2;
            // nn << 1;
        }
        myiterator pnew_start = new (std::nothrow) T[nn];
        // cout << "pstart_ established" << endl;
        if (!pnew_start) {
            // Handle error
            cout << "ERROR: memory allocation failed !!!!" << endl;
        }
        else
        {
            // memset( pnew_start, v, n * sizeof(T) );
            for(size_t i = actSize_; i < n; ++i)
            {
                *(pnew_start+i) = v;
            }
            memcpy( pnew_start, pstart_, actSize_ * sizeof(T) );
            // for(size_t i = 0; i < actSize_; ++i)
            // {
            //     *(pnew_start+i) = *(pstart_+i);
            // }
            // cout << "deconstructing" << endl;
            for(myiterator p = pstart_; p < pend_; ++p)
            {
                // cout << "deconstructing element" << endl;
                p->~T();
            }
            // delete [] pstart_;
            actSize_ = n;
            pstart_ = pnew_start;
            pend_ = pstart_ + actSize_;
            resSize_ = nn;
        }
    }
    else if (n > actSize_)
    {
        // cout << "n1:" << n << endl;
        for(size_t i = actSize_; i < n; ++i)
        {
            *(pstart_+i) = v;
        }
        actSize_ = n;
        pend_ = pstart_ + actSize_;
    }
}

template<class T>
void Myvector<T>::reserve(auto in)
{
    in = in < 0 ? 0 : in;
    size_t n = static_cast<size_t>(in);

    if(n > resSize_)
    {
        myiterator pnew_start = new (std::nothrow) T[n];
        // cout << "pstart_ established" << endl;
        if (!pnew_start) {
            // Handle error
            cout << "ERROR: memory allocation failed !!!!" << endl;
        }
        else
        {
            memcpy( pnew_start, pstart_, actSize_ * sizeof(T) );
            // cout << "deconstructing" << endl;
            for(myiterator p = pstart_; p < pend_; ++p)
            {
                // cout << "deconstructing element" << endl;
                p->~T();
            }
            // delete [] pstart_;
            pstart_ = pnew_start;
            pend_ = pstart_ + actSize_;
            resSize_ = n;
        }
    }
}


template<class T>
void print_myvec(Myvector<T>& v)
{
    cout << "******* printing vector *******" << endl;
    for( size_t i = 0; i < v.size(); ++i)
    {
        cout << "v[" << i << "]:" << v[i] << endl;
    }
    cout << "******* printing end    *******" << endl;
}

// namespace myfun
}
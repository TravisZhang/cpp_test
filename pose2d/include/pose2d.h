#ifndef POSE2D_H
#define POSE2D_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cstdlib>

namespace pose2d
{


template<typename T>
class Pose2d
{
public:

    T v[3] = {0}; // x y theta(degree)
  
    Pose2d(){}
    // Pose2d(const T& vx, const T& vy, const T& vt) {
    //     v[0] = vx; v[1] = vy; v[2] = vt;}
    template <typename S1, typename S2, typename S3>
    Pose2d(S1&& vx, S2&& vy, S3&& vt) 
        {v[0] = std::forward<S1>(vx);v[1] = std::forward<S2>(vy);v[2] = std::forward<S3>(vt);}
    Pose2d(const Pose2d& a) {
        v[0] = a.v[0]; v[1] = a.v[1]; v[2] = a.v[2];}

    // ------------- arithmetic assign operation ------------- //

    Pose2d& operator+=(const Pose2d& a) { v[0] += a.v[0]; v[1] += a.v[1]; v[2] += a.v[2]; return *this; }
    Pose2d& operator-=(const Pose2d& a) { v[0] -= a.v[0]; v[1] -= a.v[1]; v[2] -= a.v[2]; return *this; }
    Pose2d& operator*=(const Pose2d& a) { v[0] *= a.v[0]; v[1] *= a.v[1]; v[2] *= a.v[2]; return *this; }
    Pose2d& operator/=(const Pose2d& a) { v[0] /= a.v[0]; v[1] /= a.v[1]; v[2] /= a.v[2]; return *this; }

    // ------------- point operation ------------- //

    // get dist(m) between two points
    T get_distance(const Pose2d& other) {
        return sqrt(pow((v[0] - other.v[0]),2) + pow((v[1] - other.v[1]),2));}

    // create vector from two points, return a->b
    Pose2d creat_vec(const Pose2d& b);

    // ------------- vector operation ------------- //

    // get angle(degree) between two vector, return angle from self to other(counter-clockwise positive), [-180,180] 
    T get_angle_between(const Pose2d& other);

    // scalar assign operation
    Pose2d& operator*=(const T& s) { v[0] *= s; v[1] *= s; v[2] *= s; return *this; }
    Pose2d& operator/=(const T& s) { v[0] /= s; v[1] /= s; v[2] /= s; return *this; }

    // negative operation
    Pose2d operator-() const { return Pose2d(-v[0],-v[1],0); }

    // get vector length
    T get_length(){return sqrt(v[0]*v[0]+v[1]*v[1]);}

    // dot & cross product
    T dot(const Pose2d& other){ return (v[0]*other.v[0] + v[1]*other.v[1]);}
    T cross(const Pose2d& other){ return (v[0]*other.v[1] - v[1]*other.v[0]);}

    // rotate
    void rotate(const T& angle);
    Pose2d rotated(const T& angle);

    // translate
    void translate(const T& x, const T& y);
    void translate(const Pose2d& b, const int& flag);
    Pose2d translated(const T& x, const T& y);
    Pose2d translated(const Pose2d& b, const int& flag); // flag 0 means minus(-), 1 means plus(+)

private:
    /* data */
};

template<typename T>
T Pose2d<T>::get_angle_between(const Pose2d& other)
{
    T cross = v[0]*other.v[1] - v[1]*other.v[0];
    T dot = v[0]*other.v[0] + v[1]*other.v[1];
    return atan2(cross, dot)/M_PI*180;
}

template<typename T>
Pose2d<T> Pose2d<T>::creat_vec(const Pose2d& b)
{
    Pose2d c((b.v[0]-v[0]),(b.v[1]-v[1]),atan2((b.v[1]-v[1]),(b.v[0]-v[0]))/M_PI*180);
    return c;
}

template<typename T>
void Pose2d<T>::rotate(const T& angle)
{
    T x = v[0];
    T y = v[1];
    T a = (T)angle/180*M_PI;
    v[0] = x*cos(a)-y*sin(a);
    v[1] = x*sin(a)+y*cos(a);
    v[2] += angle;
}

template<typename T>
Pose2d<T> Pose2d<T>::rotated(const T& angle)
{
    Pose2d pose_temp;
    T a = (T)angle/180*M_PI;
    pose_temp.v[0] = v[0]*cos(a)-v[1]*sin(a);
    pose_temp.v[1] = v[0]*sin(a)+v[1]*cos(a);
    pose_temp.v[2] += angle;
    return pose_temp;
}

template<typename T>
void Pose2d<T>::translate(const T& x, const T& y)
{
    v[0] += x;
    v[1] += y;
}

template<typename T>
void Pose2d<T>::translate(const Pose2d& b, const int& flag)
{
    if(flag == 1)
    {
        v[0] += b.v[0];
        v[1] += b.v[1];
    }
    else
    {
        v[0] -= b.v[0];
        v[1] -= b.v[1];
    }
}

template<typename T>
Pose2d<T> Pose2d<T>::translated(const T& x, const T& y)
{
    Pose2d pose_temp;
    pose_temp.v[0] = v[0]+x;
    pose_temp.v[1] = v[1]+y;
    pose_temp.v[2] = v[2];
    return pose_temp;
}

template<typename T>
Pose2d<T> Pose2d<T>::translated(const Pose2d& b, const int& flag)
{
    Pose2d pose_temp;
    if(flag == 1)
    {
        pose_temp.v[0] = v[0]+b.v[0];
        pose_temp.v[1] = v[1]+b.v[1];
    }
    else
    {
        pose_temp.v[0] = v[0]-b.v[0];
        pose_temp.v[1] = v[1]-b.v[1];
    }
    pose_temp.v[2] = v[2];
    return pose_temp;
}

// global functions

// Pose2d& operator+(const Pose2d& a, const Pose2d& b) { return Pose2d(a) += b; }
// Pose2d& operator-(const Pose2d& a, const Pose2d& b) { return Pose2d(a) -= b; }
// Pose2d& operator*(const Pose2d& a, const Pose2d& b) { return Pose2d(a) *= b; }
// Pose2d& operator/(const Pose2d& a, const Pose2d& b) { return Pose2d(a) /= b; }

// Pose2d operator+(Pose2d a, const Pose2d& b) { a.v[0] += b.v[0]; a.v[1] += b.v[1]; a.v[2] += b.v[2]; return a; }
// Pose2d operator-(Pose2d a, const Pose2d& b) { a.v[0] -= b.v[0]; a.v[1] -= b.v[1]; a.v[2] -= b.v[2]; return a; }
// Pose2d operator*(Pose2d a, const Pose2d& b) { a.v[0] *= b.v[0]; a.v[1] *= b.v[1]; a.v[2] *= b.v[2]; return a; }
// Pose2d operator/(Pose2d a, const Pose2d& b) { a.v[0] /= b.v[0]; a.v[1] /= b.v[1]; a.v[2] /= b.v[2]; return a; }

template<typename T>
Pose2d<T> operator+(Pose2d<T> a, const Pose2d<T>& b) { a += b; return a; }
template<typename T>
Pose2d<T> operator-(Pose2d<T> a, const Pose2d<T>& b) { a -= b; return a; }
template<typename T>
Pose2d<T> operator*(Pose2d<T> a, const Pose2d<T>& b) { a *= b; return a; }
template<typename T>
Pose2d<T> operator/(Pose2d<T> a, const Pose2d<T>& b) { a /= b; return a; }

// Pose2d& operator*(const Pose2d& a, const T& s){ return Pose2d(a) *= s; }
// Pose2d& operator*(const T& s, const Pose2d& a){ return Pose2d(a) *= s; }
// Pose2d& operator/(const Pose2d& a, const T& s){ return Pose2d(a) /= s; }
// Pose2d& operator/(const T& s, const Pose2d& a){ return Pose2d(a) /= s; }

template<typename T>
Pose2d<T> operator*(Pose2d<T> a, const T& s){ a.v[0] *= s; a.v[1] *= s; a.v[2] *= s; return a; }
template<typename T>
Pose2d<T> operator*(const T& s, Pose2d<T> a){ a.v[0] *= s; a.v[1] *= s; a.v[2] *= s; return a; }
template<typename T>
Pose2d<T> operator/(Pose2d<T> a, const T& s){ a.v[0] /= s; a.v[1] /= s; a.v[2] /= s; return a; }
template<typename T>
Pose2d<T> operator/(const T& s, Pose2d<T> a){ a.v[0] /= s; a.v[1] /= s; a.v[2] /= s; return a; }


// check if two line segments ab & cd intersect 
// we treat four points as four vectors
template<typename T>
bool intersect(const Pose2d<T>& a, const Pose2d<T>& b, const Pose2d<T>& c, const Pose2d<T>& d)
{
    Pose2d<T> ab = b-a;
    Pose2d<T> cd = d-c;
    if(ab.cross(cd) == 0)
        return false;
    T t = (c-a).cross(cd)/ab.cross(cd);
    T u = ab.cross(a-c)/ab.cross(cd);
    // ROS_INFO("t:%.5f,u:%.5f",t,u);
    if(t <= 1.0 && t >= 0.0 && u <= 1.0 && u >= 0.0)
        return true;
    return false;
}


// get intersect point
// must call after intersect() return true
template<typename T>
Pose2d<T> get_intersect(const Pose2d<T>& a, const Pose2d<T>& b, const Pose2d<T>& c, const Pose2d<T>& d)
{
    Pose2d<T> ab = b-a;
    Pose2d<T> cd = d-c;
    // ROS_INFO("ab: [%.3f, %.3f]",ab.v[0],ab.v[1]);
    // ROS_INFO("cd: [%.3f, %.3f]",cd.v[0],cd.v[1]);
    T t = ((c-a).cross(cd))/(ab.cross(cd));
    // ROS_INFO("t*ab: [%.3f, %.3f]",(t*ab).v[0],(t*ab).v[1]);
    // Pose2d r0 = t*ab;
    Pose2d<T> r = a+t*ab;
    return r;
}

template<typename T>
void limit_to_360(T& angle)
{
    if(angle >= 360.0)
    {
        while(angle >= 360.0)
        {
            angle -= 360.0;
        }
    }
    else if(angle < 0.0)
    {
        while(angle < 0.0)
        {
            angle += 360.0;
        }
    }
}

}

#endif

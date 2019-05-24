#include "pose2d.h"


using namespace pose2d;


int main()
{
    double x = -723.45;
    limit_to_360(x);
    printf("x:%.3f\n",x);

    double dist_ab = 0,angle_ab = 0;
    Pose2d<double> a(-1.0,-1.0,-10.0);
    Pose2d<double> b(2.0,2.0,30.0);
    Pose2d<double> d(2.0,-1.0,20.0);
    Pose2d<double> e(-1.0,2.0,-10.0);
    Pose2d<double> ab = b-a;
    printf("a1 %.3f, %.3f, %.3f\n",a.v[0],a.v[1],a.v[2]);
    Pose2d<double> de = d-e;
    Pose2d<double> a2 = 2.0*d;
    printf("a2 %.3f, %.3f, %.3f\n",a2.v[0],a2.v[1],a2.v[2]);
    Pose2d<double> bbb(ab);
    Pose2d<double> aaa = 2.0*a+b*3.0;
    printf("a3 %.3f, %.3f, %.3f\n",a.v[0],a.v[1],a.v[2]);
    double c0 = 1, c1 = 2, c2 = 3;
    Pose2d<double> ccc(c0,c1,3.0);
    Pose2d<double> ddd = a*b;
    printf("sss %.3f, %.3f, %.3f\n",(a*2.0).v[0],(a*2.0).v[1],(a*2.0).v[2]);
    printf("a4 %.3f, %.3f, %.3f\n",a.v[0],a.v[1],a.v[2]);
    printf("nnn %.3f, %.3f, %.3f\n",(a+b).v[0],(a+b).v[1],(a+b).v[2]);
    printf("aaa %.3f, %.3f, %.3f\n",aaa.v[0],aaa.v[1],aaa.v[2]);
    printf("bbb %.3f, %.3f, %.3f\n",ab.v[0],ab.v[1],ab.v[2]);
    printf("ccc %.3f, %.3f, %.3f\n",ccc.v[0],ccc.v[1],ccc.v[2]);
    printf("ddd %.3f, %.3f, %.3f\n",ddd.v[0],ddd.v[1],ddd.v[2]);
    
    dist_ab = a.get_distance(b);
    printf("dist:%.3f\n",dist_ab);
    angle_ab = ab.get_angle_between(de);
    printf("angle:%.3f\n",angle_ab);
    Pose2d<double> c = a.creat_vec(b);
    printf("c: %.3f %.3f %.3f\n",c.v[0],c.v[1],c.v[2]);

    bool flag_i = intersect(a,b,d,e);
    printf("flag_i: %d\n",flag_i);
    if(flag_i == true)
    {
        Pose2d<double> in = get_intersect(a,b,d,e);
        printf("x:%.3f,y:%.3f\n",in.v[0],in.v[1]);
    }

    return 0;
}
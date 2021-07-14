#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <cmath>

const double p = 10.;
const double r = 28.;
const double b = 8/3;

const double h = 0.01;
const int itr_max = 10000;

double f1(double x, double y, double z);
double f2(double x, double y, double z);
double f3(double x, double y, double z);

int main(){
    std::ofstream ofs("./result/result.txt");
    int i = 0;
    double x0 = 5.;
    double y0 = 1.;
    double z0 = 1.;
    double t;

    double k0, k1, k2, k3;
    double l0, l1, l2, l3;
    double m0, m1, m2, m3;

    double x = x0;
    double y = y0;
    double z = z0;

    for(i = 0 ; i < itr_max ; i ++){
        t = i*h;
        ofs << i << ";" << t << ";" << x << ";" << y << ";" << z << "\n";
        
        k0 = f1(x, y, z);
        l0 = f2(x, y, z);
        m0 = f3(x, y, z);

        k1 = f1(x + k0*h*0.5, y + l0*h*0.5, z + m0*h*0.5);
        l1 = f2(x + k0*h*0.5, y + l0*h*0.5, z + m0*h*0.5);
        m1 = f3(x + k0*h*0.5, y + l0*h*0.5, z + m0*h*0.5);

        k2 = f1(x + k1*h*0.5, y + l1*h*0.5, z + m1*h*0.5);
        l2 = f2(x + k1*h*0.5, y + l1*h*0.5, z + m1*h*0.5);
        m2 = f3(x + k1*h*0.5, y + l1*h*0.5, z + m1*h*0.5);

        k3 = f1(x + k2*h, y + l2*h, z + m2*h);
        l3 = f2(x + k2*h, y + l2*h, z + m2*h);
        m3 = f3(x + k2*h, y + l2*h, z + m2*h);

        x += (k0 + 2*k1 + 2*k2 + k3)*h/6;
        y += (l0 + 2*l1 + 2*l2 + l3)*h/6;
        z += (m0 + 2*m1 + 2*m2 + m3)*h/6;

        if(std::isnan(x) || std::isnan(y) || std::isnan(z)){
           std::cout << "i = " << i <<  " infinite value!!!!" << std::endl;
           continue; 
        }
    }

    ofs.close();
    return 0;
}

double f1(double x, double y, double z){
    return - p*x  + p*y;
}
double f2(double x, double y, double z){
    return - x*z + r*x - y;
}
double f3(double x, double y, double z){
    return x*y  - b*z;
}
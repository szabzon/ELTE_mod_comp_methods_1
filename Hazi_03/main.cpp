
/*
Kedves Balázs!
Beszéltük a Teamsen, hogy szebb lenne átírni osztályokra, és nem csak így függvényekkel csinálni.
Végül viszont sajnos nem csináltam meg, mert időszűkében vagyok. Legközelebb szebben fogom megírni, elnézést!
*/




#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

double f(double x,double F=900, double q=1.8, double a=200, double he=35){
    return F/q*(cosh(q/F*x)-cosh(q*a/(2*F)))+he;
}

double D(double fh1, double fh2, double h){
    return (fh1-fh2)/(2*h);
}

double S(double D1, double D2){
    return (4*D1-D2)/3;
}

double richardson(double x,  double h){
    double fx1;
    double fx2;
    double d1;
    double d2;
    double s1;
    double s2;

    fx1=f(x+h);
    fx2=f(x-h);
    d1=D(fx1,fx2,h);
    h=2*h;
    fx1=f(x+h);
    fx2=f(x-h);
    d2=D(fx1,fx2,h);
    s1=S(d1,d2);

    fx1=f(x+h);
    fx2=f(x-h);
    d1=D(fx1,fx2,h);
    h=2*h;
    fx1=f(x+h);
    fx2=f(x-h);
    d2=D(fx1,fx2,h);

    s2=S(d1,d2);

    return (16*s1-s2)/15;
}

double integrandus(double x, double dx){
    double fd;
    fd=richardson(x,dx);
    return sqrt(1+fd*fd);
}

double kozeppontos(double a, double b, double n){
    double dx;
    double l=0;
    double x;
    dx=(b-a)/n;
    x=a+dx/2;

    for (int i=0; i<n; i++){
        x+=dx;
        l+=integrandus(x,dx)*dx;
    }
    return l;
}

double trapez(double a, double b, double n){
    double dx;
    double l=0;
    double x;
    dx=(b-a)/n;
    x=a;

    for (int i=0; i<n+1; i++){
        x+=dx;
        l+=integrandus(x,dx)*2;
    }
    l=l-(integrandus(x,dx)+integrandus(a,dx));
    l*=dx/2;
    return l;
}

double simpson(double a, double b, double n){
    return (2*kozeppontos(a,b,n)+trapez(a,b,n))/3;
}


void kiirat(){
    ofstream ofile;
    ofile.open ("output.txt");
    ofile.precision(16);
    double a=-100;
    double b=100;
    double n;
    double kp;
    double tp;
    double sp;
    for(int i=2;i<7;i++){
        n=pow(10,i);
        kp=kozeppontos(a,b,n);
        tp=trapez(a,b,n);
        sp=simpson(a,b,n);

        ofile<<"A lepesek szama: n="<<n<<"\n";
        ofile<<"A kozeppeontos modszerrel kapott megoldas: "<<kp<<"\n";
        ofile<<"A trapez modszerrel kapott megoldas:       "<<tp<<"\n";
        ofile<<"A Simpson modszerrel kapott megoldas:      "<<sp<<"\n\n";

        cout<<"A lepesek szama: n="<<n<<"\n";
        cout<<"A kozeppeontos modszerrel kapott megoldas: "<<kp<<"\n";
        cout<<"A trapez modszerrel kapott megoldas:       "<<tp<<"\n";
        cout<<"A Simpson modszerrel kapott megoldas:      "<<sp<<"\n\n";
    }
    ofile.close();
}




int main(int, char**) {
    std::cout.precision(16);
    kiirat();
}

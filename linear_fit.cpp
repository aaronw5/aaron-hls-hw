#include <cmath>
#include <iostream>
using namespace std;

void linear_fit(const float x[], const float y[], const float s[], int n) {
    #pragma HLS PIPELINE
    float S=0, Sx=0, Sy=0;
    for(int i=0;i<n;i++){
        float w=1.f/(s[i]*s[i]);
        S+=w; 
        Sx+=w*x[i]; 
        Sy+=w*y[i];
    }
    float xbar=Sx/S;
    float Stt=0, sum_ty=0;
    #pragma HLS PIPELINE
    for(int i=0;i<n;i++){
        float t=(x[i]-xbar)/s[i];
        Stt+=t*t;
        sum_ty+=t*y[i]/s[i];
    }
    float b=sum_ty/Stt;
    float a=(Sy-Sx*b)/S;
    float sb=1.f/std::sqrt(Stt);
    float sa=std::sqrt((1.f/S)*(1.f+(Sx*Sx)/(S*Stt)));
    float chi2=0;
    #pragma HLS PIPELINE
    for(int i=0;i<n;i++){
        float d=y[i]-a-b*x[i];
        float w=1.f/(s[i]*s[i]);
        chi2+=w*d*d;
    }
    float r=(n>2?chi2/(n-2):chi2);
    cout<<"a="<<a<<" +/- "<<sa<<", b="<<b<<" +/- "<<sb<<", chi2/ndf="<<r<<"\n";
}

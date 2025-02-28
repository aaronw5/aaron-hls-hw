#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

void linear_fit(const float[], const float[], const float[], int);

int main(){
    const int M=1000;
    float x[M],y[M],s[M];
    int n=0,e=0;
    ifstream f("data.txt");
    char line[256];
    while(f.getline(line,256)){
        if(line[0]=='\0') continue;
        float fx,fy,fs;int fl;
        sscanf(line,"%f,%f,%f,%d",&fx,&fy,&fs,&fl);
        x[n]=fx; y[n]=fy; s[n]=fs; n++;
        if(fl==1){
            e++;
            cout<<"Event "<<e<<": ";
            linear_fit(x,y,s,n);
            n=0;
        }
    }
    return 0;
}

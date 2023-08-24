#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;
int main()
{
   int j,m=101;
   double Re,U,H,dt,dy,time,oldU[m];
    Re = 100;
    U = 1.0;
    H = 1.0;
    dt = 0.01;
    dy = H/(m-1);
   double aj,bj,cj,gamma,d[m],P[m],Q[m];
   cout<<"enter the time";
   cin>>time;
    
    gamma =  dt/(Re*dy*dy);
    
    aj=-(1+2*gamma);
    bj=gamma;
    cj=gamma;

    oldU[0] = 0.0;
    oldU[m] = U;
    for(j=1;j<m;j++)  
    {  
        oldU[j] = 0.0;
    }
    ofstream out("btcstdma_data.dat");
     out<<"TITLE = VELOCITY"<<endl<<"VARIABLES = \"u\", \"y\""<<endl;
    out<<"Zone T = \"BLOCK1\", j=101, F=POINT\n\n"<<endl;
    double t;
    int iteration=0;

    for(t=0.0;t<=time;t=t+dt)
    {
    
    d[0]=-oldU[0];
    d[m]=-oldU[m];
    P[0]=-bj/aj;
    P[m]=0.0;
    Q[0]=d[0]/aj;
    Q[m]=oldU[m];

    for(j=1; j<m; j++)
    {
        d[j]=-oldU[j];

        P[j]=-(bj/(aj+cj*P[j-1]));
            
        Q[j]=(d[j]-cj*Q[j-1])/(aj+cj*P[j-1]);
    }
    
    for(j=(m-1);j>0;j--)
    {
        oldU[j] = P[j] * oldU[j+1] + Q[j];
    } 
    iteration++;

    }
    
    for(j=0;j<=m;j++)
    {
       out<<oldU[j]<<"\t"<<j*dy<<"\n";
    }
    
    cout<<"\n for t="<<time<<"\t number of iterations"<<iteration<<"\n";
    return 0;
}


#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;

int main()
{
   int j,m=101;
   float time;
   cout<<"enter time:";
   cin>>time;
   double Re,U,H,dt,dy,oldU[m];
    Re = 100;
    U = 1.0;
    H = 1.0;
    dt = 0.01;
    dy = H/(m-1);
    
   double aj,bj,cj,Y,d[m],P[m],Q[m];
    
    Y =  dt/(Re*dy*dy);
    
    aj=-(1+Y);
    bj=Y/2;
    cj=Y/2;

    oldU[1] = 0.0;
    oldU[m] = U;
    for(j=2;j<m;j++)  
    {  
        oldU[j] = 0.0;
    }
    
    ofstream out("CN_data.dat");
    out<<"TITLE = VELOCITY"<<endl<<"VARIABLES = \"u\", \"y\""<<endl;
    out<<"Zone T = \"BLOCK1\", j=101, F=POINT\n\n"<<endl;
    d[1]=-oldU[1];
    d[m]=-oldU[m];
    P[1]=-bj/aj;
    P[m]=0.0;
    Q[1]=d[1]/aj;
    Q[m]=oldU[m];

    double t;
    int iteration=0;

    for(t=0.0;t<=time;t=t+dt)
    {
    
   for(j=2; j<m; j++)
    {
        d[j]=(Y-1)*oldU[j]-(Y/2)*(oldU[j+1]+oldU[j-1]);

        P[j]=-(bj/(aj+(cj*P[j-1])));
            
        Q[j]=(d[j]-(cj*Q[j-1]))/(aj+(cj*P[j-1]));
    }
    
    for(j=(m-1);j>1;j--)
    {
        oldU[j] = P[j] * oldU[j+1] + Q[j];
    } 
    iteration++;
    }
    
    for(j=1;j<=m;j++)
    {
         out<<oldU[j]<<"\t"<<j*dy<<"\n";
    }
    
    cout<<"\n for t="<<time<<"\t number of iterations"<<iteration<<"\n";
    return 0;
}

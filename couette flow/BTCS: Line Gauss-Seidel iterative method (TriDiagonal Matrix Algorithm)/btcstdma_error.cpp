#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;
int main()
{
   int j,m=101;
   double Re,U,H,dt,dy,oldU[m+1],newU[m+1];
    Re = 100;
    U = 1.0;
    H = 1.0;
    dt = 0.01;
    dy = H/(m-1);
    
   double aj,bj,cj,gamma,d[m],P[m],Q[m];
    
    gamma =  dt/(Re*dy*dy);
    
    aj=-(1+2*gamma);
    bj=gamma;
    cj=gamma;

   ofstream out("btcstdma_error.dat");
     out<<"TITLE = VELOCITY"<<endl<<"VARIABLES = \"u\", \"y\""<<endl;
    out<<"Zone T = \"BLOCK1\", j=101, F=POINT\n\n"<<endl;

    newU[1] = 0.0;
    newU[m] = U;
    for(j=2;j<m;j++)  
    {  
        newU[j] = 0.0;
    }
    oldU[m]=U;
    for(j=1;j<m;j++)  
    {  
        oldU[j] = 0.0;
    }
    int iteration=0;
    double error = 0.0;
    do
    {
    
    d[1]=-newU[1];
    d[m]=-newU[m];
    P[1]=-bj/aj;
    P[m]=0.0;
    Q[1]=d[1]/aj;
    Q[m]=newU[m];

    for(j=2; j<m; j++)
    {
        d[j]=-newU[j];

        P[j]=-(bj/(aj+cj*P[j-1]));
            
        Q[j]=(d[j]-cj*Q[j-1])/(aj+cj*P[j-1]);
    }

    
    for(j=(m-1);j>1;j--)
    {
        newU[j] = P[j] * newU[j+1] + Q[j];
    } 
    error =0.0;
    for(j=1;j<=m;j++)
    {
        error = error + pow((newU[j]-oldU[j]),2);
    }
    error = sqrt(error/m);
    for(j=1;j<=m;j++)
    {
        oldU[j] = newU[j];
    }
    iteration++;

    }while(error > 0.000001);

     for(j=1;j<=m;j++)
        {
             out<<newU[j]<<"\t"<<(j-1)*dy<<"\n";
        }
    
    cout<<"\t number of iterations"<<iteration<<"\n";
    return 0;
}
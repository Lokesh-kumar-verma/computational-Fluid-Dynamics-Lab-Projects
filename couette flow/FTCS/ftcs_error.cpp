#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;
int main()
{  
    int j,m=101;
    double Re,U,H,dt,dy,t,gamma,oldU[m+1],newU[m+1];
    Re = 100;
    U = 1.0;
    H = 1.0;
    dt = 0.005;
    dy = H/(m-1);
    gamma = dt/(Re*dy*dy) ;
    
    ofstream out("ftcs_error.dat");

   out<<"TITLE = VELOCITY"<<endl<<"VARIABLES = \"u\", \"y\""<<endl;
    out<<"Zone T = \"BLOCK1\", j=101, F=POINT\n\n"<<endl;
    newU[1] = 0.0;
    newU[m] = U;
    for(j=2;j<m;j++)  
    {  
        newU[j] = 0.0;
    }
    int iteration =0;
    double error = 0.0;
    do
    {
        for(j=1;j<=m;j++)
        {
            oldU[j] = newU[j] ;  
        }
        
        for(j=2;j<m;j++)
        {
            newU[j] = (1-2*gamma)*oldU[j] + gamma*(oldU[j+1] + oldU[j-1]) ;
        }
        error = 0.0;
        for(j=1;j<=m;j++)
        {
            error = error + pow((newU[j]-oldU[j]),2);
        }

        error = sqrt(error/m);
        iteration++;
    
    }while(error > 0.000001);

     for(j=1;j<=m;j++)
        {
             out<<newU[j]<<"\t"<<(j-1)*dy<<"\n";
        }
     cout<<"\t number of iterations"<<iteration<<"\n";
    return 0;
}


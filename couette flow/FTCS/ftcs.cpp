#include<iostream>
#include<stdio.h>
#include<math.h>
#include<cmath>
#include<fstream>
using namespace std;
int main()
{
    int j,m=100;
    double Re,U,H,dt,dy,t,Y,oldU[m],newU[m],time;
    int iteration =0;
    Re = 100;
    H = 1.0;
    dt = 0.005;
    dy = H/(m-1);
    
    Y= dt/(Re*dy*dy) ;

    cout<<"engter time"<<"\n";
    cin>>time;
    
   ofstream out("ftcs_data.dat");
    out<<"TITLE = VELOCITY"<<endl<<"VARIABLES = \"u\", \"y\""<<endl;
    out<<"Zone T = \"BLOCK1\", j=101, F=POINT\n\n"<<endl;
    oldU[0] = 0.0;
    oldU[m] = 1.0;
    for(j=1;j<m;j++)  
    {  
        oldU[j] = 0.0;
    }
    
        for(t=0.0;t<=time;t=t+dt)
        {
   
        for(j=0;j<=m;j++)
        {
            newU[j] = oldU[j] ;    
        }
        
        for(j=1;j<m;j++)
        {
            oldU[j] = (1-2*Y)*newU[j] + Y*(newU[j+1] + newU[j-1]) ;
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



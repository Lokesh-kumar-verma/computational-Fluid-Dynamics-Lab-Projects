#include<iostream>
#include<math.h>
#include<stdio.h>
#include<fstream>
using namespace std;
int main()
{
  int m,n, i ,j;
  double B,dx,dy,s;
  double old[100][100],lat[100][100],li=0,le=0;
   cout<<"enter the size m*n\n";
  cin>>m>>n;
  dx=1.0/(m-1);
  dy=1.0/(n-1);
  B=dx/dy;
  s=pow(B,2.0);
  double l=1.0/(2.0*(1.0+s));
for(i=0;i<m;i++)
{
for (j = 0; j<n; j++)
  { 
      if (j == (n-1))
       {
        lat[i][j] = 0.0;
       }
      else if (i == 0)
       {
      lat[i][j] = 1.0;
       }
      else if (j==0)
      {
      lat[i][j] = 1.0;
      }  
      else if(i== (m-1))  
      {
        lat[i][j]=1.0;
      }
      else
      {
      lat[i][j] = 0.0;
      }
 }
}
 int iteration = 0; 
 double error = 1.0; 
 ofstream out("jacobi_2_graph.dat");
 ofstream fp("jacobi_2.dat");
 {
fp<<"VARIABLES=\"X\" \"Y\" \"TEMPERATURE\""<<endl;
fp<<"ZONE I="<<m<<" J="<<n<<" DATAPACKING=POINT"<<endl;
out<<"iteration(log10) "<<"\t"<<"error(log10)"<<"\n";
do
{
for (i = 0; i < m; i++)
 {
 for (j = 0; j<n; j++)
  {
    old[i][j] = lat[i][j];
  }
 }
  for (i = 1; i < (m-1); i++)
  {
    for (j = 1; j < (n-1); j++)
    {

     lat[i][j]= l*(s*old[i][j-1] + old[i-1][j]+old[i+1][j] + s*old[i][j+1]);
    } 
  }  
 error=0.0;
 for(i=0;i<m;i++)
 {
    for(j=0;j<n;j++)
    {
        error= error + pow(lat[i][j]-old[i][j],2);
    }
 }
 error=sqrt(error/(m*n));
 
iteration++;
li=iteration;
le=log10(error);
out<<li<<"\t"<<le<<"\n";

} while(error>0.000001); 
for(i=0;i<m;i++)
{
  for(j=0;j<n;j++)
  fp<<i*dx<<"\t"<<j*dy<<"\t"<<lat[i][j]<<endl;
}
}
cout<<"no. of iterations"<<iteration;
return 0;
}

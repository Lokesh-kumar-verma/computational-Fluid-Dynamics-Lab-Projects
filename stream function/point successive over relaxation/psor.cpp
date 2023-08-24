#include<iostream>
#include<math.h>
#include<stdio.h>
#include<fstream>
using namespace std;
int main()
{
 int m=31,n=21, i ,j;
 double B,dx,dy,s, w,a,expression,pi=3.1417;
 double old[100][100],lat[100][100],le=0,li=0;
 //dx=0.2;
 //dy=0.2;
//cout<<"enter the size m*n\n";
 //cin>>m>>n;
 dx=6.0/(m-1);
 dy=4.0/(n-1);
 B=dx/dy;
 s=pow(B,2);
 double l=1/(2*(1+s));
 expression=((cos(pi/(m-1))+s*(cos(pi/(n-1))))/(1+s));
 a=pow(expression,2);
 w=(2-sqrt(1-a))/a;
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
 lat[i][j] = 0.0;
 }
 else if (i <= 5)
 {
 lat[i][j] = 0.0;
 }
 else if (i >= 6)
 {
 lat[i][j] = 100.0;
 } 
 else
 {
 lat[i][j] = 0.0;
 }
}
}
int iteration = 0; 
double error = 1.0; 
 ofstream out("psor_1_graph.dat");
ofstream fp("psor_1.dat");
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
 lat[i][j]= (1-w)*old[i][j]+w*l*(s*lat[i][j-1] + lat[i-1][j]+old[i+1][j] + s*old[i][j+1]);
 } 
 } 
for(j=0;j<n;j++)
{
 lat[m-1][j]=lat[m-2][j];
}
error=0;
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
 fp<<(i*dx)<<"\t"<<(j*dy)<<"\t"<<lat[i][j]<<endl;
}
}
cout<<"no. of iterations = "<<iteration;
return 0;
}

#include<iostream>
#include<cmath>
#include<fstream>
#include<iomanip>
using namespace std;
int main()
{
     int i,j,m=31; int n=21;
   double dx=6.0/(m-1.0);
   double dy=4.0/(n-1.0);
   double psi[m][n],beta,temp,ai,bi,ci,d[m-2],p[m-2],q[m-2];



    beta = (dx/dy);
    ai=-2*(1+beta*beta);
        bi=1;
        ci=1;
    for(i=0; i<m; i++){
            for(j=0; j<n; j++){
                if (i<=5 && j==0){
                    psi[i][j]=0.0;      //bottom boundary
                }
                else if (i>=6 && j==0){
                    psi[i][j]=100.0;    //bottom boundary
                }
                else if (j==(n-1)){
                    psi[i][j]=0.0;      //top boundary
                }
                else if (i==0){
                    psi[i][j]=0.0;      //left boundary
                }
                else{
                    psi[i][j]=0.0;
                }
            }
        }
    int iteration=0;
    double error=1.0;
    ofstream fp("TDMA_graph.dat");
    
    do{
    error = 0.0;
        for(int j=1; j<n-1;j ++){
        d[0]=-(beta*beta)*(psi[0][j+1]+psi[0][j-1]);
        p[0]=-bi/ai;
        q[0]=d[0]/ai;

        for(i=1; i<m-1; i++){
            d[i]=-(beta*beta)*(psi[i][j+1]+psi[i][j-1]);;

                   p[i]=-(bi/(ai+ci*p[i-1]));
                   q[i]=(d[i]-ci*q[i-1])/(ai+ci*p[i-1]);



        }

         for(i=m-2; i>0; i--){
            temp=psi[i][j];
                psi[i][j]=p[i]*psi[i+1][j]+q[i];
              error+=pow((psi[i][j]- temp),2.0);
        }

    }

      for (j=0; j<n; j++){
        psi[m-1][j]=psi[m-2][j];
      }

      error=sqrt(error/((m-2)*(n-2)));
      iteration++;
     
      cout<<iteration<<"\t"<<error<<endl;

      fp<<(iteration)<<setw(10)<<"\t"<<log10(error)<<endl;
      }
      while(error > 1e-6);
      double x[m],y[n];
       x[0]=0.0; y[0]=0.0;

for(j = 0; j < n; j++)
{ y[j+1]=y[j]+dy;
}
for(i = 0; i < m; i++)
{ x[i+1]=x[i]+dx;
}
   ofstream fp2("TDMA_1.dat");
  fp2<<"VARIABLES=\"X\" \"Y\" \"PSI\""<<endl;
 fp2<<"ZONE     I="<<m<<"     J="<<n<<" DATAPACKING=POINT"<<endl;
for(i = 0; i < m; i++)  {
        for(j = 0; j < n; j++)
{
    fp2<<x[i]<<"\t"<<setw(10)<<y[j]<<"\t"<<setw(10)<<psi[i][j]<<endl;
// saving of psi values into file along with grids

 }
} 
cout<<"\nThe number of iterations ="<<iteration<<endl;
cout<<"------------check the folder for respective output files------------"<<endl;
fp2.close();
fp.close();
}


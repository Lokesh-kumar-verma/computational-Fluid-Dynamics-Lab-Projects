#include<iostream>
#include<cmath>
#include<fstream>
#include<iomanip>
using namespace std;
int main()
{
   int m,n;
   m=20;
   n=20;
   double dx=1.0/(m-1);
   double dy=1.0/(n-1);
   int i,j;

    double psi1[m][n], psi2[m][n],temp,p[m-2],q[m-2],d[m-2],d_[n-2],p_[n-2],q_[n-2];

    double as,aw,ap,ae,an,aj,bj,cj,ai,bi,ci;
    as=(1.0/pow(dy,2.0));
    aw=(1.0/pow(dx,2.0));
    ap=2.0*((1.0/pow(dx,2.0))+(1.0/pow(dy,2.0)));
    ae=(1.0/pow(dx,2.0));
    an=(1.0/pow(dy,2.0));
    cout<<ae<<"\t"<<aw<<"\t"<<an<<"\t"<<as<<"\t"<<ap<<"\t"<<endl;
    ai=ap;
    bi=-ae;
    ci=-aw;
    aj=ap;
    bj=-an;
    cj=-as;

        for(i=0;i<m;i++)
{
for (j = 0; j<n; j++)
  { 
      if (j == (n-1))
       {
        psi2[i][j] = 0.0;
       }
      else if (i == 0)
       {
      psi2[i][j] = 1.0;
       }
      else if (j==0)
      {
      psi2[i][j] = 1.0;
      }  
      else if(i== (m-1))  
      {
        psi2[i][j]=1.0;
      }
      else
      {
      psi2[i][j] = 0.0;
      }
 }
}
           int iteration = 0;
    double error=1.0;
ofstream fp("ADI2_graph.dat");
    do{



          for(i=0; i<m; i++){
         for(j=0; j<n; j++){
          psi1[i][j]= psi2[i][j];
          
      }
}

   for(j=1; j<n-1; j++){
                d[0]=an*(psi2[0][j+1]+psi2[0][j-1]);
              p[0]=-bi/ai;
              q[0]=d[0]/ai;

            for(i=1; i<m-1; i++){


                    d[i]=an*(psi2[i][j+1]+psi2[i][j-1]);

                   p[i]=-(bi/(ai+ci*p[i-1]));
                   q[i]=(d[i]-ci*q[i-1])/(ai+ci*p[i-1]);
                   
            }
             for(i=m-2; i>0; i--){

                psi2[i][j]=p[i]*psi2[i+1][j]+q[i];

            }
            }
             for(i=1; i<m-1; i++){
              d_[0]=ae*(psi2[i+1][0]+psi2[i-1][0]);
              p_[0]=-(bj/aj);
              
              q_[0]=(d_[0])/aj;

                   for(j=1; j<n-1; j++){
                  d_[j]=ae*(psi2[i+1][j]+psi2[i-1][j]);
                
                  p_[j]=-(bj/(aj+cj*p_[j-1]));
                  
                  q_[j]=(d_[j]-cj*q_[j-1])/(aj+cj*p_[j-1]);
               
            }
             for(j=n-2; j>0; j--){

                psi2[i][j]=p_[j]*psi2[i][j+1]+q_[j];
               

         }
    }

       
      error=0.0;
       for(i=0; i<m; i++){
            for(j=0; j<n; j++){
            error+=pow((psi2[i][j]-psi1[i][j]),2);
        }
    }
      iteration++ ;

      error=sqrt(error/((m-2)*(n-2)));
      cout<<iteration<<"\t"<<error<<endl;
      fp<<(iteration)<<setw(10)<<"\t"<<log10(error)<<endl;

      }
      while(error > 1e-6);
      double x[m],y[n];
x[0]=0.0; y[0]=0.0;

for(j = 0; j < n; j++)
{ 
    y[j+1]=y[j]+dy;
}
for(i = 0; i < m; i++)
{ 
    x[i+1]=x[i]+dx;
}
ofstream fp2("ADI_2.dat");
  fp2<<"VARIABLES=\"X\" \"Y\" \"PSI\""<<endl;
 fp2<<"ZONE I="<<m<<" J="<<n<<" DATAPACKING=POINT"<<endl;
for(i = 0; i < m; i++)  {
        for(j = 0; j < n; j++)
{
     fp2<<x[i]<<"\t"<<setw(8)<<y[j]<<"\t"<<setw(8)<<psi2[i][j]<<endl;
/* saving of psi values into file 0along with grids */
 }
}

cout<<"\nThe number of iterations ="<<iteration<<endl;
fp2.close();
fp.close();

}

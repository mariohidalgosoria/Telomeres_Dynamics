#include <stdio.h>
#include<stdlib.h> 
#include<math.h> 
#include <time.h>



float ran2(long *idum);
int ProbSampleReplace(int n, double *p);
#define PI 3.14159265358979323846
int main()
{
  double a,b,v,x,y,theta,thetac,Dtheta,ac,bc;
  double alpha,beta,z,zdth,alphac,betac,u;
  int id,k,T,N;
  long iseed;
  
  FILE *dat;
  char nom[50];
  int ini=1;
  int fin=10000;//numero de trayectorias  
  srand(time(NULL));
  
  x=0;
  y=0;
  T=100;//final time
  v=1;
  b=2*PI;//max value
  a=0;//min value of theta in time series with Dt=1
  
  for(id=ini;id<=fin;id++) {
    sprintf(nom,"XYT%d.dat",id);
    dat=fopen(nom,"w");
    x=0;
    y=0;  
    k=0;
    while(k<T){
      //draw an initial angle theta c
      iseed=-(long) rand();
      theta=(b-a)*ran2(&iseed)+a; //uniform thetac
      x+=v*cos(theta);
      y+=v*sin(theta);
      fprintf(dat,"%d\t%g\t%g\t%g\n",(k +1),x,y,theta);	
      k++;//create one transition between states
    }//end while(t<T)
    fclose(dat);
  }//end for id  
  return 0;
}



#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

float ran2(long *idum)
{
  int j;
  long k;
  static long idum2=123456789;
  static long iy=0;
  static long iv[NTAB];
  float temp;

  if (*idum <= 0) {
    if (-(*idum) < 1) *idum=1;
    else *idum = -(*idum);
    idum2=(*idum);
    for (j=NTAB+7;j>=0;j--) {
      k=(*idum)/IQ1;
      *idum=IA1*(*idum-k*IQ1)-k*IR1;
      if (*idum < 0) *idum += IM1;
      if (j < NTAB) iv[j] = *idum;
    }
    iy=iv[0];
  }
  k=(*idum)/IQ1;
  *idum=IA1*(*idum-k*IQ1)-k*IR1;
  if (*idum < 0) *idum += IM1;
  k=idum2/IQ2;
  idum2=IA2*(idum2-k*IQ2)-k*IR2;
  if (idum2 < 0) idum2 += IM2;
  j=iy/NDIV;
  iy=iv[j]-idum2;
  iv[j] = *idum;
  if (iy < 1) iy += IMM1;
  if ((temp=AM*iy) > RNMX) return RNMX;
  else return temp;
}
#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX




int ProbSampleReplace(int n, double *p)
{
  
  float rU;
  int i, j,ans;
  int nm1 = n - 1;
  int perm[2]={0};//the number of elements in these 
  double q[2]={0};//two arrays must coincede with p[#N]
  long iseed;
  /* record element identities */
  for (i = 0; i < n; i++) {
    perm[i] = i + 1;
    q[i]=p[i];
  }
  /* compute cumulative probabilities */
  for (i = 1 ; i < n; i++)
    q[i] += q[i - 1];
  /* compute the sample */
  iseed=-(long) rand();
  rU = ran2(&iseed);
  for (j = 0; j < nm1; j++) {
    if (rU <= q[j])
      break;
  }
  //en C despues del for j=nm1
  ans = perm[j];
  return ans;
}



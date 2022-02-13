/*
Compile using bash file MV3.sh as
$./MV3.sh
or in terminal as
$gcc -Wall -I/home/mario/gsl/include -c MV3.c
$gcc -L/home/mario/gsl/lib MV3.o -lgsl -lgslcblas -lm
$LD_LIBRARY_PATH=/home/mario/gsl/lib
$export LD_LIBRARY_PATH
Run
$./a.out
*/
#include <stdio.h>
#include<stdlib.h> 
#include<math.h> 
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#define GNUPLOT "gnuplot -persist"


float ran2(long *idum);
int ProbSampleReplace(int n, double *p);
#define PI 3.14159265358979323846
int main()
{
  double a,b,v,x,y,theta,thetac,Dtheta,ac,bc,u,thetai;
  double alpha,beta,z,pa,pc,rad,xo,yo,xd,yd,dist,MtauP,MtauNP;
  int id,k,T,N,TA,TC,t,ta,s;
  long iseed;
  const gsl_rng_type * TT;
  gsl_rng * r;
  
 
  FILE *dat;
  char nom[50];
  int ini=1;
  int fin=3000;//numero de trayectorias  
  
  FILE *dath;
  char nem[50];
  double pib[2]={0,0};//prob of plus=pib[0]; prob of minus=pib[1]
  srand(time(NULL));
  gsl_rng_env_setup();

  TT = gsl_rng_default;
  r = gsl_rng_alloc (TT);
  x=0;
  y=0;
  N=20;//number of steps between each sampling
  T=50;//final time
  v=0.0125;
  
  b=2*PI;//max value
  a=0;//min value of theta in time series with Dt=1
  alpha=5.59;//peaked near one as exp data Dt=10Delta
  beta=6.04;//WTC case
  
  MtauP=1.21;
  MtauNP=7.0;
  pa=1.0/MtauP;
  pc=1.0/MtauNP;
  rad=0.035;
  pib[0]= MtauNP  / ( MtauNP + MtauP  );//prob of starting at caging phase
  pib[1]= MtauP  / ( MtauNP + MtauP  );//prob of starting at varaying persistence phase
  sprintf(nem,"P1DTTC.dat");
  dath=fopen(nem,"w");
  for(id=ini;id<=fin;id++) {
    sprintf(nom,"XYT%d.dat",id);
    dat=fopen(nom,"w");
    //select randomly the initia; condition
    s=ProbSampleReplace(2,pib);//select initial condition
    if(s == 1){//initial condition caging phase
      x=0;
      y=0;  
      t=1;//simulation time steps  
      z=gsl_ran_beta(r,alpha,beta);
      //while(z > 0.73) z=gsl_ran_beta(r,alpha,beta);
      iseed=-(long) rand();
      u=ran2(&iseed);
      if (u>=0.5){
	thetac=z*PI;
	ac=-thetac;
	bc=thetac;
      }
      else{
	thetac=(-1)*z*PI;
	bc=-thetac;
	ac=thetac;
      }
      fprintf(dath,"%g\n",thetac);
      iseed=-(long) rand();
      thetai=(b-a)*ran2(&iseed)+a;
      while(t<=(T*N)){//loop over time
	//enter cage phase
	TC= gsl_ran_geometric(r,pc);
	TC=TC*N;
	t+=TC;
	ta=t-TC;
	k=0;
	xo=x;
	yo=y;
	while(k<TC){
	  iseed=-(long) rand();
	  theta=(b-a)*ran2(&iseed)+a;
	  xd=v*cos(theta);
	  yd=v*sin(theta);
	  x+=xd;
	  y+=yd;
	  //check if is inside the circle
	  dist=sqrt( pow((x-xo),2)  + pow((y-yo),2));	  
	  if(dist < rad){
	    if((( (ta+k) % N) == 0) && (((ta+k)/N)  <=T) )  fprintf(dat,"%d\t%g\t%g\t%g\n",(ta+k)/N,x,y,0.0);
	    
	  }//end if
	  else {
	    xd=(-1*xd);
	    yd=(-1*yd);
	    x+=xd;
	    y+=yd;
	    if((( (ta+k) % N) == 0) && (((ta+k)/N)  <=T) )  fprintf(dat,"%d\t%g\t%g\t%g\n",(ta+k)/N,x,y,0.0);
	    
	  }// end else dist > rad
	  k++;
	}//end while (t<TC) Caging phase
     
	//enter varaying persistence phase
	TA= gsl_ran_geometric(r,pa);
	TA=TA*N;
	t+=TA;
	ta=t-TA;
	k=0;
	while(k<TA){
	  if(k==0){//first step
	    theta=thetai;
	    x+=v*cos(theta);
	    y+=v*sin(theta);
	    if((( (ta+k) % N) == 0) && (((ta+k)/N)  <=T) )  fprintf(dat,"%d\t%g\t%g\t%g\n",(ta+k)/N,x,y,1.0);
	    k++;//create one transition between states
	  }//end fisrt step
	  else{//step k>0
	    //draw Dtheta Uniform
	    iseed=-(long) rand();
	    Dtheta=(bc-ac)*ran2(&iseed)+ac;
	    //end Dtheta Uniform	
	    theta+=Dtheta;
	    x+=v*cos(theta);
	    y+=v*sin(theta);
	    if((( (ta+k) % N) == 0) && (((ta+k)/N)  <=T) )  fprintf(dat,"%d\t%g\t%g\t%g\n",(ta+k)/N,x,y,1.0);
	    k++;//create one transition between states
	  }//end step k>0	
	}//end while(t<TA) varaying persistence phase
    
      }//end t<(T*N) while 
    }//end IC at caging phase

    else if(s == 2){//initial condition varaying persistence phase
      x=0;
      y=0;  
      t=1;//simulation time steps  
      z=gsl_ran_beta(r,alpha,beta);
      iseed=-(long) rand();
      u=ran2(&iseed);
      if (u>=0.5){
	thetac=z*PI;
	ac=-thetac;
	bc=thetac;
      }
      else {
	thetac=(-1)*z*PI;
	bc=-thetac;
	ac=thetac;
      }
      fprintf(dath,"%g\n",thetac);
      iseed=-(long) rand();
      thetai=(b-a)*ran2(&iseed)+a;
      while(t<=(T*N)){//loop over time

	//enter varying persistence phase 
	TA= gsl_ran_geometric(r,pa);
	TA=TA*N;
	t+=TA;
	ta=t-TA;
	k=0;
	while(k<TA){
	  if(k==0){//first step
	    theta=thetai;
	    x+=v*cos(theta);
	    y+=v*sin(theta);
	    if((( (ta+k) % N) == 0) && (((ta+k)/N)  <=T) )  fprintf(dat,"%d\t%g\t%g\t%g\n",(ta+k)/N,x,y,1.0);
	    k++;//create one transition between states
	  }//end fisrt step
	  else{//step k>0
	    //draw Dtheta Uniform
      	    iseed=-(long) rand();
	    Dtheta=(bc-ac)*ran2(&iseed)+ac;
	    //fprintf(dath,"%g\n",Dtheta);
	    //end Dtheta Uniform	
	    theta+=Dtheta;
	    x+=v*cos(theta);
	    y+=v*sin(theta);
	    if((( (ta+k) % N) == 0) && (((ta+k)/N)  <=T) )  fprintf(dat,"%d\t%g\t%g\t%g\n",(ta+k)/N,x,y,1.0);
	    k++;//create one transition between states
	  }//end step k>0	
	}//end while(t<TA) varying persistence phase
	
	//enter cage phase
	TC= gsl_ran_geometric(r,pc);
	TC=TC*N;
	t+=TC;
	ta=t-TC;
	k=0;
	xo=x;
	yo=y;
	while(k<TC){
	  iseed=-(long) rand();
	  theta=(b-a)*ran2(&iseed)+a;
	  xd=v*cos(theta);
	  yd=v*sin(theta);
	  x+=xd;
	  y+=yd;
	  //check if is inside the circle
	  dist=sqrt( pow((x-xo),2)  + pow((y-yo),2));	  
	  if(dist < rad){
	    if((( (ta+k) % N) == 0) && (((ta+k)/N)  <=T) )  fprintf(dat,"%d\t%g\t%g\t%g\n",(ta+k)/N,x,y,0.0);
	  }//end if
	  else {
	    xd=(-1*xd);
	    yd=(-1*yd);
	    x+=xd;
	    y+=yd;
	    if((( (ta+k) % N) == 0) && (((ta+k)/N)  <=T) )  fprintf(dat,"%d\t%g\t%g\t%g\n",(ta+k)/N,x,y,0.0);
	  }// end else dist > rad
	  k++;
	}//end while (t<TC) Caging phase
	
      }//end t<(T*N) while
      
    }//end IC at varying persistence  phase
    
    fclose(dat);
  }//end for id
  fclose(dath);
  gsl_rng_free (r);
  
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




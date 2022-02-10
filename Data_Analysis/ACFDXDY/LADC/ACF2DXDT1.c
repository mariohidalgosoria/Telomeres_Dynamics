#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define GNUPLOT "gnuplot -persist"
char  nom[50];//cadena para usar sprintf
char  nam[50];//cadena para usar sprintf        
FILE *tm0;//puntero para usar fopen
FILE *tm1;//puntero para usar fopen
int main(void){
   
  int          id,d,i,j,tau,dt,taumax;
  double       *Ser_X,Count;
  double       *Ser_t;
  double       *V;
  double        vser,xser;
  int ini,Nexp,Nds;
  Count=0;
  ini  =  2;
  Nexp = 129;//number of time series
  dt=1;
  taumax=40;
  for(id=ini;id<=Nexp;id++){//for over each different file          
    //count number of rows per file
    i=0;
    sprintf(nom,"CCWLT%d.dat",id);//coloca el id, file.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla file.dat
    tm0 = fopen(nom,"r");//abre file.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de file.dat
      fscanf(tm0,"%lf",&Count);//lee el primer elemento de file.dat un float y la guarda en Count
      
      fscanf(tm0,"%lf",&Count);//lee el segunda elemento de file.dat un float y la guarda en count

      fscanf(tm0,"%lf",&Count);//lee el tercer elemento de file.dat un float y la guarda en Count

      fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de file.dat un float y la guarda en Count
      //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
      i++;
    }// final del while
    fclose(tm0);
    //end counting rows per file
    Nds=i;//number of rows+1  in each file file%d.dat 
    //printf("CNds= %d\n",Nds);//imprime en la pantalla file%id.dat
    //create nad initialize arrays
    Ser_X=malloc(Nds*sizeof(double));
    Ser_t=malloc(Nds*sizeof(double));
    V=malloc(Nds*sizeof(double));
    for(i=0;i<Nds;i++){
      Ser_X[i]=0;
      Ser_t[i]=0;
      V[i]=0;
    }
  
    i=0;
    //Captura de datos:
    sprintf(nom,"CCWLT%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Ser_t[i]);//lee el primer elemento de fileid.dat un float y la guarda en Ser_t[i]
      //printf("t[%d]=%lf \n",i,Ser_t[i]);
      fscanf(tm0,"%lf",&Ser_X[i]);//lee el segunda elemento de fileid.dat un float y la guarda en Ser_X[i]
      fscanf(tm0,"%lf",&Count);//lee el tercer elemento de fileid.dat un float y la guarda en Count
      fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de fileid.dat un float y la guarda en Count
      
      i++;
    }// final del while
    fclose(tm0);
    Nds=i;
    //printf("Nds= %d\n",Nds);
  
    //create TAVDXT1%id.dat files
    sprintf(nam,"TAVDXDT1T%d.dat",id);//la cadena nom='V.dat'
    tm1 = fopen(nam,"w"); //se crea el archivo V.dat
    //Nds Final time T
    for(tau=0;tau<=taumax;tau++){//i lag time, 0<i<Nds
      for(i=0;i < ((Nds-(tau + dt))-1);i++){//X=[x0,x1,...,xNds-2] the loop has to go up to ((Nds-d)-2), to avoid evalution of Ser_X[Nds-1] and Ser_X[Nds]  
	//printf("delta=%d\tX[i+d]=%g\tSer_X[i]=%g\tSer_X[i+d]-Ser_X[i])=%g\n",d,Ser_X[i+d],Ser_X[i],Ser_X[i+d]-Ser_X[i]);
	V[tau]+=  Ser_X[i+tau+dt]*Ser_X[i+dt] - Ser_X[i+tau+dt]*Ser_X[i] - Ser_X[i+tau]*Ser_X[i+dt] + Ser_X[i+tau]*Ser_X[i];
	
	//printf("%d  %lf\n",d,V[d]);
      }
    V[tau]=V[tau]*(1.0/(Nds-(tau + dt)));  
      //printf("%d  %lf\n",d,V[d]);
      fprintf(tm1,"%d  %lf\n",tau,V[tau]);
    }
  
    fclose(tm1);

  }//end for id
  
  free(Ser_t);
  free(Ser_X);
  free(V);
  return 0;
}

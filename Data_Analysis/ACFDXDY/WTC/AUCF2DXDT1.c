#include<stdio.h>
#include<math.h>
#include<stdlib.h>
//#define Nds  500//numero de filas en cada archivo xid.dat poner numero de ultimo renglon con datos
#define GNUPLOT "gnuplot -persist"
char  nom[50];//cadena para usar sprintf
char  nam[50];//cadena para usar sprintf        
FILE *tm0;//puntero para usar fopen
FILE *tm1;//puntero para usar fopen
int main(void){
   
  int          id,d,i,j,tau,dt;
  double       *Ser_X,Count;
  double       *Ser_t;
  double       *V;
  double        VV,sVV;
  double        vser,xser;
  int ini,Nexp,Nds;
  Count=0;
  ini  =  2;
  Nexp = 364;//number of time series
  dt=1;
  VV=0;
  sVV=0;
  for(id=ini;id<=Nexp;id++){//for over each different file          
    //count number of rows per file
    i=0;
    sprintf(nom,"CCLAT%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Count);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      
      fscanf(tm0,"%lf",&Count);//lee el segunda elemento de xid.dat un float y la guarda en xser
      
      fscanf(tm0,"%lf",&Count);//lee la tercer elemento de xid.dat un float y la guarda en xser

      fscanf(tm0,"%lf",&Count);//lee la cuarto elemento de xid.dat un float y la guarda en xser
      //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
      i++;
    }// final del while
    fclose(tm0);
    //end counting rows per file
    Nds=i;//number of rows+1  in each file X%d.dat and MSD%d.dat
    //printf("CNds= %d\n",Nds);//imprime en la pantalla xid.dat
    
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
    sprintf(nom,"CCLAT%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Ser_t[i]);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      //printf("t[%d]=%lf \n",i,Ser_t[i]);
      fscanf(tm0,"%lf",&Ser_X[i]);//lee el segunda elemento de xid.dat un float y la guarda en xser
      fscanf(tm0,"%lf",&Count);//lee la tercer elemento de xid.dat un float y la guarda en xser
      fscanf(tm0,"%lf",&Count);//lee la cuarto elemento de xid.dat un float y la guarda en xser
      i++;
    }// final del while
    fclose(tm0);
    Nds=i;
    //printf("Nds= %d\n",Nds);
  
    //create MSD.dat files
    //sprintf(nam,"TAUTDXDT1T%d.dat",id);//la cadena nom='V.dat'
    //tm1 = fopen(nam,"w"); //se crea el archivo V.dat
    //Nds Final time T
    //for(tau=0;tau<=((Nds)/2);tau++){//i lag time, 0<i<Nds
    for(i=0;i < ((Nds- dt)-1);i++){//X=[x0,x1,...,xNds-2] the loop has to go up to ((Nds-d)-2), to avoid evalution of Ser_X[Nds-1] and Ser_X[Nds]  
      //printf("delta=%d\tX[i+d]=%g\tSer_X[i]=%g\tSer_X[i+d]-Ser_X[i])=%g\n",d,Ser_X[i+d],Ser_X[i],Ser_X[i+d]-Ser_X[i]);
      VV+=  Ser_X[i+dt]*Ser_X[i+dt] - Ser_X[i+dt]*Ser_X[i] - Ser_X[i]*Ser_X[i+dt] + Ser_X[i]*Ser_X[i];
      
      //printf("i=%d  %lf\n",i,VV);
    }
    VV=VV*(1.0/(Nds- dt));
    //printf("VV=%lf\n",id,VV);
    sVV+=VV;
    //printf("sVV=%lf\n",id,sVV);
    //printf("Id=%d;  VV=%lf\n",id,VV);
    //fprintf(tm1,"%lf\n",VV);
    //}//end for tau
    
    //fclose(tm1);
      
  }//end for id
  sVV=sVV/(Nexp-1);
  printf("sVV=%lf\n",sVV);
  free(Ser_t);
  free(Ser_X);
  free(V);
  return 0;
}

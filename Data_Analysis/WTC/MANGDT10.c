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
  double       *Ser_Y;
  double        theta;
  int ini,Nexp,Nds;
  Count=0;
  ini  =  2;
  Nexp = 364;//number of time series
  dt=10;


  for(id=ini;id<=Nexp;id++){//for over each different file          
    //count number of rows per file
    sprintf(nam,"MANGD10T%d.dat",id);//la cadena nom='V.dat'
    tm1 = fopen(nam,"w"); //se crea el archivo V.datw 
    i=0;
    sprintf(nom,"CCLAT%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Count);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      
      fscanf(tm0,"%lf",&Count);//lee el segunda elemento de xid.dat un float y la guarda en xser

      fscanf(tm0,"%lf",&Count);//lee el tercer elemento de xid.dat un float y la guarda en xser

      fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de xid.dat un float y la guarda en xser
      //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
      i++;
    }// final del while
    fclose(tm0);
    //end counting rows per file
    Nds=i;//number of rows+1  in each file X%d.dat and MSD%d.dat
    //printf("CNds= %d\n",Nds);//imprime en la pantalla xid.dat
    
    Ser_X=malloc(Nds*sizeof(double));
    Ser_Y=malloc(Nds*sizeof(double));
    Ser_t=malloc(Nds*sizeof(double));
    for(i=0;i<Nds;i++){
      Ser_X[i]=0;
      Ser_Y[i]=0;
      Ser_t[i]=0;
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
      fscanf(tm0,"%lf",&Ser_Y[i]);//lee el tercer elemento de xid.dat un float y la guarda en xser
      fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de xid.dat un float y la guarda en xser
      i++;
    }// final del while
    fclose(tm0);
    Nds=i;
    printf("Nds= %d\n",Nds);
  
    
    //Nds Final time T
    for(i=0;i <= (Nds-22);i++){//loop over time  	
      theta = acos( (  (Ser_X[i+dt]-Ser_X[i]) * (Ser_X[i+2*dt]-Ser_X[i+dt] )   + (Ser_Y[i+dt]-Ser_Y[i]) * (Ser_Y[i+2*dt]-Ser_Y[i+dt] )    )  /  ( sqrt(pow(Ser_X[i+dt]-Ser_X[i],2)  + pow(Ser_Y[i+dt]-Ser_Y[i],2) )*sqrt(pow(Ser_X[i+2*dt]-Ser_X[i+dt],2)  + pow(Ser_Y[i+2*dt]-Ser_Y[i+dt],2) ) )  );
      //printf("%d  %lf\n",i,theta);
      fprintf(tm1,"%d\t%lf\n",i+1,theta);
    }//end loop over time
    
    fclose(tm1);
  }//end for id
 
  free(Ser_t);
  free(Ser_X);
  free(Ser_Y);
  return 0;
}

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
//#define Nds  500//numero de filas en cada archivo xid.dat poner numero de ultimo renglon con datos
#define GNUPLOT "gnuplot -persist"
char  nom[50];//cadena para usar sprintf
char  nam[50];//cadena para usar sprintf        
FILE *tm0;//puntero para usar fopen
FILE *tm1;//puntero para usar fopen
FILE *tm2;//puntero para usar fopen
int main(void){
   
  int          id,d,i,j,CA,CNA,P;
  double       CountI,Count;
  double       *Ser_tt;
  double       *Ser_Y;
  double        *DTHP;
  
  int ini,Nexp,Nds;
  Count=0;
  ini  =  2;
  Nexp = 364;//number of time series 129
 

  
  
  for(id=ini;id<=Nexp;id++){//for over each different file
    sprintf(nam,"CALLCH10DT%d.dat",id);//la cadena nom='V.dat'
    tm1 = fopen(nam,"w"); //se crea el archivo V.dat
   
    //Diameters LCH
    i=0;
    sprintf(nom,"LLCH10DT%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&CountI);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      
      fscanf(tm0,"%lf",&Count);//lee el segunda elemento de xid.dat un float y la guarda en xser

      fscanf(tm0,"%lf",&Count);//lee el tercer elemento de xid.dat un float y la guarda en xser
      //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
      i++;
    }// final del while
    fclose(tm0);
    //end counting rows per file
    Nds=i;//number of rows+1  in each file X%d.dat and MSD%d.dat
    Nds=Nds -1;
    //printf("CNds= %d\n",Nds);//imprime en la pantalla xid.dat
    
    Ser_Y=malloc(Nds*sizeof(double));
    Ser_tt=malloc(Nds*sizeof(double));
    DTHP=malloc(Nds*sizeof(double));
    for(i=0;i<Nds;i++){
      Ser_Y[i]=0;
      Ser_tt[i]=0;
      DTHP[i]=0;
    }
  
    i=0;
    //Captura de datos:
    sprintf(nom,"LLCH10DT%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Ser_tt[i]);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      //printf("t[%d]=%d \n",i,Ser_t[i]);
      fscanf(tm0,"%lf",&DTHP[i]);//lee el segunda elemento de xid.dat un float y la guarda en xser
      //printf("DTHP[%d]=%d \n",i,DTHP[i]);
      fscanf(tm0,"%lf",&Ser_Y[i]);//lee el tercer elemento de xid.dat un float y la guarda en xser
      i++;
    }// final del while
    fclose(tm0);
    Nds=i;
    //printf("Nds= %d\n",Nds);
    //end diameters LCH
    
    
    //Nds Final time T
    for(i=0;i <= 29;i++){//loop over time  	

      fprintf(tm1,"%lf\t%lf\n",Ser_tt[i],DTHP[i]);
   
      
    }//end loop over time

    fclose(tm1);    
  }//end for id
  
  free(Ser_tt);
  
  free(Ser_Y);
  free(DTHP);
  
  return 0;
}

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
   
  int          id,d,i,j,CountI,CA,CNA;
  double       *Ser_X,Count;
  int       *Ser_t;
  double       *Ser_Y;
  int        *DTHP;
  int ini,Nexp,Nds;
  Count=0;
  ini  =  2;
  Nexp = 129;//number of time series 129
 

  sprintf(nam,"WTADT5.dat");//la cadena nom='V.dat'
  tm1 = fopen(nam,"w"); //se crea el archivo V.dat
  sprintf(nom,"WTNADT5.dat");//la cadena nom='V.dat'
  tm2 = fopen(nom,"w"); //se crea el archivo V.dat
  
  for(id=ini;id<=Nexp;id++){//for over each different file
    
    //count number of rows per file
    i=0;
    sprintf(nom,"THR5T%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%d",&CountI);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      
      fscanf(tm0,"%d",&CountI);//lee el segunda elemento de xid.dat un float y la guarda en xser

      fscanf(tm0,"%lf",&Count);//lee el tercer elemento de xid.dat un float y la guarda en xser

      fscanf(tm0,"%lf",&Count);//lee el tercer elemento de xid.dat un float y la guarda en xser
      //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
      i++;
    }// final del while
    fclose(tm0);
    //end counting rows per file
    Nds=i;//number of rows+1  in each file X%d.dat and MSD%d.dat
    Nds=Nds -1;
    //printf("CNds= %d\n",Nds);//imprime en la pantalla xid.dat
    
    Ser_X=malloc(Nds*sizeof(double));
    Ser_Y=malloc(Nds*sizeof(double));
    Ser_t=malloc(Nds*sizeof(int));
    DTHP=malloc(Nds*sizeof(int));
    for(i=0;i<Nds;i++){
      Ser_X[i]=0;
      Ser_Y[i]=0;
      Ser_t[i]=0;
      DTHP[i]=0;
    }
  
    i=0;
    //Captura de datos:
    sprintf(nom,"THR5T%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%d",&Ser_t[i]);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      //printf("t[%d]=%d \n",i,Ser_t[i]);
      fscanf(tm0,"%d",&DTHP[i]);//lee el segunda elemento de xid.dat un float y la guarda en xser
      //printf("DTHP[%d]=%d \n",i,DTHP[i]);
      fscanf(tm0,"%lf",&Ser_X[i]);//lee el tercer elemento de xid.dat un float y la guarda en xser
      fscanf(tm0,"%lf",&Ser_Y[i]);//lee el tercer elemento de xid.dat un float y la guarda en xser
      i++;
    }// final del while
    fclose(tm0);
    Nds=i;
    //printf("Nds= %d\n",Nds);
  
    CA=0;
    CNA=0;
    //Nds Final time T
    for(i=0;i < (Nds-1);i++){//loop over time  	
      if(DTHP[i]==0){//if no active
	if(CA != 0) fprintf(tm1,"%d\n",CA);
	++CNA;
	CA=0;
      }//end if no active

      else if(DTHP[i]==1){//else if active
	if(CNA != 0) fprintf(tm2,"%d\n",CNA);
	++CA;
	CNA=0;
      }//end else if active
      if(i==(Nds -2 )){//if reaches the end of the track
	if(DTHP[i]==0) fprintf(tm2,"%d\n",CNA);
	else if(DTHP[i]==1) fprintf(tm1,"%d\n",CA);
      }//end if reaches the end of the track
      //printf("%d  %lf\n",i,theta[i]);
      //fprintf(tm1,"%d\t%lf\n",i+1,theta[i]);
    }//end loop over time

    
    
  }//end for id
  fclose(tm1);
  fclose(tm2);
  free(Ser_t);
  free(Ser_X);
  free(DTHP);
  
  return 0;
}

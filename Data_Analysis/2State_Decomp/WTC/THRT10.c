#include<stdio.h>
#include<math.h>
#include<stdlib.h>
//#define Nds  500//numero de filas en cada archivo xid.dat poner numero de ultimo renglon con datos
#define GNUPLOT "gnuplot -persist"
char  nom[50];//cadena para usar sprintf
char  nam[50];//cadena para usar sprintf
char  nim[50];//cadena para usar sprintf
FILE *tm0;//puntero para usar fopen
FILE *tm1;//puntero para usar fopen
FILE *tm2;//puntero para usar fopen
FILE *tm3;//puntero para usar fopen
FILE *tm4;//puntero para usar fopen
FILE *tm5;//puntero para usar fopen
FILE *tm6;//puntero para usar fopen
#define PI 3.14159265358979323846

int main(void){
   
  int          id,d,i,j,tau,dt,DTHP;
  double       *Ser_X,Count,R,DTH,C,VX,VY,DX,DY;
  double       *Ser_t;
  double       *Ser_Y;
  double        *theta;
  int ini,Nexp,Nds;
  Count=0;
  ini  =  2;
  Nexp = 364;//number of time series 129
  dt=10;
  C=PI/6;//mean DTH 35.52 deg
  //C=1.57;//testing
  
  sprintf(nim,"VXDT10.dat");//la cadena nom='V.dat'
  tm2 = fopen(nim,"w"); //se crea el archivo V.dat
  sprintf(nim,"VYDT10.dat");//la cadena nom='V.dat'
  tm3 = fopen(nim,"w"); //se crea el archivo V.dat
  sprintf(nim,"DXDT10.dat");//la cadena nom='V.dat'
  tm4 = fopen(nim,"w"); //se crea el archivo V.dat
  sprintf(nim,"DYDT10.dat");//la cadena nom='V.dat'
  tm5 = fopen(nim,"w"); //se crea el archivo V.dat
  sprintf(nim,"THT10.dat");//la cadena nom='V.dat'
  tm6 = fopen(nim,"w"); //se crea el archivo V.dat
  for(id=ini;id<=Nexp;id++){//for over each different file
    sprintf(nam,"THR10T%d.dat",id);//la cadena nom='V.dat'
    tm1 = fopen(nam,"w"); //se crea el archivo V.dat
    //count number of rows per file
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
    theta=malloc(Nds*sizeof(double));
    for(i=0;i<Nds;i++){
      Ser_X[i]=0;
      Ser_Y[i]=0;
      Ser_t[i]=0;
      theta[i]=0;
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
    //printf("Nds= %d\n",Nds);
  
    
    //Nds Final time T
    for(i=0;i <= (Nds-22);i++){//loop getting theta  	
      theta[i] = acos( (  (Ser_X[i+dt]-Ser_X[i]) * (Ser_X[i+2*dt]-Ser_X[i+dt] )   + (Ser_Y[i+dt]-Ser_Y[i]) * (Ser_Y[i+2*dt]-Ser_Y[i+dt] )    )  /  ( sqrt(pow(Ser_X[i+dt]-Ser_X[i],2)  + pow(Ser_Y[i+dt]-Ser_Y[i],2) )*sqrt(pow(Ser_X[i+2*dt]-Ser_X[i+dt],2)  + pow(Ser_Y[i+2*dt]-Ser_Y[i+dt],2) ) )  );
      //printf("%d  %lf\n",i,theta[i]);
      //fprintf(tm1,"%d\t%lf\n",i+1,theta[i]);
    }//end loop fetting theta

    //computing P theta and Disp
    for(i=0;i <= (Nds-22);i++){//loop for PTH and R
      
      //printf("%d  %lf\n",i,DTH);
      R=sqrt(pow(Ser_X[i+2*dt]-Ser_X[i+dt],2) + pow(Ser_Y[i+2*dt]-Ser_Y[i+dt],2));
      if(theta[i] < C ){//if is active
	DTHP=1;
	fprintf(tm1,"%d\t%d\t%lf\t%lf\n",i+1,DTHP,R,theta[i]);
	VX=(Ser_X[i+dt]-Ser_X[i]);
	fprintf(tm2,"%lf\n",VX);
	VY=(Ser_Y[i+dt]-Ser_Y[i]);
	fprintf(tm3,"%lf\n",VY);
	//fprintf(tm6,"%lf\n",theta[i]);
	fprintf(tm6,"%lf\n",theta[i]);
      }//end if  is active
      else if(theta[i] >= C){//else if is cageing
	DTHP=0;
	fprintf(tm1,"%d\t%d\t%lf\t%lf\n",i+1,DTHP,R,theta[i]);
	DX=Ser_X[i+dt]-Ser_X[i];
	fprintf(tm4,"%lf\n",DX);
	DY=Ser_Y[i+dt]-Ser_Y[i];
	fprintf(tm5,"%lf\n",DY);
	
      }//end else if is cageing 
    }//end for DTH and R

    
    fclose(tm1);
  }//end for id
  
  free(Ser_t);
  free(Ser_X);
  free(Ser_Y);
  free(theta);
  fclose(tm2);
  fclose(tm3);
  fclose(tm4);
  fclose(tm5);
  fclose(tm6);
  return 0;
}

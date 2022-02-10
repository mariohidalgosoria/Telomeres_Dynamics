#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define   Nds    101 //numero de filas en cada archivo CCWLT50_%id.dat
char  nom[50];//cadena para usar sprintf        
FILE *tm0;//puntero para usar fopen

int main(void){
   
  int          id,i,Ndat;
  double       Ser_R[Nds],xser,yser,xaser,yaser;
  double       Ser_t[Nds], CountD;
  int          ini,Nexp;
   
  ini  =  272;
  Nexp = 364;
   
  for(i=0;i<Nds;i++){
    Ser_R[i]=0;
  }

   
  for(id=ini;id<=Nexp;id++){          
   
    i=0;
    //Captura de datos:
    sprintf(nom,"CCLAT%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Ser_t[i]);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      fscanf(tm0,"%lf",&xser);//lee el segunda elemento de xid.dat un float y la guarda en xser
      fscanf(tm0,"%lf",&yser);//lee tercer elemento 
      fscanf(tm0,"%lf",&CountD);//lee cuarto elelmento
      if(i==0){
	xaser=xser;
	yaser=yser;
      }
      Ser_R[i]+=pow(xser-xaser,2) + pow(yser-yaser,2);
      //printf("X=%lf;  Y=%lf\n",Ser_X[i],Ser_Y[i]);
      
      i++;     
    }// final del while
    fclose(tm0);

  }//final del for id
    
  Ndat = i; //da el numero de filas en cada archivo leido
  printf("Numero de datos: %d\n ", Ndat);
      
  sprintf(nom,"XYMSDT100.dat");//la cadena nom='x_mean.dat'
  tm0 = fopen(nom,"w"); //se crea el archivo x_mean.dat
      
  for(i=0;i<Ndat-1;i++){
    fprintf(tm0,"%lf  %0.10lf\n",Ser_t[i],Ser_R[i]/((Nexp-ini) +1));
  }
  printf("Numero de datos: %d\n ", i);
  fclose(tm0);     
  return 0;
} 

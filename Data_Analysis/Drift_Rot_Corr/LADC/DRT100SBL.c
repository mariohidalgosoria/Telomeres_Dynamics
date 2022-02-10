/*Compile and run 4 times changing ini, Nexp, and l each time*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

char  nom[50];
char  nam[50];        
FILE *tm0;
FILE *tm1;
int main(void){
   
  int          id,d,i,j,M,N,r,l;
  double       *Ser_X,Count;
  double       *Ser_Y;
  double       *Ser_Z;
  double       *Ser_t;
  double       **XT;
  double       **YT;
  double       **ZT;
  double       **XRT;
  double       **YRT;
  double       **XIRT;
  double       **YIRT;
  double       **XA;
  double       **YA;
  double       **ZA;
  double        Rx,Ry,Rz,Rd,Th,STh;
  int ini,Nexp,Nds;
  Count=0;
  
  //ini  =  2;//tracks at file 1-3DwoLMNA100
  //Nexp = 19;//total of 18 trajectories
  //ini  =  20;//tracks at file 2-3DwoLMNA100
  //Nexp = 45;//total of 26 trajectories
  //ini  =  46;//tracks at file 3-3DwoLMNA100
  //Nexp = 55;//total of 10 trajectories
  ini  =  56;//tracks at file 5-3DwoLMNA100
  Nexp = 70;//total of 15 trajectories
  
  M=100;//number of rows T=100
  N=(Nexp-ini)+1;//number of cols (Nexp-ini)+1
  //l=2;//use for 1-3DwoLMNA100 l=ini
  //l=20;//use for 2-3DwoLMNA100 l=ini
  //l=46;//use for 3-3DwoLMNA100 l=ini
  l=56;//use for 5-3DwoLMNA100 l=ini

  //create array of pointer of size M
  XA=(double **)malloc(M*sizeof(double));
  YA=(double **)malloc(M*sizeof(double));
  ZA=(double **)malloc(M*sizeof(double));
  XT=(double **)malloc(M*sizeof(double));
  YT=(double **)malloc(M*sizeof(double));
  ZT=(double **)malloc(M*sizeof(double));
  XRT=(double **)malloc(M*sizeof(double));
  YRT=(double **)malloc(M*sizeof(double));
  XIRT=(double **)malloc(M*sizeof(double));
  YIRT=(double **)malloc(M*sizeof(double));

  //allocate memory of size N
  for(r=0;r<M;r++){
    XA[r]=(double *)malloc(N*sizeof(double));
    YA[r]=(double *)malloc(N*sizeof(double));
    ZA[r]=(double *)malloc(N*sizeof(double));
    XT[r]=(double *)malloc(N*sizeof(double));
    YT[r]=(double *)malloc(N*sizeof(double));
    ZT[r]=(double *)malloc(N*sizeof(double));
    XRT[r]=(double *)malloc(N*sizeof(double));
    YRT[r]=(double *)malloc(N*sizeof(double));
    XIRT[r]=(double *)malloc(N*sizeof(double));
    YIRT[r]=(double *)malloc(N*sizeof(double));
  }
  
  
  for(id=ini;id<=Nexp;id++){//for over each different file          
    //count number of rows per file
    i=0;
    sprintf(nom,"WLAT100T%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    // printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Count);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      
      fscanf(tm0,"%lf",&Count);//lee el segunda elemento de xid.dat un float y la guarda en count
      
      fscanf(tm0,"%lf",&Count);//lee el tercer elemento de xid.dat un float y la guarda en count
      
      fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de xid.dat un float y la guarda en count
      //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
      i++;
    }// final del while
    fclose(tm0);
    //end counting rows per file
    Nds=i;//number of rows+1  in each file X%d.dat and MSD%d.dat
    //printf("CNds= %d\n",Nds);//imprime en la pantalla xid.dat
    
    Ser_X=malloc((Nds-1)*sizeof(double));
    Ser_Y=malloc((Nds-1)*sizeof(double));
    Ser_Z=malloc((Nds-1)*sizeof(double));
    Ser_t=malloc((Nds-1)*sizeof(double));
    for(i=0;i<(Nds-1);i++){
      Ser_X[i]=0;
      Ser_Y[i]=0;
      Ser_Z[i]=0;
      Ser_t[i]=0;
    }
    
    i=0;
    //Captura de datos:
    sprintf(nom,"WLAT100T%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    //printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Ser_t[i]);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      //printf("t[%d]=%lf \n",i,Ser_t[i]);
      fscanf(tm0,"%lf",&Ser_X[i]);//lee el segunda elemento de xid.dat un float y la guarda en serx
      
      fscanf(tm0,"%lf",&Ser_Y[i]);//lee el tercer elemento de xid.dat un float y la guarda en sery
      //printf("Y[%d]=%lf \n",i,Ser_Y[i]);
      fscanf(tm0,"%lf",&Ser_Z[i]);//lee el cuarto elemento de xid.dat un float y la guarda en serz
      //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
      i++;
    }// final del while
    fclose(tm0);
    Nds=i;
    //printf("Nds= %d\n",Nds);
    
    //allocating data X &  Y
    for (j = 0; j < M; j++){
      XA[j][id-l] = Ser_X[j];    // or *(A[r] + c) or *(*(A + r) + c)
      YA[j][id-l] = Ser_Y[j];
      ZA[j][id-l] = Ser_Z[j];
    }
    
  }//end for id over the file woLMNA#
  
  // print the 2D array for cheking
  //for (i = 0; i < M; i++){
  //for (j = 0; j < N; j++)
  //  printf("%lf ", XA[i][j]);    // or *(A[r] + c) or *(*(A + r) + c)
    
  //printf("\n");
  //}//end print
  
  
  //Start drift correction
  for(i=0;i<M;i++){//loop over time
    Rx=0;
    Ry=0;
    Rz=0;
    for(j=0;j<N;j++){//loop over tracks for sum
      Rx+=XA[i][j];
      Ry+=YA[i][j];
      Rz+=ZA[i][j];
    }//end loop over tracks for sum
    Rx=Rx/N;//average position at X for each time point
    Ry=Ry/N;//average position at Y for each time point
    Rz=Rz/N;//average position at Z for each time point
    //printf("%lf\t%lf\t%lf\t%lf\n",Ser_t[i],Rx,Ry,Rz);
    for(j=0;j<N;j++){//loop over tracks minus
      XT[i][j]=XA[i][j]-Rx;
      YT[i][j]=YA[i][j]-Ry;
      ZT[i][j]=ZA[i][j]-Rz;
    }//end loop over tracks minus
  }//end loop over time

  //print the 2D array for cheking
  //for (i = 0; i < M; i++){
  //for (j = 0; j < N; j++){
      //    // or *(A[r] + c) or *(*(A + r) + c)
  //  printf("%lf ", ZT[i][j]); 
  //}
  //printf("\n");
  //}//end print

  //end drift correction


  //start rotation correction
  //compute averege angle
  for(i=0;i<M;i++){//loop over time
    //Th=0;
    //Rd=0;
    STh=0;
    for(j=0;j<N;j++){//loop over tracks thav
      Rd=sqrt(pow(XT[i][j],2)+ pow(YT[i][j],2));
      Th=acos(XT[i][j]/Rd);
      STh+=Th;
    }//end loop over tracks thav
    STh=STh/N;
    //end compute average angle
    for(j=0;j<N;j++){//do rotation
      XRT[i][j]=XT[i][j]*cos(STh) - YT[i][j]*sin(STh);
      YRT[i][j]=XT[i][j]*sin(STh) + YT[i][j]*cos(STh);
    }//end rotation
    for(j=0;j<N;j++){//do inverse rotation
      XIRT[i][j]=XRT[i][j]*cos(STh) + YRT[i][j]*sin(STh);
      YIRT[i][j]= -XRT[i][j]*sin(STh) + YRT[i][j]*cos(STh);
    }//end invesre rotation
  }//end loop over time
  
  //print the 2D array for cheking
  //for (i = 0; i < M; i++){
  //for (j = 0; j < N; j++)
  //  printf("%lf ", YRT[i][j]);    // or *(A[r] + c) or *(*(A + r) + c)
    
  //printf("\n");
  //}//end print
  //end rotation correction

  //save corrected data files
  for(id=ini;id<=Nexp;id++){//for over each different file
    sprintf(nam,"CWLAT100T%d.dat",id);//la cadena nom='V.dat'
    tm1 = fopen(nam,"w"); //se crea el archivo V.dat
    for(i=0;i<M;i++){//write
      fprintf(tm1,"%lf  %lf  %lf  %lf\n",Ser_t[i],XIRT[i][id-l],YIRT[i][id-l],ZT[i][id-l]);
    }//end write
    fclose(tm1);

  }//end id
  
  
  //free memory  
  for(r=0;r<M;r++){
    free(XA[r]);
    free(YA[r]);
    free(ZA[r]);
    free(XT[r]);
    free(YT[r]);
    free(ZT[r]);
    free(XRT[r]);
    free(YRT[r]);
    free(XIRT[r]);
    free(YIRT[r]);
  }

  free(Ser_t);
  free(Ser_X);
  free(Ser_Y);
  free(Ser_Z);
  free(XA);
  free(YA);
  free(ZA);
  free(XT);
  free(YT);
  free(ZT);
  free(XRT);
  free(YRT);
  free(XIRT);
  free(YIRT);
  return 0;
}

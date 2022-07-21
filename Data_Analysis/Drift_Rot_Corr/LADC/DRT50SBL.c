/*Compile and run 4 times changing ini, Nexp, and l each time*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

char  nom[50];
char  nam[50];        
FILE *tm0;
FILE *tm1;
int main(void){
   
  int          id,i,j,M,N,r,l,k;
  double       *Ser_X,Count;
  double       *Ser_Y;
  double       *Ser_Z;
  double       *Ser_t;
  double       **XA;
  double       **YA;
  double       **ZA;
  double        Rx,Ry,Rz,Rd,Th,STh,R1,R2,Xtemp,Ytemp,avnum;
  int ini,Nexp,Nds;
  Count=0;
  
  //ini  =  2;//tracks at file woLMNA10-3D_TEL
  //Nexp = 20;//total of 19 trajectories
  //ini  =  21;//tracks at file woLMNA11-3D_TEL
  //Nexp = 37;//total of 17 trajectories
  ini  =  38;//tracks at file woLMNA13-3D_TEL
  Nexp = 60;//total of 23 trajectories
  
  M=50;//number of rows T=50
  N=(Nexp-ini)+1;//number of cols (Nexp-ini)+1
  //l=2;//use for woLMNA10-3D_TEL l=ini
  //l=21;//use for woLMNA11-3D_TEL l=ini
  l=38;//use for woLMNA13-3D_TEL l=ini


  //create array of pointer of size M
  XA=(double **)malloc(M*sizeof(double));
  YA=(double **)malloc(M*sizeof(double));
  ZA=(double **)malloc(M*sizeof(double));

  //allocate memory of size N
  for(r=0;r<M;r++){
    XA[r]=(double *)malloc(N*sizeof(double));
    YA[r]=(double *)malloc(N*sizeof(double));
    ZA[r]=(double *)malloc(N*sizeof(double));
  }
  
  
  for(id=ini;id<=Nexp;id++){//for over each different file          
    //count number of rows per file
    i=0;
    sprintf(nom,"WLAT50T%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
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
    sprintf(nom,"WLAT50T%d.dat",id);//coloca el id, xid.dat en una cadena 'nom'
    //printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Ser_t[i]);//lee el primer elemento de xid.dat un float y la guarda en Ser_t[i]
      //printf("t[%d]=%lf \n",i,Ser_t[i]);
      fscanf(tm0,"%lf",&Ser_X[i]);//lee el segunda elemento de xid.dat un float y la guarda en serx
      //printf("X[%d]=%lf \n",i,Ser_X[i]);
      fscanf(tm0,"%lf",&Ser_Y[i]);//lee el tercer elemento de xid.dat un float y la guarda en sery
      //printf("Y[%d]=%lf \n",i,Ser_Y[i]);
      fscanf(tm0,"%lf",&Ser_Z[i]);//lee el cuarto elemento de xid.dat un float y la guarda en serz
      //printf("%g\t%g\t%g\n",Ser_t[i],Ser_X[i],Ser_Y[i]);
      i++;
    }// final del while
    fclose(tm0);
    Nds=i;
    //printf("Nds= %d\n",Nds);
    //for(j=0;j<M;j++) printf("%g\t%g\t%g\n",Ser_t[j],Ser_X[j],Ser_Y[j]);
    //allocating data X &  Y
    for (j = 0; j < M; j++){
      XA[j][id-l] = Ser_X[j];    // or *(A[r] + c) or *(*(A + r) + c)
      YA[j][id-l] = Ser_Y[j];
      ZA[j][id-l] = Ser_Z[j];
      //printf("%g\t%g\t%g\n",Ser_t[j],XA[j][id-l],YA[j][id-l]);
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
    
    for(k=i;k<M;k++){//loop for k shifting tracks forward in time
      for(j=0;j<N;j++){//loop for j  over tracks 
	XA[k][j]=XA[k][j]-Rx;
	YA[k][j]=YA[k][j]-Ry;
	ZA[k][j]=ZA[k][j]-Rz;
	//printf("XT[%d][%d]=%g; YT[%d][%d]=%g\n",k,j,XT[k][j],k,j,XT[k][j]);
      }//loop for j  over tracks
    }//end loop for k shifting tracks forward in time
    //end drift correction
    
    //start rotation correction
    avnum=0;
    STh=0;
    for(j=0;j<N;j++){//loop for j  over tracks
      if(i==0){//first time step                                                               
        Rd=sqrt(pow(XA[i][j],2)+ pow(YA[i][j],2));
        Th=acos(XA[i][j]/Rd);
        if(YA[i][j]<0) Th=-Th;
        STh=STh+(Th/N);
      }//end if i==0                                                                           
      else{//i>0                                                                               
        R2=sqrt( pow(XA[i][j],2) + pow(YA[i][j],2) );
        R1=sqrt( pow(XA[i-1][j],2) + pow(YA[i-1][j],2) );
        Th=acos((  (XA[i][j]*XA[i-1][j]) +  (YA[i][j]*YA[i-1][j]) )/(R1*R2));
        if( asin( ( (-XA[i][j]*YA[i-1][j]) + (YA[i][j]*XA[i-1][j]) ) /(R1*R2)) <0) Th=-Th;
        if(R2>0.5){//traj is close to 0                                                        
          STh=STh+Th;
          avnum++;
        }//end if traj too close to 0                                                          
      }//ens else i>0                     
    }//loop for j  over tracks
    if(i !=0 ) STh=STh/avnum;

    for(k=i;k<M;k++){//loop for k shifting tracks forward in time
      for(j=0;j<N;j++){//loop for j  over tracks for inverse rotation
	Xtemp=XA[k][j]*cos(STh) +  YA[k][j]*sin(STh);
	Ytemp=-XA[k][j]*sin(STh) + YA[k][j]*cos(STh);
	XA[k][j]=Xtemp;
	YA[k][j]=Ytemp;
      }//loop for j  over tracks for inverse rotation
    }//end loop for k shifting tracks forward in time

  }//end loop over time

  //print the 2D array for cheking
  //for (i = 0; i < M; i++){
  //for (j = 0; j < N; j++){
  //    // or *(A[r] + c) or *(*(A + r) + c)
  //  printf("%lf ", ZT[i][j]); 
  //}
  //printf("\n");
  //}//end print

  
  
  //print the 2D array for cheking
  //for (i = 0; i < M; i++){
  //for (j = 0; j < N; j++)
  //  printf("%lf ", YRT[i][j]);    // or *(A[r] + c) or *(*(A + r) + c)
    
  //printf("\n");
  //}//end print
  //end rotation correction

  //save corrected data files
  for(id=ini;id<=Nexp;id++){//for over each different file
    sprintf(nam,"CWLAT50T%d.dat",id);//la cadena nom='V.dat'
    tm1 = fopen(nam,"w"); //se crea el archivo V.dat
    for(i=0;i<M;i++){//write
      fprintf(tm1,"%lf  %lf  %lf  %lf\n",Ser_t[i],XA[i][id-l],YA[i][id-l],ZA[i][id-l]);
    }//end write
    fclose(tm1);

  }//end id
  
  
  //free memory  
  for(r=0;r<M;r++){
    free(XA[r]);
    free(YA[r]);
    free(ZA[r]);
  }

  free(Ser_t);
  free(Ser_X);
  free(Ser_Y);
  free(Ser_Z);
  free(XA);
  free(YA);
  free(ZA);

  return 0;
}

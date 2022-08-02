#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define GNUPLOT "gnuplot -persist"
char  nom[50];//cadena para usar sprintf
char  nam[50];//cadena para usar sprintf        
FILE *tm0;//puntero para usar fopen
FILE *tm1;//puntero para usar fopen
void printc(int comb[], int k);
int next_comb(int comb[], int k, int n);
int main(void){
   
  int          i,j,dt,counter;
  double       *Ser_XA,Count;
  double       *Ser_t;
  double       *Ser_YA;
  double       *Ser_XB;
  double       *Ser_YB;
  double       dAB,betaAB;
  int ini,Nexp,Nds,NC,R;
  int comb[16]; /* comb[i] is the index of the i-th element in the
		   combination */
  int A, B; 
  Count=0;
  ini  =  21;
  Nexp = 37;//number of time series
  dt=5;
  NC=(Nexp-ini)+1;
  R=2;
  
  sprintf(nam,"TA2CDT5C2.dat");//la cadena nom='V.dat'
  tm1 = fopen(nam,"w"); //se crea el archivo V.dat
  /* Setup comb for the initial combination */
  counter=1;
  for (i = 0; i < R; ++i)
    comb[i] = i;
  /* Print the first combination */
  //printc(comb, R);
  A=comb[0]+1;
  B=comb[1]+1;
  printf("A=%d, B=%d\n",A,B);

 
 //get data from file CCLATA.dat
  j=0;
  sprintf(nom,"CCWLT%d.dat",A+ini-1);//coloca el id, file.dat en una cadena 'nom'
  printf("%s\n",nom);//imprime en la pantalla file.dat
  tm0 = fopen(nom,"r");//abre file.dat para lectura, creando el puntero tm0
  while((!feof(tm0))){//mientras no sea el final de file.dat
    fscanf(tm0,"%lf",&Count);//lee el primer elemento de file.dat un float y la guarda en Count
    
    fscanf(tm0,"%lf",&Count);//lee el segunda elemento de file.dat un float y la guarda en count
    
    fscanf(tm0,"%lf",&Count);//lee el tercer elemento de file.dat un float y la guarda en Count

    fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de file.dat un float y la guarda en Count
    //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
    j++;
  }// final del while
  fclose(tm0);
  //end counting rows per file
  Nds=j;//number of rows+1  in each file file%d.dat 
  //printf("CNds= %d\n",Nds);//imprime en la pantalla file%id.dat
  //create nad initialize arrays
  Ser_XA=malloc(Nds*sizeof(double));
  Ser_YA=malloc(Nds*sizeof(double));
  Ser_t=malloc(Nds*sizeof(double));
  for(j=0;j<Nds;j++){
    Ser_XA[j]=0;
    Ser_YA[j]=0;
    Ser_t[j]=0;
  }
  
  j=0;
  //Captura de datos:
  sprintf(nom,"CCWLT%d.dat",A+ini-1);//coloca el id, xid.dat en una cadena 'nom'
  printf("%s\n",nom);//imprime en la pantalla xid.dat
  tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
  while((!feof(tm0))){//mientras no sea el final de xid.dat
    fscanf(tm0,"%lf",&Ser_t[j]);//lee el primer elemento de fileid.dat un float y la guarda en Ser_t[i]
    //printf("t[%d]=%lf \n",i,Ser_t[i]);
    fscanf(tm0,"%lf",&Ser_XA[j]);//lee el segunda elemento de fileid.dat un float y la guarda en Ser_X[i]
    fscanf(tm0,"%lf",&Ser_YA[j]);//lee el tercer elemento de fileid.dat un float y la guarda en Count
    fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de fileid.dat un float y la guarda en Count
    //printf("XA=%lf, YA=%lf \n",Ser_XA[j],Ser_YA[j]);
    j++;
  }// final del while
  fclose(tm0);
  Nds=j;
  //printf("Nds= %d\n",Nds);
  //end get data from CCLATA.dat




//get data from file CCLATB.dat
  j=0;
  sprintf(nom,"CCWLT%d.dat",B+ini-1);//coloca el id, file.dat en una cadena 'nom'
  printf("%s\n",nom);//imprime en la pantalla file.dat
  tm0 = fopen(nom,"r");//abre file.dat para lectura, creando el puntero tm0
  while((!feof(tm0))){//mientras no sea el final de file.dat
    fscanf(tm0,"%lf",&Count);//lee el primer elemento de file.dat un float y la guarda en Count
    
    fscanf(tm0,"%lf",&Count);//lee el segunda elemento de file.dat un float y la guarda en count
    
    fscanf(tm0,"%lf",&Count);//lee el tercer elemento de file.dat un float y la guarda en Count

    fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de file.dat un float y la guarda en Count
    //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
    j++;
  }// final del while
  fclose(tm0);
  //end counting rows per file
  Nds=j;//number of rows+1  in each file file%d.dat 
  //printf("CNds= %d\n",Nds);//imprime en la pantalla file%id.dat
  //create nad initialize arrays
  Ser_XB=malloc(Nds*sizeof(double));
  Ser_YB=malloc(Nds*sizeof(double));
  Ser_t=malloc(Nds*sizeof(double));
  for(j=0;j<Nds;j++){
    Ser_XB[j]=0;
    Ser_YB[j]=0;
    Ser_t[j]=0;
  }
  
  j=0;
  //Captura de datos:
  sprintf(nom,"CCWLT%d.dat",B+ini-1);//coloca el id, xid.dat en una cadena 'nom'
  printf("%s\n",nom);//imprime en la pantalla xid.dat
  tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
  while((!feof(tm0))){//mientras no sea el final de xid.dat
    fscanf(tm0,"%lf",&Ser_t[j]);//lee el primer elemento de fileid.dat un float y la guarda en Ser_t[i]
    //printf("t[%d]=%lf \n",i,Ser_t[i]);
    fscanf(tm0,"%lf",&Ser_XB[j]);//lee el segunda elemento de fileid.dat un float y la guarda en Ser_X[i]
    fscanf(tm0,"%lf",&Ser_YB[j]);//lee el tercer elemento de fileid.dat un float y la guarda en Count
    fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de fileid.dat un float y la guarda en Count
    //printf("XB[%d]=%lf, YB[%d]=%lf \n",j,Ser_XB[j],j,Ser_YB[j]);
    j++;
  }// final del while
  fclose(tm0);
  Nds=j;
  //printf("Nds= %d\n",Nds);
  //end get data from CCLATB.dat

  
  //compute the initial distance between A and B
  dAB=sqrt(pow(Ser_XA[0]-Ser_XB[0],2)+ pow(Ser_YA[0]-Ser_YB[0],2));
  //printf("dAB=%lf\n",dAB);
  betaAB=0;
  //compute beta AB (time average of dot product)
  for(j=0;j <= Nds-7;j++){//X=[x0,x1,...,xNds-2] the loop has to go up to ((Nds-d)-2), to avoid evalution of Ser_X[Nds-1] and Ser_X[Nds]  
    //printf("delta=%d\tX[i+d]=%g\tSer_X[i]=%g\tSer_X[i+d]-Ser_X[i])=%g\n",d,Ser_X[i+d],Ser_X[i],Ser_X[i+d]-Ser_X[i]);
  betaAB+= ( Ser_XA[j+dt]*Ser_XB[j+dt] - Ser_XA[j+dt]*Ser_XB[j] - Ser_XA[j]*Ser_XB[j+dt] + Ser_XA[j]*Ser_XB[j]+  Ser_YA[j+dt]*Ser_YB[j+dt] - Ser_YA[j+dt]*Ser_YB[j] - Ser_YA[j]*Ser_YB[j+dt] + Ser_YA[j]*Ser_YB[j] ) /( sqrt( pow(Ser_XA[j+dt]- Ser_XA[j],2) + pow(Ser_YA[j+dt]-Ser_YA[j],2)  )  * sqrt(pow(Ser_XB[j+dt]-Ser_XB[j],2) + pow(Ser_YB[j+dt]-Ser_YB[j],2) )  )  ;
    //printf("%d  %lf\n",d,V[d]);
  }//end for j time average dot product
  betaAB=betaAB*(1.0/(Nds-7));  
  //printf("dAB=%lf;  betaAB= %lf\n",dAB,betaAB);
  fprintf(tm1,"%lf  %lf\n",dAB,betaAB);
  //end compute beta AB (time average of dot product)



  /* Generate and print all the other combinations */
  
  while (next_comb(comb, R, NC)){
    //printc(comb, R);
    A=comb[0]+1;
    B=comb[1]+1;
    printf("A=%d, B=%d\n",A,B);
    counter+=1;
    betaAB=0;



    //get data from file CCLATA.dat
    j=0;
    sprintf(nom,"CCWLT%d.dat",A+ini-1);//coloca el id, file.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla file.dat
    tm0 = fopen(nom,"r");//abre file.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de file.dat
      fscanf(tm0,"%lf",&Count);//lee el primer elemento de file.dat un float y la guarda en Count
      
      fscanf(tm0,"%lf",&Count);//lee el segunda elemento de file.dat un float y la guarda en count
      
      fscanf(tm0,"%lf",&Count);//lee el tercer elemento de file.dat un float y la guarda en Count

      fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de file.dat un float y la guarda en Count
      //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
      j++;
    }// final del while
    fclose(tm0);
    //end counting rows per file
    Nds=j;//number of rows+1  in each file file%d.dat 
    //printf("CNds= %d\n",Nds);//imprime en la pantalla file%id.dat
    //create nad initialize arrays
    Ser_XA=malloc(Nds*sizeof(double));
    Ser_YA=malloc(Nds*sizeof(double));
    Ser_t=malloc(Nds*sizeof(double));
    for(j=0;j<Nds;j++){
      Ser_XA[j]=0;
      Ser_YA[j]=0;
      Ser_t[j]=0;
    }
  
    j=0;
    //Captura de datos:
    sprintf(nom,"CCWLT%d.dat",A+ini-1);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Ser_t[j]);//lee el primer elemento de fileid.dat un float y la guarda en Ser_t[i]
      //printf("t[%d]=%lf \n",i,Ser_t[i]);
      fscanf(tm0,"%lf",&Ser_XA[j]);//lee el segunda elemento de fileid.dat un float y la guarda en Ser_X[i]
      fscanf(tm0,"%lf",&Ser_YA[j]);//lee el tercer elemento de fileid.dat un float y la guarda en Count
      fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de fileid.dat un float y la guarda en Count
      //printf("XA=%lf, YA=%lf \n",Ser_XA[j],Ser_YA[j]);
      j++;
    }// final del while
    fclose(tm0);
    Nds=j;
    //printf("Nds= %d\n",Nds);
    //end get data from CCLATA.dat




    //get data from file CCLATB.dat
    j=0;
    sprintf(nom,"CCWLT%d.dat",B+ini-1);//coloca el id, file.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla file.dat
    tm0 = fopen(nom,"r");//abre file.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de file.dat
      fscanf(tm0,"%lf",&Count);//lee el primer elemento de file.dat un float y la guarda en Count
    
      fscanf(tm0,"%lf",&Count);//lee el segunda elemento de file.dat un float y la guarda en count
    
      fscanf(tm0,"%lf",&Count);//lee el tercer elemento de file.dat un float y la guarda en Count

      fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de file.dat un float y la guarda en Count
      //        printf("%d\t%g\n",Ser_t[i],Ser_X[i]);
      j++;
    }// final del while
    fclose(tm0);
    //end counting rows per file
    Nds=j;//number of rows+1  in each file file%d.dat 
    //printf("CNds= %d\n",Nds);//imprime en la pantalla file%id.dat
    //create nad initialize arrays
    Ser_XB=malloc(Nds*sizeof(double));
    Ser_YB=malloc(Nds*sizeof(double));
    Ser_t=malloc(Nds*sizeof(double));
    for(j=0;j<Nds;j++){
      Ser_XB[j]=0;
      Ser_YB[j]=0;
      Ser_t[j]=0;
    }
  
    j=0;
    //Captura de datos:
    sprintf(nom,"CCWLT%d.dat",B+ini-1);//coloca el id, xid.dat en una cadena 'nom'
    printf("%s\n",nom);//imprime en la pantalla xid.dat
    tm0 = fopen(nom,"r");//abre xid.dat para lectura, creando el puntero tm0
    while((!feof(tm0))){//mientras no sea el final de xid.dat
      fscanf(tm0,"%lf",&Ser_t[j]);//lee el primer elemento de fileid.dat un float y la guarda en Ser_t[i]
      //printf("t[%d]=%lf \n",i,Ser_t[i]);
      fscanf(tm0,"%lf",&Ser_XB[j]);//lee el segunda elemento de fileid.dat un float y la guarda en Ser_X[i]
      fscanf(tm0,"%lf",&Ser_YB[j]);//lee el tercer elemento de fileid.dat un float y la guarda en Count
      fscanf(tm0,"%lf",&Count);//lee el cuarto elemento de fileid.dat un float y la guarda en Count
      //printf("XB[%d]=%lf, YB[%d]=%lf \n",j,Ser_XB[j],j,Ser_YB[j]);
      j++;
    }// final del while
    fclose(tm0);
    Nds=j;
    //printf("Nds= %d\n",Nds);
  //end get data from CCLATB.dat

  
  //compute the initial distance between A and B
    dAB=sqrt(pow(Ser_XA[0]-Ser_XB[0],2)+ pow(Ser_YA[0]-Ser_YB[0],2));
    //printf("dAB=%lf\n",dAB);
    //compute beta AB (time average of dot product)
    for(j=0;j <= Nds-7;j++){//X=[x0,x1,...,xNds-2] the loop has to go up to ((Nds-d)-2), to avoid evalution of Ser_X[Nds-1] and Ser_X[Nds]  
      //printf("delta=%d\tX[i+d]=%g\tSer_X[i]=%g\tSer_X[i+d]-Ser_X[i])=%g\n",d,Ser_X[i+d],Ser_X[i],Ser_X[i+d]-Ser_X[i]);
      betaAB+= ( Ser_XA[j+dt]*Ser_XB[j+dt] - Ser_XA[j+dt]*Ser_XB[j] - Ser_XA[j]*Ser_XB[j+dt] + Ser_XA[j]*Ser_XB[j]+  Ser_YA[j+dt]*Ser_YB[j+dt] - Ser_YA[j+dt]*Ser_YB[j] - Ser_YA[j]*Ser_YB[j+dt] + Ser_YA[j]*Ser_YB[j] ) /( sqrt( pow(Ser_XA[j+dt]- Ser_XA[j],2) + pow(Ser_YA[j+dt]-Ser_YA[j],2)  )  * sqrt(pow(Ser_XB[j+dt]-Ser_XB[j],2) + pow(Ser_YB[j+dt]-Ser_YB[j],2) )  )  ;
      //printf("%d  %lf\n",d,V[d]);
    }//end for j time average dot product
    betaAB=betaAB*(1.0/(Nds-7));  
    //printf("dAB=%lf;  betaAB= %lf\n",dAB,betaAB);
    fprintf(tm1,"%lf  %lf\n",dAB,betaAB);
    //end compute beta AB (time average of dot product)
 

  }
  printf("count= %d\n", counter);




  free(Ser_t);
  free(Ser_XA);
  free(Ser_YA);
  free(Ser_XB);
  free(Ser_YB);
  fclose(tm1);
  
  return 0;
}


/* Prints out a combination like {1, 2} */
void printc(int comb[], int k) {
  printf("{");
  int i;
  for (i = 0; i < k; ++i)
    printf("%d, ", comb[i] + 1);
  printf("\b\b}\n");
}

/*
  next_comb(int comb[], int k, int n)
  Generates the next combination of n elements as k after comb

  comb => the previous combination ( use (0, 1, 2, ..., k) for first)
  k => the size of the subsets to generate
  n => the size of the original set

  Returns: 1 if a valid combination was found
  0, otherwise
*/
int next_comb(int comb[], int k, int n) {
  int i = k - 1;
  ++comb[i];
  while ((i >= 0) && (comb[i] >= n - k + 1 + i)) {
    --i;
    ++comb[i];
  }

  if (comb[0] > n - k) /* Combination (n-k, n-k+1, ..., n) reached */
    return 0; /* No more combinations can be generated */

  /* comb now looks like (..., x, n, n, n, ..., n).
     Turn it into (..., x, x + 1, x + 2, ...) */
  for (i = i + 1; i < k; ++i)
    comb[i] = comb[i - 1] + 1;

  return 1;
}

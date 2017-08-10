/*
ID: lic92031
LANG: C
TASK: stamps
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_VALUE 2000000
int main(){
  FILE *fin = fopen("stamps.in","r");
  FILE *fout = fopen("stamps.out","w");
  int K,N;
  int stamp_value[50]={0};
  int *f = malloc(MAX_VALUE*sizeof(int));
  int i,j;
  int result = 0;
  fscanf(fin,"%d%d",&K,&N);
  for(i = 0; i < N; i++) fscanf(fin,"%d",&stamp_value[i]);
  memset(f,0,MAX_VALUE*sizeof(int));
  do{
    result++;
    for(i = 0; i < N; i++){
      if(result>stamp_value[i]&&f[result-stamp_value[i]]>0 && f[result-stamp_value[i]]<K){
        if(f[result] == 0 || f[result] > f[result-stamp_value[i]]+1){
          f[result] = f[result-stamp_value[i]]+1;
        }
      }else{
        if(result == stamp_value[i]) f[result] = 1;
      }
    }
    if(f[result] == 0) break;
  }while(1);
  fprintf(fout,"%d\n",result-1);
  free(f);
  fclose(fin);
  fclose(fout);
  return 0;
}

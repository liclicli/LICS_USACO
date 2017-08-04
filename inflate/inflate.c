/*
ID: lic92031
LANG: C
TASK: inflate
*/
#include<stdio.h>
int main(){
  int i,j;
  FILE *fin = fopen("inflate.in","r");
  FILE *fout = fopen("inflate.out","w");
  int M,N;
  int scores[10001]={0};
  int costs[10001]={0};
  int f[10001]={0};
  fscanf(fin,"%d%d",&M,&N);
  for(i = 0; i < N; i++) fscanf(fin,"%d%d",&scores[i],&costs[i]);
  fclose(fin);
  for(i = 0; i <= M; i++){
    for(j = 0; j < N; j++){
      if(i-costs[j]>=0&&f[i-costs[j]]+scores[j]>f[i]) f[i] = f[i-costs[j]]+scores[j];
    }
  }
  fprintf(fout,"%d\n",f[M]);
  fclose(fout);
  return 0;
}

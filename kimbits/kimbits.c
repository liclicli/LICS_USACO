/*
ID: lic92031
LANG: C
TASK: kimbits
*/
#include<stdio.h>
int main(){
  FILE *fin = fopen("kimbits.in","r");
  FILE *fout = fopen("kimbits.out","w");
  int N,L;
  long long I;
  int f[33][33] = {0};
  int g[33][33] = {0};
  int result[33] = {0};
  int i,j,rem;
  fscanf(fin,"%d%d%lld",&N,&L,&I);
  f[1][1] = 1;
  g[1][0] = 1;
  g[1][1] = 1;
  for (i = 1; i <= N; i++){
    for(j = 0; j <= L; j++){
      if(i == 1 && j <= 1) continue;
      if(j > i) {
        g[i][j] = g[i][j-1];
        f[i][j] = f[i][j-1];
      }else{
        f[i][j] = f[i-1][j-1]+g[i-1][j-1];
        g[i][j] = f[i-1][j]+g[i-1][j];
      }
    }
  }
  j = L;
  for (i = N; i > 0; i--){
    if(I > g[i][j]){
      result[i] = 1;
      I = I - g[i][j];
      j--;
    }
  }
  for (i = N; i > 0; i--) fprintf(fout,"%d",result[i]);
  fprintf(fout,"\n");
  fclose(fin);
  return 0;
}

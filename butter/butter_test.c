#include<stdio.h>
int main(){
  FILE *fin = fopen("butter.in","r");
  FILE *fout = fopen("butter.out","w");
  int N = 0, P = 0, C = 0;
  int i = 0, j = 0, k = 0;
  int cow[20]={0};
  int map[20][20];
  int f[20][20];
  fscanf(fin,"%d%d%d", &N, &P, &C);
  for(i = 1; i <= P; i++){
    for(j = 1; j <= P; j++) {
      map[i][j] = 10000;
      f[i][j] = 10000;
    }
    map[i][j] = 0;
    f[i][i] = 0;
  }
  for(i = 0; i < N; i++) fscanf(fin,"%d", &cow[i]);
  for(i = 0; i < C; i++){
    int tmp0 = 0, tmp1 = 0, tmp2 = 0;
    fscanf(fin,"%d%d%d", &tmp0, &tmp1, &tmp2);
    map[tmp0][tmp1] = tmp2;
    map[tmp1][tmp0] = tmp2;
  }
  for(k = 1; k <= P; k++)
    for(i = 1; i <= P; i++)
      for(j = 1; j <=P; j++)
      {
        if(f[i][j] > map[i][j]) f[i][j] = map[i][j];
        if(f[i][j] > f[i][k]+f[k][j]) f[i][j] = f[i][k]+f[k][j];
      }
  for(j = 1; j <= P; j++){
    for(k = 1; k <= P; k++) printf("%d ", f[j][k]);
    printf("\n");
  }
  printf("\n");
  fclose(fin);
  fclose(fout);
  return 0;
}

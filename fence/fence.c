/*
ID: lic92031
LANG: C
TASK: fence
*/
#include<stdio.h>
int dfs(int fen[501][501], int degree[501], int start, int Tf, int F, int max_fen, int result[1025]){
  int i = 0;
  result[Tf] = start;
  int ci[1025] = {0};
  ci[start] = 1;
  int qlen = 1;
  int que[1025] = {0};
  que[0] = start;
  int j = 0, k = 0;
  while(j < qlen){
    for(k = 1; k <= max_fen; k++){
      if(fen[que[j]][k]&&!ci[k]){
        que[qlen] = k;
        qlen++;
        ci[k] = 1;
      }
    }
    j++;
  }
  for(j = 1; j <= max_fen; j++)
    for(k = 1; k <= max_fen; k++)
    if(fen[j][k]&&!ci[j])
      return 0;
  for(i = 1; i <= max_fen; i++){
    if(fen[start][i]){
      fen[i][start]--;
      fen[start][i]--;
      degree[i]--;
      degree[start]--;
      if(Tf+1 == F) {result[Tf+1] = i; return 1;}
      else
      if(dfs(fen,degree,i,Tf+1,F,max_fen,result)){
        return 1;
      }else{
        fen[i][start]++;
        fen[start][i]++;
        degree[i]++;
        degree[start]++;
      }
    }
  }
  return 0;
}
int main(){
  FILE *fin = fopen("fence.in","r");
  FILE *fout = fopen("fence.out","w");
  int max_fen = 0;
  int F = 0;
  int fen[501][501]={0};
  int degree[501]={0};
  fscanf(fin,"%d",&F);
  int i = 0;
  for(i = 0; i < F; i++){
    int a = 0, b = 0;
    fscanf(fin,"%d%d", &a, &b);
    fen[a][b]++;
    fen[b][a]++;
    degree[a]++;
    degree[b]++;
    if(a > max_fen) max_fen = a;
    if(b > max_fen) max_fen = b;
  }
  int Tf = 0;
  int start = 1;
  for(i = 1; i <= max_fen; i++){
    if(degree[i]%2 == 1) {
      start = i;
      break;
    }
  }
  int result[1025] = {0};
  dfs(fen,degree,start,0,F,max_fen,result);
  for(i = 0; i <= F; i++) fprintf(fout, "%d\n", result[i]);
  return 0;
}

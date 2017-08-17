/*
ID: lic92031
LANG: C
TASK: spin
*/
#include<stdio.h>
int GetGCD(int a, int b){
  int c = 0;
  if(a == 0 || b == 0) return 0;
  else
  if(b > a){
    c = b;
    b = a;
    a = c;
  }
  while (a % b != 0){
    c = a % b;
    a = b;
    b = c;
  }
  return b;
}
int CheckThrough(int n, int a[5][2], int d){
  int i = 0, l = 0, r = 0;
  for (i = 0; i < n; i++){
    l = a[i][0];
    r = a[i][0] + a[i][1];
    if(( d >= l && d <= r)||(d+360 >= l && d+360 <= r)){
      return 1;
    }
  }
  return 0;
}
int main() {
  FILE *fin = fopen("spin.in","r");
  FILE *fout = fopen("spin.out","w");
  int speed[5] = {0};
  int W[5] = {0};
  int wedge[5][5][2]={0};
  int i = 0, j = 0, k = 0;
  int min_speed = 0;
  int t[5] = {0};
  int T = 0;
  int result = -1;
  for (i = 0; i < 5; i++){
    fscanf(fin,"%d",&speed[i]);
    fscanf(fin,"%d",&W[i]);
    for (j = 0; j < W[i]; j++){
      fscanf(fin,"%d%d",&wedge[i][j][0],&wedge[i][j][1]);
    }
  }
  min_speed = speed[0];
  for (i = 0; i < 5; i++) min_speed = min_speed > speed[i]? speed[i] : min_speed;
  for (i = 0; i < 5; i++) speed[i] -= min_speed;
  for (i = 0; i < 5; i++){
    if(speed[i]) t[i] = 360/GetGCD(360,speed[i]);
  }
  for (i = 0; i < 5; i++){
    if(T == 0 && t[i]) T = t[i];
    else
    if(t[i]) T = T/GetGCD(T,t[i])*t[i];
  }
  for (i = 0; i < T; i++){
    for (j = 0; j < 360; j++){
      for(k = 0; k < 5; k++){
        if(!CheckThrough(W[k],wedge[k],j)) break;
        else
        if(k == 4) result = i;
      }
    }
    for (j = 0; j < 5; j++){
      for (k = 0; k < W[j]; k++) wedge[j][k][0] = (wedge[j][k][0] + speed[j]) % 360;
    }
    if (result != -1) break;
  }
  if(result == -1) fprintf(fout,"none\n");
  else fprintf(fout,"%d\n",result);
  fclose(fin);
  fclose(fout);
  return 0;
}

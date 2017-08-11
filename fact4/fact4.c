/*
ID: lic92031
LANG: C
TASK: fact4
*/
#include<stdio.h>
int main(){
  FILE *fin = fopen("fact4.in","r");
  FILE *fout = fopen("fact4.out","w");
  int N;
  int rm[4221]={0};
  int i, j, min, num, num1;
  int result;
  fscanf(fin,"%d",&N);
  for(i = 1; i <= N; i++){
    rm[i] = i;
  }
  min = 1;
  num = 0;
  while(min <= N){
    if(rm[min]%2 == 0 || rm[min]%5 == 0){
      if(rm[min] % 2 == 0) {
        num = 5;
        num1 = 2;
      }else {
        num = 2;
        num1 = 5;
      }
      for(j = min; j <= N; j++){
        if(rm[j] % num == 0){
          rm[j] = rm[j] / num;
          rm[min] = rm[min] / num1;
          break;
        }
      }
      if(j > N) min++;
    }else{
      min++;
    }
  }
  result = 1;
  for(i = 1; i <= N; i++) result = (result * rm[i])%10;
  fprintf(fout,"%d\n",result);
  fclose(fin);
  fclose(fout);
  return 0;
}

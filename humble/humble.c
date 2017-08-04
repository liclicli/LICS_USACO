/*
ID: lic92031
LANG: C
TASK: humble
*/
#include<stdio.h>
void test(int *list,int n){
  int i = 0;
  for(i = 0; i < n; i++){
    printf("%d\t",list[i]);
  }
  printf("\nover\n");
}
int main(){
  FILE *fin = fopen("humble.in","r");
  FILE *fout = fopen("humble.out","w");
  int K,N;
  int ori[100]={0};
  int pos[100]={0};
  int num_n = 0;
  int list[100000]={0};
  int lp = 0, rp = 0, pp = 1;
  int i,j,k,tmp,min,min_l,min_r;
  int flag_over = 0;
  fscanf(fin,"%d%d",&K,&N);
  for(i = 0; i < K; i++) fscanf(fin,"%d",&ori[i]);
  for(i = 0; i < K-1; i++)
    for(j = i+1; j < K; j++){
      if(ori[i] > ori[j]){
        tmp = ori[i];
        ori[i] = ori[j];
        ori[j] = tmp;
      }
    }
  num_n = 1;
  list[0] = ori[0];
  if(K == 1) flag_over = 1;
  while(num_n < N){
    if(ori[lp]*list[rp] < ori[pp] || flag_over > 0){
      list[num_n] = ori[lp]*list[rp];
      min = ori[lp]*list[rp+1];
      min_l = lp;
      min_r = rp+1;
      for(i = 0; i < K; i++){
        while(ori[i]*list[pos[i]] <= list[num_n]) pos[i]++;
        if(ori[i]*list[pos[i]] < min){
          min = ori[i]*list[pos[i]];
          min_l = i;
          min_r = pos[i];
        }
      }
      lp = min_l;
      rp = min_r;
    }else{
      list[num_n] = ori[pp];
      if(pp < K-1) pp++; else flag_over = 1;
    }
    num_n++;
  }
  //test(list,num_n);
  fprintf(fout,"%d\n",list[num_n-1]);
  fclose(fin);
  fclose(fout);
}

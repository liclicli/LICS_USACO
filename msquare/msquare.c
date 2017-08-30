/*
ID: lic92031
LANG: C
TASK: msquare
*/
#include<stdio.h>
#define MAX_CANTOR_NUM 40320
typedef struct {
  int IsReach;
  int last;
  char Way;
} BFSCheck;
int CantorExtend(int a[8]){
  int i = 0, j = 0, k = 0;
  int result = 0, val = 0;
  int tmp[8] = {1,2,3,4,5,6,7,8};
  for(i = 0; i < 8; i ++){
    for(j = i; j < 8; j++){
      if(a[i] == tmp[j]){
        val = j - i;
        k = tmp[i];
        tmp[i] = tmp[j];
        tmp[j] = k;
        break;
      }
    }
    for(j = 0; j <i; j++){
      val *= (8 - j);
    }
    result += val;
  }
  return result;
}
void CantorCovert(int seq, int a[8]){
  int i = 0, j = 0, k = 0;
  for(i = 0; i < 8; i++) a[i] = i+1;
  for(i = 0; i < 8; i++){
    j = seq % (8-i);
    k = a[i];
    a[i] = a[i+j];
    a[i+j] = k;
    seq /=(8-i);
  }
}
void A(int r[8], int a[8]){
  r[0] = a[7];
  r[1] = a[6];
  r[2] = a[5];
  r[3] = a[4];
  r[4] = a[3];
  r[5] = a[2];
  r[6] = a[1];
  r[7] = a[0];
}
void B(int r[8], int a[8]){
  r[0] = a[3];
  r[1] = a[0];
  r[2] = a[1];
  r[3] = a[2];
  r[4] = a[5];
  r[5] = a[6];
  r[6] = a[7];
  r[7] = a[4];
}
void C(int r[8], int a[8]){
  r[0] = a[0];
  r[1] = a[6];
  r[2] = a[1];
  r[3] = a[3];
  r[4] = a[4];
  r[5] = a[2];
  r[6] = a[5];
  r[7] = a[7];
}
void CopyArr(int a[8], int b[8]){
  int i = 0;
  for(i = 0; i < 8; i++) a[i] = b[i];
}
void Search(FILE *fout, int init[8], int target[8]){
  int start[8] = {0};
  int tmp[8] = {0};
  int target_num = CantorExtend(target);
  BFSCheck list[MAX_CANTOR_NUM] = {0};
  char res_str[MAX_CANTOR_NUM] = {0};
  int que[MAX_CANTOR_NUM] = {0};
  int len = 0;
  int np = 0;
  int i = 0;
  if(target_num == CantorExtend(init)){
    fprintf(fout,"0\n\n");
    return ;
  }
  list[CantorExtend(init)].IsReach = 1;
  list[CantorExtend(init)].Way = '\0';
  len ++;
  que[np] = CantorExtend(init);
  do{
    CantorCovert(que[np],start);
    A(tmp,start);
    que[len] = CantorExtend(tmp);
    if(!list[que[len]].IsReach) {
      list[que[len]].IsReach = 1;
      list[que[len]].last = np;
      list[que[len]].Way = 'A';
      if(target_num == que[len]) break;
      len++;
    }
    B(tmp,start);
    que[len] = CantorExtend(tmp);
    if(!list[que[len]].IsReach) {
      list[que[len]].IsReach = 1;
      list[que[len]].last = np;
      list[que[len]].Way = 'B';
      if(target_num == que[len]) break;
      len++;
    }
    C(tmp,start);
    que[len] = CantorExtend(tmp);
    if(!list[que[len]].IsReach) {
      list[que[len]].IsReach = 1;
      list[que[len]].last = np;
      list[que[len]].Way = 'C';
      if(target_num == que[len]) break;
      len++;
    }
    np++;
  }while(1);
  do{
    res_str[i] = list[que[len]].Way;
    i++;
    len = list[que[len]].last;
  }while(len != 0);
  fprintf(fout,"%d\n",i);
  do{
    i--;
    fprintf(fout,"%c",res_str[i]);
  }while(i > 0);
  fprintf(fout,"\n");
}
int main (){
  FILE *fin = fopen("msquare.in","r");
  FILE *fout = fopen("msquare.out","w");
  int s_num[8] = {0};
  int init_num[8] = {1,2,3,4,5,6,7,8};
  int i = 0;
  for (i = 0; i < 8; i++){
    fscanf(fin,"%d",&s_num[i]);
  }
  Search(fout,init_num,s_num);
  fclose(fin);
  fclose(fout);
  return 0;
}

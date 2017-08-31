/*
ID: lic92031
LANG: C
TASK: butter
*/
#include<stdio.h>
#include<stdlib.h>
#define MAX_PATH_LEN 450000
struct AdjacencyList{
  int p;
  int len;
  struct AdjacencyList *next;
};
typedef struct{
  struct AdjacencyList *head;
  struct AdjacencyList *tail;
} LInfo;
void AddPath(LInfo *m, int p, int len){
  if(m->tail == NULL){
    m->head = m->tail = malloc(sizeof(struct AdjacencyList));
    m->head->p = p;
    m->head->len = len;
    m->head->next = NULL;
  }else{
    m->tail->next = malloc(sizeof(struct AdjacencyList));
    m->tail = m->tail->next;
    m->tail->p = p;
    m->tail->len = len;
    m->tail->next = NULL;
  }
}
void DelBinTop(int *bin_val, int *bin_pnt, int *bin_len){
  int top = 0;
  int tmp = 0;
  int min = 0;
  tmp = bin_val[top];
  bin_val[top] = bin_val[*bin_len-1];
  bin_val[*bin_len-1] = tmp;
  tmp = bin_pnt[top];
  bin_pnt[top] = bin_pnt[*bin_len-1];
  bin_pnt[*bin_len-1] = tmp;
  (*bin_len)--;
  while(top < *bin_len){
    min = top;
    if(top*2+1 < *bin_len && bin_val[min] > bin_val[top*2+1]) min = top*2+1;
    if(top*2+2 < *bin_len && bin_val[min] > bin_val[top*2+2]) min = top*2+2;
    if(min == top) break;
    tmp = bin_val[top];
    bin_val[top] = bin_val[min];
    bin_val[min] = tmp;
    tmp = bin_pnt[top];
    bin_pnt[top] = bin_pnt[min];
    bin_pnt[min] = tmp;
    top = min;
  }
}
void InsBinNode(int *bin_val, int *bin_pnt, int *bin_len, int val, int pt){
  int bottom = *bin_len;
  int tmp = 0;
  (*bin_len)++;
  bin_val[bottom] = val;
  bin_pnt[bottom] = pt;
  while(bottom > 0){
    if(bin_val[bottom] < bin_val[(bottom-1)/2]){
      tmp = bin_val[bottom];
      bin_val[bottom] = bin_val[(bottom-1)/2];
      bin_val[(bottom-1)/2] = tmp;
      tmp = bin_pnt[bottom];
      bin_pnt[bottom] = bin_pnt[(bottom-1)/2];
      bin_pnt[(bottom-1)/2] = tmp;
      bottom = (bottom-1)/2;
    }else
      break;
  }
}
int f[801][801] = {0};
int bin_val[640000] = {0};
int bin_pnt[640000] = {0};
int Solve(LInfo map[801], int cow[501], int N, int P){
  int bin_len = 0;
  int min_total = MAX_PATH_LEN * N;
  int total = 0;
  struct AdjacencyList *al = NULL;
  int start = 0;
  int i = 0, j = 0, k = 0;
  for(i = 0; i <= P; i++)
    for(j = 0; j <= P; j++) f[i][j] = MAX_PATH_LEN;
  for(i = 1; i <= P; i++){
    bin_val[0] = 0;
    bin_pnt[0] = i;
    bin_len = 1;
    f[i][i] = 0;
    do{
      if(f[i][bin_pnt[0]] < bin_val[0]){
        DelBinTop(bin_val,bin_pnt,&bin_len);
      }else{
        if(f[i][bin_pnt[0]] > bin_val[0]) f[i][bin_pnt[0]] = bin_val[0];
        start = bin_pnt[0];
        DelBinTop(bin_val,bin_pnt,&bin_len);
        al = map[start].head;
        while(al != NULL){
          if(f[i][start] + al->len < f[i][al->p])
            InsBinNode(bin_val,bin_pnt,&bin_len,f[i][start] + al->len,al->p);
          al = al->next;
        }
      }
    }while(bin_len > 0);
    total = 0;
    for(j = 0; j < N; j++) total += f[i][cow[j]];
    if(total < min_total) min_total = total;
  }
  return min_total;
}
int main(){
  FILE *fin = fopen("butter.in","r");
  FILE *fout = fopen("butter.out","w");
  int N = 0, P = 0, C = 0;
  LInfo map[801] = {0};
  int cow[501] = {0};
  int i = 0;
  fscanf(fin,"%d%d%d", &N, &P, &C);
  for(i = 0; i < N; i++) fscanf(fin,"%d", &cow[i]);
  for(i = 0; i < C; i++){
    int tmp0 = 0, tmp1 = 0, tmp2 = 0;
    fscanf(fin,"%d%d%d", &tmp0, &tmp1, &tmp2);
    AddPath(&map[tmp0], tmp1, tmp2);
    AddPath(&map[tmp1], tmp0, tmp2);
  }
  fprintf(fout,"%d\n",Solve(map, cow, N, P));
  fclose(fin);
  fclose(fout);
  return 0;
}

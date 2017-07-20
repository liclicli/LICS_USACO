/*
ID: lic92031
LANG: C
TASK: arginet.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
  int n;
  int *Mat;
} InputData;
typedef int OutputData;
int *GetPos(InputData *data, int r, int c){
  return &(data->Mat[r*data->n+c]);
}
void ReadIn(FILE *f, InputData *data){
  int i = 0, j = 0;
  fscanf(f,"%d",&data->n);
  data->Mat = malloc(data->n*data->n*sizeof(int));
  for (i = 0; i < data->n; i++)
    for (j = 0; j < data->n; j++){
      fscanf(f,"%d",GetPos(data,i,j));
    }
}
typedef struct{
  int tlen;
  int len;
  void **list;
} binHeap;
typedef struct{
  int dist;
  int lpoint;
  int rpoint;
} binNode;
int CmpBinNode(binNode* a, binNode *b){
  if(a->dist > b->dist) return 1;
  else return 0;
}
binNode *CreateBinNode(int dist, int lp, int rp){
  binNode *a = malloc(binNode);
  a->dist = dist;
  a->lpoint = lp;
  a->rpoint = rp;
  return a;
}
void BuildEmptyBinHeap(binHeap *h, int len){
  h->tlen = len;
  h->len = 0;
  h->list = malloc(len * sizeof(binNode *));
}
void UpMaintainBinHeap(binHeap *h, int pos){
  void *tmp = NULL;
  if(CmpBinNode((binNode *)(h->list[pos/2]),(binNode *)(h->list[pos]))){
    tmp = h->list[pos/2];
    h->list[pos/2] = h->list[pos];
    h->list[pos] = tmp;
    UpMaintainBinHeap(h,pos/2);
  }
}
void InsBinHeap(binHeap *h, binNode *node){
  h->list[len] = node;
  UpMaintainBinHeap(h,len);
  h->len++;
}
binNode *GetBinHeapTop(binHeap *h){
  return (binNode *)(h->list[0]);
}
void DownMaintainBinHeap(binHeap *h, int pos){
  int min_pos = 0;
  void *tmp = NULL;
  if(pos*2+1 < h->len){
    min_pos = pos*2+1;
    if(pos*2+2 < h->len){
      if(CmpBinNode((binNode *)(h->list[pos*2+1]),(binNode *)(h->list[pos*2+2])){
        min_pos = pos*2+2;
      }else{
        min_pos = pos*2+1;
      }
    }
    if(CmpBinNode((binNode *)(h->list[pos]),(binNode *)(h->list[min_pos]))){
      tmp = h->list[pos];
      h->list[pos] = h->list[min_pos];
      h->list[min_pos]  = tmp;
      DownMaintainBinHeap(h,min_pos);
    }
  }
}
void RemoveBinHeapTop(binHeap *h){
  void *tmp = NULL;
  tmp = h->list[h->len-1];
  h->list[h->len-1] = h->list[0];
  h->list[0] = tmp;
  h->len--;
  DownMaintainBinHeap(h,0);
}
void ClearBinHeap(binHeap *h){
  int i = 0;
  for (i = 0; i < h->tlen; i++) free((binNode *)(h->list[i]));
  free(h->list);
}
void ResolveProblem(InputData *inputdata, OutputData *outputdata){
  binHeap pathT;
  int *link_tree;
  int link_num = 0;
  int i = 0, j = 0;
  int max_tree = 0;
  binNode *tmp_binnode = NULL;
  link_tree = malloc(inputdata->n*sizeof(int));
  memset(link_tree,0,inputdata->n*sizeof(int));
  BuildEmptyBinHeap(&pathT,inputdata->n);
  for(i = 0; i < inputdata->n; i++)
    for (j = 0; j < i; j++){
      InsBinHeap(&pathT,CreateBinNode(*GetPos(inputdata,j,i), j,i))
    }
  while(link_num < inputdata->n - 1)
  {
    tmp_binnode = GetBinHeapTop(&pathT);
    if(tmp_binnode->lpoint == 0 && tmp_binnode->rpoint == 0){

    }else if(tmp_binnode->lpoint == 0){

    }else if(tmp_binnode->rpoint == 0)
  }
  GetBinHeapTop->dist,lpoint,rpoint;
}
void WriteOut(FILE *f, OutputData *data){

}

int main(){
  FILE *fin=fopen("arginet.in","r");
  FILE *fout=fopen("arginet.out","w");
  InputData inputdata;
  OutputData outputdata;
  ReadIn(fin,&inputdata);
  ResolveProblem(&inputdata,&outputdata);
  WriteOut(fout,&outputdata);
  fclose(fin);
  fclose(fout);
  return 0;
}

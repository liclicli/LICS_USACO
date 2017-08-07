/*
ID: lic92031
LANG: C
TASK: contact
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct{
  int rt;
  int len;
  int val;
} NodeData;
struct TreeNode{
  struct TreeNode *lc;
  struct TreeNode *rc;
  NodeData data;
  int deep;
};
typedef struct TreeNode BinTree;
void convertValtoStr(char *str, int len, int val){
  int i = 0;
  for(i = 0; i < len; i++) str[i]='0';
  i = len-1;
  while(val > 0){
    if(val & 1) str[i]='1';
    val = val >> 1;
    i--;
  }
}
int getStrVal(char *str, int len){
  int i = 0;
  int res = 0;
  for(i = 0; i < len; i++){
    if(str[i] == '1') res++;
    res = res << 1;
  }
  return res >> 1;
}
int cmpVal(NodeData *a, NodeData *b){
  if(a->len < b->len) return 1;
  if(a->len > b->len) return -1;
  if(a->val < b->val) return 1;
  if(a->val > b->val) return -1;
  return 0;
}
int cmpRT(NodeData *a, NodeData *b){
  if(a->rt > b->rt) return 1;
  if(a->rt < b->rt) return -1;
  if(a->len < b->len) return 1;
  if(a->len > b->len) return -1;
  if(a->val < b->val) return 1;
  if(a->val > b->val) return -1;
  return 0;
}
void initNode(BinTree *t){
  t->lc = NULL;
  t->rc = NULL;
  t->data.rt = 0;
  t->data.len = 0;
  t->data.val = 0;
  t->deep = 0;
}
void insertTree(BinTree *t, int len, int val){
  NodeData data;
  int cmpres = 0;
  if(t->data.len == 0){
    t->data.rt = 1;
    t->data.len = len;
    t->data.val = val;
    return;
  }
  data.len = len;
  data.val = val;
  cmpres = cmpVal(&(t->data),&data);
  if(cmpres == 0){
    t->data.rt++;
  }else
  if(cmpres >0){
    if(t->lc == NULL){
      t->lc = malloc(sizeof(BinTree));
      initNode(t->lc);
    }
    insertTree(t->lc,len,val);
    t->deep = (t->lc->deep + 1)>t->deep?t->lc->deep + 1:t->deep;
  }else
  if(cmpres <0){
    if(t->rc == NULL){
      t->rc = malloc(sizeof(BinTree));
      initNode(t->rc);
    }
    insertTree(t->rc,len,val);
    t->deep = (t->rc->deep + 1)>t->deep?t->rc->deep + 1:t->deep;
  }
}
void insertRTTree(BinTree *t,BinTree *rtt){
  int cmpres;
  if(rtt->data.len == 0){
    rtt->data.len = t->data.len;
    rtt->data.rt = t->data.rt;
    rtt->data.val = t->data.val;
    return ;
  }
  cmpres = cmpRT(&(rtt->data),&(t->data));
  if(cmpres < 0){
    if(rtt->lc == NULL){
      rtt->lc = malloc(sizeof(BinTree));
      initNode(rtt->lc);
    }
    insertRTTree(t,rtt->lc);
    rtt->deep = (rtt->lc->deep + 1)>rtt->deep?rtt->lc->deep + 1:rtt->deep;
  }else
  if(cmpres > 0){
    if(rtt->rc == NULL){
      rtt->rc = malloc(sizeof(BinTree));
      initNode(rtt->rc);
    }
    insertRTTree(t,rtt->rc);
    rtt->deep = (rtt->rc->deep + 1)>rtt->deep?rtt->rc->deep + 1:rtt->deep;
  }
}
void traTree(BinTree *t,BinTree *rtt){
  if(t->lc != NULL) traTree(t->lc,rtt);
  insertRTTree(t,rtt);
  if(t->rc != NULL) traTree(t->rc,rtt);
  free(t);
}
int N = 0;
int traRTTree(FILE *fout,BinTree *t){
  static int frec = 0;
  static int line_num = 0;
  static int no_el = 0;
  char str[13]={0};
  convertValtoStr(str,t->data.len,t->data.val);
  if(t->lc != NULL) traRTTree(fout,t->lc);
  if(frec == t->data.rt){
    fprintf(fout," %s",str);
    line_num++;
    if(line_num % 6 == 0) {
      fprintf(fout,"\n");
      no_el = 0;
    }
    else no_el = 1;
  }else{
    if(N) N--;
    else{
      if(no_el) fprintf(fout,"\n");
      no_el = 0;
      return no_el;
    }
    if(frec != 0 && line_num % 6 != 0) fprintf(fout,"\n");
    frec = t->data.rt;
    line_num = 1;
    fprintf(fout,"%d\n",frec);
    fprintf(fout,"%s",str);
    no_el = 1;
  }
  if(t->rc != NULL) traRTTree(fout,t->rc);
  free(t);
  return no_el;
}
int main() {
  FILE *fin = fopen("contact.in","r");
  FILE *fout = fopen("contact.out","w");
  int A,B;
  char ori[200001]={0};
  int i,j;
  BinTree *root = NULL, *rtroot = NULL;
  fscanf(fin,"%d%d%d",&A,&B,&N);
  while (!feof(fin)){
    i = strlen(ori);
    fscanf(fin,"%s",&ori[i]);
  }
  root = malloc(sizeof(BinTree));
  initNode(root);
  for(i = 0; i < strlen(ori); i++){
    for(j = A; j <= B; j++){
      if(i+j <= strlen(ori)) insertTree(root,j,getStrVal(&ori[i],j));
    }
  }
  rtroot = malloc(sizeof(BinTree));
  initNode(rtroot);
  traTree(root,rtroot);
  if(traRTTree(fout,rtroot)) fprintf(fout,"\n");
  fclose(fin);
  fclose(fout);
  return 0;
}

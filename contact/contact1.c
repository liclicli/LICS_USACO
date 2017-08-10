/*
ID: lic92031
LANG: C
TASK: contact
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct dicTree{
  struct dicTree *zc;
  struct dicTree *nzc;
  int frec;
  int len;
  int match;
};
typedef struct dicTree TreeNode;
typedef struct dequeList Dlist;
typedef struct dequeListInfo Dinfo;
struct dequeList{
  struct dequeList *fl;
  struct dequeList *bl;
  Dinfo *info;
  TreeNode *data;
};
struct dequeListInfo{
  int len;
  Dlist *head;
  Dlist *tail;
};
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
void initTreeNode(TreeNode *t){
  t->zc = NULL;
  t->nzc = NULL;
  t->frec = 0;
  //memset(t->match,0,13*sizeof(char));
  t->len = 0;
  t->match = 0;
}
void initDlist(Dlist *l,Dinfo *info){
  l->fl = NULL;
  l->bl = NULL;
  l->data = NULL;
  l->info = info;
}
void initDinfo(Dinfo *info){
  info->len = 0;
  info->head = NULL;
  info->tail = NULL;
}
void insertDlist(Dinfo *info, TreeNode *t){
  if(info->len == 0){
    info->head = malloc(sizeof(Dlist));
    initDlist(info->head,info);
    info->tail = info->head;
  }else{
    info->tail->bl = malloc(sizeof(Dlist));
    initDlist(info->tail->bl,info);
    info->tail->bl->fl = info->tail;
    info->tail = info->tail->bl;
  }
  info->tail->info = info;
  info->tail->data = t;
  info->len++;
}
void delDlist(Dlist *l){
  Dinfo *info = l->info;
  if(info->len == 1){
    free(l);
    initDinfo(info);
  }else{
    if(l->fl == NULL){
      info->head = l->bl;
      info->head->fl = NULL;
      free(l);
    }else
    if(l->bl == NULL){
      info->tail = l->fl;
      info->tail->bl = NULL;
      free(l);
    }else{
      l->fl->bl = l->bl;
      l->bl->fl = l->fl;
      free(l);
    }
  }
  info->len--;
}
void clearDinfo(Dinfo *info){
  while(info->len > 0){
    delDlist(info->head);
  }
  free(info);
}
void buildDicTree(char *ori, TreeNode* root, int A, int B){
  int i,j;
  int total_len = 0;
  int len = 0;
  TreeNode *now;
  total_len = strlen(ori);
  for(i = 0; i < total_len; i++){
    //printf("%d\n",i);
    now = root;
    for(j = 0; j < B; j++){
      if(i+j>=total_len) break;
      if(ori[i+j]=='0'){
        if(now->zc == NULL){
          now->zc = malloc(sizeof(TreeNode));
          initTreeNode(now->zc);
          now->zc->match = now->match << 1;
          now->zc->len = now->len + 1;
        }
        now->zc->frec++;
        now = now->zc;
      }else{
        if(now->nzc == NULL){
          now->nzc = malloc(sizeof(TreeNode));
          initTreeNode(now->nzc);
          now->nzc->match = (now->match << 1) | 1;
          now->nzc->len = now->len + 1;
        }
        now->nzc->frec++;
        now = now->nzc;
      }
    }
  }
}
void improveBFS(FILE *fout, TreeNode* root, int A, int B, int N){
  Dinfo *info = malloc(sizeof(Dinfo));
  Dlist *now = NULL;
  Dlist *tmp = NULL;
  int tmp_max = 0;
  int line_num = 0;
  int is_first_line = 1;
  char tmp_str[13] = {0};
  initDinfo(info);
  insertDlist(info,root);
  now = info->head;
  do{
    if(now != NULL){
      if(now->data->zc != NULL) insertDlist(info,now->data->zc);
      if(now->data->nzc != NULL) insertDlist(info,now->data->nzc);
      tmp = now->bl;
      if(now->data->len < A) delDlist(now);
      now = tmp;
    }else{
      now = now->bl;
    }
  }while(now != NULL);
  //printf("fin build dq\n");
  do{
    now = info->head;
    if(now == NULL) break;
    tmp_max = 0;
    do{
      if(tmp_max < now->data->frec) tmp_max = now->data->frec;
      now = now->bl;
    }while(now != NULL);
    now = info->head;
    if(is_first_line){
      is_first_line = 0;
    }else{
      if(line_num % 6 != 0)fprintf(fout,"\n");
    }
    fprintf(fout,"%d\n",tmp_max);
    line_num = 0;
    do{
      if(tmp_max == now->data->frec){
        line_num++;
        if(line_num % 6 != 1) fprintf(fout," ");
        memset(tmp_str,0,13*sizeof(char));
        convertValtoStr(tmp_str,now->data->len,now->data->match);
        fprintf(fout,"%s",tmp_str);
        if(line_num % 6 == 0) fprintf(fout,"\n");
        tmp = now->bl;
        delDlist(now);
        now = tmp;
      }else{
        now = now->bl;
      }
    }while(now != NULL);
    N--;
  }while(N > 0 && info->len != 0);
  if(line_num % 6 != 0) fprintf(fout,"\n");
  clearDinfo(info);
}
int main() {
  FILE *fin = fopen("contact.in","r");
  FILE *fout = fopen("contact.out","w");
  int A,B,N;
  char ori[200001]={0};
  int i,j;
  TreeNode *root = malloc(sizeof(TreeNode));
  fscanf(fin,"%d%d%d",&A,&B,&N);
  while (!feof(fin)){
    i = strlen(ori);
    fscanf(fin,"%s",&ori[i]);
  }
  initTreeNode(root);
  buildDicTree(ori,root,A,B);
  //testTree(root);
  //printf("built Root.\n");
  improveBFS(fout,root,A,B,N);
  //printf("finish Root.\n");
  fclose(fin);
  fclose(fout);
  return 0;
}

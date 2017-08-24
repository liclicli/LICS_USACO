/*
ID: lic92031
LANG: C
TASK: ratios
*/
#include<stdio.h>
typedef struct rationalNum{
  int num;
  int den;
} RNum;
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
void RNSimplify(RNum *a){
  if(a->den < 0){
    a->den = -a->den;
    a->num = -a->num;
  }
  if(a->num == 0) { a->den = 1; return ;}
  int tmp = a->num>0?a->num:-a->num;
  int gcd = GetGCD(tmp,a->den);
  a->num = a->num / gcd;
  a->den = a->den / gcd;
}
RNum Add(RNum a, RNum b){
  RNum r;
  r.num = a.num*b.den + a.den*b.num;
  r.den = a.den*b.den;
  RNSimplify(&r);
  return r;
}
RNum Minus(RNum a, RNum b){
  RNum r;
  r.num = a.num*b.den - a.den*b.num;
  r.den = a.den*b.den;
  RNSimplify(&r);
  return r;
}
RNum Multi(RNum a, RNum b){
  RNum r;
  r.num = a.num * b.num;
  r.den = a.den * b.den;
  RNSimplify(&r);
  return r;
}
RNum Divide(RNum a, RNum b){
  RNum r;
  r.num = a.num *b.den;
  r.den = a.den *b.num;
  RNSimplify(&r);
  return r;
}
RNum G(int a){
  RNum r;
  r.num = a;
  r.den = 1;
  return r;
}
int RNeq(RNum a, int b){
  if(a.den == 1 && a.num == b) return 1;
  return 0;
}
void SwapRow(RNum A[3][4],int a, int b){
  int i = 0;
  RNum tmp;
  for( i = 0; i < 4; i++){
    tmp = A[a][i];
    A[a][i] = A[b][i];
    A[b][i] = tmp;
  }
}
void Uptri(RNum A[3][4]){
  int i = 0, j = 0, k = 0;
  int sc = 0;
  int flag = 0;
  RNum tmp;
  for(i = 0; i < 2; i++){
    do{
      flag = 0;
      for(j = i; j < 3; j++)
        if(!RNeq(A[j][sc],0)){
          flag = 1;
          break;
        }
      if(flag && j != i) {
        SwapRow(A,i,j);
        break;
      }else
      if (flag){
        break;
      }
      else
      if(!flag) sc++;
    }while(sc < 3);
    if(RNeq(A[i][sc],0)) break;
    for(j = i + 1; j < 3; j++){
      tmp = Divide(A[j][sc],A[i][sc]);
      for(k = sc; k < 4; k++){
        A[j][k] = Minus(A[j][k],Multi(tmp,A[i][k]));
      }
    }
  }
}
int GetMinNum(RNum *X){
  int i = 0, j = 0;
  int den = 0;
  RNum tmp[4];
  for(i = 0; i < 4; i++) tmp[i] = X[i];
  for(i = 0; i < 4; i++){
    den = tmp[i].den;
    for(j = 0; j < 4; j++){
      tmp[j] = Multi(G(den),tmp[j]);
    }
  }
  return tmp[0].num+tmp[1].num+tmp[2].num;
}
void Record(RNum R[4],RNum X[4]){
  int i = 0;
  for(i = 0; i < 4; i++) R[i] = X[i];
}
void GetIntAns(RNum R[4]){
  int i = 0, j = 0;
  for(i = 0; i < 4; i++){
    int den = R[i].den;
    for(j = 0; j < 4; j++) R[j] = Multi(G(den),R[j]);
  }
}
void Solve(FILE *fout, RNum A[3][4]){
  RNum R[4];
  RNum X[4];
  int IsGetAns = 0;
  int comfirm[3]={0};
  int i = 0, j = 0, k = 0;
  int snd[3]={0};
  int nd = 0;
  int tmp_i = 0;
  RNum tmp_rn;
  X[3].num = -1;
  X[3].den = 1;
  i = 2;
  for(j = 0; j < 3; j++) X[j] = G(0);
  do{
    nd = 0;
    for(j = 0; j < 3; j++)
      if(!RNeq(A[i][j],0)&& comfirm[j]<=i+1){
        nd++;
        X[j] = G(0);
        comfirm[j] = 0;
      }
    if(!RNeq(A[i][3],0) && nd == 0){
      fprintf(fout,"NONE\n");
      return;
    }else{
      if(nd == 0){
        if(snd[i] > 0) break;
        snd[i]++;
        i--;
      }else
      if(snd[i] < nd){
        tmp_i = 0;
        tmp_rn = Minus(G(0),Multi(A[i][3],X[3]));
        for(j = 0; j < 3; j++){
          if(!RNeq(A[i][j],0)&&!comfirm[j]) {
            comfirm[j] = i+1;
          }
          if(comfirm[j]!=i+1 || tmp_i != snd[i]) tmp_rn = Minus(tmp_rn,Multi(A[i][j],X[j]));
          if(comfirm[j]==i+1) {
            tmp_i++;
          }
        }
        tmp_i = 0;
        for(j = 0; j < 3; j++){
          if(comfirm[j] == i+1){
            if(tmp_i == snd[i]){
              X[j] = Divide(tmp_rn,A[i][j]);
            }
            tmp_i++;
          }
        }
        snd[i]++;
        if(i == 0){
          tmp_i = 0;
          for(j = 0; j < 3; j++) if(X[j].num < 0) tmp_i = 1;
          if(!tmp_i){
            if(IsGetAns){
              if(GetMinNum(X)<GetMinNum(R)) Record(R,X);
            }else{
              Record(R,X);
              IsGetAns = 1;
            }
          }
        }
        else
          i--;
      }else{
        if(i < 2){
          i++;
        }else
          break;
      }
    }
  }while(1);
  if(IsGetAns){
    GetIntAns(R);
    for(j = 0; j < 3; j++) fprintf(fout,"%d ", R[j].num);
    fprintf(fout,"%d\n",-R[3].num);
  }else{
    fprintf(fout, "NONE\n");
  }
}
int main() {
  FILE *fin = fopen("ratios.in","r");
  FILE *fout = fopen("ratios.out","w");
  RNum A[3][4];
  int i,j;
  for(i = 0; i < 4; i++)
    for(j = 0; j < 3; j++)
    if(i==0){
      fscanf(fin,"%d",&(A[j][3].num));
      A[j][3].den = 1;
    }else{
      fscanf(fin,"%d",&(A[j][i-1].num));
      A[j][i-1].den = 1;
    }
  Uptri(A);
  Solve(fout,A);
  fclose(fin);
  fclose(fout);
  return 0;
}

#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 100010
#define inf 0x7fffffff

template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

int A[MAXN],B[MAXN*100],C[MAXN*100];
int cntA=1,cntB=1,cntC=1;
int topB,topC;

bool cmp(int a,int b) {
    return a>b;
}

int main() {
    int n,m,q,u,v,t;
    input(n),input(m),input(q),
    input(u),input(v),input(t);
    double p=double(u)/double(v);
    for(int i=1;i<=n;i++)
        input(A[i]);
    sort(A+1,A+n+1,cmp);
    for(int i=1;i<=m;i++) {
        
        int nowA=A[cntA]+(i-1)*q;
        int nowB=B[cntB]+(i-cntB)*q;
        int nowC=C[cntC]+(i-cntC)*q;
        
        if(cntA>n) nowA=-inf;
        if(cntB>topB) nowB=-inf;
        if(cntC>topC) nowC=-inf;
        
        int cut=nowA,cutpos=1;
        if(cut<nowB) cut=nowB,cutpos=2;
        if(cut<nowC) cut=nowC,cutpos=3;
        
        if(cutpos==1) cntA++;
        else if(cutpos==2) cntB++;
        else cntC++;
        
        if(i%t==0) printf("%d ",cut);
        
        int Short=(double)p*cut;
        B[++topB]=Short-q;
        C[++topC]=cut-Short-q;
    }
    printf("\n");
    for(int i=1;i<=n+m;i++) {
        
        int nowA=A[cntA]+m*q;
        int nowB=B[cntB]+(m-cntB+1)*q;
        int nowC=C[cntC]+(m-cntC+1)*q;
        
        if(cntA>n) nowA=-inf;
        if(cntB>topB) nowB=-inf;
        if(cntC>topC) nowC=-inf;
        
        int len=nowA,lenpos=1;
        if(len<nowB) len=nowB,lenpos=2;
        if(len<nowC) len=nowC,lenpos=3;
        
        if(lenpos==1) cntA++;
        else if(lenpos==2) cntB++;
        else cntC++;
        
        if(i%t==0) printf("%d ",len);
    }
    return 0;
}
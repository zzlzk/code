#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXNA 210
#define MAXNB 210
#define MAXN 210

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

const int win[10][10]={{ 0,-1, 1, 1,-1},
                          { 1, 0,-1, 1,-1},
                          {-1, 1, 0,-1, 1},
                       {-1,-1, 1, 0, 1},
                       { 1, 1,-1,-1, 0},};
int A[MAXNA],B[MAXNB];
int main() {
    int N,NA,NB;
    input(N),input(NA),input(NB);
    for(int i=1;i<=NA;i++)
        input(A[i]);
    for(int i=1;i<=NB;i++)
        input(B[i]);
    int sumA=0,sumB=0;
    for(int i=1,x=1,y=1;i<=N;i++) {
        int Outcome=win[A[x]][B[y]];
        if(Outcome==1) sumA++;
        else if(Outcome==-1) sumB++;
        x++;
        if(x==NA+1) x=1;
        y++;
        if(y==NB+1) y=1;
    }
    printf("%d %d",sumA,sumB);
    return 0;
}

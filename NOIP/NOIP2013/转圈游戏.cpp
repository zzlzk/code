#include<cstdio>
using namespace std;

int poow(int x,int k,int p) {
    int ret=1;
    for(;k;k>>=1,x=x*x%p)
        if(k&1) ret=ret*x%p;
    return ret;
}

int main() {
    int n,m,k,x;
    scanf("%d%d%d%d",&n,&m,&k,&x);
    printf("%d",(x+m*poow(10,k,n))%n);
    return 0;
}
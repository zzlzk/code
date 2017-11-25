#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define maxn 355
#define maxm 41
int f[maxm][maxm][maxm][maxm]={0},n,m;
int c[maxm],Score[maxn];
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&Score[i]);
    for(int i=1;i<=m;i++) {
        int Ser;
        scanf("%d",&Ser);
        c[Ser]++;
    }
    for(int i=0;i<=c[1];i++)
        for(int j=0;j<=c[2];j++)
            for(int k=0;k<=c[3];k++)
                for(int l=0;l<=c[4];l++) {
                	int &dp=f[i][j][k][l];
                    if(i!=0)dp=max(dp,f[i-1][j][k][l]);
                    if(j!=0)dp=max(dp,f[i][j-1][k][l]);
                    if(k!=0)dp=max(dp,f[i][j][k-1][l]);
                    if(l!=0)dp=max(dp,f[i][j][k][l-1]);
                    dp+=Score[i+2*j+3*k+4*l+1];
                }
    printf("%d",f[c[1]][c[2]][c[3]][c[4]]);
    return 0;
}

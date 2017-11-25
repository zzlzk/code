#include<cstdio>
using namespace std;
#define maxn 10010
inline int input() {
    int x=0,a=1;char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    return x*a;
}
struct Carpet {
    int a,b,c,d;
    Carpet() {;}
    void Build(int x,int y,int g,int k) {
        c=(a=x)+g,d=(b=y)+k;
        return;
    }
    bool Judge(int x,int y) {
        return a<=x&&x<=c&&b<=y&&y<=d;
    }
}carpet[maxn];
int main() {
    int n=input(),x,y,g,k;
    for(int i=1;i<=n;i++) {
        x=input(),y=input(),g=input(),k=input();
        carpet[i].Build(x,y,g,k);
    }
    x=input(),y=input();
    for(int i=n;i>=1;i--)
        if(carpet[i].Judge(x,y)==true) {
            printf("%d",i);
            return 0;
        }
    printf("-1");
    return 0;
}
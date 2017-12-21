#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
 
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
 
#define MAXN 2510
#define MAXM 2510
 
struct Cow {
    int Min,Max;
    Cow(int Min=0,int Max=0):
        Min(Min),Max(Max) {}
    bool operator < (const Cow &q) const {
        return Max<q.Max;
    }
};
 
Cow c[MAXN];
 
struct Sunscreens {
    int sum,SPF;
    Sunscreens(int sum=0,int SPF=0):
        sum(sum),SPF(SPF) {}
};
 
Sunscreens s[MAXM];
 
int main() {
    int n,m,a,b;
    input(n),input(m);
    for(int i=1;i<=n;i++) {
        input(a),input(b);
        c[i]=Cow(a,b);
    }
    for(int i=1;i<=m;i++) {
        input(a),input(b);
        s[i]=Sunscreens(b,a);
    }
    sort(c+1,c+n+1);
    a=0;
    for(int i=1;i<=n;i++) {
        b=-1;
        for(int j=1;j<=m;j++)
            if(s[j].sum&&s[j].SPF<=c[i].Max&&s[j].SPF>=c[i].Min)
                if(b==-1||s[j].SPF<s[b].SPF) b=j;
        if(b!=-1) a++,--s[b].sum;
    }
    printf("%d\n",a);
    return 0;
}

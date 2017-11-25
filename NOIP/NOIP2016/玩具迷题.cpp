#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 100010

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

struct People {
    
    static const int MAXNAME=15;
    
    char name[MAXNAME];
    
    int turn;
    
}p[MAXN];

int main() {
    int n,m;
    input(n),input(m);
    for(int i=0;i<n;i++)
        scanf("%d %s",&p[i].turn,p[i].name);
    int pos=0;
    while(m--) {
        int a,s;
        input(a),input(s);
        if(p[pos].turn==0&&a==0) pos=(pos-s+n)%n;
        else if(p[pos].turn==0&&a==1) pos=(pos+s)%n;
        else if(p[pos].turn==1&&a==0) pos=(pos+s)%n;
        else if(p[pos].turn==1&&a==1) pos=(pos-s+n)%n;
    }
    printf("%s",p[pos].name);
    return 0;
}
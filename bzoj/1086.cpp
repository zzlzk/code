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
 
#define MAXN 20010
#define MAXM 20010
 
struct Edge {
    int u,v,next;
    Edge(int u=0,int v=0,int next=0):
        u(u),v(v),next(next) {}
};
 
Edge edge[MAXM];
int head[MAXN],cnt;
 
void addedge(int u,int v) {
    edge[++cnt]=Edge(u,v,head[u]);
    head[u]=cnt;
    return;
}
 
int n,B;
int belong[MAXN];
int root[MAXN],tot;
int st[MAXN],top;
 
void dfs(int u,int fa) {
    int lower=top;
    for(int i=head[u];i;i=edge[i].next)
        if(edge[i].v!=fa) {
            dfs(edge[i].v,u);
            if(top-lower>=B) {
                root[++tot]=u;
                while(top!=lower)
                    belong[st[top--]]=tot;
            }
        }
    st[++top]=u;
    return;
}
 
int main() {
    input(n),input(B);
    for(int i=1,u,v;i<n;i++) {
        input(u),input(v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,-1);
    while(top)
        belong[st[top--]]=tot;
    printf("%d\n",tot);
    for(int i=1;i<=n;i++)
        printf("%d ",belong[i]);
    printf("\n");
    for(int i=1;i<=tot;i++)
        printf("%d ",root[i]);
    return 0;
}
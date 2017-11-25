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

#define MAXN 100010
#define MAXM1 100010

struct Edge {
    int u,v,next;
    Edge(int u=0,int v=0,int next=0):
        u(u),v(v),next(next) {}
};

Edge edge[MAXM1<<1];
int head[MAXN],cnt;
int indeg[MAXN];

void addedge(int u,int v) {
    edge[++cnt]=Edge(u,v,head[u]);
    head[u]=cnt;
    indeg[v]++;
    return;
}

int n,m1,m2;
int order[MAXN],timee;

template<typename Type>
struct Stack {
    static const int SIZE=100010;
    Type st[SIZE];
    int top;
    Stack() { top=0; }
    void push(Type x) { st[++top]=x; return;}
    void pop() { top--; return; }
    Type front() { return st[top]; }
    bool empty() { return top==0; }
};

Stack<int> s;

void topo() {
    for(int i=1;i<=n;i++)
        if(!indeg[i]) {
            s.push(i);
            order[i]=++timee;
        }
    int u,v;
    while(not s.empty()) {
        u=s.front();
        s.pop();
        for(int i=head[u];i;i=edge[i].next) {
            v=edge[i].v;
            indeg[v]--;
            if(!indeg[v]) {
                s.push(v);
                order[v]=++timee;
            }
        }
    }
    return;
}

int main() {
    input(n),input(m1),input(m2);
    for(int i=1,u,v;i<=m1;i++) {
        input(u),input(v);
        addedge(u,v);
    }
    topo();
    for(int i=1,u,v;i<=m2;i++) {
        input(u),input(v);
        if(order[u]<order[v])
            printf("%d %d\n",u,v);
        else printf("%d %d\n",v,u);
    }
    return 0;
}

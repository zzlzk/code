#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

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

struct TreeNode {
    int father,val;
    vector<int> son;
    TreeNode() {
        son.clear();
        val=0;
        father=-1;
    }
    void addson(int x) {
        son.push_back(x);
        return;
    }
}t[MAXN];

int S,n;

bool Judge(TreeNode x) {
    int sum=x.val;
    while(sum<S) {
        x=t[x.father];
        sum+=x.val;
        if(x.father==-1) break;
    }
    return sum==S;
}

queue<TreeNode> q;

int ans;
void bfs() {
    q.push(t[1]);
    while(!q.empty()) {
        TreeNode u=q.front();
        q.pop();
        if(Judge(u)) ans++;
        if(!u.son.empty()) for(int i=0;i<u.son.size();i++)
            q.push(t[u.son[i]]);
    }
    return;
}

int main() {
    input(n),input(S);
    for(int i=1;i<=n;i++)
        input(t[i].val);
    for(int i=1,u,v;i<n;i++) {
        input(u),input(v);
        t[u].addson(v);
        t[v].father=u;
    }
    bfs();
    printf("%d",ans);
    return 0;
}
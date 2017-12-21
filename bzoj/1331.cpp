#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
 
template<typename T>
void input(T &x) {
    x=0; T a=1;
    register char c=getchar();
    for(;c<48||c>57;c=getchar())
        if(c==45) a=-1;
    for(;c>=48&&c<=57;c=getchar())
        x=x*10+c-48;
    x*=a;
    return;
}
 
const int fac[]={1,1,2,6,24,120,720,5040,40320};
 
struct State {
    int a[10],cnt,last;
    char op;
    State(): cnt(0),last(0) {}
};
 
State A(State s) {
    swap(s.a[1],s.a[8]),
    swap(s.a[2],s.a[7]),
    swap(s.a[3],s.a[6]),
    swap(s.a[4],s.a[5]);
    return s;
}
 
State B(State s) {
    swap(s.a[4],s.a[3]),
    swap(s.a[3],s.a[2]),
    swap(s.a[2],s.a[1]),
    swap(s.a[5],s.a[6]),
    swap(s.a[6],s.a[7]),
    swap(s.a[7],s.a[8]);
    return s;
}
 
State C(State s) {
    swap(s.a[2],s.a[7]),
    swap(s.a[7],s.a[6]),
    swap(s.a[6],s.a[3]);
    return s;
}
 
int Cantor(State s) {
    int ans=0;
    for(int i=1,sum;i<=8;i++) {
        sum=0;
        for(int j=i+1;j<=8;j++)
            if(s.a[j]<s.a[i]) sum++;
        ans+=sum*fac[8-i];
    }
    return ans;
}
 
State q[40330];
 
bool vis[40330];
 
int aim[10];
 
bool check(State s) {
    for(int i=1;i<=8;i++)
        if(s.a[i]!=aim[i]) return false;
    return true;
}
 
void Print(State s) {
    char Out[10];
    int top=0;
    for(;s.last!=0;s=q[s.last])
        Out[++top]=s.op;
    for(int i=top;i>=1;i--)
        printf("%c",Out[i]);
    puts("");
    return;
}
 
void bfs(State s) {
    int head=1,tail=0;
    q[++tail]=s;
    vis[Cantor(s)]=true;
    while(head<=tail) {
        s=q[head];
        if(check(s)) {
            printf("%d\n",s.cnt);
            //if(s.cnt) Print(s);
            return;
        }
        for(int i=0;i<3;i++) {
            State ss=(i==0?A(s):(i==1?B(s):C(s)));
            int Hash=Cantor(ss);
            if(!vis[Hash]) {
                vis[Hash]=true;
                ss.cnt=s.cnt+1;
                ss.last=head;
                ss.op=(i==0?'A':(i==1?'B':'C'));
                q[++tail]=ss;
            }
        }
        head++;
    }
    return;
}
 
int main() {
    for(int i=1;i<=8;i++)
        input(aim[i]);
    State s;
    for(int i=1;i<=8;i++)
        s.a[i]=i;
    bfs(s);
    return 0;
}
?
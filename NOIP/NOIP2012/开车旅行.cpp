#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define MAXN 100010
#define inf 1e9
const double eps=1e-6;

template<typename T>
void input(T &x) {
    x=0; T a=1;
    char c=getchar();
    for(;c<'0'||c>'9';c=getchar())
        if(c=='-') a=-1;
    for(;c>='0'&&c<='9';c=getchar())
        x=x*10+c-'0';
    x*=a;
    return;
}

struct City {
    
    int h,id,L,R;
    
    bool operator < (const City& p)const {
        return h<p.h;
    }
    
}a[MAXN];

int now,n;
ll disA,disB;
int pos[MAXN],first[MAXN],second[MAXN],h[MAXN];
int w[MAXN][31],A[MAXN][31],B[MAXN][31];

bool equ(double a,double b) {
    double x=a-b;
    return x>=-eps&&x<=eps;
}

int GetID(int p,int q) {
    if(p==-1&&q==-1) return -1;
    if(p==-1) return a[q].id;
    if(q==-1) return a[p].id;
    if(a[now].h-a[p].h<=a[q].h-a[now].h)
        return a[p].id;
    return a[q].id;
}

void Start(int s,int X) {
    disA=disB=0;
    for(int i=30;i;i--)
        if(w[s][i]>0&&A[s][i]+B[s][i]<=X) {
            X-=A[s][i]+B[s][i];
            disA+=A[s][i];
            disB+=B[s][i];
            s=w[s][i];
        }
    if(second[s]>0&&abs(h[second[s]]-h[s])<=X)
        disA+=abs(h[second[s]]-h[s]);
    return;
}

int main() {
    input(n);
    for(int i=1;i<=n;i++) {
        input(h[i]);
        a[i].h=h[a[i].id=i];
    }
    int x0;
    input(x0);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) {
        pos[a[i].id]=i;
        a[i].L=i-1;
        a[i].R=i+1;
    }
    a[1].L=a[n].R=-1;
    for(int i=1;i<=n;i++) {
        now=pos[i];
        int left=a[now].L,right=a[now].R;
        int &First=first[i],&Second=second[i];
        First=GetID(left,right);
        if(First==-1) Second=-1;
        else if(First==a[left].id)
            Second=GetID(a[left].L,right);
        else Second=GetID(left,a[right].R);
        a[left].R=right;
        a[right].L=left; 
    }
    for(int i=1;i<=n;i++)
        w[i][0]=second[i],w[i][1]=first[w[i][0]];
    for(int j=2;j<31;j++)
        for(int i=1;i<=n;i++)
            if(w[i][j-1]>0)
                w[i][j]=w[w[i][j-1]][j-1];
    for(int i=1;i<=n;i++)
        if(w[i][0]>0) {
            A[i][1]=abs(h[i]-h[w[i][0]]);
            if(w[i][1]>0)
                B[i][1]=abs(h[w[i][1]]-h[w[i][0]]);
        }
    for(int j=2;j<31;j++)
        for(int i=1;i<=n;i++) {
            A[i][j]=A[i][j-1];
            B[i][j]=B[i][j-1];
            if(w[i][j-1]>0) {
                A[i][j]+=A[w[i][j-1]][j-1];
                B[i][j]+=B[w[i][j-1]][j-1];
            }
        }
    double Min=inf;
    int ans=0;
    for(int i=1;i<=n;i++) {
        Start(i,x0);
        if(disB) {
            double t=(double)disA/disB;
            if(t<Min||(equ(t,Min)&&h[ans]<h[i]))
                Min=t,ans=i;
        }
    }
    printf("%d\n",ans);
    int Q;
    input(Q);
    while(Q--) {
        int s,X;
        input(s),input(X);
        Start(s,X);
        printf("%lld %lld\n",disA,disB);
    }
    return 0;
}
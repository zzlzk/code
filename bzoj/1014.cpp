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
 
typedef unsigned long long ull;
const ull BASE=2000001001LL;
 
#define MAXN 150005
 
char s[MAXN];
int root,x,y,L,R;
int fa[MAXN],ch[MAXN][2],size[MAXN];
char key[MAXN];
ull Pow[MAXN],hash[MAXN];
 
#define lc ch[now][0]
#define rc ch[now][1]
 
void updata(int now) {
    hash[now]=0ull,size[now]=0;
    if(rc) hash[now]+=hash[rc],size[now]+=size[rc];
    hash[now]+=(ull)key[now]*Pow[size[now]];
    ++size[now];
    if(lc) hash[now]+=hash[lc]*Pow[size[now]],size[now]+=size[lc];
    return;
}
 
int build(int l,int r,int dad) {
    if (l>r) return 0;
    int mid=l+r>>1;
    fa[mid]=dad,key[mid]=s[mid-1],
    ch[mid][0]=build(l,mid-1,mid),
    ch[mid][1]=build(mid+1,r,mid),
    updata(mid);
    return mid;
}
 
#define get(x) (ch[fa[x]][1]==x)
 
void rotate(int x) {
    int y=fa[x],z=fa[y],d=get(x);
    ch[y][d]=ch[x][d^1];
    if (ch[y][d]) fa[ch[y][d]]=y;
    ch[x][d^1]=y,fa[y]=x;
    if (z) ch[z][ch[z][1]==y]=x;
    fa[x]=z;
    return updata(y),updata(x);
}
 
void splay(int x,int dad) {
    while(fa[x]!=dad) {
        int y=fa[x],z=fa[y];
        if(z!=dad) {
            if(get(x)^get(y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(!dad) root=x;
    return;
}
 
int getkth(int x) {
    for(int now=root;true;) {
        if(lc&&size[lc]>=x) now=lc;
        else {
            if(lc) x-=size[lc];
            if(--x==0) return now;
            now=rc;
        }
    }
    return 0;
}
 
#define interval ch[ch[root][1]][0]
 
bool Judge(int k) {
    splay(L,0),splay(getkth(x+k+1),L);
    ull HASH1=hash[interval];
    splay(R,0),splay(getkth(y+k+1),R);
    ull HASH2=hash[interval];
    return HASH1==HASH2;
}
 
int main() {
    Pow[0]=1;
    for(int i=1;i<=100000;i++)
        Pow[i]=Pow[i-1]*BASE;
    scanf("%s",s+1);
    int n=strlen(s+1),m;
    s[0]=s[n+1]='#',
    root=build(1,n+2,0);
    char op[5];
    for(input(m);m;m--) {
        scanf("%s",op);
        switch(op[0]) {
            case 'Q': {
                scanf("%d%d",&x,&y);
                if(x>y) swap(x,y);
                L=getkth(x),R=getkth(y);
                int l=1,r=n-y+1,mid,ans=0;
                while (l<=r) {
                    mid=(l+r)>>1;
                    if(Judge(mid)) ans=mid,l=mid+1;
                    else r=mid-1;
                }
                printf("%d\n",ans);
                break;
            }
            case 'R': {
                input(x),scanf("%s",op);
                int A=getkth(x+1);
                splay(A,0);
                key[root]=op[0];
                updata(root);
                break;
            }
            case 'I': {
                input(x),scanf("%s",op);
                int A=getkth(x+1),B=getkth(x+2);
                splay(A,0),splay(B,A),++n;
                key[n+2]=hash[n+2]=op[0],
                size[n+2]=1,
                fa[n+2]=ch[root][1],
                ch[ch[root][1]][0]=n+2,
                updata(ch[root][1]),updata(root);
                break;
            }
        }
    }
    return 0;
}
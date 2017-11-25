#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
#define maxn 55
#define mod 998244353
#define QAQ 19171
#define OVO 26473
int topnum,topsym,n;
char a[maxn],sym[maxn];
ll ans1,ans2;
struct Exp {
    ll Y1,Y2;
    Exp(ll Y1=0,ll Y2=0):
        Y1(Y1),Y2(Y2) {}
}num[maxn];
inline int level(char ch) {
    if(ch=='-'||ch=='+') return 1;
    if(ch=='*') return 2;
    if(ch=='^') return 3;
    return 0;
}
bool Judge(char a,char b) {
	return level(a)<level(b);
}
ll poow(ll a,int k) {
    ll ret=1;
    for(;k;k>>=1,a=(a*a)%mod)
        if(k&1) ret=(ret*a)%mod;
    return ret;
}
void calc(char op) {
    Exp &N=num[--topnum];
    ll a1=N.Y1,b1=num[topnum+1].Y1;
    ll a2=N.Y2,b2=num[topnum+1].Y2;
    if(op=='+') N=Exp((a1+b1)%mod,(a2+b2)%mod);
    else if(op=='-') {
        N=Exp((a1-b1)%mod,(a2-b2)%mod);
        if(N.Y1<0) N.Y1+=mod;
        if(N.Y2<0) N.Y2+=mod;
    } else if(op=='*') N=Exp((a1%mod*b1)%mod,(a2%mod*b2)%mod);
    else N=Exp(poow(a1,b1),poow(a2,b2));
    return;
}
void GetAnExp() {
    gets(a);
    int m=strlen(a),p=0;
    while(p<m) {
        if(a[p]==' ') {
            p++;
            continue;
        }
        if(a[p]>='0'&&a[p]<='9') {
            int x=a[p++]-'0';
            while(a[p]>='0'&&a[p]<='9')
                x=x*10+a[p++]-'0';
            p--,num[++topnum]=Exp(x,x);
        } else if(a[p]=='a') num[++topnum]=Exp(QAQ,OVO);
        else if(a[p]=='(') sym[++topsym]='(';
        else if(a[p]==')') {
            while(topsym>1&&sym[topsym]!='(')
                calc(sym[topsym--]);
            if(topsym>=1) topsym--;
        } else if(!topsym||Judge(sym[topsym],a[p]))
			sym[++topsym]=a[p];
        else {
            calc(sym[topsym--]);
            while(topsym>0&&!Judge(sym[topsym],a[p]))
                calc(sym[topsym--]);
            sym[++topsym]=a[p];
        }
        p++;
    }
    while(topsym>0) calc(sym[topsym--]);
}
int main() {
    GetAnExp();
    ans1=num[1].Y1,ans2=num[1].Y2,topnum=0;
    scanf("%d",&n);
    gets(a);
    for(int i=0;i<n;i++) {
        GetAnExp();
        if(num[1].Y1==ans1&&num[1].Y2==ans2)
            printf("%c",'A'+i);
        topnum=0;
    }
    return 0;
}

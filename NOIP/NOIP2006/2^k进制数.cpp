#include<cstdio>
#include<algorithm>
using namespace std;
struct STR{
    int s[210];
}c[510][510]; 
STR One,ans;
void put(STR a){
    printf("%d",a.s[a.s[0]]);
    for(int i=a.s[0]-1;i>0;i--)
		printf("%.4d",a.s[i]);
	return;
}
STR add(STR &d,STR a,STR b){
    int L=max(a.s[0],b.s[0]);
    for(int i=1;i<=L;i++){
        d.s[i]+=a.s[i]+b.s[i];
        d.s[i+1]+=d.s[i]/10000;
        d.s[i]%=10000;
    }
    if(d.s[L+1]) ++L;
    d.s[0]=L;
    return d;
}
void Inc(STR &a,STR b){
    int L=max(a.s[0],b.s[0]);
    for(int i=1;i<=L;i++){
        a.s[i]+=b.s[i];
        a.s[i+1]+=a.s[i]/10000;
        a.s[i]%=10000;
    }
    if(a.s[L+1]) ++L;
    a.s[0]=L;
    return;
}
STR C(int n,int m){
    if(c[n][m].s[0]) return c[n][m];
    if(n==m||!m) return c[n][m]=One;
    return add(c[n][m],C(n-1,m-1),C(n-1,m));
}
int main(){
    One.s[0]=One.s[1]=1;
    int k,w;
    scanf("%d%d",&k,&w);
    int Max=w/k,lim1=(1<<k)-1;
    for(int i=2;i<=Max;i++) 
      if(i<=lim1) Inc(ans,C(lim1,i));
    int lim2=1<<(w%k);
    for(int j=1;j<lim2&&lim1-j>=Max;j++) 
       Inc(ans,C(lim1-j,Max));
    put(ans);
    return 0;
}

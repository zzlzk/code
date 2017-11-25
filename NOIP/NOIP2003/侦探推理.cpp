#include<map>
#include<string>
#include<cstdio>
#include<iostream>
using namespace std;
#define maxn 110
#define maxm 30
map<string,int>t;
map<int,string>h;
int s[maxm][maxn],d[maxm][maxn],day[maxm][maxn];
int l[maxm],gu[maxm];
string str,v[maxn],g[maxn],q[maxn],str0;
int main() {
	int n,m,p;
	scanf("%d%d%d",&m,&n,&p);
	for(int i=1;i<=m;i++) {
		cin>>str;
		t[str]=i;
		h[i]=str;
	}
	for(int i=0;i<p;i++) {
		int y,len=1;
		str="";
		while(str[len-1]!='.'&&str[len-1]!='?'&&str[len-1]!='!') {
			cin>>str0;
			if(len>1) str+=' ';
			str+=str0;
			len=str.length();
		}
		for(int j=0;j<len&&str[j]!=':';j++) {
			v[i]+=str[j];
			y=j;
		}
		int jj=t[v[i]],b=-1,nn=0,uu=0;
		for(int j=y+3;j<len;j++) {
			if(!uu) g[i]+=str[j];
			else q[i]+=str[j];
			if(!nn&&!uu&&str[j+1]==' ')
				for(int k=1;k<=m;k++)
					if(h[k]==g[i]) {
						b=k;
						break;
					}
			if(b!=-1&&!nn&&!uu) {
				g[i]=str[j+2];
				j+=2;
				nn=1;
			}
			if(g[i]=="Today is ") uu=1;
		}
		if(g[i]=="I am guilty.") s[jj][l[jj]++]=1;
		if(g[i]=="I am not guilty.") s[jj][l[jj]++]=2;
		if(g[i]=="is guilty.") {
			s[jj][l[jj]]=3;
			d[jj][l[jj]++]=b;
		}
		if(g[i]=="is not guilty.") {
			s[jj][l[jj]]=4;
			d[jj][l[jj]++]=b;
		}
		if(g[i]=="Today is ") {
			s[jj][l[jj]]=5;
			if(q[i]=="Monday.") day[jj][l[jj]++]=1;
			if(q[i]=="Tuesday.") day[jj][l[jj]++]=2;
			if(q[i]=="Wednesday.") day[jj][l[jj]++]=3;
			if(q[i]=="Thursday.") day[jj][l[jj]++]=4;
			if(q[i]=="Friday.") day[jj][l[jj]++]=5;
			if(q[i]=="Saturday.") day[jj][l[jj]++]=6;
			if(q[i]=="Sunday.") day[jj][l[jj]++]=7;
		}
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=7;j++) {
			int fa=0,T,F,abc=0;
			for(int k=1;k<=m;k++) {
				T=F=0;
				for(int kk=0;kk<l[k];kk++) {
					if(s[k][kk]==1)
						if(i==k) T=1;
						else F=1;
					if(s[k][kk]==2)
						if(i!=k) T=1;
						else F=1;
					if(s[k][kk]==3)
						if(i==d[k][kk]) T=1;
						else F=1;
					if(s[k][kk]==4)
						if(i!=d[k][kk]) T=1;
						else F=1;
					if(s[k][kk]==5)
						if(j==day[k][kk]) T=1;
						else F=1;
				}
				if(T&&F) break;
				if(F) fa++;
				if(!F&&!T) abc++;
			}
			if(T&&F) continue;
			if(fa==n||fa<=n&&fa+abc>=n) gu[i]=1;
		}
	int ans=0;
	for(int i=1;i<=m;i++)
		if(gu[i]) ans++;
	if(!ans) printf("Impossible");
	else if(ans>1) printf("Cannot Determine");
	else {
		for(int i=1;i<=m;i++)
			if(gu[i]) {
				cout<<h[i];
				break;
			}
	}
	return 0;
}

#include<cstdio>
#include<cstring> 
using namespace std;
#define maxn 1000010
#define maxm 1010
char a[maxn],b[maxm];
int next[maxn];
void Get_next(char *s) {
	int l=strlen(s),t;
	next[0]=-1;
	for(int i=1;i<l;i++) {
		t=next[i-1];
		while(s[t+1]!=s[i]&&t>=0) t=next[t];
		if(s[t+1]==s[i]) next[i]=t+1;
		else next[i]=-1;
	}
	return;
}
void KMP(char *s1,char *s2) {
	Get_next(s2);
	int len1=strlen(s1),len2=strlen(s2);
	int i=0,j=0;
	while(j<len1) {
		if(s2[i]==s1[j]) {
			i++;
			j++;
			if(i==len2) {
				printf("%d\n",j-len2+1);
				i=next[i-1]+1;
			}
		} else {
			if(i==0) j++;
			else i=next[i-1]+1;
		}
	}
	return;
}
int main() {
	scanf("%s%s",a,b);
	KMP(a,b);
	for(int i=0;i<strlen(b);i++)
		printf("%d ",next[i]+1);
	return 0;
}

#include<cstdio>
#include<cstring>
using namespace std;
#define maxn 110
char s1[maxn],s2[maxn],s3[maxn];
int cor[30]={0};
inline int id(char c) {
	return c-'A'+1;
}
inline char id(int x) {
	return (char)x-1+'A';
}
int main() {
	scanf("%s",s1);
	scanf("%s",s2);
	scanf("%s",s3);
	int n=strlen(s2);
	if(n<26) {
		printf("Failed");
		return 0;
	}
	for(int i=0;i<n;i++) {
		int x=id(s1[i]),y=id(s2[i]);
		if(cor[y]==0) cor[y]=x;
		else if(cor[y]!=x) {
			printf("Failed");
			return 0;
		}
	}
	n=strlen(s3);
	for(int i=0;i<n;i++) {
		int x=id(s3[i]);
		for(int i=1;i<=26;i++)
			if(cor[i]==x) {
				printf("%c",id(i));
				break;
			}
	}
	return 0;
}

#include<cstdio>
#include<cstring>
using namespace std;
#define maxn 110
char c[maxn];
inline char tocap(char ch) {
	if(ch>='A'&&ch<='Z') return ch;
	return ch-32;
}
inline char tolow(char ch) {
	if(ch>='a'&&ch<='z') return ch;
	return ch+32;
}
int main() {
	int p1,p2,p3;
	scanf("%d%d%d",&p1,&p2,&p3);
	scanf("%s",c);
	int len=strlen(c);
	for(int i=0;i<len;i++)
		if(c[i]!='-') printf("%c",c[i]);
		else if(i==0||i==len-1) {
			printf("-");
			continue;
		} else {
			char a=c[i-1],b=c[i+1];
			if(a=='-'||b=='-') {
				printf("-");
				continue;
			}
			if((a>='0'&&a<='9')&&((b>='a'&&b<='z')||(b>='A'&&b<='Z'))) {
				printf("-");
				continue;
			}
			if((b>='0'&&b<='9')&&((a>='a'&&a<='z')||(a>='A'&&a<='Z'))) {
				printf("-");
				continue;
			}
			if(a>=b) {
				printf("-");
				continue;
			} else if(a+1==b) continue;
			else {
				int num=b-a-1;
				int begin=a+1,end=b-1;
				if(p1==3) {
					for(int i=1;i<=num*p2;i++)
						printf("*");
				} else if(a>='0'&&a<='9') {
					if(p3==2) {
						for(int i=end;i>=begin;i--)
							for(int j=1;j<=p2;j++)
								printf("%c",i);
					} else {
						for(int i=begin;i<=end;i++)
							for(int j=1;j<=p2;j++)
								printf("%c",i);
					}
				} else {
					if(p3==2) {
						if(p1==1) {
							for(int i=end;i>=begin;i--)
								for(int j=1;j<=p2;j++)
									printf("%c",tolow((char)i));
						} else {
							for(int i=end;i>=begin;i--)
								for(int j=1;j<=p2;j++)
									printf("%c",tocap((char)i));
						}
					} else {
						if(p1==1) {
							for(int i=begin;i<=end;i++)
								for(int j=1;j<=p2;j++)
									printf("%c",tolow((char)i));
						} else {
							for(int i=begin;i<=end;i++)
								for(int j=1;j<=p2;j++)
									printf("%c",tocap((char)i));
						}
					}
				}
			}
		}
	return 0;
}

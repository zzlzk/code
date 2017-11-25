#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define mod 2014

string s;
map<string,int> remember;

int dfs(string now) {
    if(remember[now])
        return remember[now];
    int ans=1,len=now.size();
    for(int i=1;i*2<len;i++) {
        if(now.substr(0,i)==now.substr(len-i,i))
            ans+=dfs(now.substr(i,len-i))+dfs(now.substr(0,len-i));
        if(now.substr(0,i)==now.substr(i,i))
            ans+=dfs(now.substr(i,len-i));
        if(now.substr(len-2*i,i)==now.substr(len-i,i))
            ans+=dfs(now.substr(0,len-i));
    }
    return remember[now]=ans%mod;
}

int main() {
    cin>>s;
    printf("%d",(dfs(s)+mod-1)%mod);
    return 0;
} 

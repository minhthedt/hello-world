#include <stdio.h>
#include <string.h>
#include <vector>
#define M 67108864 // 2<<26
using namespace std;

int ans,sum,num[M+10];
char s[50009];
bool chk[30];
vector<int> temp;

int main(){
	int T; scanf("%d",&T); while(T--){
		int i;
		scanf("%s",s);

		for (i=0;i<26;i++) chk[i]=false;
		sum=0; ans=0; num[0]=1;
		temp.clear(); temp.push_back(0);

		for (i=0;s[i];i++){
			int now = s[i]-'a';
			if (chk[now]) sum -= 1<<now;
			else sum += 1<<now;
			chk[now] = (chk[now]+1)%2;

			ans += num[sum];
			num[sum]++;
			temp.push_back(sum);
		}
		printf("%d\n",ans);
		for (i=0;i<temp.size();i++)
			if (num[temp[i]]) num[temp[i]]=0;
	}
	return 0;
}

//
//  main.cpp
//  LG
//
//  Created by jungrae on 2016. 8. 13..
//  Copyright © 2016년 jungrae. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#define mp make_pair
#define pi pair<int,int>
#define M 10000
using namespace std;

struct pp{
    int pos,data;
    pp(){}
    pp(int a,int b){
        pos=a; data=b;
    }
    bool operator<(const pp &q)const{
        return data>q.data;
    }
};
vector<pp> v[M];
int n,m,K,st1,st2;
int d1[M],d2[M],chk[M];
double ans;
pi edge;
priority_queue<pp> q;

vector<pi> temp;

int main(int argc, const char * argv[]) {
//    freopen("in.txt","r",stdin);

    bool flag=false;
    int T; scanf("%d",&T); while(T--){

        temp.clear();

        int i,j;
        scanf("%d %d %d",&n,&m,&K);
        for (i=1;i<=n;i++) v[i].clear();
        for (i=1;i<=m;i++){
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            v[a].push_back(pp(b,c)); v[b].push_back(pp(a,c));
        }
//        printf("::%d\n",K);
        for (i=1;i<=K;i++){
            scanf("%d %d",&st1,&st2);
//            printf("%d %d\n",st1,st2);
//            if (st1==st2){ printf("%d %d\n",st1,st1); continue; }

            ans=2e9; edge=mp(n+1,n+1);
            
            for (j=1;j<=n;j++) d1[j]=2e9,chk[j]=0;
            while(!q.empty()) q.pop();
            
            q.push(pp(st1,0)); d1[st1]=0;
            while(!q.empty()){
                pp here = q.top(); q.pop();
                if (chk[here.pos]) continue;
                chk[here.pos]=1;
//                for (auto there : v[here.pos]){
                for (int k=0;k<v[here.pos].size();k++){
                    pp there = v[here.pos][k];
                    if (chk[there.pos]) continue;
                    if (d1[there.pos] > d1[here.pos]+there.data){
                        d1[there.pos] = d1[here.pos]+there.data;
                        q.push(pp(there.pos,d1[there.pos]));
                    }
                }
            }
            
            for (j=1;j<=n;j++) d2[j]=2e9,chk[j]=0;
            while(!q.empty()) q.pop();
            
            q.push(pp(st2,0)); d2[st2]=0;
            while(!q.empty()){
                pp here = q.top(); q.pop();
                if (chk[here.pos]) continue;
                chk[here.pos]=1;
//                for (auto there : v[here.pos]){
                for (int k=0;k<v[here.pos].size();k++){
                    pp there = v[here.pos][k];
                    if (chk[there.pos]) continue;
                    if (d2[there.pos] > d2[here.pos]+there.data){
                        d2[there.pos] = d2[here.pos]+there.data;
                        q.push(pp(there.pos,d2[there.pos]));
                        if (d1[there.pos]==d2[there.pos]){
                            if (ans>d1[there.pos]){
                                ans = d1[there.pos];
                                edge=mp(there.pos,there.pos);
                                temp.clear(); temp.push_back(edge);
                            }
                            else if (ans==d1[there.pos]){
                                edge=min(edge,mp(there.pos,there.pos));
                                temp.push_back(mp(there.pos,there.pos));
                            }
                        }
                        if (d1[there.pos] < d2[there.pos] && d1[here.pos] > d2[here.pos]){
                            if (ans > max(d1[there.pos],d2[here.pos]) + (double)(there.data-abs(d1[there.pos]-d2[here.pos]))/2){
                                ans = max(d1[there.pos],d2[here.pos]) + (double)(there.data-abs(d1[there.pos]-d2[here.pos]))/2;
                                edge = mp(min(here.pos,there.pos),max(here.pos,there.pos));
                                temp.clear(); temp.push_back(edge);
                            }
                            else if (ans==max(d1[there.pos],d2[here.pos]) + (double)(there.data-abs(d1[there.pos]-d2[here.pos]))/2){
                                edge=min(edge,mp(min(here.pos,there.pos),max(here.pos,there.pos)));
                                temp.push_back(mp(min(here.pos,there.pos),max(here.pos,there.pos)));
                            }
                        }
                    }
                }
            }
//            printf("::%lf\n",ans);
            if (temp.size()>1) flag=true;
            printf("%d %d\n",edge.first,edge.second);
        }
    }
//    if (flag) printf("YES\n");
//    else printf("NO\n");
    return 0;
}


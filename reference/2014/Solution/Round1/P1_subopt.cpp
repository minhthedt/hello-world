#include <stdio.h>
#include <algorithm>
#include <memory.h>

#define LEFT 0
#define RIGHT 1
#define MAX_N 100001

using namespace std;

struct LIST{
    int y1;
    int y2;
    int x;
    int lr;
}list[MAX_N*3];

struct SORTF{
    bool inline operator () (LIST a, LIST b)
    {
        return a.x < b.x;
    }
};

struct poly{
    long long area;
    int cnt;
    int idx;
}poly[MAX_N*3];

int N, M, C;
int yidx[MAX_N*3], onoff[MAX_N*3];
int area_idx[MAX_N*3];
int valid[MAX_N*3];
long long max_area;

int idx_q[MAX_N*3], Head, Tail;

int bsearch(int val)
{
    int s = 1, e = M;
    int m;
    while(s <= e)
    {
        m = (s+e) >> 1;
        if(yidx[m] < val) s=m+1;
        else if(yidx[m] > val) e=m-1;
        else return m;
    }
    return -1;
}

void enqueue(int v)
{
    if(v==0) printf("ERROR");
    idx_q[Tail++] = v;
    if(Tail > M) Tail = 0;
    valid[v] = 0;
}
int dequeue()
{
    int r = idx_q[Head++];
    if(Head > M) Head = 0;
    valid[r] = 1;
    return r;
}
int main()
{
    int i, j, k;
    int x1, x2, y1, y2;
        memset(valid, 0, sizeof(valid));
        scanf("%d", &N);
        C = 0;
        M = 0;
        max_area = 0;
        for(i = 1; i <= N; i++)
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            ++M; list[M].x = x1;
            list[M].y1 = y1; list[M].y2 = y2;
            list[M].lr = LEFT;
            yidx[M] = y1;

            ++M; list[M].x = x2;
            list[M].y1 = y1; list[M].y2 = y2;
            list[M].lr = RIGHT;
            yidx[M] = y2;
        }
        sort(list+1, list+1+M, SORTF());
        sort(yidx+1, yidx+1+M);

        memset(onoff, 0, sizeof(onoff[0]) * (M+1));
        for(i = 1; i <= M; i++)
        {
            list[i].y1 = bsearch(list[i].y1);
            list[i].y2 = bsearch(list[i].y2);
        }

        Head = Tail = 0;
        for(i = 1; i <= M; i++) idx_q[Tail++] = i;

        int last;
        for(i = 1; i <= M; i++)
        {
            // Calculate 
            for(last = 0, j = 1; j <= M; j++)
            {
                if(onoff[j] == 0) continue;
                if(last) poly[area_idx[j]].area += (long long)(list[i].x - list[i-1].x) * (yidx[j] - yidx[last]);
                last = j;
            }

            if(list[i].lr == LEFT)
            {
                for(last = list[i].y1 - 1; last >= 1; last --)
                    if(onoff[last]) break;
                for(j = list[i].y1 + 1; j <= M; j++)
                    if(onoff[j]) break;
                if(last != 0){
                    area_idx[list[i].y1] = area_idx[j];
                    if(j > list[i].y2)
                        poly[area_idx[j]].cnt += 1;
                }
                onoff[list[i].y1] = 1;
                onoff[list[i].y2] = 1;
            }
            if(list[i].lr == RIGHT)
            {
                for(j = list[i].y1 + 1; j < list[i].y2; j++)
                    if(onoff[j]) break;

                if(j != list[i].y2){
                    poly[area_idx[j]].cnt --;
                    if(poly[area_idx[j]].cnt == 0 && area_idx[j] != 0){
                        C++;
                        if(max_area < poly[area_idx[j]].area)
                            max_area = poly[area_idx[j]].area;
                        enqueue(area_idx[j]);
                        area_idx[j] = 0;
                    }
                }

                poly[area_idx[list[i].y2]].cnt --;
                if(poly[area_idx[list[i].y2]].cnt == 0 && area_idx[list[i].y2] != 0){
                    C++;
                    if(max_area < poly[area_idx[list[i].y2]].area)
                        max_area = poly[area_idx[list[i].y2]].area;
                    enqueue(area_idx[list[i].y2]);
                    area_idx[list[i].y2] = 0;
                }
            }
            for(last = 0, j = list[i].y1 + 1; j < list[i].y2; j++)
            {
                if(onoff[j] == 0) continue;

                if(last) {
                    poly[area_idx[j]].cnt --;
                    if(poly[area_idx[j]].cnt == 0 && area_idx[j] != 0){
                        C++;
                        if(max_area < poly[area_idx[j]].area)
                            max_area = poly[area_idx[j]].area;
                        enqueue(area_idx[j]);
                        area_idx[j] = 0;
                    }
                }
                last = j;
            }

            // clean
            for(j = 1; j <= M; j++)
                if(valid[area_idx[j]] == 0)
                    area_idx[j] = 0;
            // generate next..
            for(last = 0, j = list[i].y1 + 1; j < list[i].y2; j++)
            {
                if(onoff[j] == 0) continue;

                if(last) {
                    int ai = dequeue();
                    area_idx[j] = ai;
                    poly[ai].area = 0;
                    poly[ai].cnt = 1;

                }
                last = j;
            }

            if(list[i].lr == LEFT)
            {
                for(j = list[i].y1 + 1; j < list[i].y2; j++)
                    if(onoff[j]) break;

                int ai = dequeue();
                area_idx[j] = ai;
                poly[ai].area = 0;
                poly[ai].cnt = 1;

                if(j != list[i].y2){
                    for(j = list[i].y2 - 1; j > list[i].y1; j--)
                        if(onoff[j]) break;

                    int ai = dequeue();
                    area_idx[list[i].y2] = ai;
                    poly[ai].area = 0;
                    poly[ai].cnt = 1;
                }
            }
            if(list[i].lr == RIGHT)
            {
                onoff[list[i].y1] = 0;
                onoff[list[i].y2] = 0;

                for(last = list[i].y1 - 1; last >= 1; last --)
                    if(onoff[last]) break;
                for(k = list[i].y1 + 1; k < list[i].y2; k++)
                    if(onoff[k]) break;
                for(j = list[i].y2 + 1; j <= M; j++)
                    if(onoff[j]) break;
                if(k == list[i].y2){
                    if(last != 0 && j != M+1) // mergeable
                    {
                        if(area_idx[j] == area_idx[list[i].y1]){
                            poly[area_idx[j]].cnt --;
                        }
                        else {
                            int from = area_idx[list[i].y1];
                            int target = area_idx[j];
                            if(from == 0){
                                int tmp = from;
                                from = target;
                                target = tmp;
                            }
                            for(k = 1; k <= M; k++) if(area_idx[k] == from) area_idx[k] = target;

                            poly[target].cnt += poly[from].cnt - 1;
                            poly[target].area += poly[from].area;
                            enqueue(from);

                            area_idx[list[i].y1] = 0;
                        }
                    }
                    else if(last != 0 && area_idx[list[i].y1] != 0)
                    {
                        int tmp = area_idx[list[i].y1];
                        for(k = 1; k <= M; k++) if(area_idx[k] == tmp) area_idx[k] = 0;
                        enqueue(tmp);
                    }
                    else if(j != M+1 && area_idx[j] != 0)
                    {
                        int tmp = area_idx[j];
                        for(k = 1; k <= M; k++) if(area_idx[k] == tmp) area_idx[k] = 0;
                        enqueue(tmp);

                    }
                }
                else if(last != 0){
                    int tmp = area_idx[list[i].y1];
                    area_idx[list[i].y1] = 0;
                    for(j = last + 1; j <= M; j++)
                        if(onoff[j]) break;
                    if(j != M+1) area_idx[j] = tmp;
                }
            }
        }
        printf("%d %lld\n", C, max_area);
    return 0;
}

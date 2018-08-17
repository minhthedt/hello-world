/*
    Compiler : Visual C++ 2010
    Build mode : Release mode
    Usage : ProgramName <input file> <output file>
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct ValueT
{
    int v;
};

struct EdgeT
{
    int from;
    int to;
    int w;

    bool operator ==(const EdgeT& r) const
    {
        return from == r.from && to == r.to;
    }

    bool operator <(const EdgeT& r) const
    {
        if (from < r.from)
            return true;
        else if (from > r.from)
            return false;
        else
            return to < r.to;
    }
};

vector<ValueT> gV;
long long gE1Cost;
long long gE2Cost;
vector<EdgeT> gE;

int gEQCnt;
int* gEQ;

bool gVisited[110000];

int gCycleCnt;
int* gCycle;

int gOutECnt;
EdgeT* gOutE;

set<int> gOutW;
long long gE1CostOut;
long long gE2CostOut;
bool gUnique;

bool lessW(const EdgeT& l, const EdgeT& r)
{
    return l.w < r.w;
}

bool lessEQW(int l, int r)
{
    return gE[l].w < gE[r].w;
}

bool lessFrom(const EdgeT& l, const EdgeT& r)
{
    return l.from < r.from;
}

bool makeCycle(int prev, int from, int goal)
{
    EdgeT ek;
    EdgeT *itS, *itE;

    if (from == goal)
        return true;

    ek.from = from;
    itS = lower_bound(gOutE, gOutE + gOutECnt, ek, lessFrom);
    itE = upper_bound(itS, gOutE + gOutECnt, ek, lessFrom);
    while (itS != itE)
    {
        if (itS->to != prev && makeCycle(from, itS->to, goal))
        {
            gCycle[gCycleCnt++] = itS->w;
            return true;
        }
        ++itS;
    }

    return false;
}

void checkUnique(const EdgeT& e)
{
    if (gUnique == false || gOutW.find(e.w) == gOutW.end())
        return;

    gCycleCnt = 0;

    makeCycle(-1, e.from, e.to);

    int *it, *itE;
    itE = gCycle + gCycleCnt;
    for (it = gCycle; it < itE; ++it)
    {
        if (e.w == *it)
        {
            gUnique = false;
            break;
        }
    }
}

void insertEQ(int* pos, int e)
{
    int* end = gEQ + gEQCnt;
    if (pos < end)
        memmove(pos+1, pos, (char*)end - (char*)pos);
    *pos = e;
    gEQCnt++;
}

void pushEdgeToEQ(int v)
{
    EdgeT ek;
    vector<EdgeT>::iterator itS, itE;

    ek.from = v;
    itS = lower_bound(gE.begin(), gE.end(), ek, lessFrom);
    itE = upper_bound(itS, gE.end(), ek, lessFrom);
    for (; itS != itE; ++itS)
    {
        if (!gVisited[itS->to])
        {
            int index = itS - gE.begin();
            insertEQ(upper_bound(gEQ, gEQ + gEQCnt, index, lessEQW), index);
        }
        else
            checkUnique(*itS);
    }
}

void insertOutE(EdgeT* pos, const EdgeT& e)
{
    EdgeT* end = gOutE + gOutECnt;
    if (pos < end)
        memmove(pos+1, pos, (char*)end - (char*)pos);
    *pos = e;
    gOutECnt++;
}

void calcCost()
{
    int e;
    ValueT v;

    gEQCnt = 0;
    gOutECnt = 0;
    gOutW.clear();

    gUnique = true;
    gE1CostOut = 0ll;
    gE2CostOut = 0ll;

    v = gV.back();
    gV.pop_back();

    gVisited[v.v] = true;
    pushEdgeToEQ(v.v);

    while (gEQCnt > 0)
    {
        e = gEQ[--gEQCnt];

        EdgeT ee = gE[e];
        if (gVisited[ee.to])
        {
            checkUnique(ee);
            continue;
        }

        if (ee.w > 0)
            gE1CostOut += (long long)ee.w;
        else
            gE2CostOut += (long long)-ee.w;
        gOutW.insert(ee.w);

        gVisited[ee.to] = true;
        pushEdgeToEQ(ee.to);

        insertOutE(upper_bound(gOutE, gOutE + gOutECnt, ee, lessFrom), ee);
        swap(ee.from, ee.to);
        insertOutE(upper_bound(gOutE, gOutE + gOutECnt, ee, lessFrom), ee);
    }
}

void process(FILE* pfIn, FILE* pfOut)
{
    EdgeT e;
    ValueT v;
    int i, j, count, f, t, w, N, M, K;

    gV.reserve(110000);
    gE.reserve(610000 * 2);
    gEQ = new int[610000 * 2];
    gCycle = new int[210000];
    gOutE = new EdgeT[610000];

    fscanf(pfIn, "%d", &count);
    for (i = 0; i < count; i++)
    {
        fscanf(pfIn, "%d %d %d", &N, &M, &K);

        gE.clear();
        memset(gVisited, 0, sizeof(gVisited));
        for (j = 0; j < N; j++)
        {
            v.v = j;
            gV.push_back(v);
        }

        gE1Cost = 0ll;
        for (j = 0; j < M; j++)
        {
            fscanf(pfIn, "%d %d %d", &f, &t, &w);
            e.from = --f;
            e.to = --t;
            e.w = w;
            gE.push_back(e);
            e.from = t;
            e.to = f;
            e.w = w;
            gE.push_back(e);
            gE1Cost += (long long)w;
        }
        gE2Cost = 0ll;
        for (j = 0; j < K; j++)
        {
            fscanf(pfIn, "%d %d %d", &f, &t, &w);
            e.from = --f;
            e.to = --t;
            e.w = -w;
            gE.push_back(e);
            e.from = t;
            e.to = f;
            e.w = -w;
            gE.push_back(e);
            gE2Cost += (long long)w;
        }
        sort(gE.begin(), gE.end());

        calcCost();

        fprintf(pfOut, "%lld %d\n", (gE1Cost - gE1CostOut) + gE2CostOut, (int)gUnique);
    }

    delete[] gEQ;
    delete[] gCycle;
    delete[] gOutE;
}

//-----------------------------------------------------------------------------

void process(const char* pcszInFile, const char* pcszOutFile)
{
    FILE* pfIn = fopen(pcszInFile, "rt");
    if (pfIn == NULL)
    {
        printf("file not found! \"%s\"\n", pcszInFile);
        exit(-2);
    }

    FILE* pfOut = fopen(pcszOutFile, "wt");
    if (pfOut == NULL)
    {
        printf("can't create file! \"%s\"\n", pcszOutFile);
        exit(-3);
    }

    process(pfIn, pfOut);

    fclose(pfIn);
    fclose(pfOut);
}

void main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage : %s <input_file> <output_file>\n", argv[0]);
        exit(-1);
    }

    process(argv[1], argv[2]);
}

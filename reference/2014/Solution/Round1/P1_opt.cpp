/*********** n sqrt n ************/


const int K = 250; // ~ sqrt(MAX_N)


#include <algorithm>
using std::sort;


#include <cmath>
using std::min;


#include <utility>
using std::pair;
using std::make_pair;


#include <map>
using std::map;

#include <memory.h>
#include <stdio.h>

#define MAX_N 100000
#define MAX_COORD 1000000000
#define MIN_COORD 0


struct VerticalLine {
	int x, y0, y1;
	bool left;

	VerticalLine () {}
	VerticalLine (int x, int y0, int y1, bool left) : x(x), y0(y0), y1(y1), left(left) {}

	bool operator < (const VerticalLine& rhs) const {
		return x < rhs.x;
	}
};


static int top;
static long long buffer[MAX_N * 4];
static long long* stack[MAX_N * 4];


long long* mallocFromBuffer() { return stack[--top]; }
void freeBuffer (long long* ptr) { stack[top++] = ptr; }


struct Rect {
	long long id;
	long long* area;
	long long* refCnt;

	static long long _id_generator;


	Rect () : area (NULL), refCnt (NULL) {}
	Rect (long long area) : id(_id_generator++) {
		this->area = mallocFromBuffer ();
		refCnt = mallocFromBuffer ();
		*(this->area) = area;
		*refCnt = 1;
	}
};

long long Rect::_id_generator = 0;


enum EventType {
	EVENT_OUT_OF_RANGE,
	TYPE1,
	TYPE2_ADD,
	TYPE2_DELETE,
	TYPE3_ADD,
	TYPE3_DELETE,
	TYPE4_ADD,
	TYPE4_DELETE,
};

enum SpecialCaseType {
	SPECIAL_TYPE1, 
	SPECIAL_TYPE2, 
	SPECIAL_TYPE3,
	SPECIAL_UNDEFINED
};


int n, rectangle[MAX_N][4];


int xcnt, x[MAX_N * 2 + 2];
int ycnt, y[MAX_N * 4 + 2];


int linecnt;
VerticalLine line[MAX_N * 2];


long long rectCnt;
long long rectMaxArea;


struct MergeInfo {
	long long id, oid;
	long long* area;

	MergeInfo () {}
	MergeInfo (long long id, long long oid, long long* area)
		: id (id), oid (oid), area (area) {}
};


int idRenameGenerator;
map<long long, int> idRenameMap;
int edgecnt;
pair<MergeInfo, MergeInfo> edge[MAX_N * 2];


int parent[MAX_N * 2];
long long area[MAX_N * 2];
long long smallestId [MAX_N * 2];


int root (int x) { return x==parent[x] ? x : (parent[x] = root (parent[x])); }
void merge (int x, int y)
{
	if (x!=y) {
		area[x] += area[y];
		smallestId[x] = min (smallestId[x], smallestId[y]);
		parent[y] = x;
	}
}


void addMergeList (Rect& r1, Rect& r2)
{
	if (idRenameMap.find (r1.id) == idRenameMap.end())
		idRenameMap[r1.id] = idRenameGenerator++;
	if (idRenameMap.find (r2.id) == idRenameMap.end())
		idRenameMap[r2.id] = idRenameGenerator++;

	edge[edgecnt++] = make_pair (
		MergeInfo (idRenameMap[r1.id], r1.id, r1.area),
		MergeInfo (idRenameMap[r2.id], r2.id, r2.area)
		);
}


void renewAnswer (Rect& r)
{
	rectCnt++;
	if (rectMaxArea < *r.area)
		rectMaxArea = *r.area;

	freeBuffer (r.area);
	freeBuffer (r.refCnt);
}


void preprocess ()
{
	for (int i=0; i<n; i++) {
		rectangle[i][1] *= 2;
		rectangle[i][3] *= 2;
	}
}


int binary_search (int* x, int n, int v)
{
	int low=0, high=n-1, mid;
	while (low<=high) {
		mid = (low+high) / 2;
		if (x[mid]==v) return mid;
		if (x[mid]<v) low = mid+1;
		else high = mid-1;
	}
	return -1;
}


void plane_sweeping ()
{
	xcnt = ycnt = 0;

	x[xcnt++] = MIN_COORD;
	x[xcnt++] = MAX_COORD;
	y[ycnt++] = MIN_COORD;
	y[ycnt++] = MAX_COORD;

	for (int i=0; i<n; i++) {
		x[xcnt++] = rectangle[i][0];
		x[xcnt++] = rectangle[i][2];

		y[ycnt++] = rectangle[i][1];
		y[ycnt++] = rectangle[i][3];
	}

	sort(x, x+xcnt);
	sort(y, y+ycnt);

	for (int i = (ycnt-1) / (K-1) * (K-1); i > 0; i -= K-1)
		y[ycnt++] = y[i] + 1;

	sort(y, y+ycnt);

	for (int i=0; i<n; i++) {
		rectangle[i][0] = binary_search (x, xcnt, rectangle[i][0]);
		rectangle[i][1] = binary_search (y, ycnt, rectangle[i][1]);
		rectangle[i][2] = binary_search (x, xcnt, rectangle[i][2]);
		rectangle[i][3] = binary_search (y, ycnt, rectangle[i][3]);
	}
}


void make_vertical_lines ()
{
	linecnt = 0;
	for (int i=0; i<n; i++) {
		line[linecnt++] = VerticalLine(rectangle[i][0], rectangle[i][1], rectangle[i][3], true);
		line[linecnt++] = VerticalLine(rectangle[i][2], rectangle[i][1], rectangle[i][3], false);
	}

	sort (line, line + linecnt);
}


EventType specify_type (int y0, int y1, const VerticalLine& l)
{
	if (l.y1 < y0 || l.y0 > y1)
		return EVENT_OUT_OF_RANGE;

	if (l.y0 < y0 && l.y1 > y1)
		return TYPE1;

	if (l.y0 < y0)
		return l.left ? TYPE2_ADD : TYPE2_DELETE;

	if (l.y1 > y1)
		return l.left ? TYPE3_ADD : TYPE3_DELETE;

	return l.left ? TYPE4_ADD : TYPE4_DELETE;
}


void setLeftDown (EventType type, int m, int start, int y0, int y1, bool* left, bool* down)
{
	switch (type) {
	case EVENT_OUT_OF_RANGE:
		break;

	case TYPE1:
		break;

	case TYPE2_ADD:
		for (int j=0; j<m; j++) {
			left[j] = start+j < y1 ? false : true;
			if (start+j == y1)
				down[j] = false;
		}
		break;

	case TYPE2_DELETE:
		for (int j=0; j<m; j++) {
			left[j] = start+j < y1 ? false : true;
			if (start+j == y1)
				down[j] = true;
		}
		break;

	case TYPE3_ADD:
		for (int j=0; j<m; j++) {
			left[j] = start+j >= y0 ? false : true;
			if (start+j == y0)
				down[j] = false;
		}
		break;

	case TYPE3_DELETE:
		for (int j=0; j<m; j++) {
			left[j] = start+j >= y0 ? false : true;
			if (start+j == y0)
				down[j] = true;
		}
		break;

	case TYPE4_ADD:
		for (int j=0; j<m; j++) {
			left[j] = start+j >= y0 && start+j < y1 ? false : true;
			if (start+j == y0 || start+j == y1)
				down[j] = false;
		}
		break;

	case TYPE4_DELETE:
		for (int j=0; j<m; j++) {
			left[j] = start+j >= y0 && start+j < y1 ? false : true;
			if (start+j == y0 || start+j == y1)
				down[j] = true;
		}
		break;
	}
}


void sweepNextEvent (int xidx, int m, int start, bool* left, bool* down, Rect rectLeft[], Rect rectBottom[])
{
	long long xlen = x[xidx+1] - x[xidx];

	for (int i=0; i<m; i++) {
		long long area = xlen * (y[start+i+1] - y[start+i]);

		Rect& rectCur = i<m-1 ? rectLeft[i] : rectBottom[xidx];
		Rect& d = i ? rectLeft[i-1] : rectBottom[xidx];
		Rect& l = i<m-1 ? rectLeft[i] : rectBottom[xidx-1];

		if (i==0) {
			(*rectBottom[xidx].refCnt) --;
			// K even ==> refCnt should be > 0
		}

		if (left[i] && down[i]) {
			if (d.id == l.id) {
				rectCur = l;
				if (i==m-1) (*rectCur.refCnt) ++;
				*rectCur.area += area;
			}

			else {
				// ㄱ자로 꺾어지는 부분에서만 merge가 일어난다
				if (i && !left[i-1]) {
					// merge되는 rect num들을 map에 저장한다
					addMergeList (l, d);


					// refCnt는 1 이상으로 남겨둬야
					//  현재까지 구한 area 정보가 맵에 계속 남는다.
					(*l.refCnt) ++;
					(*d.refCnt) ++;
				}

				if (i < m-1) {
					(*l.refCnt) --;
					if (*l.refCnt == 0)
						renewAnswer (l);
				}

				rectCur = d;
				*rectCur.area += area;
				(*rectCur.refCnt) ++;

			}
		}

		else if (left[i]) {
			rectCur = l;
			if (i==m-1) (*rectCur.refCnt) ++;
			*rectCur.area += area;
		}

		else if (down[i]) {
			if (i < m-1) {
				(*l.refCnt) --;
				if (*l.refCnt == 0)
					renewAnswer (l);
			}

			rectCur = d;
			*rectCur.area += area;
			(*rectCur.refCnt) ++;
		}

		else {
			if (i < m-1) {
				(*l.refCnt) --;
				if (*l.refCnt == 0)
					renewAnswer (l);
			}

			rectCur = Rect(area); // constructor에서 refCnt = 1
		}
	}
}


void solve_in_band (int start, int end, Rect rectFromBottom[])
{
	// 연결 정보를 나타냄. true: 연결됨
	static bool left[K], down[K];

	// 왼쪽의 직사각형 영역 정보를 나타냄
	static Rect rectLeft[K];

	EventType prevType = EVENT_OUT_OF_RANGE;
	SpecialCaseType specialType = SPECIAL_UNDEFINED;

	long long rectCntSpecialCase = 0;
	long long rectMaxY_SpecialCase = 0;
	long long rectCurX_Length = 0;
	long long rectUpperY_SpecialCase = 0;
	long long rectLowerY_SpecialCase = 0;

	int m = end - start;

	int s = 0, e = 0;

	for (int i=0; i<m; i++) {
		left[i] = down[i] = true;
		rectLeft[i] = rectFromBottom[0];
		(*rectLeft[i].refCnt) ++;
	}

	for (int i=0; i<linecnt; i++) {
		EventType curType = specify_type (start, end, line[i]);


		// line 없음 ->
		if (curType == EVENT_OUT_OF_RANGE) {
			//  1. 다음 event로 x좌표 연장
			rectCurX_Length += x[line[i].x+1] - x[line[i].x];

			//  2. rectFromBottom은 따로 계산: O(1)
			if (true) {
				(*rectFromBottom[line[i].x].refCnt) --;
				if (*rectFromBottom[line[i].x].refCnt == 0)
					renewAnswer (rectFromBottom[line[i].x]);

				rectFromBottom[line[i].x] = rectFromBottom[line[i-1].x];
				(*rectFromBottom[line[i].x].refCnt) ++;
			}
		}

		else if (curType == TYPE1) {
			// special case: O(1)
			if (prevType == TYPE1) {
				// rectFromBottom은 따로 계산: O(1)
				switch (specialType) {
					// 가로선이 없으면
				case SPECIAL_TYPE1:
					*rectFromBottom[line[i-1].x].area += rectCurX_Length * (y[end] - y[start]);
					break;

					// 가로선이 하나 또는 여러개
				case SPECIAL_TYPE2:
				case SPECIAL_TYPE3:
					*rectLeft[0].area += rectCurX_Length * rectLowerY_SpecialCase;
					*rectFromBottom[line[i-1].x].area += rectCurX_Length * rectUpperY_SpecialCase;

					(*rectLeft[0].refCnt) --;
					if (*rectLeft[0].refCnt == 0)
						renewAnswer (rectLeft[0]);

					rectLeft[0] = rectFromBottom[line[i].x];
					(*rectLeft[0].refCnt) ++;

					(*rectFromBottom[line[i].x].refCnt) --;
					if (*rectFromBottom[line[i].x].refCnt == 0)
						renewAnswer (rectFromBottom[line[i].x]);

					rectFromBottom[line[i].x] = Rect(0);
					break;
				}


				// rectCnt에 사각형개수 한꺼번에 더하기: O(1)
				rectCnt += rectCntSpecialCase;

				// rectMaxArea에 사각형 최대 넓이 한번에 갱신: O(1)
				if (rectMaxArea < rectMaxY_SpecialCase * rectCurX_Length)
					rectMaxArea = rectMaxY_SpecialCase * rectCurX_Length;

				// rectCurX_Length: x좌표 새로 시작
				rectCurX_Length = x[line[i].x+1] - x[line[i].x];
			}

			// 처음으로 TYPE1이 나온 경우
			else {
				setLeftDown (curType, m, start, line[i].y0, line[i].y1, left, down);


				for (int j=0; j<m-1; j++)
					*rectLeft[j].area += (y[start+j+1] - y[start+j]) * rectCurX_Length;
				*rectFromBottom[line[i-1].x].area += (y[end] - y[end-1]) * rectCurX_Length;
				rectCurX_Length = 0;


				// 다음번 TYPE1 event에서 사용할 변수 갱신: O(k)

				// rectCntSpecialCase
				rectCntSpecialCase = -1;
				for (int j=1; j<m; j++)
					if (!down[j])
						rectCntSpecialCase ++;

				// rectMaxY_SpecialCase, rectCurX_Length
				rectCurX_Length = x[line[i+1].x] - x[line[i].x];

				s = e = 0;
				for (int j=1; j<m; j++) {
					if (!down[j]) {
						if (!s) s = j;
						e = j;
					}
				}

				if (s > 0) {
					specialType = SPECIAL_TYPE3;

					long long consecutiveY_Length = 0;
					for (int j=s; j<e; j++) {
						if (!down[j]) consecutiveY_Length = 0;
						consecutiveY_Length += y[start+j+1] - y[start+j];

						if (rectMaxY_SpecialCase < consecutiveY_Length)
							rectMaxY_SpecialCase = consecutiveY_Length;
					}
				}
				else {
					specialType = SPECIAL_TYPE1;
					rectCntSpecialCase = 0;
					rectMaxY_SpecialCase = 0;
				}

				// rectFromBottom과 rectLeft[0]은 따로 계산: O(k)
				//  만약 가로선이 하나 이상 존재한다면,
				if (specialType == SPECIAL_TYPE2 || specialType == SPECIAL_TYPE3) {
					// rectLowerY_SpecialCase, rectUpperY_SpecialCase
					rectLowerY_SpecialCase = y[start+s] - y[start];
					rectUpperY_SpecialCase = y[end] - y[start+e];

					//    rectLeft에 있는 사각형들 모두 ref 제거
					for (int j=0; j<m-1; j++) {
						(*rectLeft[j].refCnt) --;
						if (*rectLeft[j].refCnt == 0)
							renewAnswer (rectLeft[j]);

						// 의미없는 영역
						rectLeft[j] = Rect();
					}

					//    rectLeft[0]을 갱신. 이것만 bottom으로 유지해둔다
					rectLeft[0] = rectFromBottom[line[i].x];
					(*rectLeft[0].refCnt) ++;

					//    rectFromBottom에 해당하는 사각형 새로 생성
					(*rectFromBottom[line[i].x].refCnt) --; // it should be > 0
					rectFromBottom[line[i].x] = Rect(0);
				}

				//  가로선이 없다면
				else {
					//   rectFromBottom은 그대로 유지하고,
					//   모든 rectLeft의 ref 제거
					for (int j=0; j<m-1; j++) {
						(*rectLeft[j].refCnt) --;
						if (*rectLeft[j].refCnt == 0)
							renewAnswer (rectLeft[j]);

						rectLeft[j] = Rect();
					}
				}
			}
		}

		// general case: O(k)
		else {
			if (prevType == TYPE1) {
				// TYPE1을 처리할 때 rectLeft를 -1로 만들었었다
				//  rectLeft를 복구해야 한다

				// 가로선이 있다면
				if (specialType == SPECIAL_TYPE2 || specialType == SPECIAL_TYPE3) {
					for (int j=1; j<s; j++) {
						rectLeft[j] = rectLeft[j-1];
						(*rectLeft[j].refCnt) ++;
					}
					for (int j=e; j<m-1; j++) {
						rectLeft[j] = rectFromBottom[line[i-1].x];
						(*rectLeft[j].refCnt) ++;
					}

					for (int j=s; j<e; j++) {
						if (!down[j])
							rectLeft[j] = Rect(0);
						else {
							rectLeft[j] = rectLeft[j-1];
							(*rectLeft[j].refCnt) ++;
						}
					}
				}

				// 가로선이 없다면
				else {
					rectLeft[0] = rectFromBottom[line[i-1].x];
					(*rectLeft[0].refCnt) ++;
					for (int j=1; j<m-1; j++) {
						rectLeft[j] = rectLeft[j-1];
						(*rectLeft[j].refCnt) ++;
					}
				}
			}


			setLeftDown (curType, m, start, line[i].y0, line[i].y1, left, down);


			for (int j=0; j<m-1; j++)
				*rectLeft[j].area += (y[start+j+1] - y[start+j]) * rectCurX_Length;
			*rectFromBottom[line[i-1].x].area += (y[end] - y[end-1]) * rectCurX_Length;
			rectCurX_Length = 0;

			sweepNextEvent (line[i].x, m, start, left, down, rectLeft, rectFromBottom);
		}


		if (curType != EVENT_OUT_OF_RANGE)
			prevType = curType;
	}
}


pair<long long, long long> solve_n_sqrt_n ( int arg_n, int arg_rectangle[][4] )
{
	n = arg_n;
	memcpy (rectangle, arg_rectangle, sizeof(int) * 4 * arg_n);

	xcnt = ycnt = linecnt = 0;
	rectCnt = rectMaxArea = 0;
	Rect::_id_generator = 0;
	idRenameGenerator = 0;
	idRenameMap.clear();
	edgecnt = 0;

	top = 0;
	for (int i=0; i<n*4; i++)
		freeBuffer (buffer + i);

	preprocess () ;

	plane_sweeping () ;
	make_vertical_lines () ;
	
	static Rect rectAbove[MAX_N * 2 + 2];

	Rect::_id_generator = 0;
	rectAbove[0] = Rect (0);
	*rectAbove[0].refCnt = MAX_N;
	for (int i=1; i<xcnt; i++) {
		rectAbove[i] = rectAbove[0];
		(*rectAbove[i].refCnt) ++;
	}

	for (int i=0; i<ycnt-1; i+=K) {
		int band_end = i+K <= ycnt ? i+K : ycnt;
		solve_in_band (i, band_end, rectAbove);
	}

	// 각 band마다 문제 풀 때 merge된 사각형들만 골라서 다시 계산 O(n)
	for (int i=0; i<idRenameGenerator; i++)
		parent[i] = i;

	for (int i=0; i<edgecnt; i++) {
		long long x1 = edge[i].first.id;
		long long x2 = edge[i].second.id;
		long long a1 = *edge[i].first.area;
		long long a2 = *edge[i].second.area;

		area[x1] = a1;
		area[x2] = a2;
		smallestId[x1] = edge[i].first.oid;
		smallestId[x2] = edge[i].second.oid;
	}

	for (int i=0; i<edgecnt; i++) {
		long long x1 = edge[i].first.id;
		long long x2 = edge[i].second.id;

		merge (root(x1), root(x2));
	}

	for (int i=0; i<idRenameGenerator; i++) {
		if (i == parent[i] && smallestId[i] != 0) {
			rectCnt++;
			if (rectMaxArea < area[i])
				rectMaxArea = area[i];
		}
	}

	return make_pair(rectCnt, rectMaxArea / 2);
}




static int test_n = 0;
static int test_rectangle[MAX_N][4];


static void getInput ()
{
	scanf ("%d", &test_n);
	for (int i=0; i<test_n; i++) {
		scanf ("%d%d%d%d", 
			&test_rectangle[i][0],
			&test_rectangle[i][1],
			&test_rectangle[i][2],
			&test_rectangle[i][3]
		);
	}
}


int main()
{
	getInput ();
	pair<long long, long long> ans = 
		solve_n_sqrt_n (test_n, test_rectangle);
	printf ("%lld %lld\n", ans.first, ans.second);
	return 0;
}

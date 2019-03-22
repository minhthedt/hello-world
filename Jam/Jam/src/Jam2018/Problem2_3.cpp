#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <unordered_set>
#include <utility>      // std::pair, std::make_pair
using namespace std;

namespace Jam2018
{
#define uint64 unsigned int
    namespace BruteForce
    {
        class Vertice
        {
        public:
            uint64 x, y;
            bool wasChecked;
            Vertice(uint64 x, uint64 y) : x(x), y(y), wasChecked(false) {};
            std::vector<Vertice*> childrens;
            void tryAddNode(Vertice* nd)
            {
                if (y == nd->x)
                {
                    childrens.push_back(nd);
                }
            }
        };

        void Find(uint64 first, Vertice* root, uint64 depth, uint64& result)
        {
        	//printf("find\n");
            root->wasChecked = true;
            if (depth == 0)
            {
                uint64 sum = first * root->y;
                result = result < sum ? sum : result;
                root->wasChecked = false;
                return;
            }

            std::vector<Vertice*> vertices = root->childrens;
            for (uint64 i = 0; i < vertices.size(); i++)
            {
                if (vertices[i]->wasChecked == false)
                {
                    Find(first, vertices[i], depth - 1, result);
                }

            }

            root->wasChecked = false;
        }

        void Run_Problem2_3(const char* inputPath)
        {
        	auto begin = chrono::high_resolution_clock::now();

            printf("Problem 3: %s\n", inputPath);
            uint64 n, x, y;

            FILE *fi = fopen(inputPath, "r");

            fscanf(fi, "%dll", &n);

            std::vector<Vertice*> vertices;
            vertices.reserve(n);

            for (uint64 i = 0; i < n; i++)
            {
                fscanf(fi, "%dll", &x);
                fscanf(fi, "%dll", &y);

                Vertice* node = new Vertice(x, y);
                for (uint64 j = 0; j < vertices.size(); j++)
                {
                    vertices[j]->tryAddNode(node);
                    node->tryAddNode(vertices[j]);
                }
                vertices.push_back(node);

                printf("n = %d\n",i);
                uint64 result = 0;
                for (uint64 k = 0; k < vertices.size(); k++)
				{
					Find(vertices[k]->x, vertices[k], vertices.size() - 1, result);
				}

                cout  << result << endl;
            }

            printf("finish Problem 3\n");


            fclose(fi);

            for (uint64 i = 0; i < vertices.size(); i++)
            {
                delete vertices[i];
            }
			auto end = chrono::high_resolution_clock::now();
			auto dur = end - begin;
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
			cout << ms <<" ms"<< endl;
        }
    }
//[2019.03.14] http://collab.lge.com/main/pages/viewpage.action?pageId=878214072
//Actually, we don't have to traverse graph to find Eulerian path. We can just using the properties of Eulerian path(or Eulerian trail) instead.
//
//The properties of Eulerian path are shown below,
//
//Definition in directed graph
//- in-degree: # of edges incoming to the vertex
//- out-degree : # of edges outgoing from the vertex
//
//Definition of Eulerian cycle in directed graph
//: The path in directed graph forms a cycle(starting vertex is same as ending vertex) that uses each edge exactly once.
//
//A directed graph has an Eulerian cycle if and only if every vertex has equal in-degree and out-degree, and all of its vertices with nonzero degree belong to a single strongly connected component.
//
//A directed graph has an Eulerian trail if and only if,
//- at most one vertex has (out-degree) − (in-degree) = 1, which is starting vertex
//- at most one vertex has (in-degree) − (out-degree) = 1, which is ending vertex
//- every other vertex has equal in-degree and out-degree
//- all of its vertices with nonzero degree belong to a single connected component of the underlying undirected graph.
//[2019.03.18] the.vu: OK to understand
    namespace GraphTraversal
    {

		class Vertex {
		public:
			int num;
			int deg;
			int odr;
			std::unordered_set<Vertex*> edge;

			Vertex(int v) {
				num = v;
				deg = 0;
				odr = 0;
			}
		};

		class Graph {
			vector<Vertex*> m;

		  public:
			Graph(int n) {
				m.resize(n, NULL);
			}

			virtual ~Graph() {
				for (auto& vt : m) {
					if (vt)  delete vt;
				}
			}

			void addEdge(int loop, int from, int to) {
				if (!m[from]) m[from] = new Vertex(from);
				if (!m[to]) m[to] = new Vertex(to);

				m[from]->edge.insert(m[to]);
				m[from]->deg -= 1;
				m[from]->odr = loop;

				m[to]->edge.insert(m[from]);
				m[to]->deg += 1;
				m[to]->odr = loop;
			}

			int checkEulerian(int loop) {
				int from = -1;
				int to = -1;

				// check whether given graph has eulerian path(or cycle) or not
				//- at most one vertex has (out-degree) − (in-degree) = 1, which is starting vertex
				//- at most one vertex has (in-degree) − (out-degree) = 1, which is ending vertex
				//- every other vertex has equal in-degree and out-degree
				for (auto& vt : m) {
					if (vt && vt->deg) {
						if (vt->deg == -1) {
							if (from<0) {
								from = vt->num;
							} else {
								return 0;
							}
						} else if (vt->deg == 1) {
							if (to<0) {
								to = vt->num;
							} else {
								return 0;
							}
						} else {
							return 0;
						}
					}
				}

				// All the connected nodes have same indegree & outdegree.
				// This means connected nodes can be formed as an eulerian cycle.
				// So, we can choose a vertex having maximum number as starting & ending point
				if (from < 0 && to < 0) {
					int p = m.size() - 1;
					while (!m[p]) p--;//m[p]->num = p
					from = to = p;
				}

				// Now, check whether given graph is fully connected
				//      and update these connected nodes to use next stage
				//đoạn này đơi giản giống BFS duyệt tree nhưng loại bỏ các node đã duyệt trước đó
				//Mỗi vertice sau khi được visited sẽ có odr > loop
				queue<Vertex*> q;
				q.push(m[from]);
				while (!q.empty()) {
					Vertex* t = q.front();
					q.pop();
					t->odr = loop+1;

					for (auto& u : t->edge) {
						if (u && u->odr <= loop) {
							q.push(u);
						}
					}
				}

				//nếu tồn tại vertice chưa được duyệt => all Not connected
				for (auto& vt : m) {
					if (vt && vt->odr <= loop) return 0;
				}

				return (from + 1) * (to + 1);
			}
		};

		void Run_Problem2_3(const char* inputPath)
		{
			//fopen dùng để mở 1 file, và trả về 1 stream liên kết với file đó để cho phép hàm thao tác trên stream này
			//freopen dùng để sử dụng lại stream, đóng liên kết stream với file cũ và liên kết lai với file mới
			//nếu gọi freopen với file cũ thì có tác dụng thay đổi mode
			auto begin = chrono::high_resolution_clock::now();

			FILE* file = freopen(inputPath, "r", stdin);
			if(file)
			{
				int n;
				cin >> n;

				Graph g(1000);
				int r, c;
				for (int i = 1; i <= n; ++i) {
					cin >> r >> c;
					r--, c--;

					g.addEdge(i, r, c);
					cout << g.checkEulerian(i) << endl;
				}

				fclose (stdin);
			}

			auto end = chrono::high_resolution_clock::now();
			auto dur = end - begin;
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
			cout << ms <<" ms"<< endl;

		};
    }

    void Problem2_3()
    {
        //Run_Problem2_3(DATA_PROBLEM_2018_2_301);
        //Run_Problem2_3(DATA_PROBLEM_2018_2_310);
        //Run_Problem2_3(DATA_PROBLEM_2018_2_311);
        //Run_Problem2_3(DATA_PROBLEM_2018_2_313);
        //BruteForce::Run_Problem2_3("D:\\Training\\github\\data\\2018_round2\\C\\subtask2\\C-data-043.in");
    	GraphTraversal::Run_Problem2_3("D:\\Training\\github\\data\\2018_round2\\C\\subtask2\\C-data-043.in");

    }
}

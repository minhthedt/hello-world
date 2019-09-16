#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

enum {MIN_X=0, MAX_X, MIN_Y, MAX_Y};

int min_x_y(vector<tuple<int, int>>& coord, vector<int>& idx) {
    int min_x_val = 100000001;
    int max_x_val = -min_x_val;
    int min_y_val = min_x_val;
    int max_y_val = max_x_val;

    for (int i = 0; i < coord.size(); ++i) {
        int x = get<0>(coord[i]);
        int y = get<1>(coord[i]);

        if (x < min_x_val) {
            min_x_val = x;
            idx[MIN_X] = i;
        }

        if (x > max_x_val) {
            max_x_val = x;
            idx[MAX_X] = i;
        }

        if (y < min_y_val) {
            min_y_val = y;
            idx[MIN_Y] = i;
        }
        if (y > max_y_val) {
            max_y_val = y;
            idx[MAX_Y] = i;
        }
    }

    return max(max_x_val - min_x_val, max_y_val - min_y_val);
}

int solve(vector<tuple<int, int>>& coord) {
    int answer = 200000001;

    auto remove1 = vector<int>(4, 0);
    auto remove2 = vector<int>(4, 0);
    auto remove3 = vector<int>(4, 0);
    auto remove4 = vector<int>(4, 0);

    answer = min(answer, min_x_y(coord, remove1));
    for (int i = 0; i < 4; ++i) {
        auto backup = coord[remove1[i]];
        coord.erase(coord.begin() + remove1[i]);

        answer = min(answer, min_x_y(coord, remove2));
        for (int j = 0; j < 4; ++j) {
            auto backup = coord[remove2[j]];
            coord.erase(coord.begin() + remove2[j]);

            answer = min(answer, min_x_y(coord, remove3));
            for (int k = 0; k < 4; ++k) {
                auto backup = coord[remove3[k]];
                coord.erase(coord.begin() + remove3[k]);

                answer = min(answer, min_x_y(coord, remove4));

                coord.insert(coord.begin() + remove3[k], backup);
            }

            coord.insert(coord.begin() + remove2[j], backup);
        }
        coord.insert(coord.begin() + remove1[i], backup);
    }

    return answer;
}

int main() {
    int problem;
    cin >> problem;

    while (problem --> 0) {
        int N;
        cin >> N;

        auto coord = vector<tuple<int, int>>(N);

        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            coord[i] = make_tuple(x, y);
        }

        cout << solve(coord) << endl;
    }

    return 0;
}

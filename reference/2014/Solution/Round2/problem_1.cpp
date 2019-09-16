#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int solve(vector<int>& minimum_frequency, vector<tuple<int, int>>& words) {
    int min_range = 0;

    int start = 0;
    auto frequency = vector<int>(minimum_frequency.size(), 0);

    int last = 0;
    for (int i = 0; i < minimum_frequency.size(); ++i) {
        while (frequency[i] < minimum_frequency[i] && last < words.size()) {
            int word_num = get<0>(words[last]);
            int word_pos = get<1>(words[last]);

            frequency[word_num]++;
            last++;
        }

        if (frequency[i] < minimum_frequency[i])
            return -1;
    }

    if (last == 0)
        return 0;

    min_range = get<1>(words[last-1]) - get<1>(words[start]) + 1;

    while (last < words.size()) {
        int idx = get<0>(words[start]);
        start++;
        frequency[idx]--;

        while (frequency[idx] < minimum_frequency[idx] && last < words.size()) {
            int word_num = get<0>(words[last]);
            int word_pos = get<1>(words[last]);

            frequency[word_num]++;
            last++;
        }

        if (frequency[idx] < minimum_frequency[idx])
            return min_range;

        min_range = min(min_range, get<1>(words[last-1]) - get<1>(words[start]) + 1);
    }

    return min_range;
}

int main() {
    int testcase = 0;
    cin >> testcase;

    while (testcase --> 0) {
        int N, K;
        cin >> N >> K;

        auto minimum_frequency = vector<int>(K);
        for (int i = 0; i < K; ++i)
            cin >> minimum_frequency[i];

        auto words = vector<tuple<int, int>>(N);
        for (int i = 0; i < N; ++i) {
            int word, pos;
            cin >> word >> pos;
            words[i] = make_tuple(word-1, pos);
        }

        cout << solve(minimum_frequency, words) << endl;
    }
}

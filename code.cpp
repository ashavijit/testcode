#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int abhimanyuPower, skips, regenerates;
int dp[12][12][12];

int dynamicProgramming(const vector<int>& monsters, int idx, int power, int a, int b) {
    if (idx == 11)
        return power;

    if (dp[idx][a][b] != -1)
        return dp[idx][a][b];

    if (monsters[idx] > power) {
        if (b > 0)
            dp[idx][a][b] = max(dp[idx][a][b], dynamicProgramming(monsters, idx, abhimanyuPower, a, b - 1));

        if (a > 0) {
            if (idx == 2 || idx == 6)
                monsters[idx + 1] += (monsters[idx] + monsters[idx] / 2);
            dp[idx + 1][a][b] = max(dp[idx + 1][a][b], dynamicProgramming(monsters, idx + 1, power, a - 1, b));
        }
    } else {
        dp[idx + 1][a][b] = max(dp[idx + 1][a][b], dynamicProgramming(monsters, idx + 1, power - monsters[idx], a, b));
    }

    return dp[idx][a][b];
}

int main() {
    cin >> abhimanyuPower >> skips >> regenerates;
    vector<int> monsters(11);
    for (int i = 0; i < 11; ++i)
        cin >> monsters[i];

    for (int i = 0; i <= 11; ++i)
        for (int j = 0; j <= skips; ++j)
            for (int k = 0; k <= regenerates; ++k)
                dp[i][j][k] = -1;

    int result = dynamicProgramming(monsters, 0, abhimanyuPower, skips, regenerates);

    for (int j = 0; j <= skips; ++j)
        for (int k = 0; k <= regenerates; ++k)
            if (dp[11][j][k] >= 0) {
                cout << "YES";
                return 0;
            }

    cout << "NO";
    return 0;
}

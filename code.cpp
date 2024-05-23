#include <iostream>
#include <vector>
#include <cstring>
#include <chrono>
#include <fstream>

using namespace std;

const int MOD = 1000000007;
const int N = 100005;

int initialPower;
int dp[20][201][20][20];

bool canWinWithMemoization(int index, int currentPower, int remainingSkips, int remainingHeals, vector<int> enemies)
{
  if (dp[index][currentPower][remainingSkips][remainingHeals] != -1)
    return dp[index][currentPower][remainingSkips][remainingHeals];

  if (index == enemies.size())
  {
    if (currentPower >= 0)
      return true;
    else
      return false;
  }

  bool isPossibleToWin = false;

  if (currentPower >= enemies[index])
    isPossibleToWin |= canWinWithMemoization(index + 1, currentPower - enemies[index], remainingSkips, remainingHeals, enemies);

  if (index == 2 || index == 6)
    enemies[index + 1] += enemies[index] / 2;

  if (remainingSkips > 0)
    isPossibleToWin = isPossibleToWin || canWinWithMemoization(index + 1, currentPower, remainingSkips - 1, remainingHeals, enemies);

  if (remainingHeals > 0)
    isPossibleToWin = isPossibleToWin || canWinWithMemoization(index, initialPower, remainingSkips, remainingHeals - 1, enemies);

  return dp[index][currentPower][remainingSkips][remainingHeals] = isPossibleToWin;
}

bool recursivelyFight(int index, int currentPower, int remainingSkips, int remainingHeals, vector<int> enemies)
{
  if (currentPower < 0)
    return false;

  if (index == enemies.size())
  {
    if (currentPower >= 0)
      return true;
    else
      return false;
  }
  else
  {
    bool isPossibleToWin = false;

    isPossibleToWin = isPossibleToWin || recursivelyFight(index + 1, currentPower - enemies[index], remainingSkips, remainingHeals, enemies);

    if (index == 2 || index == 6)
      enemies[index + 1] += enemies[index] / 2;

    if (remainingSkips > 0)
      isPossibleToWin = isPossibleToWin || recursivelyFight(index + 1, currentPower, remainingSkips - 1, remainingHeals, enemies);

    if (remainingHeals > 0)
      isPossibleToWin = isPossibleToWin || recursivelyFight(index, initialPower, remainingSkips, remainingHeals - 1, enemies);

    return isPossibleToWin;
  }
}

void solve()
{
  memset(dp, -1, sizeof dp);

  int numEnemies, initialPower, skipMoves, healMoves;
  cin >> numEnemies >> initialPower >> skipMoves >> healMoves;

  vector<int> enemies(numEnemies, 0);
  for (int i = 0; i < numEnemies; i++)
    cin >> enemies[i];

  bool canDefeatRec = recursivelyFight(0, initialPower, skipMoves, healMoves, enemies);
  bool canDefeat = canWinWithMemoization(0, initialPower, skipMoves, healMoves, enemies);

  cout << "\nRec : ";
  if (canDefeatRec)
    cout << "Won";
  else
    cout << "Lost";

  cout << " | MemoProcess : ";
  if (canDefeat)
    cout << "Won";
  else
    cout << "Lost";
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  // Take input from input.txt and output to output.txt
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int testCases;
  cin >> testCases;

  while (testCases--)
  {
    auto start = chrono::high_resolution_clock::now();
    solve();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
  }

  return 0;
}

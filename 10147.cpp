#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int find(vector<int> &C, int x) { return (C[x] == x) ? x : C[x] = find(C, C[x]); }
void merge(vector<int> &C, int x, int y) { C[find(C, x)] = find(C, y); }

int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    int n;
    cin >> n;
    vector<pair<int, int>> loc(n);
    for (int i = 0; i < n; i++)
    {
      int x, y;
      cin >> x >> y;
      loc[i] = make_pair(x, y);
    }

    vector<int> s(n);
    for (int i = 0; i < n; i++)
      s[i] = i;

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
      int x, y;
      cin >> x >> y;
      merge(s, x - 1, y - 1);
    }

    vector<pair<int, pair<int, int>>> e;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (i != j && find(s, i) != find(s, j))
        {
          int t1 = abs(loc[i].first - loc[j].first);
          int t2 = abs(loc[i].second - loc[j].second);
          int dist = t1 * t1 + t2 * t2;
          e.push_back(make_pair(dist, make_pair(i, j)));
        }
      }
    }

    sort(e.begin(), e.end());

    bool build = false;
    for (int i = 0, size = e.size(); i < size; i++)
    {
      int x = e[i].second.first, y = e[i].second.second;
      if (find(s, x) != find(s, y))
      {
        build = true;
        merge(s, x, y);
        cout << x + 1 << " " << y + 1 << endl;
      }
    }

    if (!build)
      cout << "No new highways need" << endl;

    if (t != 0)
      cout << endl;
  }
}
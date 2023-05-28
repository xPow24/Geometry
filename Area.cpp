//https://oj.vnoi.info/problem/area
//https://vnoi.info/wiki/algo/geometry/Sweep-Line.md

#include<bits/stdc++.h>
#define vi vector<int>
#define vl vector<long long>
#define ll long long
#define all(x) x.begin(), x.end()
#define SZ(x) (int)x.size()
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define FORREV(i, a, b) for (int i = a; i >= b; --i)
using namespace std;
const int MX = 30000;

struct Segment {
  int x, y1, y2, id;
  bool operator < (const Segment& other) const {
    return x < other.x;
  }
};

struct SegmentTree {
  vector<pair<int, int>> s;
  SegmentTree(int N) : s(4 * N + 5) {
    FOR(i, 0, 4 * N) s[i] = {0, 0};
  }
  void update(int id, int l, int r, int nl, int nr, int type) {
    if (nr < l || r < nl) return;
    if (nl <= l && r <= nr) {
      s[id].second += type;
      if (s[id].second) s[id].first = r - l + 1;
      else if (l != r) s[id].first = s[id * 2].first + s[id * 2 + 1].first;
      else s[id].first = 0;
      return;
    }
    int mid = (l + r) >> 1;
    update(id * 2, l, mid, nl, nr, type);
    update(id * 2 + 1, mid + 1, r, nl, nr, type);
    if (!s[id].second) s[id].first = s[id * 2].first + s[id * 2 + 1].first;
  }
};

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  vector<Segment> s;
  int N; cin >> N;
  FOR(i, 1, N) {
    int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
    s.push_back({x1, y1, y2, 1});
    s.push_back({x2, y1, y2, -1});
  }
  sort(all(s));
  SegmentTree ST(MX);
  int res = 0;
  FOR(i, 0, SZ(s) - 2) {
    ST.update(1, 0, MX, s[i].y1, s[i].y2 - 1, s[i].id);
    res += (s[i + 1].x - s[i].x) * ST.s[1].first;
  }
  cout << res;
}

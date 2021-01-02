#include <iostream>
#include<stack>
#include <queue>
#include <algorithm>
using namespace std;

#define __sz(x) ((int)(x).size())
typedef long long ll;

const int maxN = 200 * 1000 + 10;
pair<int, int> a[maxN];
int nx[maxN];

stack<int> curr;
int main() {
	// capacity , num of cities
	int  n, m;
	cin >> m;
	//getting distances and costs in stations
	for (int i = 0; i < m; i++)
		cin >> a[i].first;
	for (int i = 0; i < m; i++)
		cin >> a[i].second;
	sort(a, a + m);
	cin >> n;
	a[m].first = a[m-1].first;
	curr.push(m);
	for (int i = m - 1; i >= 0; i--) {
		while (curr.size() > 1 && a[curr.top()].second >= a[i].second)
			curr.pop();
		nx[i] = curr.top();
		curr.push(i);
	}
	int fuel = n;
	ll cost = 0;
	for (int i = 0; i <= m; i++) {
		fuel -= a[i].first - (i ? a[i - 1].first : 0);
		if (fuel < 0) {
			cout << -1 << endl;
			return 0;
		}
		if (i == m) break;
		int x = min(n - fuel, max(0, a[nx[i]].first - a[i].first - fuel));
		fuel += x;
		cost += a[i].second * 1ll * x;
	}
	cout << cost << endl;
}

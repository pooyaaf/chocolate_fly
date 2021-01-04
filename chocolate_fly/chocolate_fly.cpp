#include <iostream>
#include<stack>
#include <queue>
#include <algorithm>
using namespace std;

#define __sz(x) ((int)(x).size())
typedef long long ll;

const int maxN = 200 * 1000 + 10;
pair<int, int> a[maxN];


namespace A
{
	


	int partition(pair<int, int>* arr, int low, int high)
	{
		int pivot = arr[high].first;  
		int i = (low - 1);   

		for (int j = low; j <= high - 1; j++)
		{
			if (arr[j].first < pivot)
			{
				i++;
				pair<int, int> temp(arr[i].first, arr[i].second);
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
		pair<int, int> temp(arr[i + 1].first, arr[i + 1].second);
		arr[i + 1] = arr[high];
		arr[high] = temp;
		return (i + 1);
	}

	
	void quickSort(pair<int, int>* arr, int low, int high)
	{
		if (low < high)
		{
			
			int pi = partition(arr, low, high);

			quickSort(arr, low, pi - 1);
			quickSort(arr, pi + 1, high);
		}
	}

}


int nx[maxN];

stack<int> curr;
int main() {

	// capacity , num of cities
	int  n, m;
	cin >> m;
	for (int i = 0; i < m; i++)
		cin >> a[i].first;
	for (int i = 0; i < m; i++)
		cin >> a[i].second;

	A::quickSort(&a[0], 0, m);


	for (int i{ 0 }; i < m; ++i)
	{
		a[i] = a[i + 1];
	}
	a[m] = { 0,0 };


	cin >> n;
	a[m].first = a[m - 1].first;
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


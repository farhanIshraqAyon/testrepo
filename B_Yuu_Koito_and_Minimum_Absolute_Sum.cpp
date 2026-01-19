#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
#define for1(i, n) for (int i = 1; i <= (int)n; ++i)
#define fore(i, l, r) for (int i = (int)l; i <= (int)r; ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fored(i, l, r) for (int i = (int)r; i >= (int)l; --i)
#define pb push_back
#define el '\n'
#define db(x) cout << #x << " " << x << el
#define ri(n) scanf("%d", &n)
#define sz(v) int(v.size())
#define all(v) v.begin(), v.end()

using namespace std;

typedef long long ll;
typedef double ld;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<ld> vd;

const int inf = 1e9;
const int nax = 1e5 + 200;
const ld pi = acos(-1);
const ld eps = 1e-9;

int dr[] = {1, -1, 0, 0, 1, -1, -1, 1};
int dc[] = {0, 0, 1, -1, 1, 1, -1, -1};

void solve()
{
    ll n;
    cin >> n;
    vll v(n);
    ll idx = -1;
    forn(i, n)
    {
        cin >> v[i];
        if (v[i] == -1)
        {
            idx = i;
        }
    }
    ll val = 0;
    if (v[0] == -1 && v[n - 1] == -1)
    {
        v[0] = 0;
        v[n-1] = 0;
    }
    else if (v[0] == -1 || v[n - 1] == -1)
    {
        val = max(v[0], v[n - 1]);
        v[0] = val;
        v[n - 1] = val;
    }
    for (int i = 1; i < n - 1; i++)
    {
        if (v[i] == -1)
        {
            v[i] = 0;
        }
    }
    cout << abs(v[n - 1] - v[0]) << el;
    forn(i, n)
    {
        cout << v[i] << " ";
    }
    cout << el;
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << setprecision(20) << fixed;
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
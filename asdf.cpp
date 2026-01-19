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
const ll MOD = 1e9 + 7;

int dr[] = {1, -1, 0, 0, 1, -1, -1, 1};
int dc[] = {0, 0, 1, -1, 1, 1, -1, -1};

void solve()
{
    ll n;
    cin >> n;
    vll a(n);
    vll ap(n);
    forn(i, n)
    {
        cin >> a[i];
    }
    forn(i, n)
    {
        cin >> ap[i];
    }
    ll l = 0;
    ll r = 0;
    ll diff = 0;
    for (ll i = 0; i < n - 1; i++)
    {
        if (ap[i] <= ap[i + 1])
        {
            ll tmpL = i;
            ll tmpR;
            while (i < n - 1 && a[i] != ap[i + 1])
            {
                tmpR = i + 1;
                i++;
            }
            i--;
            if (diff < abs(tmpR - tmpL))
            {
                diff = abs(tmpR - tmpL);
                l = tmpL;
                r = tmpR;
            }
        }
    }
    cout<<l+1<<" "<<r+1<<el;
    return;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << setprecision(20) << fixed;
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
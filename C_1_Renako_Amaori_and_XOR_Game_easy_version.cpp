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
    vll a(n), b(n);
    ll cntA = 0;
    ll cntB = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] == 1)
        {
            cntA++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        if (b[i] == 1)
        {
            cntB++;
        }
    }
    ll ap = (cntA % 2);
    ll bp = (cntB % 2);
    ll ai = -1;
    ll bi = -1;
    //cout<<ap<<" "<<bp<<el;
    forn(i, n)
    {
        if (a[i] != b[i])
        {
            if ((i + 1) % 2 == 1)
            {
                if (ap)
                {
                    if (bp)
                    {
                        bp = 0;
                    }
                    else
                    {
                        bp = 1;
                    }
                    ap = 0;
                }
                ai = i;
            }
            else
            {
                if (bp)
                {
                    if (ap)
                    {
                        ap = 0;
                    }
                    else
                    {
                        ap = 1;
                    }
                    bp = 0;
                }
                bi = i;
            }
        }
    }
    //cout<<ap<<" "<<bp<<el;
    if(ap == bp){
        cout<<"Tie"<<el;
        return;
    }
    else if(ap == 0){
        cout<<"Ajisai"<<el;
    }
    else{
        cout<<"Mai"<<el;
    }
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
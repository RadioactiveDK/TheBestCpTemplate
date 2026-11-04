// LIBRARIES
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// TYPEDEF
typedef long long ll;
typedef long double ld;

typedef vector< ll > vll;
typedef pair< ll, ll > pll;
typedef vector< pll > vpll;

typedef set< ll > setll;
typedef multiset< ll > msetll;

typedef map< ll, ll > mapll;
typedef map< string, ll > mapsll;

typedef priority_queue< ll > PQmax;
typedef priority_queue<ll, vll, greater< ll >> PQmin;

typedef stack< ll > Sll;
typedef queue< ll > Qll;
typedef deque< ll > Dll;

    // complex number
typedef complex< ll > Cll;
    // arg(c) for angle
    // polar(r,theta) for polar form

    // indexed set
typedef tree<ll, null_type, less< ll >, rb_tree_tag,
            tree_order_statistics_node_update> Isetll;
    // find_by_order returns an iterator to the element at a given position
    // auto x = s.find_by_order(2);
    // cout << *x << "\n"; // 7
    // n order_of_key returns the position of a given element
    // If the element does not appear in the set, we get the position that the element would have in the set
    // cout << s.order_of_key(7) << "\n"; // 2

// MACROS

    // basic
#define MOD 1000000007
#define PI (3.141592653589)
#define FOR(i,a,b) for(ll i = a; i < b; i++)
#define NESFOR(x,y) for(long long i=0;i<x;i++)for(long long j=0;j<y;j++)
#define GETLINE(str) getline(cin, s)

    // pair
#define F first
#define S second
#define MP make_pair

    // data structures
#define PB push_back
#define PoB pop_back
#define PF push_front
#define PoF pop_front
   
    // vector
#define take(v) for(ll i=0;i<v.size();i++) cin>>v[i]
#define takeS(start,v) for(ll i=start;i<v.size();i++) cin>>v[i]
#define show(v) for(autox x:v) cout<<x<<" ";
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()

    // funcitons
#define SORT(v) sort(v.begin(), v.end())
#define REV(v) reverse(v.begin(), v.end())

    // complex
#define X real()
#define Y imag()

// CLASSES
    // Binary Index Tree
class FenwickTree {
    public:
    vll FenwickTreeArr;
    ll n;
    vll &arr;

    // Update the FenwickTree at index i by adding delta
    void updateByAdding_(ll i, ll delta) {
        while (i <= n) {
            FenwickTreeArr[i] += delta;
            i += i & -i; // Move to next
        }
    }

    void updateArrByAdding(ll i, ll delta) {
        arr[i] += delta;
        updateByAdding_(i + 1, delta);
    }

    void fill(vll &arr){
        for (ll i = 1; i <= n; ++i) {
            updateByAdding_(i, arr[i-1]);
        }
    }

    FenwickTree(vll &arr) : arr(arr), n(arr.size()) {
        FenwickTreeArr.resize(n + 1, 0);
        fill(arr);
    }

    // Get the prefix sum from 1 to i
    ll prefixSum(ll i) const {
        ll sum = 0;
        while (i > 0) {
            sum += FenwickTreeArr[i];
            i -= i & -i; // Move to parent
        }
        return sum;
    }

    // Get the sum of elements in range [l, r]
    ll rangeSumInclusive(ll l, ll r) const {
        return prefixSum(r+1) - prefixSum(l);
    }
};




void solve(){
    // code
}

int main(){
    // to make input output more efficient
    ios::sync_with_stdio(0);
    cin.tie(0);
    // for io using files
    FILE *fp = fopen("input.txt", "r");
    if(fp!=NULL){
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    ll t=1;
    cin>>t;
    while(t--) {
        solve();
        cout<<endl;
    }
    return 0;
}
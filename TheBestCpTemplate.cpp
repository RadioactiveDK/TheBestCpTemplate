// libraries
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
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()

    // funcitons
#define SORT(v) sort(v.begin(), v.end())
#define REV(v) reverse(v.begin(), v.end())

    // complex
#define X real()
#define Y imag()

// CLASSES
class DSU {
    public:
    vll parent, size;
   
    DSU(ll n){
        size = vll(n,1);
        parent = vll(n);
        FOR(i,0,n) parent[i]=i;
    }

    ll find(ll x){
        while(x != parent[x]) x = parent[x];
        return x;
    }

    void unite(ll a, ll b){
        a = find(a);
        b = find(b);
        if(size[a]<size[b])swap(a,b);
        size[a]+=size[b];
        parent[b]=a;
    }
};

class TRIE {
    vector<vector<ll>> trie;
    ll A;   // alphabet size with 'a' as 0 idx and A+1 index for flag
   
    void make_node(){
        trie.PB(vll(A+1));
    }

    public:
    TRIE(ll n){
        A = n;
        make_node();
    }

    void insert(string s){
        ll idx=0;
        FOR(i,0,s.size()){
            if(trie[idx][s[i]-'a'] == 0) {
                make_node();
                trie[idx][s[i]-'a'] = trie.size()-1;
            }
            idx = trie[idx][s[i]-'a'];
        }
        trie[idx][A]++;
    }

    bool is_present(string s){
        ll idx=0;
        FOR(i,0,s.size()){
            idx = trie[idx][s[i]-'a'];
            if(idx==0) return false;
        }
        return trie[idx][A]>0;
    }

    void remove_one(string s){
        ll idx=0;
        FOR(i,0,s.size()){
            idx = trie[idx][s[i]-'a'];
        }
        trie[idx][A]--;
    }

    void remove_all(string s){
        ll idx=0;
        FOR(i,0,s.size()){
            idx = trie[idx][s[i]-'a'];
        }
        trie[idx][A]=0;
    }

    void display(ll idx, string s){
        FOR(i,0,trie[idx][A]) cout<<s<<" ";
        FOR(i,0,A){
            if(trie[idx][i] != 0) display(trie[idx][i],s+(char)('a'+i));
        }
    }

};

// Static Array Queries
class SAQ {
    ll n;
    vector<vll> minTable, maxTable;
    vll logValues;

    public:
    void make_prefix_array(vll &v, vll::iterator pre){
        partial_sum(all(v),pre);
    }

    void fill_sparse_table(vll &arr){
        n = arr.size();
        ll maxLog = std::log2(n) + 1;

        minTable.resize(n, vll(maxLog));
        maxTable.resize(n, vll(maxLog));
        logValues.resize(n + 1);

        // Precompute logarithms for each length
        for (int i = 2; i <= n; ++i)
            logValues[i] = logValues[i / 2] + 1;

        // Initialize the first column of minTable and maxTable with array values
        for (int i = 0; i < n; ++i) {
            minTable[i][0] = arr[i];
            maxTable[i][0] = arr[i];
        }

        // Build the sparse table
        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                minTable[i][j] = min(minTable[i][j - 1], minTable[i + (1 << (j - 1))][j - 1]);
                maxTable[i][j] = max(maxTable[i][j - 1], maxTable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    ll rangeMinQuery(ll L, ll R) {
        ll j = logValues[R - L + 1];
        return min(minTable[L][j], minTable[R - (1 << j) + 1][j]);
    }

    ll rangeMaxQuery(ll L, ll R) {
        ll j = logValues[R - L + 1];
        return max(maxTable[L][j], maxTable[R - (1 << j) + 1][j]);
    }
};

// Binary Indexed Tree 1-indexed
class BIT {
    private:
    vll bit;
    ll n;

    public:
    BIT(ll size) : n(size) {
        bit.resize(n + 1, 0); // BIT is 1-indexed, so we need size + 1
    }

    // Update the BIT at index i by adding delta
    void update(ll i, ll delta) {
        while (i <= n) {
            bit[i] += delta;
            i += i & -i; // Move to next
        }
    }

    void fill(vll &arr){
        for (ll i = 1; i <= n; ++i) {
            update(i, arr[i]);
        }
    }

    // Get the prefix sum from 1 to i
    ll prefixSum(ll i) const {
        i++;
        ll sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= i & -i; // Move to parent
        }
        return sum;
    }

    // Get the sum of elements in range [l, r]
    ll rangeSum(ll l, ll r) const {
        return prefixSum(r) - prefixSum(l - 1);
    }
};

class ModularArithmetic {
private:
    ll maxn, mod;

public:
    vll fac, inv;

    // Class constructor to initialise the factorials and inverse factorials
    ModularArithmetic(ll N, ll M) {
        maxn = N, mod = M;

        fac.assign(maxn + 1, 1);
        for (ll i = 1; i <= maxn; i++) {
            fac[i] = (fac[i - 1] * i) % mod;
        }

        inv.assign(maxn + 1, 0);
        inv[maxn] = invmod(fac[maxn]);
        for (ll i = maxn; i >= 1; i--) {
            inv[i - 1] = (inv[i] * i) % mod;
        }
    }

    // Function to calculate A raised to power B modulo 'mod'
    ll mpow(ll A, ll B) {
        ll res = 1;
        A = A % mod;
        while (B) {
            if (B & 1) {
                res = (res * A) % mod;
            }
            A = (A * A) % mod;
            B >>= 1;
        }
        return res;
    }

    // Function to calculate the inverse modulo of A with respect to 'mod'
    ll invmod(ll A) {
        return mpow(A, mod - 2);
    }

    // Function to calculate the number of ways of choosing R objects out of N objects modulo 'mod'
    ll nCr(ll N, ll R) {
        if (N < 0 || R < 0 || N < R) {
            return 0;
        }
        if (R == 0) {
            return 1;
        }
        return (fac[N] * inv[R] % mod * inv[N - R] % mod) % mod;
    }
};
class NumTheory {
public:
    // Method to find primes till n
    // TC : O(n log log n)
    vector<bool> sieveOfEratosthenes(ll n){
        vector<bool> isPrime(n + 1, true);
        isPrime[0] = isPrime[1] = false;
        for (ll i = 2; i <= n; i++){
            if (isPrime[i] && (long long)i * i <= n){
                for (ll j = i * i; j <= n; j += i)
                    isPrime[j] = false;
            }
        }
        return isPrime;
    }
    // Method to find the GCD of two numbers using the Euclidean algorithm
    // TC: O(log(min(a,b)))
    ll _gcd(ll a, ll b){
        while (b){
            a %= b;
            swap(a, b);
        }
        return a;
    }
    // Method to find the LCM of two numbers
    ll _lcm(ll a, ll b){
        if (a == 0 || b == 0)
            return 0; // LCM of zero is undefined
        return (a / _gcd(a, b)) * b;
    }
    // Method to find the ceiling of a/b
    ll _ceiling(ll a, ll b){
        if (a % b){
            return (a / b) + 1;
        }
        return (a / b);
    }
};
// 1-indexed
class SegmentTree {
private:
    ll maxn;
    vll seg, lazy;

    // Auxiliary function to help perform the update when required (addition)
    void pushDown(ll node, ll L, ll R) {
        if (lazy[node] != 0) {
            seg[node] += lazy[node] * (R - L + 1);
            if (L != R) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    // Function to perform the given update (addition) in a given range in the tree
    void _update(ll node, ll L, ll R, ll low, ll high, ll value) {
        pushDown(node, L, R);
        if (L > R || L > high || R < low) {
            return;
        }
        if (L >= low && R <= high) {
            lazy[node] += value;
            pushDown(node, L, R);
            return;
        }

        ll mid = L + (R - L) / 2;
        _update(2 * node, L, mid, low, high, value);
        _update(2 * node + 1, mid + 1, R, low, high, value);
        seg[node] = min(seg[2 * node], seg[2 * node + 1]);
    }

    // Function to query (minimum) and get the required element from a given range
    ll _query(ll node, ll L, ll R, ll low, ll high) {
        pushDown(node, L, R);
        if (L > R || L > high || R < low) {
            return LLONG_MAX;
        }
        if (L >= low && R <= high) {
            return seg[node];
        }

        ll mid = L + (R - L) / 2;
        ll que1 = _query(2 * node, L, mid, low, high);
        ll que2 = _query(2 * node + 1, mid + 1, R, low, high);
        return min(que1, que2);
    }

public:
    // Class constructor
    SegmentTree(ll N) {
        maxn = N;
        seg.assign(4 * maxn + 10, 0);
        lazy.assign(4 * maxn + 10, 0);
    }

    void fill(vll &arr) {
        for (int i = 0; i < arr.size(); i++) {
            update(i + 1, i + 1, arr[i]);
        }
    }

    // Update wrapper function
    void update(ll low, ll high, ll value) {
        _update(1, 1, maxn, low, high, value);
    }

    // Query wrapper function
    ll query(ll low, ll high) {
        return _query(1, 1, maxn, low, high);
    }
};
class StringAlgos {
public:
    // KMP Algorithm: Build the LPS array (Longest Prefix Suffix)
    vector<ll> buildLPS(const string& pattern) {
        ll m = pattern.size();
        vector<ll> lps(m, 0);
        ll len = 0; // Length of the previous longest prefix suffix
        ll i = 1;
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }
    // KMP Algorithm: Pattern Searching
    // TC : O(n+m)
    void KMPSearch(const string& text, const string& pattern) {
        ll n = text.size();
        ll m = pattern.size();
        vector<ll> lps = buildLPS(pattern);
        ll i = 0; // Index for text
        ll j = 0; // Index for pattern
        while (i < n) {
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            if (j == m) {
                cout << "Pattern found at index " << i - j << "\n";
                j = lps[j - 1];
            } else if (i < n && pattern[j] != text[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
    }
    // Z Algorithm: Build the Z array
    vector<ll> buildZArray(const string& s) {
        ll n = s.size();
        vector<ll> Z(n, 0);
        ll L = 0, R = 0;
        for (ll i = 1; i < n; ++i) {
            if (i <= R) {
                Z[i] = min(R - i + 1, Z[i - L]);
            }
            while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
                Z[i]++;
            }
            if (i + Z[i] - 1 > R) {
                L = i;
                R = i + Z[i] - 1;
            }
        }
        return Z;
    }
    // Z Algorithm: Pattern Searching
    // TC : O(n+m)
     void ZSearch(const string& text, const string& pattern) {
        string concat = pattern + "$" + text;
        vector<ll> Z = buildZArray(concat);
        ll m = pattern.size();
        for (ll i = 0; i < Z.size(); ++i) {
            if (Z[i] == m) {
                cout << "Pattern found at index " << i - m - 1 << "\n";
            }
        }
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
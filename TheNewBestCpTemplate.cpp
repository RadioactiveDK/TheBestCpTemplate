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

typedef priority_queue< ll > pqmax;
typedef priority_queue<ll, vll, greater< ll > > pqmin;

typedef stack< ll > stll;
typedef queue< ll > qull;
typedef deque< ll > dqll;

// complex number: arg(c) for angle and polar(r,theta) for polar form
typedef complex< ll > cxll;

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
#define MOD 1000000007
#define PI (3.141592653589)
#define FOR(i,a,b) for(ll i = a; i < b; i++)
#define NESFOR(x,y) for(long long i = 0; i < x; i++) for(long long j = 0; j < y; j++)
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
#define take(v) for(ll i = 0; i < v.size(); i++) cin>>v[i]
#define takeS(start,v) for(ll i = start; i < v.size(); i++) cin>>v[i]
#define show(v) for(auto x:v) cout<<x<<" ";
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()

// funcitons
#define SORT(v) sort(v.begin(), v.end())
#define REV(v) reverse(v.begin(), v.end())

// complex
#define X real()
#define Y imag()



// CLASSES
class FenwickTree { // Binary Index Tree
	public:
		vll FenwickTreeArr;
		ll n;
		vll &arr;

		// Update the FenwickTree at index i by adding delta
		void _updateByAdding(ll i, ll delta) {
			while (i <= n) {
				FenwickTreeArr[i] += delta;
				i += i& -i; // Move to next
			}
		}

		void updateArrByAdding(ll i, ll delta) {
			arr[i] += delta;
			_updateByAdding(i+1, delta);
		}

		void fill(vll &arr){
			for (ll i = 1; i <= n; ++i) {
				_updateByAdding(i, arr[i-1]);
			}
		}

		FenwickTree(vll &arr) : arr(arr), n(arr.size()) {
			FenwickTreeArr.resize(n+1, 0);
			fill(arr);
		}

		// Get the prefix sum from 1 to i
		ll prefixSum(ll i) const {
			ll sum = 0;
			while (i > 0) {
				sum += FenwickTreeArr[i];
				i -= i& -i; // Move to parent
			}
			return sum;
		}

		// Get the sum of elements in range [l, r]
		ll rangeSumInclusive(ll l, ll r) const {
			return prefixSum(r+1)-prefixSum(l);
		}
};

class SegmentTree {
	public:
		ll n;
		ll sz;
		vpll seg;     // {value, lazy}

		// Apply an addition to the entire node interval [L, R)
		void apply(ll node, ll L, ll R, ll value) {
			seg[node].F += (R-L)*value;
			seg[node].S += value;
		}

		// Push pending lazy update to children
		void push(ll node, ll L, ll R) {
			if (seg[node].S == 0||R-L == 1)
				return;

			ll mid = L+(R-L)/2;
			ll lazy = seg[node].S;

			apply(2*node, L, mid, lazy);
			apply(2*node+1, mid, R, lazy);

			seg[node].S = 0;
		}

		// Range addition: add value to [low, high)
		void _update(ll node, ll L, ll R,
		             ll low, ll high, ll value) {

			if (R <= low||high <= L)
				return;

			if (low <= L&&R <= high) {
				apply(node, L, R, value);
				return;
			}

			push(node, L, R);

			ll mid = L+(R-L)/2;

			_update(2*node, L, mid, low, high, value);
			_update(2*node+1, mid, R, low, high, value);

			seg[node].F = seg[2*node].F+seg[2*node+1].F;
		}

		// Range sum query: sum of [low, high)
		ll _query(ll node, ll L, ll R, ll low, ll high) {
			if (R <= low||high <= L)
				return 0;

			if (low <= L&&R <= high)
				return seg[node].F;

			push(node, L, R);

			ll mid = L+(R-L)/2;

			ll left = _query(2*node, L, mid, low, high);
			ll right = _query(2*node+1, mid, R, low, high);

			return left+right;
		}

		SegmentTree(const vll &arr) {
			sz = arr.size();
			n = 1;
			while (n < sz) n *= 2;

			seg.assign(2*n, {0, 0});

			for (ll i = 0; i < sz; i++)
				seg[n+i].F = arr[i];

			for (ll i = n-1; i >= 1; i--)
				seg[i].F = seg[2*i].F+seg[2*i+1].F;
		}

		void updateRangeByAddingToEachInclusively(ll low, ll high, ll value) {
			high++;
			if (low >= high||low < 0||high > sz)
				return;
			_update(1, 0, n, low, high, value);
		}

		ll rangeSumInclusive(ll low, ll high) {
			high++;
			if (low >= high||low < 0||high > sz)
				return 0;
			return _query(1, 0, n, low, high);
		}
};

mt19937 rng(67);
class Treap {
	public:
		struct Node {
			ll val;
			ll prio;
			int l, r;
			int sz;
		};

		vector<Node> nodes;
		int root = -1;

		int size(int t) {
			return t == -1 ? 0 : nodes[t].sz;
		}

		void pull(int i){
			nodes[i].sz = 1+size(nodes[i].l)+size(nodes[i].r);
		}

		pair<int,int> split(int i, ll val) {
			if (i == -1) return {-1, -1};

			if (nodes[i].val < val) {
				auto [rl,rr] = split(nodes[i].r,val);
				nodes[i].r = rl;
				pull(i);
				return {i,rr};
			}
			else {
				auto [ll,lr] = split(nodes[i].l,val);
				nodes[i].l = lr;
				pull(i);
				return {ll,i};
			}
		}

		int merge(int left, int right){
			if (left == -1) return right;
			if (right == -1) return left;

			if (nodes[left].prio > nodes[right].prio) {
				nodes[left].r = merge(nodes[left].r, right);
				pull(left);
				return left;
			} else {
				nodes[right].l = merge(left, nodes[right].l);
				pull(right);
				return right;
			}
		}

		void insertVal(ll val){
			Node v;
			v.val = val;
			v.l = v.r = -1;
			v.prio = rng();
			v.sz = 1;
			nodes.PB(v);

			int idx = nodes.size()-1;
			if(root == -1) {
				root = idx;
				return;
			}

			auto[l,r] = split(root,val);
			auto[rl,rr] = split(r,val+1);
			int t = rl;
			if(t == -1) rl = idx;
			else{
				while(size(t) > 1&&nodes[t].prio < nodes[idx].prio){
					nodes[t].sz++;
					t = nodes[t].r;
				}
				nodes[t].sz++;
				nodes[idx].r = nodes[t].r;
				nodes[t].r = idx;
			}
			pull(idx);
			r = merge(rl,rr);
			root = merge(l,r);
		}

		void deleteVal(ll val){
			auto[l,r] = split(root,val);
			auto[rl,rr] = split(r,val+1);
			rl = nodes[rl].r;
			r = merge(rl,rr);
			root = merge(l,r);
		}

		array<int,3> splitSubTreap(ll val1,ll val2){
			auto[l,r] = split(root,val1);
			auto[rl,rr] = split(r,val2+1);
			return {l,rl,rr};
		}

		int mergeSubTreap(array<int,3> arr){
			arr[1] = merge(arr[1],arr[2]);
			root = merge(arr[0],arr[1]);
			return root;
		}

		bool isVal(ll val){
			auto arr = splitSubTreap(val,val);
			bool b = (arr[1] != -1);
			mergeSubTreap(arr);
			return b;
		}

		int deleteSubTreap(ll val1,ll val2){
			auto arr = splitSubTreap(val1,val2);
			root = merge(arr[0],arr[2]);
			return root;
		}

		int querySubTreap(ll val1,ll val2){
			auto arr = splitSubTreap(val1,val2);
			int b = size(arr[1]);
			mergeSubTreap(arr);
			return b;
		}

		int orderOfKey(ll val){
			auto arr = splitSubTreap(val,val);
			int b = size(arr[0]);
			mergeSubTreap(arr);
			return b;
		}

		ll findByOrder(int k){
			int x = root;
			k++;

			int idx = 0;
			while(idx != k){
				if(1+size(nodes[x].l) > k)
					x = nodes[x].l;
				else {
					idx += 1+size(nodes[x].l);
					if(idx != k) x = nodes[x].r;
				}
			}
			return nodes[x].val;
		}
};

class ImplicitTreap {
	public:
		struct Node {
			ll val;
			int l, r;
			int sz;
			ll sm,mx;
			bool rev;
		};

		vector<Node> nodes;
		int root = -1;

		int size(int t){
			return t == -1 ? 0 : nodes[t].sz;
		}
		int summ(int t){
			return t == -1 ? 0 : nodes[t].sm;
		}
		ll maxx(int t){
			return t == -1 ? -1 : nodes[t].mx;
		}

		void pull(int i){
			nodes[i].sz = 1+size(nodes[i].l)+size(nodes[i].r);
			nodes[i].sm = nodes[i].val+summ(nodes[i].l)+summ(nodes[i].r);
			nodes[i].mx = (ll)max({nodes[i].val,maxx(nodes[i].l),maxx(nodes[i].r)});
		}

		void push(int i){
			if(nodes[i].rev){
				swap(nodes[i].l,nodes[i].r);
				nodes[i].rev = false;
				int l = nodes[i].l,r = nodes[i].r;
				if(l != -1)nodes[l].rev ^= 1;
				if(r != -1)nodes[r].rev ^= 1;
			}
		}

		pair<int,int> splitSize(int i, ll k) {
			if (i == -1) return {-1, -1};

			int leftSize = 1+size(nodes[i].l);
			if (leftSize <= k) {
				push(i);
				auto [rl,rr] = splitSize(nodes[i].r,k-leftSize);
				nodes[i].r = rl;
				pull(i);
				return {i,rr};
			}
			else {
				push(i);
				auto [ll,lr] = splitSize(nodes[i].l,k);
				nodes[i].l = lr;
				pull(i);
				return {ll,i};
			}
		}

		int merge(int left, int right){
			if (left == -1) return right;
			if (right == -1) return left;

			if (rng()%(size(left)+size(right)) < size(left)) {
				push(left);
				nodes[left].r = merge(nodes[left].r, right);
				pull(left);
				return left;
			} else {
				push(right);
				nodes[right].l = merge(left, nodes[right].l);
				pull(right);
				return right;
			}
		}

		array<int,3> splitSizeSubTreap(ll i, ll j){
			auto[l,r] = splitSize(root,j+1);
			auto[ll,lr] = splitSize(l,i);
			return {ll,lr,r};
		}

		int mergeSubTreap(array<int,3> arr){
			arr[1] = merge(arr[1],arr[2]);
			root = merge(arr[0],arr[1]);
			return root;
		}

		pll querySubTreap(int i,int j){
			auto arr = splitSizeSubTreap(i,j);
			pll b = {nodes[arr[1]].sm,nodes[arr[1]].mx};
			mergeSubTreap(arr);
			return b;
		}

		int deleteSubTreap(ll val1,ll val2){
			auto arr = splitSizeSubTreap(val1,val2);
			root = merge(arr[0],arr[2]);
			return root;
		}

		ll findByOrder(int k){
			auto arr = splitSizeSubTreap(k,k);
			ll val = nodes[arr[1]].val;
			mergeSubTreap(arr);
			return val;
		}

		ll replaceVal(int k,ll val){
			auto arr = splitSizeSubTreap(k,k);
			nodes[arr[1]].val = val;
			mergeSubTreap(arr);
			return val;
		}

		void insertVal(ll val, int k){
			Node v;
			v.val = val;
			v.rev = false;
			v.l = v.r = -1;
			v.sz = 1;
			nodes.PB(v);

			int idx = nodes.size()-1;
			if(root == -1) {
				root = idx;
				return;
			}

			auto arr = splitSizeSubTreap(k,k);
			nodes[idx].r = arr[1];
			pull(idx);
			arr[1] = idx;
			mergeSubTreap(arr);
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
	if(fp != NULL){
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
		srand(time(0));
		cout<<rand()<<endl;
	}
	ll t = 1;
	cin>>t;
	while(t--) {
		solve();
		cout<<endl;
	}
	return 0;
}
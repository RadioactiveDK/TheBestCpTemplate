

class ImplicitTreap {
	public:
		struct Node {
			ll val;
			int l, r;
			int sz;
		};

		vector<Node> nodes;
		int root = -1;

		int size(int t){
			return t == -1 ? 0 : nodes[t].sz;
		}

		void pull(int i){
			nodes[i].sz = 1+size(nodes[i].l)+size(nodes[i].r);
		}

		pair<int,int> splitSize(int i, ll k) {
			if (i == -1) return {-1, -1};

			if (1+size(i) < k) {
				auto [rl,rr] = splitSize(nodes[i].r,k-1-size(i));
				nodes[i].r = rl;
				pull(i);
				return {i,rr};
			}
			else {
				auto [ll,lr] = splitSize(nodes[i].l,val);
				nodes[i].l = lr;
				pull(i);
				return {ll,i};
			}
		}

		int merge(int left, int right){
			if (left == -1) return right;
			if (right == -1) return left;

			if (rng()%(size(left)+size(right)) < size(left)) {
				nodes[left].r = merge(nodes[left].r, right);
				pull(left);
				return left;
			} else {
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

		int querySubTreap(int i,int j){
			auto arr = splitSizeSubTreap(i,j);
			int b = size(arr[1]);
			mergeSubTreap(arr);
			return b;
		}

		int deleteSubTreap(ll val1,ll val2){
			auto arr = splitSizeSubTreap(val1,val2);
			root = merge(arr[0],arr[2]);
			return root;
		}


















		void insertVal(ll val, int k){
			Node v;
			v.val = val;
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

		int getVal(ll val){
			auto arr = splitSizeSubTreap(val,val);
			int b = size(arr[0]);
			mergeSubTreap(arr);
			return b;
		}
};

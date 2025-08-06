#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
public:
  vector<int> tree;
  int n;

  SegmentTree(vector<int> &arr)
  {
    n = arr.size();
    tree.resize(4 * n);
    build(0, 0, n - 1, arr);
  }

  void build(int node, int l, int r, vector<int> &arr)
  {
    if (l == r)
    {
      tree[node] = arr[l];
      return;
    }
    int mid = (l + r) / 2;
    build(2 * node + 1, l, mid, arr);
    build(2 * node + 2, mid + 1, r, arr);
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
  }

  int query(int node, int l, int r, int ql, int qr)
  {
    if (ql > r || qr < l)
      return 0;
    if (ql <= l && r <= qr)
      return tree[node];

    int mid = (l + r) / 2;
    int left = query(2 * node + 1, l, mid, ql, qr);
    int right = query(2 * node + 2, mid + 1, r, ql, qr);
    return left + right;
  }

  void update(int node, int l, int r, int idx, int val)
  {
    if (l == r)
    {
      tree[node] = val;
      return;
    }

    int mid = (l + r) / 2;
    if (idx <= mid)
    {
      update(2 * node + 1, l, mid, idx, val);
    }
    else
    {
      update(2 * node + 2, mid + 1, r, idx, val);
    }

    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
  }
};

int main()
{
  vector<int> arr = {1, 2, 3, 4};
  SegmentTree st(arr);

  cout << "Sum [1,3]: " << st.query(0, 0, arr.size() - 1, 1, 3) << endl;

  st.update(0, 0, arr.size() - 1, 1, 10);

  cout << "Sum [1,3]: " << st.query(0, 0, arr.size() - 1, 1, 3) << endl;

  return 0;
}

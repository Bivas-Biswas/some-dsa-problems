#include <bits/stdc++.h>

using namespace std;

// Union-Find (Disjoint Set Union - DSU) with union by size and path compression
struct UnionFind
{
    int n;           // Total number of elements
    int set_size;    // Current number of disjoint sets
    int *par;        // Parent array: par[i] is the representative (parent) of element i
    int *rank;       // Size array: rank[i] is the size of the set whose representative is i

    // Default constructor
    UnionFind() {}

    // Parameterized constructor: initializes DSU for `a` elements (1-based indexing)
    UnionFind(int a)
    {
        n = set_size = a;
        par = new int[a + 1];   // Allocate memory for parent array
        rank = new int[a + 1];  // Allocate memory for size array

        // Initially, each element is its own parent and forms a set of size 1
        for (int i = 1; i <= n; i++)
        {
            par[i] = i;
            rank[i] = 1;
        }
    }

    // Find function with path compression
    int find(int x)
    {
        // If x is not the representative of its set, recursively find the root
        // and compress the path
        if (x != par[x])
            return par[x] = find(par[x]); // Path compression
        return x;
    }

    // Merge the sets containing x and y
    void merge(int x, int y)
    {
        int xroot = find(x); // Find representative of x
        int yroot = find(y); // Find representative of y

        // If they are already in the same set, do nothing
        if (xroot == yroot)
            return;

        // Union by size: attach smaller set to larger set
        if (rank[xroot] >= rank[yroot])
        {
            par[yroot] = xroot;             // Make xroot the new parent
            rank[xroot] += rank[yroot];     // Update size of the new set
        }
        else
        {
            par[xroot] = yroot;             // Make yroot the new parent
            rank[yroot] += rank[xroot];     // Update size of the new set
        }

        set_size--; // After merging, one less disjoint set exists
    }

    // Returns the current number of disjoint sets
    int size()
    {
        return set_size;
    }

    // Resets the DSU to its initial state
    void reset()
    {
        set_size = n;
        for (int i = 1; i <= n; i++)
        {
            par[i] = i;     // Each element is its own parent
            rank[i] = 1;    // Each set has size 1
        }
    }
};

int main()
{

    return 0;
}
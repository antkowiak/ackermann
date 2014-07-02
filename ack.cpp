//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
// 03 July 2014
//
// Compile with: g++ ack.cpp -o ack
//

#include <cstdio>
#include <cstdlib>
#include <map>

// Use a typedef for the data type, so it can easily be changed...
// Possibly to a custom type that can store larger integer types
// than can typically be stored in a primitive type
typedef uint64_t TNumber;


// Used as the key/index for a map that caches the
// values of ack(m,n)
class CacheIndex
{
public:
    CacheIndex() : m(0), n(0) {}
    CacheIndex(TNumber m_, TNumber n_) : m(m_), n(n_) {}

    // equality comparision operator
    bool operator == (const CacheIndex & rhs) const
    {
        return (m==rhs.m && n==rhs.n);
    }

    // less than comparison operator (so the stl map can order the indices)
    bool operator < (const CacheIndex & rhs) const
    {
        if (m < rhs.m)
        {
            return true;
        }
        else if (m > rhs.m)
        {
            return false;
        }
        else
        {
            return (n < rhs.n);
        }
    }
    
public:
    TNumber m;
    TNumber n;
};


// The ack function
TNumber ack(const TNumber m, const TNumber n)
{
    // Static cache of ack values, to prevent re-calculation of duplicates
    static std::map<CacheIndex, TNumber> cache;

    // Check for a cache hit before doing any comparisons or computations
    if (cache.find(CacheIndex(m,n)) != cache.end())
    {
        return cache[CacheIndex(m,n)];
    }

    // We didn't find it in the cache... allow for the ack() calculation
    TNumber ans;
    if (m == 0)
    {
        ans = n+1;
    }
    else if (n == 0)
    {
        ans = ack(m-1, 1);
    }
    else
    {
        ans = ack(m-1, ack(m, n-1));
    }

    // Store our result in the cache, to prevent re-calculating it
    // unnecessarily later
    cache[CacheIndex(m,n)] = ans;

    return ans;
}


// Main function
int main(int argc, char *argv[])
{
    for (int i = 0 ; i < 6 ; ++i)
    {
        for (int j = 0 ; j < 6 ; ++j)
        {
            fprintf(stdout, "ack(%ld, %ld) is: %ld\n", i, j, ack(i,j));
            fflush(stdout);
        }
    }

    return 0;
}


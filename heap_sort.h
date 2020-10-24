#ifndef heap_sort_h
#define heap_sort_h

#include <cassert>
#include <functional>
#include <algorithm>
#include "utils.h"

template <typename T>

class Heap {
public:
  Heap() {}
  static void sort(T* pq, const comparator<T>& comp=fwd_comparator<T>()) {
    size_t n = std::size(pq);

    // heapify phase
    for (size_t k = n/2; k >= 1; k--) sink(pq, k, n);

    // sortdown phase
    size_t k = n;
    while (k > 1) {
       exchange(pq, 1, k--);
       sink(pq, 1, k);
    }
  }

private:
  static void sink(T* pq, size_t k, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
    while (2*k <= n) {
      size_t j = 2*k;
      if (j < n && less(pq[j-1], pq[j])) j++;
      if (!less(pq[k-1], pq[j-1])) break;
      exchange(pq, k, j);
      k = j;
    }
  }
};

template <typename T>

class MaxPQ {
public:
  MaxPQ(size_t maxN) { pq = new T[N+1]; }

  bool isEmpty() { return N == 0; }

  size_t size() { return N; }

  void insert(T* v, const comparator<T>& comp=fwd_comparator<T>()) {
    pq[++N] = v;
    swim(v, N);
  }

  T delMax() {
    T max = pq[1];
    exchange9(1, N--);
    pq[N+1] = NULL;
    sink(1);
    return max;
  }

private:
  T pq;
  size_t N = 0;

  static void sink(T* pq, size_t k, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
    while (2*k <= n) {
      size_t j = 2*k;
      if (j < n && less(pq[j-1], pq[j])) j++;
      if (!less(pq[k-1], pq[j-1])) break;
      exchange(pq, k, j);
      k = j;
    }
   }

   void swim(T* pq, size_t k, const comparator<T>& comp=fwd_comparator<T>()) {
     while (k > 1 && less(pq[(k/2)-1], pq[k-1])) {
        exchange(pq, k, k/2);
        k = k/2;
      }
   }

};

#endif

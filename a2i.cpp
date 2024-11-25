#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;
using ld = long double;

const ld EPSILON = 1e-12;
const ll INFINITY = 1e12;

template <typename T>
using Vector = std::vector<T>;

Vector<ll> combinationSort(Vector<ll>& array, ll threshold, ll left, ll right) {

  if (right - left <= threshold) {
    ll size = std::min(threshold, right - left);
    Vector<ll> subarray(size);

    for (ll i = left; i < right; ++i) {
      subarray[i - left] = array[i];
    }

    for (ll i = 1; i < size; ++i) {
      ll j = i;
      while (j > 0 && subarray[j - 1] > subarray[j]) {
        std::swap(subarray[j - 1], subarray[j]);
        --j;
      }
    }

    return subarray;
  }

  ll mid = (left + right) / 2;
  Vector<ll> sortedLeft = combinationSort(array, threshold, left, mid);
  Vector<ll> sortedRight = combinationSort(array, threshold, mid, right);

  Vector<ll> merged;
  ll i = 0, j = 0;

  while (i < sortedLeft.size() && j < sortedRight.size()) {
    if (sortedLeft[i] <= sortedRight[j]) {
      merged.push_back(sortedLeft[i++]);
    } else {
      merged.push_back(sortedRight[j++]);
    }
  }

  while (i < sortedLeft.size()) {
    merged.push_back(sortedLeft[i++]);
  }
  while (j < sortedRight.size()) {
    merged.push_back(sortedRight[j++]);
  }

  return merged;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  ll numberOfElements;
  std::cin >> numberOfElements;

  Vector<ll> data(numberOfElements);
  for (ll i = 0; i < numberOfElements; ++i) {
    std::cin >> data[i];
  }

  data = combinationSort(data, 15, 0, numberOfElements);

  for (const auto& element : data) {
    std::cout << element << " ";
  }

  return 0;
}

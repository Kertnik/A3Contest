#include "SortTester.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using ll = long long;
using ld = long double;

const ld EPSILON = 1e-12;

template <typename T>
using Vector = std::vector<T>;

Vector<ll> CombinationSort(Vector<ll>& array, const ll threshold, const ll left, const ll right) {

  if (right - left <= threshold) {
    const ll size = std::min(threshold, right - left);
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

  const ll mid = (left + right) / 2;
  Vector<ll> sorted_left = CombinationSort(array, threshold, left, mid);
  Vector<ll> sorted_right = CombinationSort(array, threshold, mid, right);

  Vector<ll> merged;
  ll i = 0;
  ll j = 0;

  while (i < sorted_left.size() && j < sorted_right.size()) {
    if (sorted_left[i] <= sorted_right[j]) {
      merged.push_back(sorted_left[i++]);
    } else {
      merged.push_back(sorted_right[j++]);
    }
  }

  while (i < sorted_left.size()) {
    merged.push_back(sorted_left[i++]);
  }
  while (j < sorted_right.size()) {
    merged.push_back(sorted_right[j++]);
  }

  return merged;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  SortTester tester(CombinationSort);

  const std::vector<ll> starts = {1, 5, 10, 20, 30, 50};
  constexpr ll num_tests = 200;
  constexpr ll start_size = 500;
  constexpr ll step_size = 100;
  constexpr ll max_size = 10000;

  for (const auto& change_par : starts) {
    const ll iterations = 15;
    std::vector<ld> avg_chaotic(num_tests, 0);
    std::vector<ld> avg_reverse_sorted(num_tests, 0);
    std::vector<ld> avg_shuffled(num_tests, 0);

    for (ll i = 0; i < iterations; ++i) {
      tester.Test(change_par, start_size, max_size, step_size, avg_chaotic, avg_reverse_sorted, avg_shuffled);
      tester.UpdateSamples();
    }

    auto normalize = [&](std::vector<ld>& results) {
      for (auto& value : results) {
        value /= iterations;
      }
    };

    normalize(avg_chaotic);
    normalize(avg_reverse_sorted);
    normalize(avg_shuffled);

    auto write_results = [&](const std::string& filename, const std::vector<ld>& results) {
      std::ofstream ofs(filename);
      for (ll i = 0; i < num_tests; ++i) {
        ll size = start_size + i * step_size;
        ofs << std::setprecision(5) << "(" << size << ", " << results[i] << ") ";
      }
      ofs.close();
    };

    write_results("chaos_res" + std::to_string(change_par) + ".txt", avg_chaotic);
    write_results("reverse_res" + std::to_string(change_par) + ".txt", avg_reverse_sorted);
    write_results("shuffle_res" + std::to_string(change_par) + ".txt", avg_shuffled);
  }

  return 0;
}

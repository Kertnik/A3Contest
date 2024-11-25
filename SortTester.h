#ifndef SORTTESTER_H
#define SORTTESTER_H

#include <chrono>
#include <functional>
#include <vector>
#include "ArrayGenerator.h"

using ld = long double;

class SortTester {
 private:
  std::function<std::vector<ll>(std::vector<ll>&, ll, ll, ll)> sorter_;
  ArrayGenerator generator_;
  static constexpr ll kDefaultSize = 10000;
  std::vector<ll> group_chaotic_;
  std::vector<ll> group_reverse_sorted_;
  std::vector<ll> group_shuffled_;

 public:
  explicit SortTester(std::function<std::vector<ll>(std::vector<ll>&, ll, ll, ll)> sort_algo)
      : sorter_(std::move(sort_algo))
      , generator_()
      , group_chaotic_(kDefaultSize)
      , group_reverse_sorted_(kDefaultSize)
      , group_shuffled_(kDefaultSize) {
    UpdateSamples();
  }

  void UpdateSamples() {
    group_chaotic_ = generator_.GetChaotic(kDefaultSize);
    group_reverse_sorted_ = generator_.GetReverseSorted(kDefaultSize);
    group_shuffled_ = generator_.GetShuffled(kDefaultSize);
  }

  void Test(const ll k, const ll min_size, const ll max_size, const ll step, std::vector<ld>& avg_chaotic,
            std::vector<ld>& avg_reverse_sorted, std::vector<ld>& avg_shuffled) {
    const size_t num_tests = (max_size - min_size) / step + 1;
    avg_chaotic.resize(num_tests, 0);
    avg_reverse_sorted.resize(num_tests, 0);
    avg_shuffled.resize(num_tests, 0);

    for (ll i = min_size, index = 0; i <= max_size; i += step, ++index) {
      avg_chaotic[index] += MeasureSortTime(group_chaotic_, k, i);
      avg_reverse_sorted[index] += MeasureSortTime(group_reverse_sorted_, k, i);
      avg_shuffled[index] += MeasureSortTime(group_shuffled_, k, i);
    }
  }

 private:
  ld MeasureSortTime(std::vector<ll>& data, const ll k, const ll size) const {
    const auto start = std::chrono::high_resolution_clock::now();
    sorter_(data, k, 0, size);
    const auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration<ld, std::micro>(elapsed).count();
  }
};

#endif  // SORTTESTER_H


#ifndef ARRAYGENERATOR_H
#define ARRAYGENERATOR_H

#include <algorithm>
#include <vector>
#include <random>

using ll = long long;

class ArrayGenerator {
 private:
  std::mt19937 gen_;
  std::uniform_int_distribution<ll> ds_;

 public:
  ArrayGenerator() {
    gen_ = std::mt19937(23424536);
    ds_ = std::uniform_int_distribution<ll>(0, 6000);
  }

  std::vector<ll> GetChaotic(const ll of_size) {

    std::vector<ll> new_vec(of_size, 0);

    for (auto& i : new_vec) {
      i = ds_(gen_);
    }

    return new_vec;
  }

  std::vector<ll> GetReverseSorted(ll of_size) {
    std::vector<ll> new_vec = GetChaotic(of_size);
    std::sort(new_vec.rbegin(), new_vec.rend());
    return new_vec;
  }

  std::vector<ll> GetShuffled(ll of_size) {
    std::vector<ll> new_vec = GetChaotic(of_size);
    std::sort(new_vec.begin(), new_vec.end());

    ll onep = of_size / 10;

    std::uniform_int_distribution<ll> coord_ds(0, of_size - 1);

    while (onep--) {
      ll a = coord_ds(gen_);
      ll b = coord_ds(gen_);
      std::swap(a, b);
    }

    return new_vec;
  }
};

#endif  // ARRAYGENERATOR_H

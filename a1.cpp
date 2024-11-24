//

//
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <fstream>

using ll = long long;
using ld = long double;

const ld eps = 1e-12;

struct Circle {
  ld centerX, centerY;
  ld radiusSquared;

  Circle(const ld x = 0, const ld y = 0, const ld r = 0) : centerX(x), centerY(y), radiusSquared(r * r) {
  }

  bool contains(ld x, ld y) const {
    ld distanceSquared = (centerX - x) * (centerX - x) + (centerY - y) * (centerY - y);
    return radiusSquared - distanceSquared >= eps;
  }
};

ld monteCarloArea(std::mt19937& generator, Circle& c1, Circle& c2, Circle& c3, ld startX, ld startY, ld width,
                  ld height, ll numSamples) {

  std::uniform_real_distribution<ld> randomX(startX, startX + width);
  std::uniform_real_distribution<ld> randomY(startY, startY + height);

  ll pointsInside = 0;

  for (ll i = 0; i < numSamples; ++i) {

    ld x = randomX(generator);
    ld y = randomY(generator);

    if (c1.contains(x, y) && c2.contains(x, y) && c3.contains(x, y)) {
      ++pointsInside;
    }
  }

  return (width * height * pointsInside) / static_cast<ld>(numSamples);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Circle c1(1, 1, 1);
  Circle c2(1.5, 2, 1.25);
  Circle c3(2, 1.5, 1.25);

  std::mt19937 gen(102345);
  ld sx = 0, sy = 0;
  ld ss = 3.2;

  ld ex = 0.8, ey = 0.8;

  ld sa = 1.2, sb = 1.2;

  std::ofstream ofs("result.txt");
  std::ofstream ofs2("accur.txt");
  ofs << std::setprecision(7);
  ll steps = 6;

  ld pi = std::atan2(0, -2);
  ld ideal = pi / 4.0 + 1.25 * std::asin(0.8) - 1;

  std::cout << pi << " " << ideal;

  ld point_step = ex / steps;
  ld sa_step = (sa - ss) / steps;
  ld sb_step = (sb - ss) / steps;

  for (ll i = 0; i <= steps; ++i) {
    ld x0 = point_step * i, y0 = point_step * i;
    ld ai = ss + sa_step * i;
    ld bi = ss + sb_step * i;

    for (ll j = 100; j <= 1e5 + 100; j += 500) {
      ld res = monteCarloArea(gen, c1, c2, c3, x0, y0, ai, bi, j);
      ofs << "(" << ai * bi << ", " << j << ", " << res << ") ";
      ofs2 << "(" << ai * bi << ", " << j << ", " << (res - ideal) / ideal << ") ";
    }

    ofs << "\n\n";
    ofs2 << "\n\n";
  }

  ofs.close();
  ofs2.close();

  return 0;
}
#include <finedex.hpp>

#include <limits>
#include <random>

int main() {
  using Key = uint64_t;
  using Value = size_t;

  const size_t n = 1000;
  const size_t max_error = 42;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<Value> val_dist(
      std::numeric_limits<Value>::min(),
      std::numeric_limits<Value>::max() >> 1ULL);

  std::vector<Key> keys;
  std::vector<Value> values;
  keys.reserve(n);
  values.reserve(n);

  for (size_t i = 0; i < n; i++) {
    keys.push_back(i * i);
    values.push_back(val_dist(gen));
  }

  assert(keys.size() == n);
  assert(values.size() == n);

  // create and train findex
  finedex::FINEdex<uint64_t, uint64_t> d;
  d.train(keys, values, max_error);

  // test that all values are correctly found
  for (size_t i = 0; i < n; i++) {
    Value test_val;
    d.find(keys[i], test_val);
    assert(test_val == values[i]);
  }

  return 0;
}
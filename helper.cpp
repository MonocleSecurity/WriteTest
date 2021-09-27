#include <limits>
#include <random>
#include <stdio.h>
#include <unistd.h>
#include <utility>

const size_t MAX_SIZE = 1024; // 1KB
const size_t RANDOM_DATA_SIZE = 16 * 1024 * MAX_SIZE;

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> distsize(1, MAX_SIZE);
std::uniform_int_distribution<std::mt19937::result_type> distdata(0, RANDOM_DATA_SIZE - MAX_SIZE);
std::vector<char> randomdata;

void GenerateRandomData()
{
  std::uniform_int_distribution<std::mt19937::result_type> dist(std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
  randomdata.reserve(RANDOM_DATA_SIZE);
  for (int i = 0; i < RANDOM_DATA_SIZE; ++i)
  {
    randomdata.push_back(dist(rng));
  }
}

std::pair<const char*, size_t> RandomData()
{
  return std::make_pair(randomdata.data() + distdata(rng), distsize(rng));
}

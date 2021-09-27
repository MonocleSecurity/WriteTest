#include <chrono>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <utility>

#include "helper.hpp"

int main()
{
  GenerateRandomData();
  const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  size_t totaldata = 0;
  { // The ofstream destructor can block, so it has to go into its own scope
    std::ofstream file("out.dat");
    while (totaldata < OUTPUT_SIZE)
    {
      const std::pair<const char*, size_t> randomdata = RandomData();
      file.write(randomdata.first, randomdata.second);
      totaldata += randomdata.second;
    }
  }
  const auto durationms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
  std::cout << "Wrote " << (totaldata / (1024 * 1024)) << "MB in " << durationms << "ms" << std::endl;
  return 0;
}

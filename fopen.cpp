#include <chrono>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <utility>

#include "helper.hpp"

int main()
{
  GenerateRandomData();
  
  const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  size_t totaldata = 0;
  
  {
    FILE* file = fopen("out.dat", "w");
    while (totaldata < OUTPUT_SIZE)
    {
      const std::pair<const char*, size_t> randomdata = RandomData();
      fwrite(randomdata.first, randomdata.second, 1, file);
      totaldata += randomdata.second;
    }
    fclose(file);
  }
  const auto durationms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
  std::cout << "Wrote " << (totaldata / (1024 * 1024)) << "MB in " << durationms << "ms" << std::endl;
  return 0;
}

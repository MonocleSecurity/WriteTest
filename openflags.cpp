#include <chrono>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <utility>
#include <vector>

#include "helper.hpp"

const size_t PAGE_SIZE = sysconf(_SC_PAGESIZE);

int main()
{
  GenerateRandomData();
  
  const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  size_t totaldata = 0;
  const int file = open("out.dat", O_CREAT | O_WRONLY | O_DIRECT, 0600);
  std::vector<char> buffer;
  while (totaldata < OUTPUT_SIZE)
  {
    const std::pair<const char*, size_t> randomdata = RandomData();
    buffer.insert(buffer.end(), randomdata.first, randomdata.first + randomdata.second);
    if (buffer.size() >= PAGE_SIZE)
    {
      const size_t size = (buffer.size() / PAGE_SIZE) * PAGE_SIZE;
      write(file, buffer.data(), size);
      buffer.erase(buffer.begin(), buffer.begin() + size);
      totaldata += size;
    }
  }
  close(file);
  const auto durationms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
  std::cout << "Wrote " << (totaldata / (1024 * 1024)) << "MB in " << durationms << "ms" << std::endl;
  return 0;
}

#pragma once

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

class libds {
  private:
  public:
    libds();
    ~libds();

  // ----------------- CSV Parser -----------------------
    struct StringRef {
      const char *data;
      size_t length;

      std::string toString() const {
        return std::string(data, length);
      }
    };
    static int processCSV(const std::string& filepath) {
      int fd = open(filepath.c_str(), O_RDONLY);
      if (fd == -1)
        return (std::cout << "Error while opening file!" << std::endl, -1);
      struct stat st; fstat(fd, &st);
      char *data = static_cast<char *>(mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
      close(fd);
      madvise(data, st.st_size, MADV_SEQUENTIAL);
      munmap(data, st.st_size);
    }
  // ---------------------------------------------------
  /* Z Score Normalization  
   *
   double val = 1, mean = 3, std, 2;
   double norm = z_score_norm(val, mean, std);*/
  template <typename A>
  static A z_score_norm(A val, A mean, A std){return (val - mean) / std;}
  /* Z Score Denormalization  
   *
   double val = 1, mean = 3, std, 2;
   double norm = z_score_norm(val, mean, std);
   double denorm = z_score_denorm(norm, mean, std);*/
  template <typename A>
  static A z_score_denorm(A val, A mean, A std){return std * val + mean;};
  ///
};

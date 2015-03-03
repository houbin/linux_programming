#ifndef UTIL_BITMAPPER_H
#define UTIL_BITMAPPER_H

#include <string.h>
#include <stdlib.h>

namespace util
{

class bitmapper {
  char *data_;
  int len_;

 public:
  bitmapper() : data_(0), len_(0) { }
  bitmapper(int len) : len_(len)
  {
    data_ = (char *)malloc(len_);
    memset(data_, 0, len_);
  }

  ~bitmapper()
  {
    free(data_);
    data_ = NULL;
  }

  int bytes() const { return len_; }
  int bits() const { return len_ * 8; }

  int get_free_bit()
  {
    int i = 0;
    for (i = 0; i < len_ / 4; i++)
    {
        int *temp = (int *)data_;
        if (temp[i] == 0xFFFFFFFF)
        {
            continue;
        }

        int j = 0;
        for (j = 0; j < 32; j++)
        {
            if (!get(i * 32 + j))
            {
                return (i * 32 + j);
            }
        }
        
        if (j == 32)
        {
            return -1;
        }
    }

    return -1;
  }

  bool operator[](int b) const {
    return get(b);
  }
  bool get(int b) const {
    return data_[b >> 3] & (1 << (b&7));
  }
  void set(int b) {
    data_[b >> 3] |= 1 << (b&7);
  }
  void clear(int b) {
    data_[b >> 3] &= ~(1 << (b&7));
  }
};

}

#endif

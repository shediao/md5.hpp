#ifndef __MD5_MD5_HPP__
#define __MD5_MD5_HPP__
#include <algorithm>
#include <cstdint>
#include <string>

namespace md5 {
namespace detail {

constexpr uint32_t S11 = 7;
constexpr uint32_t S12 = 12;
constexpr uint32_t S13 = 17;
constexpr uint32_t S14 = 22;
constexpr uint32_t S21 = 5;
constexpr uint32_t S22 = 9;
constexpr uint32_t S23 = 14;
constexpr uint32_t S24 = 20;
constexpr uint32_t S31 = 4;
constexpr uint32_t S32 = 11;
constexpr uint32_t S33 = 16;
constexpr uint32_t S34 = 23;
constexpr uint32_t S41 = 6;
constexpr uint32_t S42 = 10;
constexpr uint32_t S43 = 15;
constexpr uint32_t S44 = 21;

static constexpr unsigned char PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

inline uint32_t F(uint32_t x, uint32_t y, uint32_t z) {
  return (x & y) | (~x & z);
}

inline uint32_t G(uint32_t x, uint32_t y, uint32_t z) {
  return (x & z) | (y & ~z);
}

inline uint32_t H(uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; }

inline uint32_t I(uint32_t x, uint32_t y, uint32_t z) { return y ^ (x | ~z); }

// rotate_left rotates x left n bits.
inline uint32_t rotate_left(uint32_t x, int n) {
  return (x << n) | (x >> (32 - n));
}

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
inline void FF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x,
               uint32_t s, uint32_t ac) {
  a = rotate_left(a + F(b, c, d) + x + ac, s) + b;
}

inline void GG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x,
               uint32_t s, uint32_t ac) {
  a = rotate_left(a + G(b, c, d) + x + ac, s) + b;
}

inline void HH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x,
               uint32_t s, uint32_t ac) {
  a = rotate_left(a + H(b, c, d) + x + ac, s) + b;
}

inline void II(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x,
               uint32_t s, uint32_t ac) {
  a = rotate_left(a + I(b, c, d) + x + ac, s) + b;
}
inline void decode(uint32_t output[], const unsigned char input[], size_t len) {
  for (unsigned int i = 0, j = 0; j < len; i++, j += 4) {
    output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) |
                (((uint32_t)input[j + 2]) << 16) |
                (((uint32_t)input[j + 3]) << 24);
  }
}

inline void encode(unsigned char output[], const uint32_t input[], size_t len) {
  for (size_t i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = input[i] & 0xff;
    output[j + 1] = (input[i] >> 8) & 0xff;
    output[j + 2] = (input[i] >> 16) & 0xff;
    output[j + 3] = (input[i] >> 24) & 0xff;
  }
}

}  // namespace detail

class MD5 {
  constexpr static unsigned int blocksize = 64;

 public:
  MD5();
  MD5(const char *input, size_t length) {
    update(input, length);
    finalize();
  }
  MD5(const unsigned char *input, size_t length) {
    update(input, length);
    finalize();
  }
  MD5(const std::string &text) {
    update(text.data(), text.size());
    finalize();
  }
  std::string hexdigest() const {
    if (!finalized_) {
      return "";
    }

    const char hexs[] = "0123456789abcdef";

    char buf[33];
    for (int i = 0; i < 16; i++) {
      unsigned char c = digest_[i];
      buf[i * 2] = hexs[c >> 4];
      buf[i * 2 + 1] = hexs[c & 0x0f];
    }
    buf[32] = 0;

    return std::string(buf);
  };
  void update(const char input[], size_t length) {
    update((const unsigned char *)input, length);
  }
  void update(const unsigned char *input, size_t length) {
    size_t index = count_ / 8 % blocksize;
    count_ += length << 3;

    while (length > 0) {
      if (length >= 64 - index) {
        std::copy_n(input, 64 - index, &buffer_[index]);
        transform(buffer_);
        length -= (64 - index);
        input += (64 - index);
      } else {
        std::copy_n(input, length, &buffer_[index]);
        length = 0;
        input = nullptr;
      }
      index = 0;
    }
  }

  void finalize() {
    if (!finalized_) {
      unsigned char bits[8];
      uint32_t counts[2]{static_cast<uint32_t>(count_),
                         static_cast<uint32_t>(count_ >> 32)};

      detail::encode(bits, counts, 8);

      size_t index = counts[0] / 8 % 64;
      size_t padLen = (index < 56) ? (56 - index) : (120 - index);
      update(detail::PADDING, padLen);

      update(bits, 8);

      detail::encode(digest_, state_, 16);

      std::fill_n(buffer_, std::size(buffer_), 0);
      count_ = 0;
      finalized_ = true;
    }
  }

 private:
  void transform(unsigned char *block) {
    uint32_t a = state_[0], b = state_[1], c = state_[2], d = state_[3], x[16];
    detail::decode(x, block, blocksize);

    /* Round 1 */
    detail::FF(a, b, c, d, x[0], detail::S11, 0xd76aa478);  /* 1 */
    detail::FF(d, a, b, c, x[1], detail::S12, 0xe8c7b756);  /* 2 */
    detail::FF(c, d, a, b, x[2], detail::S13, 0x242070db);  /* 3 */
    detail::FF(b, c, d, a, x[3], detail::S14, 0xc1bdceee);  /* 4 */
    detail::FF(a, b, c, d, x[4], detail::S11, 0xf57c0faf);  /* 5 */
    detail::FF(d, a, b, c, x[5], detail::S12, 0x4787c62a);  /* 6 */
    detail::FF(c, d, a, b, x[6], detail::S13, 0xa8304613);  /* 7 */
    detail::FF(b, c, d, a, x[7], detail::S14, 0xfd469501);  /* 8 */
    detail::FF(a, b, c, d, x[8], detail::S11, 0x698098d8);  /* 9 */
    detail::FF(d, a, b, c, x[9], detail::S12, 0x8b44f7af);  /* 10 */
    detail::FF(c, d, a, b, x[10], detail::S13, 0xffff5bb1); /* 11 */
    detail::FF(b, c, d, a, x[11], detail::S14, 0x895cd7be); /* 12 */
    detail::FF(a, b, c, d, x[12], detail::S11, 0x6b901122); /* 13 */
    detail::FF(d, a, b, c, x[13], detail::S12, 0xfd987193); /* 14 */
    detail::FF(c, d, a, b, x[14], detail::S13, 0xa679438e); /* 15 */
    detail::FF(b, c, d, a, x[15], detail::S14, 0x49b40821); /* 16 */

    /* Round 2 */
    detail::GG(a, b, c, d, x[1], detail::S21, 0xf61e2562);  /* 17 */
    detail::GG(d, a, b, c, x[6], detail::S22, 0xc040b340);  /* 18 */
    detail::GG(c, d, a, b, x[11], detail::S23, 0x265e5a51); /* 19 */
    detail::GG(b, c, d, a, x[0], detail::S24, 0xe9b6c7aa);  /* 20 */
    detail::GG(a, b, c, d, x[5], detail::S21, 0xd62f105d);  /* 21 */
    detail::GG(d, a, b, c, x[10], detail::S22, 0x2441453);  /* 22 */
    detail::GG(c, d, a, b, x[15], detail::S23, 0xd8a1e681); /* 23 */
    detail::GG(b, c, d, a, x[4], detail::S24, 0xe7d3fbc8);  /* 24 */
    detail::GG(a, b, c, d, x[9], detail::S21, 0x21e1cde6);  /* 25 */
    detail::GG(d, a, b, c, x[14], detail::S22, 0xc33707d6); /* 26 */
    detail::GG(c, d, a, b, x[3], detail::S23, 0xf4d50d87);  /* 27 */
    detail::GG(b, c, d, a, x[8], detail::S24, 0x455a14ed);  /* 28 */
    detail::GG(a, b, c, d, x[13], detail::S21, 0xa9e3e905); /* 29 */
    detail::GG(d, a, b, c, x[2], detail::S22, 0xfcefa3f8);  /* 30 */
    detail::GG(c, d, a, b, x[7], detail::S23, 0x676f02d9);  /* 31 */
    detail::GG(b, c, d, a, x[12], detail::S24, 0x8d2a4c8a); /* 32 */

    /* Round 3 */
    detail::HH(a, b, c, d, x[5], detail::S31, 0xfffa3942);  /* 33 */
    detail::HH(d, a, b, c, x[8], detail::S32, 0x8771f681);  /* 34 */
    detail::HH(c, d, a, b, x[11], detail::S33, 0x6d9d6122); /* 35 */
    detail::HH(b, c, d, a, x[14], detail::S34, 0xfde5380c); /* 36 */
    detail::HH(a, b, c, d, x[1], detail::S31, 0xa4beea44);  /* 37 */
    detail::HH(d, a, b, c, x[4], detail::S32, 0x4bdecfa9);  /* 38 */
    detail::HH(c, d, a, b, x[7], detail::S33, 0xf6bb4b60);  /* 39 */
    detail::HH(b, c, d, a, x[10], detail::S34, 0xbebfbc70); /* 40 */
    detail::HH(a, b, c, d, x[13], detail::S31, 0x289b7ec6); /* 41 */
    detail::HH(d, a, b, c, x[0], detail::S32, 0xeaa127fa);  /* 42 */
    detail::HH(c, d, a, b, x[3], detail::S33, 0xd4ef3085);  /* 43 */
    detail::HH(b, c, d, a, x[6], detail::S34, 0x4881d05);   /* 44 */
    detail::HH(a, b, c, d, x[9], detail::S31, 0xd9d4d039);  /* 45 */
    detail::HH(d, a, b, c, x[12], detail::S32, 0xe6db99e5); /* 46 */
    detail::HH(c, d, a, b, x[15], detail::S33, 0x1fa27cf8); /* 47 */
    detail::HH(b, c, d, a, x[2], detail::S34, 0xc4ac5665);  /* 48 */

    /* Round 4 */
    detail::II(a, b, c, d, x[0], detail::S41, 0xf4292244);  /* 49 */
    detail::II(d, a, b, c, x[7], detail::S42, 0x432aff97);  /* 50 */
    detail::II(c, d, a, b, x[14], detail::S43, 0xab9423a7); /* 51 */
    detail::II(b, c, d, a, x[5], detail::S44, 0xfc93a039);  /* 52 */
    detail::II(a, b, c, d, x[12], detail::S41, 0x655b59c3); /* 53 */
    detail::II(d, a, b, c, x[3], detail::S42, 0x8f0ccc92);  /* 54 */
    detail::II(c, d, a, b, x[10], detail::S43, 0xffeff47d); /* 55 */
    detail::II(b, c, d, a, x[1], detail::S44, 0x85845dd1);  /* 56 */
    detail::II(a, b, c, d, x[8], detail::S41, 0x6fa87e4f);  /* 57 */
    detail::II(d, a, b, c, x[15], detail::S42, 0xfe2ce6e0); /* 58 */
    detail::II(c, d, a, b, x[6], detail::S43, 0xa3014314);  /* 59 */
    detail::II(b, c, d, a, x[13], detail::S44, 0x4e0811a1); /* 60 */
    detail::II(a, b, c, d, x[4], detail::S41, 0xf7537e82);  /* 61 */
    detail::II(d, a, b, c, x[11], detail::S42, 0xbd3af235); /* 62 */
    detail::II(c, d, a, b, x[2], detail::S43, 0x2ad7d2bb);  /* 63 */
    detail::II(b, c, d, a, x[9], detail::S44, 0xeb86d391);  /* 64 */

    state_[0] += a;
    state_[1] += b;
    state_[2] += c;
    state_[3] += d;
  };

 private:
  bool finalized_{false};
  unsigned char buffer_[blocksize];
  std::uint64_t count_{0};
  uint32_t state_[4]{0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
  unsigned char digest_[16];
};

inline std::string md5sum(std::string const &input) {
  return MD5(input).hexdigest();
}
inline std::string md5sum(const char *input, size_t length) {
  return MD5(input, length).hexdigest();
}
inline std::string md5sum(const unsigned char *input, size_t length) {
  return MD5(input, length).hexdigest();
}
};  // namespace md5

#endif  // __MD5_MD5_HPP__

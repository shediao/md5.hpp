#include <gtest/gtest.h>

#include <algorithm>
#include <environment/environment.hpp>
#include <md5/md5.hpp>
#include <subprocess/subprocess.hpp>

using md5::md5sum;

TEST(MD5Test, Test1){
#undef TEST_MATCH
#define TEST_MATCH(x, y) \
  ASSERT_EQ(md5sum(x), y) << "md5sum(`" << x << "`) == `" << y << "`\n"
#include "./test.h"
}

TEST(MD5Test, Test2) {
  ASSERT_EQ(md5sum("abc"), "900150983cd24fb0d6963f7d28e17f72");
  ASSERT_EQ(md5sum("message digest"), "f96b697d7cb7938d525a2f31aaf161d0");
  ASSERT_EQ(md5sum("abcdefghijklmnopqrstuvwxyz"),
            "c3fcd3d76192e4007dfb496cca67e13b");
  ASSERT_EQ(
      md5sum("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"),
      "d174ab98d277d9f5a5611c2c9f419d9f");
  ASSERT_EQ(md5sum("123456789012345678901234567890123456789012345678901234567"
                   "89012345678901234567890"),
            "57edf4a22be3c955ac49da2e2107b67a");
  ASSERT_EQ(md5sum("你好啊"), "124756ef340daf80196b4124686d651c");
}

void test_md5sum_command(const std::string& s) {
  subprocess::buffer stdout_buf;
  subprocess::buffer stdin_buf{{s.begin(), s.end()}};
  ASSERT_EQ(
      0, subprocess::run("md5sum", $stdout > stdout_buf, $stdin < stdin_buf));
  auto md5 = md5sum(stdin_buf.data(), stdin_buf.size());
  ASSERT_TRUE(std::equal(md5.begin(), md5.begin(), stdout_buf.data()));
}

#if !defined(_WIN32)
TEST(MD5Test, Test3) {
  auto envs = env::all();
  for (auto const& [key, value] : envs) {
    test_md5sum_command(key + "=" + value);
  }

  subprocess::buffer buf;
  ASSERT_EQ(0, subprocess::run("uname", "-a", $stdout > buf));
  test_md5sum_command({buf.data(), buf.size()});
  buf.clear();
  ASSERT_EQ(0, subprocess::run("printenv", $stdout > buf));
  test_md5sum_command({buf.data(), buf.size()});
  buf.clear();
}
#endif

TEST(MD5Test, Test4) {
  using namespace md5::literals;

  static_assert("123"_md5 == "202cb962ac59075b964b07152d234b70");

#undef TEST_MATCH
#define TEST_MATCH(x, y) static_assert(x##_md5 == y)
#include "./test.h"
}

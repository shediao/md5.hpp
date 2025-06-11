#include <gtest/gtest.h>

#include <md5/md5.hpp>

using md5::md5sum;

TEST(MD5Test, Test1) {
  ASSERT_EQ(md5sum(""), "d41d8cd98f00b204e9800998ecf8427e");
  ASSERT_EQ(md5sum(" "), "7215ee9c7d9dc229d2921a40e899ec5f");
  ASSERT_EQ(md5sum("!"), "9033e0e305f247c0c3c80d0c7848c8b3");
  ASSERT_EQ(md5sum("\""), "b15835f133ff2e27c7cb28117bfae8f4");
  ASSERT_EQ(md5sum("#"), "01abfc750a0c942167651c40d088531d");
  ASSERT_EQ(md5sum("$"), "c3e97dd6e97fb5125688c97f36720cbe");
  ASSERT_EQ(md5sum("%"), "0bcef9c45bd8a48eda1b26eb0c61c869");
  ASSERT_EQ(md5sum("&"), "6cff047854f19ac2aa52aac51bf3af4a");
  ASSERT_EQ(md5sum("("), "84c40473414caf2ed4a7b1283e48bbf4");
  ASSERT_EQ(md5sum(")"), "9371d7a2e3ae86a00aab4771e39d255d");
  ASSERT_EQ(md5sum("*"), "3389dae361af79b04c9c8e7057f60cc6");
  ASSERT_EQ(md5sum("+"), "26b17225b626fb9238849fd60eabdf60");
  ASSERT_EQ(md5sum(","), "c0cb5f0fcf239ab3d9c1fcd31fff1efc");
  ASSERT_EQ(md5sum("-"), "336d5ebc5436534e61d16e63ddfca327");
  ASSERT_EQ(md5sum("."), "5058f1af8388633f609cadb75a75dc9d");
  ASSERT_EQ(md5sum("/"), "6666cd76f96956469e7be39d750cc7d9");
  ASSERT_EQ(md5sum("0"), "cfcd208495d565ef66e7dff9f98764da");
  ASSERT_EQ(md5sum("1"), "c4ca4238a0b923820dcc509a6f75849b");
  ASSERT_EQ(md5sum("2"), "c81e728d9d4c2f636f067f89cc14862c");
  ASSERT_EQ(md5sum("3"), "eccbc87e4b5ce2fe28308fd9f2a7baf3");
  ASSERT_EQ(md5sum("4"), "a87ff679a2f3e71d9181a67b7542122c");
  ASSERT_EQ(md5sum("5"), "e4da3b7fbbce2345d7772b0674a318d5");
  ASSERT_EQ(md5sum("6"), "1679091c5a880faf6fb5e6087eb1b2dc");
  ASSERT_EQ(md5sum("7"), "8f14e45fceea167a5a36dedd4bea2543");
  ASSERT_EQ(md5sum("8"), "c9f0f895fb98ab9159f51fd0297e236d");
  ASSERT_EQ(md5sum("9"), "45c48cce2e2d7fbdea1afc51c7c6ad26");
  ASSERT_EQ(md5sum(":"), "853ae90f0351324bd73ea615e6487517");
  ASSERT_EQ(md5sum(";"), "9eecb7db59d16c80417c72d1e1f4fbf1");
  ASSERT_EQ(md5sum("<"), "524a50782178998021a88b8cd4c8dcd8");
  ASSERT_EQ(md5sum("="), "43ec3e5dee6e706af7766fffea512721");
  ASSERT_EQ(md5sum(">"), "cedf8da05466bb54708268b3c694a78f");
  ASSERT_EQ(md5sum("?"), "d1457b72c3fb323a2671125aef3eab5d");
  ASSERT_EQ(md5sum("@"), "518ed29525738cebdac49c49e60ea9d3");
  ASSERT_EQ(md5sum("A"), "7fc56270e7a70fa81a5935b72eacbe29");
  ASSERT_EQ(md5sum("B"), "9d5ed678fe57bcca610140957afab571");
  ASSERT_EQ(md5sum("C"), "0d61f8370cad1d412f80b84d143e1257");
  ASSERT_EQ(md5sum("D"), "f623e75af30e62bbd73d6df5b50bb7b5");
  ASSERT_EQ(md5sum("E"), "3a3ea00cfc35332cedf6e5e9a32e94da");
  ASSERT_EQ(md5sum("F"), "800618943025315f869e4e1f09471012");
  ASSERT_EQ(md5sum("G"), "dfcf28d0734569a6a693bc8194de62bf");
  ASSERT_EQ(md5sum("H"), "c1d9f50f86825a1a2302ec2449c17196");
  ASSERT_EQ(md5sum("I"), "dd7536794b63bf90eccfd37f9b147d7f");
  ASSERT_EQ(md5sum("J"), "ff44570aca8241914870afbc310cdb85");
  ASSERT_EQ(md5sum("K"), "a5f3c6a11b03839d46af9fb43c97c188");
  ASSERT_EQ(md5sum("L"), "d20caec3b48a1eef164cb4ca81ba2587");
  ASSERT_EQ(md5sum("M"), "69691c7bdcc3ce6d5d8a1361f22d04ac");
  ASSERT_EQ(md5sum("N"), "8d9c307cb7f3c4a32822a51922d1ceaa");
  ASSERT_EQ(md5sum("O"), "f186217753c37b9b9f958d906208506e");
  ASSERT_EQ(md5sum("P"), "44c29edb103a2872f519ad0c9a0fdaaa");
  ASSERT_EQ(md5sum("Q"), "f09564c9ca56850d4cd6b3319e541aee");
  ASSERT_EQ(md5sum("R"), "e1e1d3d40573127e9ee0480caf1283d6");
  ASSERT_EQ(md5sum("S"), "5dbc98dcc983a70728bd082d1a47546e");
  ASSERT_EQ(md5sum("T"), "b9ece18c950afbfa6b0fdbfa4ff731d3");
  ASSERT_EQ(md5sum("U"), "4c614360da93c0a041b22e537de151eb");
  ASSERT_EQ(md5sum("V"), "5206560a306a2e085a437fd258eb57ce");
  ASSERT_EQ(md5sum("W"), "61e9c06ea9a85a5088a499df6458d276");
  ASSERT_EQ(md5sum("X"), "02129bb861061d1a052c592e2dc6b383");
  ASSERT_EQ(md5sum("Y"), "57cec4137b614c87cb4e24a3d003a3e0");
  ASSERT_EQ(md5sum("Z"), "21c2e59531c8710156d34a3c30ac81d5");
  ASSERT_EQ(md5sum("["), "815417267f76f6f460a4a61f9db75fdb");
  ASSERT_EQ(md5sum("\\"), "28d397e87306b8631f3ed80d858d35f0");
  ASSERT_EQ(md5sum("]"), "0fbd1776e1ad22c59a7080d35c7fd4db");
  ASSERT_EQ(md5sum("^"), "7e6a2afe551e067a75fafacf47a6d981");
  ASSERT_EQ(md5sum("_"), "b14a7b8059d9c055954c92674ce60032");
  ASSERT_EQ(md5sum("`"), "833344d5e1432da82ef02e1301477ce8");
  ASSERT_EQ(md5sum("a"), "0cc175b9c0f1b6a831c399e269772661");
  ASSERT_EQ(md5sum("b"), "92eb5ffee6ae2fec3ad71c777531578f");
  ASSERT_EQ(md5sum("c"), "4a8a08f09d37b73795649038408b5f33");
  ASSERT_EQ(md5sum("d"), "8277e0910d750195b448797616e091ad");
  ASSERT_EQ(md5sum("e"), "e1671797c52e15f763380b45e841ec32");
  ASSERT_EQ(md5sum("f"), "8fa14cdd754f91cc6554c9e71929cce7");
  ASSERT_EQ(md5sum("g"), "b2f5ff47436671b6e533d8dc3614845d");
  ASSERT_EQ(md5sum("h"), "2510c39011c5be704182423e3a695e91");
  ASSERT_EQ(md5sum("i"), "865c0c0b4ab0e063e5caa3387c1a8741");
  ASSERT_EQ(md5sum("j"), "363b122c528f54df4a0446b6bab05515");
  ASSERT_EQ(md5sum("k"), "8ce4b16b22b58894aa86c421e8759df3");
  ASSERT_EQ(md5sum("l"), "2db95e8e1a9267b7a1188556b2013b33");
  ASSERT_EQ(md5sum("m"), "6f8f57715090da2632453988d9a1501b");
  ASSERT_EQ(md5sum("n"), "7b8b965ad4bca0e41ab51de7b31363a1");
  ASSERT_EQ(md5sum("o"), "d95679752134a2d9eb61dbd7b91c4bcc");
  ASSERT_EQ(md5sum("p"), "83878c91171338902e0fe0fb97a8c47a");
  ASSERT_EQ(md5sum("q"), "7694f4a66316e53c8cdd9d9954bd611d");
  ASSERT_EQ(md5sum("r"), "4b43b0aee35624cd95b910189b3dc231");
  ASSERT_EQ(md5sum("s"), "03c7c0ace395d80182db07ae2c30f034");
  ASSERT_EQ(md5sum("t"), "e358efa489f58062f10dd7316b65649e");
  ASSERT_EQ(md5sum("u"), "7b774effe4a349c6dd82ad4f4f21d34c");
  ASSERT_EQ(md5sum("v"), "9e3669d19b675bd57058fd4664205d2a");
  ASSERT_EQ(md5sum("w"), "f1290186a5d0b1ceab27f4e77c0c5d68");
  ASSERT_EQ(md5sum("x"), "9dd4e461268c8034f5c8564e155c67a6");
  ASSERT_EQ(md5sum("y"), "415290769594460e2e485922904f345d");
  ASSERT_EQ(md5sum("z"), "fbade9e36a3f36d3d676c1b808451dd7");
  ASSERT_EQ(md5sum("{"), "f95b70fdc3088560732a5ac135644506");
  ASSERT_EQ(md5sum("|"), "b99834bc19bbad24580b3adfa04fb947");
  ASSERT_EQ(md5sum("}"), "cbb184dd8e05c9709e5dcaedaa0495cf");
  ASSERT_EQ(md5sum("~"), "4c761f170e016836ff84498202b99827");
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

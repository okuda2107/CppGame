#include <gtest/gtest.h>

// テストフィクスチャとTEST_Fマクロを使う場合

class MyLibraryTest : public ::testing::Test {
   protected:
    // データメンバーの初期化
    void SetUp() override { data1_ = 2.0; }
    // データメンバー
    double data1_;
}

// テストフィクスチャを使うには、テストケース名とテストフィクスチャ名が一致していなければならない。
TEST_F(MyLibraryTest, Function1Test) {
    double result = Function1(data1_);  // data1_にアクセスできる
}

TEST_F(MyLibraryTest, Class1Test) {
    Class1 obj(data1_);  // data1_にアクセスできる
}

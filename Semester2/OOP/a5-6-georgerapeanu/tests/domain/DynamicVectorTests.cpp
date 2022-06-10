/*!
 * @file DynamicVectorTests.cpp this file contains the implementation for the DynamicVector tests
 */

#pragma once
#include "gtest/gtest.h"
#include "Exceptions.h"
#include "DynamicVector.h"
#include <string>
#include <cassert>
#include <algorithm>

TEST(DynamicVectorTests, generic_test3) {
    DynamicVector<std::string> v(5, "aaa");
    DynamicVector<std::string> v2(v);
    DynamicVector<std::string> v3;
    v3 = v;
    v2[2] = "vvv";
    v3[3] = "bbb";
    ASSERT_EQ(v.size(), 5);
    for (int i = 0; i < (int) v.size(); i++) {
        ASSERT_EQ(v[i], "aaa");
        if (i != 2) {
            ASSERT_EQ(v2[i], "aaa");
        }
        if (i != 3) {
            ASSERT_EQ(v3[i], "aaa");
        }
    }
    ASSERT_EQ(v2[2], "vvv");
    ASSERT_EQ(v3[3], "bbb");
    v2.remove(0);
    ASSERT_EQ(v2.size(), 4);
    for (int i = 0; i < (int) v2.size(); i++) {
        if (i != 1) {
            ASSERT_EQ(v2[i], "aaa");
        } else {
            ASSERT_EQ(v2[i], "vvv");
        }
    }
    EXPECT_THROW(v2.remove(10), DynamicVectorException);
    v2.resize(5);
    ASSERT_EQ(v2.size(), 5);
    for(int i = 0;i < 4;i++){
        if(i != 1){
            ASSERT_EQ(v2[i], "aaa");
        }else{
            ASSERT_EQ(v2[i], "vvv");
        }
    }
    ASSERT_EQ(v2[4], "");
    v2.resize(1);
    ASSERT_EQ(v2.size(), 1);
    ASSERT_EQ(v2[0], "aaa");
    auto tmp_func = [&](const DynamicVector<std::string> &v){
        ASSERT_EQ(v[0], "aaa");
        EXPECT_THROW(v[1], DynamicVectorException);
    };
    tmp_func(v2);
    ASSERT_NE(v2, v);
    ASSERT_EQ(v3, v3);
}

TEST(DynamicVectorTests, generic_test2) {
    DynamicVector<std::string> v(10);
    ASSERT_EQ(v.size(), 10);
    for(int i = 0;i < (int)v.size();i++){
        ASSERT_EQ(v[i], std::string());
    }
    EXPECT_THROW(v[-1], DynamicVectorException);
    EXPECT_THROW(v[10], DynamicVectorException);

    while(v.size() > 0){
        v.pop_back();
    }
    EXPECT_THROW(v.pop_back(), DynamicVectorException);
}

TEST(DynamicVectorTests, generic_test1) {
    DynamicVector<std::string> v;
    ASSERT_EQ(v.size(), 0);
    v.push_back("asfasfasfa");
    ASSERT_EQ(v[0], "asfasfasfa");
    v.push_back("bbbb");
    ASSERT_EQ(v[1], "bbbb");
    std::swap(v[0], v[1]);
    ASSERT_EQ(v.size(), 2);
    v.pop_back();
    ASSERT_EQ(v[0], "bbbb");
    ASSERT_EQ(v.back(), "bbbb");
    v.back() = "a";
    ASSERT_EQ(v.back(), "a");
    v.pop_back();
    EXPECT_THROW(v.back(), DynamicVectorException);
}

TEST(DynamicVectorTests, test_eq) {
    DynamicVector<std::string> v;
    DynamicVector<std::string> v2;
    v.push_back("aaa");
    v2.push_back("aaa");
    ASSERT_EQ(v, v2);
    v2.push_back("safasfsa");
    ASSERT_NE(v, v2);
    v2.pop_back();
    ASSERT_EQ(v, v2);
    v.push_back("bbb");
    v2.push_back("ccc");
    ASSERT_NE(v, v2);
    v.resize(0);
    v2.resize(0);
    ASSERT_EQ(v, v2);
}
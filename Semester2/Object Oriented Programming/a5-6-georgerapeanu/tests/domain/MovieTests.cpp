//
// Created by georgerapeanu on 22.03.2022.
//

#pragma once
#include "Movie.h"
#include "gtest/gtest.h"

TEST(MovieTests, GenericTest1) {
    Movie first("titanic", "romance", 1997, 97, "https://www.youtube.com/watch?v=cIJ8ma0kKtY");
    Movie second(first);
    ASSERT_EQ(second.get_id(), "titanic###1997");
    Movie third = second;
    ASSERT_EQ(first.get_title(), "titanic");
    ASSERT_EQ(first.get_genre(), "romance");
    first.set_year(1000);
    first.set_genre("drama");
    ASSERT_EQ(third.get_year(), 1997);
    ASSERT_EQ(second.get_likes(), 97);
    second.set_title("TITANIC");
    third.set_likes(100);
    first.set_trailer_link("placeholder");
    ASSERT_EQ(first.get_trailer_link(), "placeholder");
    ASSERT_EQ(third.get_likes(), 100);
    ASSERT_EQ(first.get_id(), "titanic###1000");

    Movie empty;
    ASSERT_EQ(empty.get_title(), "");
    ASSERT_EQ(empty.get_genre(), "");
    ASSERT_EQ(empty.get_likes(), 0);
    ASSERT_EQ(empty.get_year(), 0);
    ASSERT_EQ(empty.get_trailer_link(), "");
    ASSERT_NE(empty, first);
    ASSERT_EQ(first, first);
}
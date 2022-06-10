/*!
 * @file MovieControllerTests.cpp this file contains the tests for the movie controller
 */

//
// Created by georgerapeanu on 23.03.2022.
//

#pragma once
#include "Movie.h"
#include "Repository.h"
#include "MovieController.h"



/*!
 * @file MovieController.cpp this file contains the implementations for MovieController
 */

//
// Created by georgerapeanu on 21.03.2022.
//

#pragma once
#include "MovieController.h"
#include "Repository.h"
#include "Movie.h"
#include "Exceptions.h"
#include "gtest/gtest.h"

class MovieControllerTests : public testing::Test{
protected:
    MovieController controller;
    DynamicVector<Movie> movies;
    void SetUp()override{
        controller.add_movie_admin("The_Wolf_of_Wall_Street", "Drama", 2013, 1326274, "https://www.youtube.com/watch?v=iszwuX1AK6A");
        controller.add_movie_admin("American_Psycho", "thriller", 2000, 556104, "https://www.youtube.com/watch?v=5YnGhW4UEhc");
        controller.add_movie_admin("Whiplash", "drama", 2014, 798775, "https://www.youtube.com/watch?v=7d_jQycdQGo");
        controller.add_movie_admin("Inception", "science_fiction", 2010, 2250250, "https://www.youtube.com/watch?v=YoHD9XEInc0");
        controller.add_movie_admin("The_departed", "drama", 2006, 1276764, "https://www.youtube.com/watch?v=iojhqm0JTW4");
        controller.add_movie_admin("Goodfellas", "crime", 1990, 1106463, "https://www.youtube.com/watch?v=qo5jJpHtI1Y");
        controller.add_movie_admin("Gladiator", "adventure", 2000, 1443081, "https://www.youtube.com/watch?v=P5ieIbInFpg");
        controller.add_movie_admin("The_Truman_Show", "comedy", 1998, 1025789, "https://www.youtube.com/watch?v=dlnmQbPGuls");
        controller.add_movie_admin("The_Dark_Knight", "adventure", 2008, 2525486, "https://www.youtube.com/watch?v=LDG9bisJEaI");
        controller.add_movie_admin("Catch_me_if_you_can", "drama", 2002, 928668, "https://www.youtube.com/watch?v=lN6Irv9tnYI");
        movies.push_back(Movie("the_wolf_of_wall_street", "drama", 2013, 1326274, "https://www.youtube.com/watch?v=iszwuX1AK6A"));
        movies.push_back(Movie("american_psycho", "thriller", 2000, 556104, "https://www.youtube.com/watch?v=5YnGhW4UEhc"));
        movies.push_back(Movie("whiplash", "drama", 2014, 798775, "https://www.youtube.com/watch?v=7d_jQycdQGo"));
        movies.push_back(Movie("inception", "science_fiction", 2010, 2250250, "https://www.youtube.com/watch?v=YoHD9XEInc0"));
        movies.push_back(Movie("the_departed", "drama", 2006, 1276764, "https://www.youtube.com/watch?v=iojhqm0JTW4"));
        movies.push_back(Movie("goodfellas", "crime", 1990, 1106463, "https://www.youtube.com/watch?v=qo5jJpHtI1Y"));
        movies.push_back(Movie("gladiator", "adventure", 2000, 1443081, "https://www.youtube.com/watch?v=P5ieIbInFpg"));
        movies.push_back(Movie("the_truman_show", "comedy", 1998, 1025789, "https://www.youtube.com/watch?v=dlnmQbPGuls"));
        movies.push_back(Movie("the_dark_knight", "adventure", 2008, 2525486, "https://www.youtube.com/watch?v=LDG9bisJEaI"));
        movies.push_back(Movie("catch_me_if_you_can", "drama", 2002, 928668, "https://www.youtube.com/watch?v=lN6Irv9tnYI"));
    }
};

TEST_F(MovieControllerTests, test_add_movie_admin){
    ASSERT_EQ(controller.get_all_movies_admin(), movies);
    EXPECT_THROW(controller.add_movie_admin("inception", "sf", 2010, 22, ""), MovieControllerException);
    controller.add_movie_admin("Inception", "science_fiction", 2011, 2250250, "https://www.youtube.com/watch?v=YoHD9XEInc0");
    movies.push_back(Movie("inception", "science_fiction", 2011, 2250250,"https://www.youtube.com/watch?v=YoHD9XEInc0"));
    ASSERT_EQ(controller.get_all_movies_admin(), movies);
}

TEST_F(MovieControllerTests, test_update_movie_admin){
    EXPECT_THROW(controller.update_movie_admin("inception", "sf", 2011, 22, ""), MovieControllerException);
    controller.update_movie_admin("Inception", "SF", 2010, 100, "nOp");
    movies[3] = Movie("inception", "sf", 2010, 100, "nOp");
    ASSERT_EQ(controller.get_all_movies_admin(), movies);
}

TEST_F(MovieControllerTests, test_remove_movie_admin){
    EXPECT_THROW(controller.remove_movie_admin("inception", 2011), MovieControllerException);
    controller.remove_movie_admin("Inception", 2010);
    movies.remove(3);
    ASSERT_EQ(controller.get_all_movies_admin(), movies);
}

TEST_F(MovieControllerTests, test_get_movie_user){
    EXPECT_THROW(controller.get_movie_user("inception", 2011), MovieControllerException);
    ASSERT_EQ(controller.get_movie_user("inception", 2010), movies[3]);
}

TEST_F(MovieControllerTests, test_get_movies_user){
    ASSERT_EQ(controller.get_movies_user("idk"), DynamicVector<Movie>());
    DynamicVector<Movie> controller_movies = controller.get_movies_user("adventure");
    DynamicVector<Movie> expected_movies;
    expected_movies.push_back(movies[6]);
    expected_movies.push_back(movies[8]);
    ASSERT_EQ(controller_movies, expected_movies);
}

TEST_F(MovieControllerTests, test_add_movie_user){
    controller.add_movie_user(movies[0]);
    EXPECT_THROW(controller.add_movie_user(movies[0]), ControllerException);
    controller.add_movie_user(movies[3]);
    DynamicVector<Movie> expected_movies;
    expected_movies.push_back(movies[0]);
    expected_movies.push_back(movies[3]);
    ASSERT_EQ(controller.get_watchlist_user(), expected_movies);
}

TEST_F(MovieControllerTests, test_remove_movie_user){
    controller.add_movie_user(movies[0]);
    EXPECT_THROW(controller.add_movie_user(movies[0]), ControllerException);
    controller.add_movie_user(movies[3]);
    controller.remove_movie_user(movies[0]);
    controller.add_movie_user(movies[1]);
    controller.add_movie_user(movies[0]);
    DynamicVector<Movie> expected_movies;
    expected_movies.push_back(movies[3]);
    expected_movies.push_back(movies[1]);
    expected_movies.push_back(movies[0]);
    EXPECT_THROW(controller.remove_movie_user(movies[2]), ControllerException);
    ASSERT_EQ(controller.get_watchlist_user(), expected_movies);
}

TEST_F(MovieControllerTests, test_get_watchlist_user){
    ASSERT_EQ(controller.get_watchlist_user(), DynamicVector<Movie>());
    controller.add_movie_user(movies[0]);
    controller.add_movie_user(movies[3]);
    DynamicVector<Movie> expected_movies;
    expected_movies.push_back(movies[0]);
    expected_movies.push_back(movies[3]);
    ASSERT_EQ(controller.get_watchlist_user(), expected_movies);
}

TEST_F(MovieControllerTests, test_like_movie_user){
    controller.like_movie_user(movies[0]);
    movies[0].set_likes(movies[0].get_likes() + 1);
    ASSERT_EQ(movies, controller.get_all_movies_admin());
    controller.like_movie_user(movies[2]);
    movies[2].set_likes(movies[2].get_likes() + 1);
    ASSERT_EQ(movies, controller.get_all_movies_admin());
}

TEST_F(MovieControllerTests, test_get_all_movies_admin){
    ASSERT_EQ(controller.get_all_movies_admin(), movies);
}

TEST_F(MovieControllerTests, test_my_to_lower){
    ASSERT_EQ(" asfsafasfasv ra   ", controller.my_tolower(" AsFSafAsFasv Ra   "));
    ASSERT_EQ("abcdefghijklmnopqrstuvwxyz1234567890", controller.my_tolower("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"));
}

TEST_F(MovieControllerTests, test_copy){
    MovieController controller2(controller);
    controller.remove_movie_admin("inception", 2010);
    ASSERT_EQ(controller2.get_all_movies_admin(), movies);
}

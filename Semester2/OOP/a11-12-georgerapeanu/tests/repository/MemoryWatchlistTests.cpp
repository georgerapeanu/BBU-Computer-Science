/*!
 * @file MemoryWatchlistTests.cpp this file contains the tests for the repository
 */

#include "gtest/gtest.h"
#include "MemoryWatchlist.h"
#include "Exceptions.h"
#include "Movie.h"
#include <cstdio>

using namespace std;

class MemoryWatchlistTests:public testing::Test{
protected:
    MemoryWatchlist<Movie> repository;
    void SetUp()override{
        repository = MemoryWatchlist<Movie>();
        repository.add(Movie("movie1", "genre1", 1, 10, "trailer1"));
        repository.add(Movie("movie2", "genre2", 2, 12, "trailer2"));
        repository.add(Movie("movie1", "genre1", 2, 10, "trailer1"));
    }
};

TEST_F(MemoryWatchlistTests, test_add){
    EXPECT_THROW(repository.add(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    vector<Movie> movies = repository.get_all();
    vector<Movie> expected_movies;
    expected_movies.push_back(Movie("movie1", "genre1", 1, 10, "trailer1"));
    expected_movies.push_back(Movie("movie2", "genre2", 2, 12, "trailer2"));
    expected_movies.push_back(Movie("movie1", "genre1", 2, 10, "trailer1"));
    ASSERT_EQ(expected_movies, movies);
}

TEST_F(MemoryWatchlistTests, test_update){
    EXPECT_THROW(repository.add(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    repository.update(Movie("movie1", "genre_new", 1, 200, "trailer_new"));
    EXPECT_THROW(repository.add(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    EXPECT_THROW(repository.update(Movie("movie1", "genre3", 45, 10, "trailer3")), RepositoryException);
    vector<Movie> movies = repository.get_all();
    vector<Movie> expected_movies;
    expected_movies.push_back(Movie("movie1", "genre_new", 1, 200, "trailer_new"));
    expected_movies.push_back(Movie("movie2", "genre2", 2, 12, "trailer2"));
    expected_movies.push_back(Movie("movie1", "genre1", 2, 10, "trailer1"));
    ASSERT_EQ(expected_movies, movies);
}

TEST_F(MemoryWatchlistTests, test_remove){
    EXPECT_THROW(repository.add(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    repository.remove(Movie("movie1", "genre_new", 1, 200, "trailer_new"));
    EXPECT_THROW(repository.remove(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    repository.add(Movie("movie1", "genre3", 1, 10, "trailer3"));

    vector<Movie> movies = repository.get_all();
    vector<Movie> expected_movies;
    expected_movies.push_back(Movie("movie2", "genre2", 2, 12, "trailer2"));
    expected_movies.push_back(Movie("movie1", "genre1", 2, 10, "trailer1"));
    expected_movies.push_back(Movie("movie1", "genre3", 1, 10, "trailer3"));
    ASSERT_EQ(expected_movies, movies);
}

TEST_F(MemoryWatchlistTests, test_find){
    ASSERT_EQ(repository.find(Movie("movie1","nop",1,0,"nop")),Movie("movie1", "genre1", 1, 10, "trailer1"));
    ASSERT_EQ(repository.find(Movie("movie2", "genre", 2, 10, "t")), Movie("movie2", "genre2", 2, 12, "trailer2"));
    ASSERT_EQ(repository.find(Movie("movie1", "genre1", 2, 10, "trailer1")), Movie("movie1", "genre1", 2, 10, "trailer1"));
    EXPECT_THROW(repository.find(Movie("movie1","nop",10,0,"nop")), RepositoryException);
    EXPECT_THROW(repository.find(Movie("movie12","nop",1,0,"nop")), RepositoryException);
}
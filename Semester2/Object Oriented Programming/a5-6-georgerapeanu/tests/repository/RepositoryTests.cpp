/*!
 * @file RepositoryTests.cpp this file contains the tests for the reposiory
 */

#include "gtest/gtest.h"
#include "Repository.h"
#include "Movie.h"

TEST(RepositoryTests, test_add){
    Repository<Movie> repository;
    repository.add(Movie("movie1", "genre1", 1, 10, "trailer1"));
    repository.add(Movie("movie2", "genre2", 2, 12, "trailer2"));
    repository.add(Movie("movie1", "genre1", 2, 10, "trailer1"));
    EXPECT_THROW(repository.add(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    DynamicVector<Movie> movies = repository.get_all();
    DynamicVector<Movie> expected_movies;
    expected_movies.push_back(Movie("movie1", "genre1", 1, 10, "trailer1"));
    expected_movies.push_back(Movie("movie2", "genre2", 2, 12, "trailer2"));
    expected_movies.push_back(Movie("movie1", "genre1", 2, 10, "trailer1"));
    ASSERT_EQ(expected_movies, movies);
}

TEST(RepositoryTests, test_update){
    Repository<Movie> repository;
    repository.add(Movie("movie1", "genre1", 1, 10, "trailer1"));
    repository.add(Movie("movie2", "genre2", 2, 12, "trailer2"));
    repository.add(Movie("movie1", "genre1", 2, 10, "trailer1"));
    EXPECT_THROW(repository.add(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    repository.update(Movie("movie1", "genre_new", 1, 200, "trailer_new"));
    EXPECT_THROW(repository.add(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    EXPECT_THROW(repository.update(Movie("movie1", "genre3", 45, 10, "trailer3")), RepositoryException);
    DynamicVector<Movie> movies = repository.get_all();
    DynamicVector<Movie> expected_movies;
    expected_movies.push_back(Movie("movie1", "genre_new", 1, 200, "trailer_new"));
    expected_movies.push_back(Movie("movie2", "genre2", 2, 12, "trailer2"));
    expected_movies.push_back(Movie("movie1", "genre1", 2, 10, "trailer1"));
    ASSERT_EQ(expected_movies, movies);
}

TEST(RepositoryTests, test_remove){
    Repository<Movie> repository;
    repository.add(Movie("movie1", "genre1", 1, 10, "trailer1"));
    repository.add(Movie("movie2", "genre2", 2, 12, "trailer2"));
    repository.add(Movie("movie1", "genre1", 2, 10, "trailer1"));
    EXPECT_THROW(repository.add(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    repository.remove(Movie("movie1", "genre_new", 1, 200, "trailer_new"));
    EXPECT_THROW(repository.remove(Movie("movie1", "genre3", 1, 10, "trailer3")), RepositoryException);
    repository.add(Movie("movie1", "genre3", 1, 10, "trailer3"));

    DynamicVector<Movie> movies = repository.get_all();
    DynamicVector<Movie> expected_movies;
    expected_movies.push_back(Movie("movie2", "genre2", 2, 12, "trailer2"));
    expected_movies.push_back(Movie("movie1", "genre1", 2, 10, "trailer1"));
    expected_movies.push_back(Movie("movie1", "genre3", 1, 10, "trailer3"));
    ASSERT_EQ(expected_movies, movies);
}

TEST(RepositoryTests, test_copy){
    Repository<Movie> repository;
    repository.add(Movie("movie1", "genre1", 1, 10, "trailer1"));
    repository.add(Movie("movie2", "genre2", 2, 12, "trailer2"));
    repository.add(Movie("movie1", "genre1", 2, 10, "trailer1"));

    Repository<Movie> repository2(repository);

    repository2.remove(Movie("movie1", "genre_new", 1, 200, "trailer_new"));
    repository2.add(Movie("movie1", "genre3", 1, 10, "trailer3"));


    {
        DynamicVector<Movie> movies = repository2.get_all();
        DynamicVector<Movie> expected_movies;
        expected_movies.push_back(Movie("movie2", "genre2", 2, 12, "trailer2"));
        expected_movies.push_back(Movie("movie1", "genre1", 2, 10, "trailer1"));
        expected_movies.push_back(Movie("movie1", "genre3", 1, 10, "trailer3"));
        ASSERT_EQ(expected_movies, movies);
    }
    {
        DynamicVector<Movie> movies = repository.get_all();
        DynamicVector<Movie> expected_movies;
        expected_movies.push_back(Movie("movie1", "genre1", 1, 10, "trailer1"));
        expected_movies.push_back(Movie("movie2", "genre2", 2, 12, "trailer2"));
        expected_movies.push_back(Movie("movie1", "genre1", 2, 10, "trailer1"));
        ASSERT_EQ(expected_movies, movies);
    }
}

TEST(RepositoryTests, test_find){
    Repository<Movie> repository;
    repository.add(Movie("movie1", "genre1", 1, 10, "trailer1"));
    repository.add(Movie("movie2", "genre2", 2, 12, "trailer2"));
    repository.add(Movie("movie1", "genre1", 2, 10, "trailer1"));

    ASSERT_EQ(repository.find(Movie("movie1","",1,0,"")),Movie("movie1", "genre1", 1, 10, "trailer1"));
    ASSERT_EQ(repository.find(Movie("movie2", "genre", 2, 10, "t")), Movie("movie2", "genre2", 2, 12, "trailer2"));
    ASSERT_EQ(repository.find(Movie("movie1", "genre1", 2, 10, "trailer1")), Movie("movie1", "genre1", 2, 10, "trailer1"));
    EXPECT_THROW(repository.find(Movie("movie1","",10,0,"")), RepositoryException);
    EXPECT_THROW(repository.find(Movie("movie12","",1,0,"")), RepositoryException);
}
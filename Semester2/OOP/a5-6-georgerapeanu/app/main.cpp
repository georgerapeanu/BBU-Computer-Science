/*!
 * @file main.cpp the main file of the application
 */

#include "Movie.h"
#include "Repository.h"
#include "MovieController.h"
#include "UI.h"

int main(){
    MovieController controller;
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

    UI ui(controller);
    ui.run();
    return 0;
}
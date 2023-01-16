#pragma once
#include "library.h"

MovieLibrary::MovieLibrary() {
    printf("MovieLibrary Created.\n");
    movies = new std::vector<Movie*>{      // Create <Vector> Pointer
    new Movie(		// Create Movie Pointer
        "Once_Upon_a_Time_in_Hollywood.png", "Once Upon a Time in Hollywood",
        "Quentin Tarantino",
        new std::vector<std::string> { "Comedy", "Drama" },
        new std::vector<std::string> { "Leonardo DiCaprio", "Brad Pitt", "Margot Robbie" },
        2019),
    new Movie(		// Create Movie Pointer
        "The_Hateful_Eight.png", "The Heightful Eight",
        "Quentin Tarantino",
        new std::vector<std::string> { "Crime", "Drama", "Mystery"},
        new std::vector<std::string> { "Samuel L. Jackson", "Kurt Russell", "Jennifer J. Leigh" },
        2015),
    new Movie(		// Create Movie Pointer
        "Django_Unchained.png", "Django Unchained",
        "Quentin Tarantino",
        new std::vector<std::string>{ "Drama", "Western" },
        new std::vector<std::string>{ "Jamie Foxx", "Christoph Waltz", "Leonardo DiCaprio" },
        2012),
    new Movie(		// Create Movie Pointer
        "Kill_Bill_The_Whole_Bloody_Affair.png", "Kill Bill: The Whole Bloody Affair",
        "Quentin Tarantino",
        new std::vector<std::string>{ "Action", "Crime"},
        new std::vector<std::string>{ "Uma Thurman", "Lucy Liu", "Vivica A. Fox" },
        2011),
    new Movie(		// Create Movie Pointer
        "Inglourious_Basterds.png", "Inglourious Basterds",
        "Quentin Tarantino",
        new std::vector<std::string>{ "Adventure", "Drama", "War"},
        new std::vector<std::string>{ "Brad Pitt", "Diane Kruger", "Eli Roth" },
        2009),
    new Movie(		// Create Movie Pointer
        "The_Irishman.png", "The Irishman",
        "Martin Scorsese",
        new std::vector<std::string>{ "Biography", "Crime", "Drama"},
        new std::vector<std::string>{ "Robert De Niro", "Al Pacino", "Joe Pesci" },
        2019),
    new Movie(		// Create Movie Pointer
        "Rolling_Thunder_Revenue.png", "Rolling Thunder Revue",
        "Martin Scorsese",
        new std::vector<std::string>{ "Documentary", "Biography", "History"},
        new std::vector<std::string>{ "Bod Dylan", "Allen Ginsberg", "Patti Smith" },
        2019),
    new Movie(		// Create Movie Pointer
        "Silence.png", "Silence",
        "Martin Scorsese",
        new std::vector<std::string>{ "Drama", "History" },
        new std::vector<std::string>{ "Andrew Garfield", "Adam Driver", "Liam Neeson" },
        2016),
    new Movie(		// Create Movie Pointer
        "The_50_Year_Argument.png", "The 50 Year Argument",
        "Martin Scorsese",
        new std::vector<std::string>{ "Documentary"},
        new std::vector<std::string>{ "Bod Dylan", "Allen Ginsberg", "Patti Smith" },
        2014),
    new Movie(		// Create Movie Pointer
        "The_Wolf_of_Wall_Street.png", "The Wolf of Wall Street",
        "Martin Scorsese",
        new std::vector<std::string>{ "Biography", "Comedy", "Crime"},
        new std::vector<std::string>{ "Leonardo DiCaprio", "Jonah Hill", "Margot Robbie" },
        2013),
    new Movie(		// Create Movie Pointer
        "Avatar_The_Way_of_Water.png", "Avatar: The Way of Water",
        "James Cameron",
        new std::vector<std::string>{ "Action", "Adventure", "Fantasy"},
        new std::vector<std::string>{ "Sam Worthington", "Zoe Saldana", "Sigourney Weaver" },
        2022),
    new Movie(		// Create Movie Pointer
        "Avatar.png", "Avatar",
        "James Cameron",
        new std::vector<std::string>{ "Action", "Adventure", "Fantasy"},
        new std::vector<std::string>{ "Sam Worthington", "Zoe Saldana", "Sigourney Weaver" },
        2009),
    new Movie(		// Create Movie Pointer
        "Aliens_of_the_Deep.png", "Aliens of the Deep",
        "James Cameron",
        new std::vector<std::string>{ "Documentary"},
        new std::vector<std::string>{ "James Cameron", "Anatoly M. Sagalevitch", "Genya Chernaiev" },
        2005),
    new Movie(		// Create Movie Pointer
        "Titanic.png", "Titanic",
        "James Cameron",
        new std::vector<std::string>{ "Drama", "Romance" },
        new std::vector<std::string>{ "Leonardo DiCaprio", "Kate Winslet", "Billy Zane" },
        1997),
    new Movie(		// Create Movie Pointer
        "Terminator_2_Judgment_Day.png", "Terminator 2: Judgment Day",
        "James Cameron",
        new std::vector<std::string>{ "Action", "Sci-Fi" },
        new std::vector<std::string>{ "Arnold Schwarzenegger", "Linda Hamilton", "Edward Furlong" },
        1991),
    new Movie(		// Create Movie Pointer
        "The_Fabelmans.png", "The Fabelmans",
        "Steven Spielberg",
        new std::vector<std::string>{ "Drama" },
        new std::vector<std::string>{ "Michelle Williams", "Gabriel LaBelle", "Paul Dano" },
        2022),
    new Movie(		// Create Movie Pointer
        "West_Side_Story.png", "West Side Story",
        "Steven Spielberg",
        new std::vector<std::string>{ "Crime", "Drama", "Musical"},
        new std::vector<std::string>{ "Ansel Elgort", "Rachel Zegler", "Ariana DeBose" },
        2021),
    new Movie(		// Create Movie Pointer
        "Ready_Player_One.png", "Ready Player One",
        "Steven Spielberg",
        new std::vector<std::string>{ "Action", "Adventure", "Sci-Fi"},
        new std::vector<std::string>{ "Tye Sheridan", "Olivia Cooke", "Ben Mendelsohn" },
        2018),
    new Movie(		// Create Movie Pointer
        "Bride_of_Spies.png", "Bride of Spies",
        "Steven Spielberg",
        new std::vector<std::string>{ "Drama", "History"},
        new std::vector<std::string>{ "Tom Hanks", "Mark Rylance", "Alan Alda" },
        2015),
    new Movie(		// Create Movie Pointer
        "Lincoln.png", "Lincoln",
        "Steven Spielberg",
        new std::vector<std::string>{ "Biography", "Drama", "History"},
        new std::vector<std::string>{ "Daniel Day-Lewis", "Sally Field", "David Strathairn" },
        2012) };
    genres = new std::set<std::string>;		// Create <Set> Pointer
    years = new std::set<int>;		        // Create <Set> Pointer
    for (const auto& movie : *movies) {
        for (const auto& genre : *(movie->getGenres()))
            genres->insert(genre);
        years->insert(movie->getYear());
    }

}

MovieLibrary::~MovieLibrary() {
    if (movies) {
        for (const auto& movie: *movies)
            delete movie;	// Delete Movie Objects
        movies->clear();	// Delete Movie Pointers
        delete movies;		// Delete <Vector> Pointer
        movies = nullptr;
        printf("MovieLibrary: Movies Destroyed.\n");
    }
    if (genres) {
        delete genres;		// Delete <Set> Pointer
        genres = nullptr;
        printf("MovieLibrary: Genres Destroyed.\n");
    }
    if (years) {
        delete years;		// Delete <Set> Pointer
        years = nullptr;
        printf("MovieLibrary: Years Destroyed.\n");
    }
    printf("MovieLibrary Destroyed.\n");
}
#pragma once
#include "Movie.h"
#include <set>

class MovieLibrary {

private:
    std::vector<Movie*>* movies = nullptr;
    std::set<std::string>* genres = nullptr;
    std::set<int>* years = nullptr;

public:

    MovieLibrary();
    ~MovieLibrary();

    std::vector<Movie*>* getMovies() const { return movies; }
    std::set<std::string>* getGenres() const { return genres; }
    std::set<int>* getYears() const { return years; }

};
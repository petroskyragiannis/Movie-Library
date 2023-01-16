#pragma once
#include <string>
#include <vector>

class Movie {

private:

	const std::string path;
	const std::string title;
	const std::string director;
	const std::vector<std::string>* const genres = nullptr;
	const std::vector<std::string>* const actors = nullptr;
	const int year;

public:

	Movie(const std::string& p, const std::string& t, const std::string& dir, std::vector<std::string>* g, std::vector<std::string>* a, const int& y) :
		path(p), title(t), director(dir), genres(g), actors(a), year(y) {
		printf("Movie Created.\n");
	}

	~Movie() {
		if (genres) {
			delete genres;
			//printf("Movie: Genres Destroyed.\n");
		}
		if (actors) {
			delete actors;
			//printf("Movie: Actors Destroyed.\n");
		}
		printf("Movie Destroyed.\n");
	}

	const std::string& getPath() const { return path; }
	const std::string& getTitle() const { return title; }
	const std::string& getDirector() const { return director; }
	const std::vector<std::string>* getGenres() const { return genres; }
	const std::vector<std::string>* getActors() const { return actors; }
	const int& getYear() const { return year; }
};
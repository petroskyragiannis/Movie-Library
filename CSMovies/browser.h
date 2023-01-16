#pragma once
#include "gui.h"
#include "library.h"

class Browser {

	GUI* gui = nullptr;
	MovieLibrary* movie_library = nullptr;
	std::set<std::string>* genre_filters = nullptr;
	std::pair<int, int>* year_filters = nullptr;

public:
	Browser();
	~Browser();
	void init();
	void draw();
	void update();

	std::set<std::string>* getGenreFilters() { return genre_filters; }
	std::pair<int, int>* getYearFilters() { return year_filters; }
	
	void clearFilters();
	void applyFilters();
	void openWindow(Movie* movie);
};
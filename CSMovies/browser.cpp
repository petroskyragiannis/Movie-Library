#pragma once
#include "graphics.h"
#include "config.h"
#include "browser.h"
#include "gui.h"

Browser::Browser() {
	printf("Browser Created.\n");
}

Browser::~Browser() {
	if (gui) delete gui;						// Delete GUI
	if (movie_library) delete movie_library;	// Delete MovieLibrary
	if (genre_filters) delete genre_filters;	// Delete Genre Filters
	if (year_filters) delete year_filters;		// Delete Year Filters
	printf("Browser Destroyed.\n");
}

void Browser::init() {

	// Initialize Variables
	gui = new GUI();
	movie_library = new MovieLibrary();
	genre_filters = new std::set<std::string>;
	year_filters = new std::pair<int, int>{ *movie_library->getYears()->begin(), *movie_library->getYears()->rbegin()};

	// Set Application's Font
	graphics::setFont(std::string(ASSET_PATH) + "Roboto-Regular.ttf");

	// Create GenreButton Widgets
	float g_x = 10, g_y = 50;
	float g_width = 0, g_height = 1.5 * FONT_SIZE;
	for (const auto& genre : *(movie_library->getGenres())) {
		g_width = 0.65 * FONT_SIZE * genre.length();
		g_x += g_width / 2;
		if (g_x + g_width / 2 + 10 > CANVAS_WIDTH / 2) {
			g_x = g_width / 2 + 10;
			g_y += 1.5 * FONT_SIZE + 10;
		}
		gui->add(new GenreButton(genre, g_x, g_y, g_width, g_height, this));
		g_x += g_width / 2 + 10;
	}

	// Create Slider Widgets
	gui->add(new Slider(std::vector<int> (movie_library->getYears()->begin(), movie_library->getYears()->end()), true, 0.7 * CANVAS_WIDTH + 10, 50, 0.25 * CANVAS_WIDTH, 5, this));
	gui->add(new Slider(std::vector<int> (movie_library->getYears()->begin(), movie_library->getYears()->end()), false, 0.7 * CANVAS_WIDTH + 10, 75, 0.25 * CANVAS_WIDTH, 5, this));

	// Create ClearFilters Widget
	gui->add(new ClearFiltersButton(0.9 * CANVAS_WIDTH, 60, 75, 25, this));
	
	// Create MovieButton Widgets
	float m_x = IMAGE_WIDTH / 2;
	float m_y = IMAGE_HEIGHT;
	for (const auto& movie : *movie_library->getMovies()) {
		if (m_x >= CANVAS_WIDTH) {
			m_x -= CANVAS_WIDTH;
			m_y += IMAGE_HEIGHT;
		}
		gui->add(new MovieButton(movie, m_x, m_y, IMAGE_WIDTH, IMAGE_HEIGHT, this));
		m_x += IMAGE_WIDTH;
	}

	// Create MovieWindow Widget.
	gui->add(new MovieWindow(nullptr, CANVAS_WIDTH/2, CANVAS_HEIGHT - IMAGE_HEIGHT, 6 * IMAGE_WIDTH, 1.5 * IMAGE_HEIGHT, this));
}

void Browser::draw() {
	gui->draw();
}

void Browser::update() {
	gui->update();
}

void Browser::clearFilters() {
	genre_filters->clear();
	year_filters->first = *movie_library->getYears()->begin();
	year_filters->second = *movie_library->getYears()->rbegin();
	for (const auto& w : *gui->getGenreButtons())
		w->setChecked(false);
	for (const auto& w : *gui->getSliders())
		w->init();
}

void Browser::applyFilters() {
	float x = IMAGE_WIDTH / 2, y = IMAGE_HEIGHT;
	for (const auto& m: *gui->getMovieButtons()) {
		bool visible = true;
		if (year_filters->first > m->getMovie()->getYear() ||
			year_filters->second < m->getMovie()->getYear()) {
			visible = false;
		}
		if (!genre_filters->empty())
			for (const auto& filter : *genre_filters) {
				if (std::find(m->getMovie()->getGenres()->begin(), m->getMovie()->getGenres()->end(), filter) 
					== m->getMovie()->getGenres()->end())
					visible = false;
			}
		m->setVisible(visible);
		// Set Position for Visible ImageButtons
		if (m->isVisible()) {
			if (x >= CANVAS_WIDTH) {
				x -= CANVAS_WIDTH;
				y += IMAGE_HEIGHT;
			}
			m->setCoords(x, y);
			x += IMAGE_WIDTH;
		}
	}
}

void Browser::openWindow(Movie* movie) {
	gui->getMovieWindow()->setMovie(movie);
	gui->getMovieWindow()->setVisible(true);
}
#pragma once
#include "movie.h"

class Widget {

protected:

	class Browser* browser;

	float pos_x, pos_y;			// Coordinates
	float width, height;		// Dimensions
	bool visible = true;		// Determines if the Widget is drawn on the screen.
	
	static int next_id;						// Unique ID for each Widget.
	int id = 0;

	static int m_focus;						// The Widget (id) that the mouse is focused on.
	bool requestFocus();
	void releaseFocus();

	bool m_contains(float x, float y);		// Checks if the mouse (x,y) is within the Widget.

public:
	Widget(float x, float y, float w, float h, Browser* br);
	~Widget();
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;

	void setCoords(float x, float y) { pos_x = x, pos_y = y; }
	void setVisible(bool v) { visible = v; }
	bool isVisible() { return visible; }
};

class Button : public Widget {

protected:
	enum button_state {BUTTON_IDLE, BUTTON_HIGHLIGHTED, BUTTON_PRESSED};
	button_state state = BUTTON_IDLE;
	std::string text;

public:
	Button(const std::string& t, float x, float y, float w, float h, Browser* br);
	~Button();
	void init() override;
	void draw() override;
	void update() override;
};

class GenreButton : public Button {

protected:
	bool checked = false;

public:
	GenreButton(const std::string& g, float x, float y, float w, float h, Browser* br);
	~GenreButton();
	void init() override;
	void draw() override;
	void update() override;

	void setChecked(bool c) { checked = c; }
	bool getChecked() { return checked; }
};

class ClearFiltersButton : public Button {
public:
	ClearFiltersButton(float x, float y, float w, float h, Browser* br);
	~ClearFiltersButton();
	void init() override;
	void draw() override;
	void update() override;
};

class MovieButton : public Button {

protected:
	Movie* movie;

public:
	MovieButton(Movie* m, float x, float y, float w, float h, Browser* br);
	~MovieButton();
	void init() override;
	void draw() override;
	void update() override;

	void setMovie(Movie* m) { movie = m; }
	Movie* getMovie() { return movie; }
};

class Window : public Widget {

protected:
	enum window_state { WINDOW_CLOSED, WINDOW_OPEN };
	window_state state = WINDOW_CLOSED;

public:
	Window(float x, float y, float w, float h, Browser* br);
	~Window();
	void init() override;
	void draw() override;
	void update() override;
};

class MovieWindow : public Window {

protected:
	Movie* movie;

public:
	MovieWindow(Movie* m, float x, float y, float w, float h, Browser* br);
	~MovieWindow();
	void init() override;
	void draw() override;
	void update() override;

	void setMovie(Movie* m) { movie = m; }
	Movie* getMovie() { return movie; }
};

class Slider : public Widget {

protected:
	enum slide_direction { SLIDE_LEFT, SLIDE_RIGHT };
	slide_direction direction = SLIDE_RIGHT;

	std::vector<int> data;
	int selected_data;

	bool m_contains(float mx, float my, float x_offset, float y_offset);

public:
	Slider(std::vector<int> d, bool dir, float x, float y, float w, float h, Browser* br);
	~Slider();
	void init() override;
	void draw() override;
	void update() override;
};

class GUI {

private:
	std::vector<Widget*>* widgets = nullptr;
	std::vector<GenreButton*>* genre_buttons = nullptr;
	std::vector<Slider*>* sliders = nullptr;
	std::vector<MovieButton*>* movie_buttons = nullptr;
	MovieWindow* movie_window = nullptr;


public:
	GUI();
	~GUI();
	void init();
	void draw();
	void update();

	std::vector<Widget*>* getWidgets() { return widgets; }
	std::vector<GenreButton*>* getGenreButtons() { return genre_buttons; }
	std::vector<Slider*>* getSliders() { return sliders; }
	std::vector<MovieButton*>* getMovieButtons() { return movie_buttons; }
	MovieWindow* getMovieWindow() { return movie_window; }

	void add(Button* button);
	void add(GenreButton* genre_button);
	void add(Slider* slider);
	void add(MovieButton* movie_button);
	void add(MovieWindow* movie_window);

};
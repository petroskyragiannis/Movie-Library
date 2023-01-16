#pragma once
#include "graphics.h"
#include "config.h"
#include "browser.h"
#include "gui.h"

// Widget

int Widget::next_id = 0;
int Widget::m_focus = 0;

Widget::Widget(float x, float y, float w, float h, Browser* br) :
	pos_x(x), pos_y(y), width(w), height(h), browser(br) {
	id = ++next_id;
}

Widget::~Widget() {}

bool Widget::requestFocus() {
	//printf("Request - ID = %d, Focus ID = %d\n", id, focus);
	if (!m_focus || m_focus == id) {
		m_focus = id;
		return true;
	}
	return false;
}

void Widget::releaseFocus() {
	//printf("Release - ID = %d, Focus ID = %d\n", id, focus);
	if (m_focus = id) m_focus = 0;
}

bool Widget::m_contains(float x, float y) {
	if (x > pos_x - width / 2 && x < pos_x + width / 2
		&& y > pos_y - height / 2 && y < pos_y + height / 2)
		return true;
	return false;
}



// Button

Button::Button(const std::string& t, float x, float y, float w, float h, Browser* br) :
	text(t), Widget(x, y, w, h, br) {}

Button::~Button() {}

void Button::init() {}

void Button::draw() {}

void Button::update() {
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
	if (m_contains(mx, my)) {
		state = BUTTON_HIGHLIGHTED;
		//printf("Button Highlighted\n");
		if (ms.button_left_pressed) {
			if (!requestFocus()) return;
			state = BUTTON_PRESSED;
			//printf("Button Pressed\n");
		}
		else if (ms.button_left_released) {
			state = BUTTON_IDLE;
			releaseFocus();
			//printf("Button Released\n");
		}
	} else {
		state = BUTTON_IDLE;
		//printf("Button Idle\n");
	}
}



// Check Button

GenreButton::GenreButton(const std::string& t, float x, float y, float w, float h, Browser* br) :
	Button(t, x, y, w, h, br) {}

GenreButton::~GenreButton() {}

void GenreButton::init() {}

void GenreButton::draw() {
	if (!visible) return;
	
	// Draw Button Rectangle
	graphics::Brush br;
	if (!checked) {
		br.outline_color[0] = 1.0f;
		br.outline_color[1] = 0.5f;
		br.outline_color[2] = 0.0f;
		br.outline_width = 1;
	} else {
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.5f;
		br.fill_color[2] = 0.0f;
		br.outline_color[0] = 1.0f;
		br.outline_color[1] = 1.0f;
		br.outline_color[2] = 1.0f;
		br.outline_width = 1;
	}
	if (state == BUTTON_HIGHLIGHTED) br.outline_opacity = 1;
	else br.outline_opacity = 0;
	graphics::drawRect(pos_x, pos_y, width, height, br);

	// Draw Button Text
	br.fill_color[0] = 0;
	br.fill_color[1] = 0;
	br.fill_color[2] = 0;
	graphics::drawText(pos_x - width/2 + 1, pos_y + height/4, FONT_SIZE, text, br);
}

void GenreButton::update() {
	Button::update();
	if (!checked && state == BUTTON_PRESSED) {
		checked = true;
		browser->getGenreFilters()->insert(text);
	}
	else if (checked && state == BUTTON_PRESSED) {
		checked = false;
		browser->getGenreFilters()->erase(text);
	}
	browser->applyFilters();
}



// ClearFilters Button

ClearFiltersButton::ClearFiltersButton(float x, float y, float w, float h, Browser* br) :
	Button("Clear Filters", x, y, w, h, br) {}

ClearFiltersButton::~ClearFiltersButton() {}

void ClearFiltersButton::init() {}

void ClearFiltersButton::draw() {
	if (!visible) return;
	
	// Draw Button Rectangle
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 0.0f;
	br.outline_color[0] = 1.0f;
	br.outline_color[1] = 1.0f;
	br.outline_color[2] = 1.0f;
	br.outline_width = 1;
	if (state == BUTTON_IDLE) br.outline_opacity = 0;
	else br.outline_opacity = 1;
	graphics::drawRect(pos_x, pos_y, width, height, br);

	// Draw Button Text
	br.fill_color[0] = 0;
	br.fill_color[1] = 0;
	br.fill_color[2] = 0;
	graphics::drawText(pos_x - width / 2 + 1, pos_y + height / 4, 1.5 * FONT_SIZE, text, br);
}

void ClearFiltersButton::update() {
	Button::update();
	if (state == BUTTON_PRESSED) {
		browser->clearFilters();
		browser->applyFilters();
	}
}



// Movie Button

MovieButton::MovieButton(Movie* m, float x, float y, float w, float h, Browser* br) :
	movie(m), Button(m->getPath(), x, y, w, h, br) {}

MovieButton::~MovieButton() {}

void MovieButton::init() {}

void MovieButton::draw() {
	if (!visible) return;
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + text;
	br.outline_color[0] = 1.0f;
	br.outline_color[1] = 0.5f;
	br.outline_color[2] = 0.0f;
	br.outline_width = 2;
	if (state == BUTTON_IDLE) br.outline_opacity = 0;
	else br.outline_opacity = 1;
	graphics::drawRect(pos_x, pos_y, width, height, br);
}

void MovieButton::update() {
	Button::update();
	if (state == BUTTON_PRESSED) 
		browser->openWindow(movie);
}



// Window

Window::Window(float x, float y, float w, float h, Browser* br) :
	Widget(x, y, w, h, br) {
	visible = false;
}

Window::~Window() {}

void Window::init() {}

void Window::draw() {}

void Window::update() {
	if (!visible || !requestFocus()) return;
	//printf("Window Open.\n");
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
	if (!m_contains(mx, my) && ms.button_left_pressed) {
		visible = false;
		releaseFocus();
		//printf("Window Closed.\n");
	}
}



// Movie Window

MovieWindow::MovieWindow(Movie* m, float x, float y, float w, float h, Browser* br) :
	movie(m), Window(x, y, w, h, br) {}

MovieWindow::~MovieWindow() {}

void MovieWindow::init() {}

void MovieWindow::draw() {
	if (!visible) return;
	float text_y = pos_y - 0.75 * IMAGE_HEIGHT;	// Top of Window
	
	// Apply Font
	graphics::setFont(std::string(ASSET_PATH) + "Roboto-Bold.ttf");

	// Draw Window
	graphics::Brush br;
	br.outline_color[0] = 0.0f;
	br.outline_color[1] = 0.0f;
	br.outline_color[2] = 0.0f;
	br.outline_width = 1;
	br.outline_opacity = 1;
	br.texture = std::string(ASSET_PATH) + "theater.png";
	graphics::drawRect(pos_x, pos_y, width, height, br);
	
	// Draw Movie Title
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	text_y += 2 * FONT_SIZE;
	graphics::drawText(pos_x - 0.375 * FONT_SIZE * movie->getTitle().length(), text_y - 4, 2 * FONT_SIZE, movie->getTitle(), br);

	// Draw Movie Image
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.outline_color[0] = 0.0f;
	br.outline_color[1] = 0.0f;
	br.outline_color[2] = 0.0f;
	br.outline_width = 1;
	br.texture = std::string(ASSET_PATH) + movie->getPath();
	graphics::drawRect(pos_x - 0.75 * IMAGE_WIDTH, text_y + IMAGE_HEIGHT/2 + 10, IMAGE_WIDTH, IMAGE_HEIGHT, br);

	// Draw Movie Genres
	text_y += 1.5 * FONT_SIZE + 10;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(pos_x + 5, text_y, 1.5 * FONT_SIZE, "Genre:", br);
	for (const auto& genre : *movie->getGenres()) {
		graphics::drawText(pos_x + 5 * 1.5 * FONT_SIZE, text_y, 1.5 * FONT_SIZE, genre, br);
		text_y += 1.5 * FONT_SIZE + 5;
	}

	// Draw Movie Director
	text_y += 1.5 * FONT_SIZE + 5;
	graphics::drawText(pos_x + 5, text_y, 1.5 * FONT_SIZE, "Director:", br);
	graphics::drawText(pos_x + 5 * 1.5 * FONT_SIZE, text_y, 1.5 * FONT_SIZE, movie->getDirector(), br);
	text_y += 1.5 * FONT_SIZE + 5;

	// Draw Movie Actors
	text_y += 1.5 * FONT_SIZE + 5;
	graphics::drawText(pos_x + 5, text_y, 1.5 * FONT_SIZE, "Actors:", br);
	for (const auto& a : *movie->getActors()) {	
		graphics::drawText(pos_x + 5 * 1.5 * FONT_SIZE, text_y, 1.5 * FONT_SIZE, a, br);
		text_y += 1.5 * FONT_SIZE + 5;
	}

	// Reset Font
	graphics::setFont(std::string(ASSET_PATH) + "Roboto-Regular.ttf");
}

void MovieWindow::update() {
	Window::update();
}



// Slider

Slider::Slider(std::vector<int> d, bool dir, float x, float y, float w, float h, Browser* br) :
	data(d), Widget(x, y, w, h, br) {
	if (dir) direction = SLIDE_RIGHT;
	else direction = SLIDE_LEFT;
	init();
}

Slider::~Slider() {}

void Slider::init() {
	if (direction == SLIDE_RIGHT) selected_data = data[0];
	else selected_data = data[data.size() - 1];
}

void Slider::draw() {
	if (!visible) return;

	// Draw Slider Rectangle
	graphics::Brush br;
	graphics::drawRect(pos_x, pos_y, width, height, br);

	// Draw Slider Text
	std::string text;
	if (direction == SLIDE_RIGHT) text = "From :";
	else text = "To :";
	graphics::drawText(pos_x - 0.625* width, pos_y + 3, FONT_SIZE, text, br);

	// Draw Selected Data Text
	float x = pos_x - width / 2;
	float margin = width / (data.size() - 1);
	for (int i : data) {
		if (i == selected_data) {
			graphics::drawRect(x, pos_y, 5, 15, br);
			if (direction == SLIDE_RIGHT) graphics::drawText(x - 10, pos_y - 15, FONT_SIZE, std::to_string(i), br);
			else graphics::drawText(x - 10, pos_y + 20, FONT_SIZE, std::to_string(i), br);
		}
		x += margin;
	}
}

void Slider::update() {
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
	float margin = (width / (data.size() - 1));
	if (m_contains(mx, my, 10, 20) && ms.dragging) {
		int n = int(((mx - (pos_x - width / 2)) / margin) + 0.5);
		if (n < 0) n = 0;
		if (n >= data.size() - 1) n = data.size() - 1;
		selected_data = data[n];
		if (direction == SLIDE_RIGHT) browser->getYearFilters()->first = selected_data;
		else browser->getYearFilters()->second = selected_data;
		browser->applyFilters();
	}
}

bool Slider::m_contains(float x, float y, float x_offset, float y_offset) {
	if (x > pos_x - (width + x_offset) / 2 && x < pos_x + (width + x_offset) / 2
		&& y > pos_y - (height + y_offset) / 2 && y < pos_y + (height + y_offset) / 2)
		return true;
	return false;
}



// GUI

GUI::GUI() {
	printf("GUI Created.\n");
	init();
}

GUI::~GUI() { 
	if (widgets) {
		for (auto w : *widgets)
			delete w;					// Delete Widgets
		widgets->clear();				// Delete Widget Pointers
		delete widgets;					// Delete <Vector> Pointer
		printf("GUI: Widgets Destroyed.\n");
	}
	if (genre_buttons) {
		genre_buttons->clear();			// Delete GenreButton Pointers
		delete genre_buttons;			// Delete Vector Pointer
		printf("GUI: CheckButtons Destroyed.\n");
	}
	if (movie_buttons) {
		movie_buttons->clear();			// Delete ImageButton Pointers
		delete movie_buttons;			// Delete Vector Pointer
		printf("GUI: MovieButtons Destroyed.\n");
	}
	if (sliders) {
		sliders ->clear();			// Delete Slider Pointers
		delete sliders;				// Delete Vector Pointer
		printf("GUI: Sliders Destroyed.\n");
	}
	printf("GUI Destroyed.\n");
}

void GUI::init() {
	widgets = new std::vector<Widget*>;
	genre_buttons = new std::vector<GenreButton*>;
	sliders = new std::vector<Slider*>;
	movie_buttons = new std::vector<MovieButton*>;
	movie_window = nullptr;
}

void GUI::draw() {
	for (const auto& widget : *widgets)
		if (widget) widget->draw();
}

void GUI::update() {
	for (const auto& widget : *widgets) 
		if (widget) widget->update();
}

void GUI::add(Button* b) {
	widgets->push_back(b);
}

void GUI::add(GenreButton* b) {
	genre_buttons->push_back(b);
	widgets->push_back(b);
}

void GUI::add(Slider* s) {
	sliders->push_back(s);
	widgets->push_back(s);
}

void GUI::add(MovieButton* b) {
	movie_buttons->push_back(b);
	widgets->push_back(b);
}

void GUI::add(MovieWindow* b) {
	movie_window = b;
	widgets->push_back(b);
}
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include "Go Game.h"
#include <random>
#include <string>

#define ALLEGRO_STATICLINK

using namespace std;

void make_AI_move(int& current, Board* board);
	

#define BLACK (1)
#define WHITE (2)
#define CELL_SIZE (40)

int Stone::stone_type_empty = 0;
int White::stone_type_white = 2;
int Black::stone_type_black = 1;

int AI = 1;

random_device rd; // obtain a random number from hardware
mt19937 gen(rd()); // seed the generator
uniform_int_distribution<> distr(0, 18); // define the range

enum Game_State{menu,ai,multi};
int STATE = menu;
int SURRENDER = 0;

ALLEGRO_DISPLAY* display;

int main()
{
	
	Board* board = new Board;
	bool running = true;
	float x = 0, y = 0;
	int current = BLACK;

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_mouse();
	al_init_primitives_addon();
	

	//anti-aliasing
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	ALLEGRO_EVENT_QUEUE* queue;
	display = al_create_display(CELL_SIZE * 23, CELL_SIZE * 19);
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);


	ALLEGRO_FONT* font = al_load_font("c:/windows/fonts/Arial.ttf", 22, NULL);
	if (font == NULL) {
		font = al_create_builtin_font();
	}
	

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	
	
	while (running) {
		
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		
		

		if (event.type == ALLEGRO_EVENT_TIMER) {
			

			if (STATE == menu) {
				draw_menu(font);
			}
			else {
				draw_board(board,current,font);
			}
			
			
		}

		
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			if (STATE != menu) {
				save_game(current, board);
			}
			running = false;
			
		}
		


		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			int retflag;
			mouse_click(event, current, retflag, board);


			if (retflag == 3) continue;
			
		}
		
		
		if (STATE == ai && AI == current) {
			
			make_AI_move(current, board);
			
		}

		
	}
	
	al_destroy_display(display);
	al_uninstall_mouse();
	al_destroy_font(font);
	delete board;

	return 0;
}

int make_move(int y, int x, int& current, Board* board) {
	try {
		if (current == BLACK) {
			board->SetAtLocation(y, x, new Black);
		}
		else {
			board->SetAtLocation(y, x, new White);
		}

		flip_side(current);
	}
	catch (IllegalMove_Exception* e) {
		// allegroy pop up ktory pokaze ze ruch jest nielegalny
		return 1;
	}
	return 0;
}

void flip_side(int& current)
{
	if (current == BLACK) {
		current = WHITE;
	}
	else {
		current = BLACK;
	}
}

void save_game(int& current, Board* board) {
	
	ofstream saved_file;
	saved_file.open("saved_file.txt");
	saved_file << STATE << " "<< current << " ";
	for (int i = 0;i < 19;i++) {
		for (int j = 0;j < 19;j++) {
			if (board->GetAtLocation(j, i)->GetType() == BLACK) {
				saved_file << BLACK << " ";
			}
			else if (board->GetAtLocation(j, i)->GetType() == WHITE) {
				saved_file << WHITE << " ";
			}
			else {
				saved_file << 0 << " ";
			}

		}
	}
	saved_file.close();

}

void load_game(int& current, Board* board) {

	int tempState;
	int tempCurrent;
	ifstream load_file;
	load_file.open("saved_file.txt");
	if (load_file.is_open() != true) {
		return;
	}
	load_file >> tempState;
	load_file >> tempCurrent;
	current = tempCurrent;
	STATE = tempState;
	for (int i = 0;i < 19;i++) {
		for (int j = 0;j < 19;j++) {
			int num;
			load_file >> num;
			
			if (num == Black::stone_type_black) {
				board->SetAtLocation(j, i, new Black);
			}
			if (num == White::stone_type_white) {
				board->SetAtLocation(j, i, new White);
			}
		}
	}
	load_file.close();

}

void make_AI_move(int& current, Board* board) {
	while (true) {
		int x = distr(gen);
		int y = distr(gen);

		if (make_move(y, x, current, board) == 0) {
			return;
		}
	}
}

void mouse_click(ALLEGRO_EVENT& event, int& current, int& retflag, Board* board)
{
	if (STATE == menu) {
		int ix = event.mouse.x;
		int iy = event.mouse.y;
		handle_menu(ix, iy, current, board);
		 
	}
	else {
		if (event.mouse.x >= (CELL_SIZE * 18.9) && event.mouse.x <= (CELL_SIZE * 22.7)) {
			if (event.mouse.y >= (CELL_SIZE * 5) && event.mouse.y <= (CELL_SIZE * 7)) {
				if (SURRENDER > 0 || STATE == ai) {
					handle_end_game(board,current);
					return;
				}

				

				flip_side(current);
				SURRENDER++;
				return;
			}
		}
		retflag = 1;
		SURRENDER = 0;
		if (STATE == ai && current == AI) {
			return;
		}

		int ix = event.mouse.x / CELL_SIZE;
		int iy = event.mouse.y / CELL_SIZE;
		if (board->GetAtLocation(iy, ix)->GetType() != 0) {
			retflag = 3; 
			return;
		}
		make_move(iy, ix, current, board);
	}

}

void handle_end_game(Board* board, int& current) {
	
	int button;
	if (board->get_black_score() > board->get_white_score()) {

		button = al_show_native_message_box(display, "GAME ENDED", " ", "Black Win", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
	}
	else if (board->get_black_score() < board->get_white_score()) {

		button = al_show_native_message_box(display, "GAME ENDED", " ", "White Win", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
	}
	else {
		button = al_show_native_message_box(display, "GAME ENDED", " ", "Tie", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
	}

	STATE = menu;
	board->board_reset();
	SURRENDER = 0;
	current = BLACK;
}

void handle_menu(int ix, int iy, int& current, Board* board) {
	if (ix >= (CELL_SIZE * 8) && ix <= (CELL_SIZE * 15)) {
		if (iy >= (CELL_SIZE * 4) && iy <= (CELL_SIZE * 6)) {
			STATE = multi;
		}

		if (iy >= CELL_SIZE * 8 && iy <= CELL_SIZE * 10) {
			STATE = ai;
		}

		if (iy >= CELL_SIZE * 12 && iy <= CELL_SIZE * 14) {
			
			load_game(current, board);
		}
	}
}

void draw_menu(ALLEGRO_FONT* font) {

	al_flip_display();
	al_clear_to_color(al_map_rgb(255, 222, 0));

	if (font == NULL) {
		return;
	}
	handle_menu(font);
	
}

void handle_menu(ALLEGRO_FONT* font)
{
	//multiplayer mode
	al_draw_filled_rectangle(CELL_SIZE * 8, CELL_SIZE * 4, CELL_SIZE * 15, CELL_SIZE * 6, al_map_rgb(137, 135, 0));
	al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 11.5, CELL_SIZE * 4.68, ALLEGRO_ALIGN_CENTRE, "Multiplayer mode.");

	//player vs AI mode
	al_draw_filled_rectangle(CELL_SIZE * 8, CELL_SIZE * 8, CELL_SIZE * 15, CELL_SIZE * 10, al_map_rgb(137, 135, 0));
	al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 11.5, CELL_SIZE * 8.68, ALLEGRO_ALIGN_CENTRE, "Player vs AI.");

	//load the game
	al_draw_filled_rectangle(CELL_SIZE * 8, CELL_SIZE * 12, CELL_SIZE * 15, CELL_SIZE * 14, al_map_rgb(137, 135, 0));
	al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 11.5, CELL_SIZE * 12.68, ALLEGRO_ALIGN_CENTRE, "Load the game.");
}

void draw_board(Board* board, int& current, ALLEGRO_FONT* font)
{
	al_flip_display();
	al_clear_to_color(al_map_rgb(255, 222, 0));
	

	float half_cell = 1.0 * CELL_SIZE / 2;
	bool start = true;
	
	horizontal_lines(half_cell);
	
	vertical_lines(half_cell);

	//current color moves area
	draw_current_player(current,font);


	draw_point(board, font);



	//surrender arrea
	draw_surrender(font);
	


	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			al_draw_circle(half_cell + (3 + 6 * j) * CELL_SIZE, half_cell + (3 + 6 * i) * CELL_SIZE, 1, al_map_rgb(0, 0, 0), 5);
		}

	}
	draw_stones(half_cell, board);
}

void draw_surrender(ALLEGRO_FONT* font)
{
	al_draw_filled_rectangle(CELL_SIZE * 18.9, CELL_SIZE * 5, CELL_SIZE * 22.7, CELL_SIZE * 7, al_map_rgb(137, 135, 0));
	if (SURRENDER == 1) {
		al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 20.8, CELL_SIZE * 5.7, ALLEGRO_ALIGN_CENTRE, "End Game.");
	}
	else {
		al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 20.8, CELL_SIZE * 5.7, ALLEGRO_ALIGN_CENTRE, "Pass.");
	}
}

void draw_point(Board* board, ALLEGRO_FONT* font)
{
	string white = (to_string(board->get_white_score()));
	string black = (to_string(board->get_black_score()));
	const char* black_string = black.c_str();
	const char* white_string = white.c_str();


	//points of white player area
	al_draw_filled_rectangle(CELL_SIZE * 20, CELL_SIZE * 14, CELL_SIZE * 22, CELL_SIZE * 16, al_map_rgb(137, 135, 0));
	al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 21, CELL_SIZE * 13, ALLEGRO_ALIGN_CENTRE, "White points.");
	al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 21, CELL_SIZE * 14.8, ALLEGRO_ALIGN_CENTRE, white_string);
	//points of black player area
	al_draw_filled_rectangle(CELL_SIZE * 20, CELL_SIZE * 9, CELL_SIZE * 22, CELL_SIZE * 11, al_map_rgb(137, 135, 0));
	al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 21, CELL_SIZE * 8, ALLEGRO_ALIGN_CENTRE, "Black points.");
	al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 21, CELL_SIZE * 9.8, ALLEGRO_ALIGN_CENTRE, black_string);
}

void draw_current_player(int& current, ALLEGRO_FONT* font)
{
	al_draw_text(font, al_map_rgb(0, 0, 0), CELL_SIZE * 21, CELL_SIZE * 3, ALLEGRO_ALIGN_CENTRE, "Current player.");

	al_draw_filled_rectangle(CELL_SIZE * 20, CELL_SIZE, CELL_SIZE * 22, CELL_SIZE * 3, al_map_rgb(137, 135, 0));
	if (current == BLACK) {

		al_draw_filled_circle(CELL_SIZE * 21, CELL_SIZE * 2, 15, al_map_rgb(0, 0, 0));
	}
	if (current == WHITE) {

		al_draw_filled_circle(CELL_SIZE * 21, CELL_SIZE * 2, 15, al_map_rgb(255, 255, 255));
	}
}

void horizontal_lines(float half_cell)
{
	for (int i = 0;i < 19;i++) {
		al_draw_line(half_cell, half_cell + i * CELL_SIZE, CELL_SIZE * 19 - half_cell, half_cell + i * CELL_SIZE, al_map_rgb(0, 0, 0), 2);

	}
}

void vertical_lines(float half_cell)
{
	for (int i = 0;i <19;i++) {
		al_draw_line(half_cell + i * CELL_SIZE, half_cell, half_cell + i * CELL_SIZE, CELL_SIZE * 19 - half_cell, al_map_rgb(0, 0, 0), 2);

	}
}

void draw_stones(float half_cell, Board* board)
{
	for (int y = 0; y < 19; y++) {
		for (int x = 0; x < 19; x++) {

			if (board->GetAtLocation(y, x)->GetType() == BLACK) {

				al_draw_filled_circle(half_cell + CELL_SIZE * x, half_cell + y * CELL_SIZE, 15, al_map_rgb(0, 0, 0));
			}
			if (board->GetAtLocation(y, x)->GetType() == WHITE) {

				al_draw_filled_circle(half_cell + CELL_SIZE * x, half_cell + y * CELL_SIZE, 15, al_map_rgb(255, 255, 255));
			}
		}

	}
}

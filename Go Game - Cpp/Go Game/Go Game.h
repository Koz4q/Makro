#pragma once
#include "Stone.h"
#include "Black.h"
#include "White.h"
#include "Board.h"

void draw_board(Board* board, int& current, ALLEGRO_FONT* font);

void draw_surrender(ALLEGRO_FONT* font);

void draw_point(Board* board, ALLEGRO_FONT* font);

void draw_current_player(int& current, ALLEGRO_FONT* font);

void horizontal_lines(float half_cell);

void vertical_lines(float half_cell);

void mouse_click(ALLEGRO_EVENT& event, int& current, int& retflag, Board* board);

void drawing_stone(float half_cell);

void drawing_board(float half_cell);

void draw_stones(float half_cell, Board* board);

void draw_menu(ALLEGRO_FONT* font);

void handle_menu(ALLEGRO_FONT* font);

void handle_menu(int ix, int iy, int& current, Board* board);

void save_game(int& current, Board* board);

void flip_side(int& current);

void handle_end_game(Board* board, int& current);
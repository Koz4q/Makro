#pragma once
#include "Stone.h"
#include <list>
#include <iterator>
#include "Position.h"
#include <exception>

using namespace std;

class IllegalMove_Exception : public exception {
public:
};

class Board
{
private:
	Stone* board[19][19];
	int black_score = 0;
	int white_score = 0;
public:
	
	Board() {
		init_board();
	}
	void init_board()
	{
		Stone* empty = new Stone;
		for (int i = 0;i < 19;i++) {
			for (int j = 0;j < 19;j++) {
				board[i][j] = empty;
			}
		}
	}
	Stone* GetAtLocation(int y, int x) {
		return board[y][x];
	}

	void clear_at_location(int y, int x) {
		board[y][x] = new Stone;

	}

	void SetAtLocation(int y, int x,Stone* stone) {
		
		if (y < 0 || y>18 || x < 0 || x>18) {
			throw new IllegalMove_Exception;
		}
		//part of the ''AI''
		if (GetAtLocation(y,x)->GetType() != 0) {
			 throw new IllegalMove_Exception; 
		}

		board[y][x] = stone;
		
		list < Position* > list_neighbours = legal_neighbours(new Position(y, x));
		for (Position* pos : list_neighbours) {
			handle_enemy(pos->y, pos->x, stone);
			
		}
		if(handle_suicide(y,x,stone)==true){
			clear_at_location(y, x);
			throw new IllegalMove_Exception;
		}
	}

	void handle_enemy(int y, int x, Stone* stone)
	{
		Stone* stn = GetAtLocation(y, x);
		if (stn->GetType() == Stone::stone_type_empty) {
			return;
		}
		if (stn->GetType() != stone->GetType()) {
			list<Position*>* enemy_group = group(new Position(y, x));
			if (have_breath(enemy_group) == false) {
				for (Position* pos : *enemy_group) {
					clear_at_location(pos->y, pos->x);
					if (stn->GetType() == Stone::stone_type_black) {
						white_score++;
					}else{
						black_score++;
						
					}
				}
			}
		}
	}

	bool handle_suicide(int y, int x, Stone* stone) {
		list<Position*>* suicide_group = group(new Position(y, x));
		if (have_breath(suicide_group) == false) {
			return true;
		}
		return false;

	}
	
	list <Position*> legal_neighbours(Position* pos) {
		// list of leegel neighbours around the position 
		list <Position*> returned;
		if (pos->y != 0) {
			returned.push_back(new Position((pos->y - 1), pos->x));
		}

		if (pos->y != 18) {
			returned.push_back(new Position((pos->y + 1), pos->x));
		}

		if (pos->x != 0) {
			returned.push_back(new Position((pos->y), pos->x - 1));
		}

		if (pos->x != 18) {
			returned.push_back(new Position((pos->y), pos->x + 1));
		}
		return returned;
	}

	list <Position*>* group(Position* start) {
		
		list <Position*>* returned = new list <Position*>;
		reccur_group(start,returned);
		return returned;

	}
	void reccur_group(Position* start,list<Position*>* group) {
		
		bool is_in_group = false;
		
		for (Position* pos : *group) {
			if (start->x == pos->x && start->y == pos->y) {
				is_in_group = true;
				break;
			}
		}
		if (is_in_group == false) {
			Stone* s = GetAtLocation(start->y, start->x);
			group->push_back(start);
			list < Position* > list_neighbours = legal_neighbours(new Position(start->y, start->x));
			for (Position* pos : list_neighbours) {
				Stone* s_at_pos = GetAtLocation(pos->y, pos->x);
				if (s_at_pos->GetType() == s->GetType()) {
					reccur_group(pos, group);
				}
				
			}
		}
		
	}

	bool have_breath(list<Position*>* group) {
		for (Position* pos : *group) {
			list < Position* > list_neighbours = legal_neighbours(new Position(pos->y, pos->x));
			for (Position* neighbour : list_neighbours) {
				// cheking is the neighbour is empty
				Stone* stone_at_neighbour = GetAtLocation(neighbour->y, neighbour->x);
				if (stone_at_neighbour->GetType() == Stone::stone_type_empty) {
					return true;
				}
			}
		}
		return false;
	}

	int get_black_score() {


		return black_score;
	}

	int get_white_score() {


		return white_score;
	}

	void board_reset() {
		black_score = 0;
		white_score = 0;

		init_board();

	}
};


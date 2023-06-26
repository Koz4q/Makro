#pragma once

class Stone{

public:
	static int stone_type_white;
	static int stone_type_black;
	static int stone_type_empty;

	virtual int GetType() {
		return stone_type_empty;
	}
	

};

#pragma once
#include "Stone.h"
class Black : public Stone{
    
public:
    
    Black() {

    }

    virtual int GetType() {
        return stone_type_black;
    }

};



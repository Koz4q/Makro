#pragma once
#include "Stone.h"
class White : public Stone{
    
public:

    White() {
        
    }

    virtual int GetType() {
        return stone_type_white;
    }
    
};


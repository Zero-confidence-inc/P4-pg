//
// Created by nicol on 09-05-2024.
//
#include "Semantic.h






bool CheckSemantics()
{

    switch(Toke)

    case("bool") {
        if(true)
        {
            return true;
        }else
        {
            return false;
        }break;
    }
    case ("char"){
        if(true)
        {
            return true;
        }else
        {
            return false;
        }break;
    }
    case ("string"){
        if(true)
        {
            return true;
        }else
        {
            return false;
        }break;
    }
    case ("int"){
        if(true)
        {
            return true;
        }else
        {
            return false;
        }break;
    }
    case ("float"){
        if(true)
        {
            return true;
        }else
        {
            return false;
        }break;
    }






}

class SymbolTable{
    std::vector
    string Type;
    bool Assigned;
};
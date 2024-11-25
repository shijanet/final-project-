#ifndef HERO_H_INCLUDED
#define Hero_H_INCLUDED

#include <string> //開始寫的時候才會知道要include什麼
#include "Object.h" //下面發現要用Object
#include <map>

enum class herostate{
    left,
    right,
    front,
    back,
    herostate_max
};


class hero : public Object
{
    public:
        void init();
        void update();
        void draw();
    private:
        herostate state = herostate::front;
        double speed = 5;
        std::map<herostate,std::string> gifPath;
};

#endif
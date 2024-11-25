#include "hero.h"
#include <cstdio>
#include "data/GIFCenter.h"
#include "data/DataCenter.h"
#include "shapes/Rectangle.h"

namespace HeroSetting {
	static constexpr char gif_root_path[50] = "./assets/gif/hero";
	static constexpr char gif_postfix[][10] = {
		"left", "right", "front", "back"
	};
}

void hero::init()
{
    for (size_t type = 0; type < static_cast<size_t>(herostate::herostate_max); type++) //static_cast用來安全的轉型
    {
        char buffer[50];
        sprintf(//像print但印在buffer裡面
            buffer,"%s/dragonite_%s.gif",
            HeroSetting::gif_root_path,
            HeroSetting::gif_postfix[static_cast<int>(type)]
        );
        gifPath[static_cast<herostate>(type)] = std::string(buffer);
    }

    DataCenter *DC = DataCenter::get_instance();
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);

    shape.reset(new Rectangle{
        DC->window_width/2,
        DC->window_height/2,
        DC->window_width/2 + gif->width,
        DC->window_height/2 + gif->height, //設定初始位置，給左上跟右下座標
    });
    
}



void hero::draw()
{
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC-> get(gifPath[state]);
    algif_draw_gif(gif,
    shape->center_x() - gif->width/2,
    shape->center_y() - gif->height/2,
    0
    );
}


void hero::update()
{
    DataCenter *DC = DataCenter::get_instance();
    if(DC->key_state[ALLEGRO_KEY_W])
    {
        shape->update_center_y(shape->center_y() - speed);
        state = herostate::back;
    }
    else if(DC->key_state[ALLEGRO_KEY_A])
    {
        shape->update_center_x(shape->center_x() - speed);
        state = herostate::left;
    }
    else if(DC->key_state[ALLEGRO_KEY_S])
    {
        shape->update_center_y(shape->center_y() + speed);
        state = herostate::front;
    }
    else if(DC->key_state[ALLEGRO_KEY_D])
    {
        shape->update_center_x(shape->center_x() + speed);
        state = herostate::right;
    }
}
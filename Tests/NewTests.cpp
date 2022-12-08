//
// Created by David on 25/11/2022.
//
#include "iostream"
#include "../Player.h"
#include "../worldcup23a1.h"
#include "../wet1util.h"
#define AGREGATE_TEST_RESULT(res, cond) (res) = ((res) && (cond))

namespace NewTests{
    bool genTest1()
    {
        world_cup_t *obj = new world_cup_t();

        obj->add_team(3, 3572);
        obj->add_team (4 ,9788);
        obj->add_player (3, 3, 1786, 3298 ,4255, false);
        obj->unite_teams( 3 ,4, 4);
        obj->remove_player( 3);
        delete obj;
        return true;
    }
    bool genTest()
    {
        world_cup_t *obj = new world_cup_t();

        obj->add_team(  1, 11393);
        obj->add_team(  2 ,5025);
        obj->add_team(  3 ,1689);
//        obj->add_player(  1, 2, 11844 ,6778, 10497 ,true);
//        obj->add_player(  2, 3 ,11034, 11128 ,2526, false);
//        obj->add_player(  3, 3 ,5162 ,4839 ,470 ,false);
//        obj->add_player(  4, 2 ,6536 ,11627 ,11939, true);
//        obj->add_player(  5, 2 ,9117 ,3103 ,3034 ,true);
//        obj->add_player(  6, 2 ,7718 ,5097 ,10811 ,false);
//        obj->add_player(  7, 2 ,10357 ,1673 ,10860 ,true);
//        obj->add_player(  8, 2 ,2187 ,11408 ,3274 ,true);
//        obj->add_player(  9, 3 ,2565 ,11972 ,11109 ,false);
//        obj->add_player(  10, 3, 7680 ,10194 ,10941 ,false);
        obj->add_player(  1, 2, 11844 ,6778, 0 ,true);
        obj->add_player(  2, 3 ,11034, 11128 ,0, false);
        obj->add_player(  3, 3 ,5162 ,4839 ,0 ,false);
        obj->add_player(  4, 2 ,6536 ,11627 ,0, true);
        obj->add_player(  5, 2 ,9117 ,3103 ,0 ,true);
        obj->add_player(  6, 2 ,7718 ,5097 ,0 ,false);
        obj->add_player(  7, 2 ,10357 ,1673 ,0 ,true);
        obj->add_player(  8, 2 ,2187 ,11408 ,0 ,true);
        obj->add_player(  9, 3 ,2565 ,11972 ,0 ,false);
        obj->add_player(  10, 3, 7680 ,10194 ,0 ,false);


        obj->remove_player(  3);
        obj->remove_player(  7);
        obj->update_player_stats(  6 ,11528, 6529, 10966); // THIS IS WORKING
        obj->remove_player(  10);
        obj->update_player_stats(  6, 8764 ,624, 5902); // TODO: CHECK SEG FAULT WHEN UNCOMMENT THIS
        StatusType st = obj->unite_teams(  2 ,1, 2); // THIS IS WORKING
//        std::cout << "Current Status:" << int(st) << std::endl;
        obj->update_player_stats(  8 ,836 ,1956 ,3742);
        obj->update_player_stats(  1 ,10543 ,8783 ,1652);
        obj->unite_teams(  3, 2, 2);






        delete obj;
        return true;
    }
}

//
// Created by David on 25/11/2022.
//
#include "iostream"
#include "../Player.h"
#include "../worldcup23a1.h"
#include "../wet1util.h"
#define AGREGATE_TEST_RESULT(res, cond) (res) = ((res) && (cond))

namespace WorldCupTests{
    bool teamsNoPlayersAddTest(world_cup_t &wc)
    {
        bool result = true;
        StatusType st = wc.add_team(1,5);
        result = result && (st == StatusType::SUCCESS);
        st = wc.add_team(1,6);
        // Team id already exists in tree
        result = result && (st == StatusType::FAILURE);
        // Invalid input check
        st = wc.add_team(-5,6);
        result = result && (st == StatusType::INVALID_INPUT);

        st = wc.add_team(2,99);
        result = result && (st == StatusType::SUCCESS);

        st = wc.add_team(8,6);
        result = result && (st == StatusType::SUCCESS);

        st = wc.add_team(9,4);
        result = result && (st == StatusType::SUCCESS);

        st = wc.add_team(10,6);
        result = result && (st == StatusType::SUCCESS);


        return result;
    }

    bool teamsNoPlayersDeleteTest(world_cup_t &wc)
    {
        bool result = true;

        // Invalid id check
        StatusType st = wc.remove_team(0);
        result = result && (st == StatusType::INVALID_INPUT);
        // Team does not exist check
        st = wc.remove_team(5);
        result = result && (st == StatusType::FAILURE);
//        st = wc.remove_team(8);
        st = wc.remove_team(10);

        st = wc.remove_team(1);
        result = result && (st == StatusType::SUCCESS);

        return result;
    }

    bool uniteTreesTest(world_cup_t &wc)
    {
        wc.add_team(5,5);
        wc.add_team(6,5);
        wc.add_team(7,5);
        wc.add_team(8,5);
        wc.add_team(9,5);

        wc.add_player(1,6,4,3,2,false);
        wc.add_player(5,6,4,30,2,false);
        wc.add_player(50,6,4,21,2,false);
        wc.add_player(40,6,4,100,2,false);
        wc.add_player(20,6,4,7,2,false);
        wc.add_player(30,6,4,5,2,false);

        wc.add_player(21,9,4,80,2,false);
        wc.add_player(22,9,4,30,2,false);
        wc.add_player(25,9,4,31,2,false);
        wc.add_player(28,9,4,40,2,false);
        wc.add_player(23,9,4,21,2,false);
        wc.add_player(24,9,4,42,2,false);
        wc.add_player(31,9,4,50,2,false);


        wc.unite_teams(6,9,10);

        wc.add_player(101,10,4,200,2,false);


        output_t<int> out = wc.get_all_players_count(10);
        int count = out.ans();
        StatusType st = out.status();
        int* output1 = new int[count];
        wc.get_all_players(-1,output1);
        std::cout << std::endl;
        delete[] output1;


        return true;
    }

    bool playersAddRemoveTest(world_cup_t &wc)
    {
        std::cout << "ADD/REMOVE TEST" << std::endl;

        // Adding to team with id:2
        wc.add_player(35,8,2,100,20,false);
        wc.add_player(34,8,2,1,20,false);
        wc.add_player(33,8,2,1,20,false);
        wc.add_player(32,8,2,1,20,false);
        wc.add_player(31,8,2,1,20,false);

        // Adding to team with id:2
        wc.add_player(1,2,3,5,3,false);

        wc.add_player(21,2,2,1,20,false);
        wc.add_player(25,2,2,1,20,false);
        wc.add_player(3,2,2,1,5,false);
        wc.add_player(4,2,2,1,1,false);
        wc.add_player(5,2,2,2,5,false);
        wc.add_player(6,2,2,2,4,false);
        wc.add_player(24,2,2,2,3,false);
        wc.add_player(7,2,2,2,2,false);
        wc.add_player(8,2,2,2,1,false);
        wc.add_player(9,2,2,5,30,false);
        wc.add_player(10,2,2,5,29,false);
        wc.add_player(11,2,2,5,28,false);
        wc.add_player(12,2,2,5,27,false);
        wc.add_player(51,2,2,6,40,false);
        wc.add_player(52,2,2,6,40,false);
        wc.add_player(53,2,2,6,40,false);
        wc.add_player(54,2,2,6,10,false);
        wc.add_player(60,2,2,6,5,false);
        wc.add_player(70,2,2,6,4,false);
        wc.add_player(100,2,2,8,6,false);
        wc.add_player(80,2,2,10,7,false);
        wc.add_player(90,2,2,10,7,false);
//        StatusType st = wc.remove_player(4);
        wc.remove_player(1);
        return true;
    }
    
    bool segelTest()
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        bool result = true;
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_team(2, 2);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_team(3, 2);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_team(4, 2);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_team(5, 2);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_team(6, 2);
        result = result &&res == StatusType::SUCCESS;

        // add players
        res = obj->add_player(21, 1, 10, 1, 20, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(25, 1, 10, 1, 20, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(3, 1, 10, 1, 5, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(4, 4, 10, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(5, 5, 10, 2, 5, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(6, 6, 10, 2, 4, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(24, 1, 10, 2, 3, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(7, 5, 10, 2, 2, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(8, 6, 10, 2, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(9, 3, 10, 5, 30, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(10, 2, 10, 5, 29, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(11, 2, 10, 5, 28, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(12, 2, 10, 5, 27, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(51, 5, 10, 6, 40, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(52, 6, 10, 6, 40, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(53, 3, 10, 6, 40, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(54, 2, 10, 6, 10, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(60, 2, 10, 6, 5, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(70, 2, 10, 6, 4, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(100, 2, 10, 8, 6, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(80, 2, 10, 10, 7, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(90, 2, 10, 10, 7, false);
        result = result &&res == StatusType::SUCCESS;

        // check all closest
        output_t<int> resn1 = obj->get_closest_player(21, 1);
        result = result &&resn1.status() == StatusType::SUCCESS;
        result = result &&resn1.ans() == 25;
        output_t<int> resn2 = obj->get_closest_player(25, 1);
        result = result &&resn2.status() == StatusType::SUCCESS;
        result = result &&resn2.ans() == 21;
        output_t<int> resn3 = obj->get_closest_player(3, 1);
        result = result &&resn3.status() == StatusType::SUCCESS;
        result = result &&resn3.ans() == 4;

        int count = obj->get_all_players_count(-1).ans();
        int arr[count];
        obj->get_all_players(-1, arr);
        for(int i=0;i<count;i++)
            std::cout << arr[i] <<",";
        output_t<int> resn4 = obj->get_closest_player(4, 4);
        result = result &&resn4.status() == StatusType::SUCCESS;
        result = result &&resn4.ans() == 3;
        output_t<int> resn5 = obj->get_closest_player(5, 5);
        result = result &&resn5.status() == StatusType::SUCCESS;
        result = result &&resn5.ans() == 6;
        output_t<int> resn6 = obj->get_closest_player(6, 6);
        result = result &&resn6.status() == StatusType::SUCCESS;
        result = result &&resn6.ans() == 5;
        output_t<int> resn7 = obj->get_closest_player(24, 1);
        result = result &&resn7.status() == StatusType::SUCCESS;
        result = result &&resn7.ans() == 7;
        output_t<int> resn8 = obj->get_closest_player(7, 5);
        result = result &&resn8.status() == StatusType::SUCCESS;
        result = result &&resn8.ans() == 8;
        output_t<int> resn9 = obj->get_closest_player(8, 6);
        result = result &&resn9.status() == StatusType::SUCCESS;
        result = result &&resn9.ans() == 7;
        output_t<int> resn10 = obj->get_closest_player(9, 3);
        result = result &&resn10.status() == StatusType::SUCCESS;
        result = result &&resn10.ans() == 10;
        output_t<int> resn11 = obj->get_closest_player(10, 2);
        result = result &&resn11.status() == StatusType::SUCCESS;
        result = result &&resn11.ans() == 11;
        output_t<int> resn12 = obj->get_closest_player(11, 2);
        result = result &&resn12.status() == StatusType::SUCCESS;
        result = result &&resn12.ans() == 12;
        output_t<int> resn13 = obj->get_closest_player(12, 2);
        result = result &&resn13.status() == StatusType::SUCCESS;
        result = result &&resn13.ans() == 11;
        output_t<int> resn14 = obj->get_closest_player(51, 5);
        result = result &&resn14.status() == StatusType::SUCCESS;
        result = result &&resn14.ans() == 52;
        output_t<int> resn15 = obj->get_closest_player(52, 6);
        result = result &&resn15.status() == StatusType::SUCCESS;
        result = result &&resn15.ans() == 53;
        output_t<int> resn16 = obj->get_closest_player(53, 3);
        result = result &&resn16.status() == StatusType::SUCCESS;
        result = result &&resn16.ans() == 52;
        output_t<int> resn17 = obj->get_closest_player(54, 2);
        result = result &&resn17.status() == StatusType::SUCCESS;
        result = result &&resn17.ans() == 60;
        output_t<int> resn18 = obj->get_closest_player(60, 2);
        result = result &&resn18.status() == StatusType::SUCCESS;
        result = result &&resn18.ans() == 70;
        output_t<int> resn19 = obj->get_closest_player(70, 2);
        result = result &&resn19.status() == StatusType::SUCCESS;
        result = result &&resn19.ans() == 60;
        output_t<int> resn20 = obj->get_closest_player(100, 2);
        result = result &&resn20.status() == StatusType::SUCCESS;
        result = result &&resn20.ans() == 80;
        output_t<int> resn21 = obj->get_closest_player(80, 2);
        result = result &&resn21.status() == StatusType::SUCCESS;
        result = result &&resn21.ans() == 90;
        output_t<int> resn22 = obj->get_closest_player(90, 2);
        result = result &&resn22.status() == StatusType::SUCCESS;
        result = result &&resn22.ans() == 80;

        delete obj;
        return result;
    }

    bool playerUpdateTest(world_cup_t &wc)
    {
        std::cout << "UPDATE TEST" << std::endl;
        StatusType st = wc.update_player_stats(5,30,30,30);
        return true;
    }

    bool getAllPlayersTest(world_cup_t &wc)
    {
        // TEAM NUMBER 2 RANKED
        int count = wc.get_all_players_count(2).ans();
        std::cout << "Current count is:" << count << std::endl;
        int* output = new int[count];
        wc.get_all_players(2,output);
        for(int i=0;i<count;i++) std::cout << output[i] << ",";
        std::cout << std::endl;
        delete[] output;

        // ALL PLAYERS RANKED
        count = wc.get_all_players_count(-1).ans();
        std::cout << "Current count is:" << count << std::endl;
        int* output1 = new int[count];
        wc.get_all_players(-1,output1);
        for(int i=0;i<count;i++) std::cout << output1[i] << ",";
        std::cout << std::endl;
        delete[] output1;

        std::cout << "Top Scorer for team 2:" << wc.get_top_scorer(2).ans() << std::endl;
        std::cout << "Top Scorer globally:" << wc.get_top_scorer(-1).ans() << std::endl;
        return true;
    }

    bool segelTesting()
    {
        world_cup_t wc;
        wc.add_team(1, 10000);
        wc.add_team(2, 20000);
        wc.add_team(3 ,30000);
        wc.add_team( 4 ,40000);
        wc.add_player( 1001 ,1, 10, 0 ,0, false);
        wc.add_player( 1002 ,1, 10 ,0 ,0 ,false);
        wc.add_player( 1003 ,1 ,10 ,0, 0 ,false);
        wc.add_player( 1004 ,1 ,10 ,0 ,2 ,false);
        wc.add_player( 1005 ,1 ,10 ,0 ,0 ,false);
        wc.add_player( 1006 ,1 ,10 ,4 ,3 ,false);
        wc.add_player( 1007 ,1 ,10 ,0 ,0 ,false);
        wc.add_player( 1008 ,1 ,10 ,0 ,0,true);
        wc.add_player( 1009 ,1 ,10 ,0 ,0 ,false);
        wc.add_player( 1010 ,1 ,10 ,0 ,0 ,false);
        wc.add_player( 1011 ,1 ,10 ,0 ,0 ,false);
        wc.add_player( 1012 ,1 ,10 ,0 ,0 ,false);
        wc.add_player( 2001 ,2 ,20 ,0 ,0 ,false);
        wc.add_player( 2002 ,2 ,20 ,0 ,0 ,false);
        wc.add_player( 2003 ,2 ,20 ,0 ,0 ,false);
        wc.add_player( 2004 ,2 ,20 ,0 ,0 ,false);
        wc.add_player( 2005 ,2 ,20 ,0 ,0 ,false);
        wc.add_player( 2006 ,2 ,20 ,0 ,0 ,false);
        wc.add_player( 2007 ,2 ,20 ,0 ,0 ,false);
        wc.add_player( 2008 ,2 ,20 ,6 ,4 ,true);
        wc.add_player( 2009 ,2 ,20 ,0 ,0 ,false);
        wc.add_player( 2010 ,2 ,0 ,0 ,0 ,false);
        wc.add_player( 2011 ,2 ,20 ,0 ,0 ,false);
        wc.add_player( 3001 ,3 ,30 ,0 ,0 ,false);
        wc.add_player( 3002 ,3 ,30 ,0 ,0 ,false);
        wc.add_player( 3003 ,3 ,30 ,0 ,0 ,false);
        wc.add_player( 3004 ,3 ,30 ,0 ,0 ,false);
        wc.add_player( 3005 ,3 ,30 ,2 ,0 ,false);
        wc.add_player( 3006 ,3 ,30 ,0 ,0 ,false);
        wc.add_player( 3007 ,3 ,30 ,0, 0 ,false);
        wc.add_player( 3008 ,3 ,30 ,0, 0 ,false);
        wc.add_player(3009 ,3 ,30 ,0 ,2 ,false);
        wc.add_player(3010 ,3 ,30 ,0 ,0 ,true);
        wc.add_player(3011 ,3 ,30 ,0 ,0 ,true);
        wc.add_player(4001 ,4 ,2 ,1 ,2 ,false);
        wc.add_player(4002 ,4, 2, 2, 2, false);
        wc.update_player_stats( 3011 ,2 ,1 ,1);
        wc.play_match( 2, 3);
        wc.play_match( 1 ,2);
        wc.get_num_played_games( 2003);
        wc.get_team_points (3);
        wc.unite_teams (1 ,2 ,2);
        wc.get_top_scorer(-1);
        int count = wc.get_all_players_count(2).ans();
        int *out_mem = nullptr;
        out_mem = new int[count];
        wc.get_all_players (4,out_mem);
        wc.get_closest_player( 2008, 2);
        output_t<int> out = wc.knockout_winner (0 ,3);
        StatusType st1 = wc.remove_team(2);
        int st = wc.get_all_players_count(2).ans();

        wc.remove_player (3008);
        return true;
    }

    bool uniteTeamsTesting()
    {
        world_cup_t *obj = new world_cup_t();
        bool result = true;
        StatusType res = obj->add_team(1, 2);
        result = result && res == StatusType::SUCCESS;
        res = obj->add_player(1001, 1, 1, 5, 2, true);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1002, 1, 1, 3, 4, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1004, 1, 1, 1, 2, true);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1005, 1, 1, 1, 4, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_team(2, 2);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1006, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1007, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1008, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1009, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1010, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1011, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1012, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1013, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1014, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1015, 2, 1, 1, 1, true);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1016, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        res = obj->add_player(1017, 2, 1, 1, 1, false);
        result = result &&res == StatusType::SUCCESS;
        output_t<int> resn3 = obj->knockout_winner(1, 4);
        result = result &&resn3.status() == StatusType::SUCCESS;
        result = result &&resn3.ans() == 2;

        res = obj->unite_teams(1, 2, 3);
        result = result &&res == StatusType::SUCCESS;
        std::cout << "working";

        output_t<int> resn1 = obj->get_all_players_count(3);
        result = result &&resn1.status() == StatusType::SUCCESS;
        result = result &&resn1.ans() == 17;
        output_t<int> resn2 = obj->knockout_winner(1, 4);
        result = result &&resn2.status() == StatusType::SUCCESS;
        result = result &&resn2.ans() == 3;
        std::cout << "Test result:" << resn2.ans() << std::endl;

        delete obj;
        return result;
    }
    bool knockoutWinnerTest()
    {
        world_cup_t wc;
        wc.add_team(1,5);
        wc.add_team(2,5);
        wc.add_team(3,20);
        wc.add_team(4,5);
        wc.add_team(5,21);
        wc.add_team(6,5);

        for(int i=1;i<20;i++)
        {
            wc.add_player(i,1,1,5,0,true);
        }
        for(int i=30;i<43;i++)
        {
            wc.add_player(i,2,0,0,0,true);
        }
        for(int i=54;i<67;i++)
        {
            wc.add_player(i,3,0,0,0,true);
        }
        for(int i=100;i<113;i++)
        {
            wc.add_player(i,4,0,0,0,true);
        }
        for(int i=200;i<213;i++)
        {
            wc.add_player(i,5,0,0,0,true);
        }

        for(int i=300;i<313;i++)
        {
            wc.add_player(i,6,0,0,0,true);
        }

//        wc.knockout_winner(0,30);
        wc.play_match(4,3);
        wc.play_match(4,3);
        wc.play_match(4,3);
        wc.play_match(4,3);
        std::cout << "Points to teams:" << wc.get_team_points(4).ans() << "," << wc.get_team_points(3).ans() << std::endl;
        std::cout << "Player with id played:" << wc.get_num_played_games(55).ans() << std::endl;
        std::cout << "Player count in team:3 |" << wc.get_all_players_count(3).ans() << std::endl;
        StatusType st = wc.add_player(500,3,0,0,0,true);
        std::cout << "Player with id played:" << int(st) << std::endl;
        int result = wc.get_num_played_games(500).ans();
        std::cout << "Played games:" << result << std::endl;
        wc.play_match(4,3);
        result = wc.get_num_played_games(500).ans();
        std::cout << "Played games:" << result << std::endl;




        return true;

    }
    bool teamsTreeTest()
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        bool result = (res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        result = result && res == StatusType::SUCCESS;
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        result = result && res == StatusType::SUCCESS;
        output_t<int> resn1 = obj->get_closest_player(1001, 1);
        result = result &&(resn1.status() == StatusType::FAILURE);
        std::cout << result;

        delete obj;
//        world_cup_t wc;
//        bool result = teamsNoPlayersAddTest(wc);
//        result = result && teamsNoPlayersDeleteTest(wc);
//
//        StatusType st = wc.remove_team(10);
//        result = result && (st == StatusType::SUCCESS);
//
//        result =  result && (playersAddRemoveTest(wc));
//        result = result && (getAllPlayersTest(wc));
//
//
//        result = result && (playerUpdateTest(wc));
////        uniteTreesTest(wc);
        return result;
    }
    bool createBasicGame()
    {
        std::cout << "Running test:" << std::endl;
        world_cup_t wc;
//        wc.add_team(5,5);


        return true;
    }
}

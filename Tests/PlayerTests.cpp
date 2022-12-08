//
// Created by David on 25/11/2022.
//
#include "iostream"
#include "../Player.h"

#define AGREGATE_TEST_RESULT(res, cond) (res) = ((res) && (cond))

namespace PlayerTests{
    bool comparePlayersTest()
    {
        bool testResult = true;
        bool compResult;
        // More Goals
        Player p1(6,4,3,5,1,false);
        Player p2(7,4,3,4,1,false);
        compResult = p1>p2;
        testResult = compResult && testResult;

        p2.updateStats(4,5,3);
        compResult = p2>p1;
        testResult = compResult && testResult;

        // p1 has more cards than p2
        p1.updateStats(4,4,5);
        compResult = p1>p2;
        testResult = compResult && testResult;

        // p2 has higher id value.
        p2.updateStats(4,4,2);
        compResult = p2>p1;
        testResult = compResult && testResult;
        return testResult;
    }
}

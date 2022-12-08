
#include <functional>
#include <iostream>
#include "TestUtils.h"
#include "../AVLTree.h"

namespace NewTests{
    bool genTest();
    //	bool testQueueMethods();
//	bool testQueueMethods();
//	bool testQueueMethods();

}


namespace PlayerTests{
    bool comparePlayersTest();
    //	bool testQueueMethods();
//	bool testQueueMethods();
//	bool testQueueMethods();

}

namespace AVLTreeTests{
    bool checkTree();
}

namespace WorldCupTests{
    bool teamsTreeTest();
    bool knockoutWinnerTest();
    bool segelTest();
    bool segelTesting();
    bool uniteTeamsTesting();
}

std::function<bool()> testsList[] = {
        NewTests::genTest,
//    PlayerTests::comparePlayersTest,
//        WorldCupTests::knockoutWinnerTest,
//    AVLTreeTests::checkTree,
//	HealthPointsTests::testArithmaticOperators,
//	HealthPointsTests::testComparisonOperators,
//	HealthPointsTests::testOutputOperator,
//
//	QueueTests::testQueueMethods,
//	QueueTests::testModuleFunctions,
//	QueueTests::testExceptions,
//    QueueTests::testConstQueue,
};

const int NUMBER_OF_TESTS = sizeof(testsList)/sizeof(std::function<bool()>);

//static void merge(int a [], int na, int b[], int nb, int c [] )
//{
//    int ia = 0, ib = 0, ic = 0;
//    while(ia < na && ib < nb) {
//        if (a[ia] < b[ib])
//            c[ic++] = a[ia++];
//        else
//            c[ic++] = b[ib++];
//    }
//    while(ia<na)
//        c[ic++] = a[ia++];
//    while(ib<nb)
//        c[ic++] = b[ib++];
//}
int main(int argc, char *argv[])
{

//    AVLTree<int,int>* tr = new AVLTree<int,int>();
//    tr->insert(5,5);
//    tr->insert(3,3);
//    tr->insert(2,2);
//    tr->insert(4,4);
//    tr->insert(0,0);
//    tr->insert(88, 88);
//    int arr[6] = {0};

//    tr->treeToArray(tr, arr);
//    for (int i = 0; i < 6; ++i) {
//        std::cout << arr[i] << ' ';
//    }
//    AVLTree<int,int>* tr1 = new AVLTree<int,int>();
    //tr1->arrayToTree(arr);
//    std::cout << '\n' << std::endl;
//    tr->printBT();
    /*
int a[] = {1,2,3,8};
int b[] = {2,3, 4, 5};
int c[8];
    merge(a,4,b,4,c);
    for (int i = 0; i < 8; ++i) {
        std::cout << c[i] << ' ';
    }


*/

    if (argc < 2) {
        for (int i = 0; i < NUMBER_OF_TESTS; ++i) {
            runTest(testsList[i], "Test " + std::to_string(i + 1));
        }
    }
    else {
        int idx = -1;
        try {
            idx = std::stoi(argv[1]) - 1;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: invalid argument: " << argv[1] << std::endl;
            return 1;
        }
        if (idx < 0 || idx > NUMBER_OF_TESTS - 1) {
            std::cerr << "Error: index out of range: " << argv[1] << std::endl;
            return 1;
        }
        runTest(testsList[idx], "Test " + std::to_string(idx + 1));
    }


    return 0;
}

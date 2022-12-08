//
// Created by David on 25/11/2022.
//
#define AGREGATE_TEST_RESULT(res, cond) (res) = ((res) && (cond))
#include "iostream"
#include "../AVLTree.h"
#include "../Player.h"
#include "../Team.h"
namespace AVLTreeTests{
    bool RRTreeTest()
    {
        AVLTree<int,Player*>* tr = new AVLTree<int,Player*>();
        Player* pl1 = new Player(20,5,5,5,5,false);
        Player* pl2 = new Player(22,5,5,5,5,false);
        Player* pl3 = new Player(30,5,5,5,5,false);
        tr->insert(pl1->getId(),pl1);
        tr->insert(pl2->getId(),pl2);
        tr->insert(pl3->getId(),pl3);
        tr->printBT();
        delete tr;
        return true;
    }

    bool LLTreeTest()
    {
        AVLTree<int,Player*>* tr = new AVLTree<int,Player*>();

        Player* pl1 = new Player(20,5,5,5,5,false);
        Player* pl2 = new Player(10,5,5,5,5,false);
        Player* pl3 = new Player(5,5,5,5,5,false);

        tr->insert(pl1->getId(),pl1);
        tr->insert(pl2->getId(),pl2);
        tr->insert(pl3->getId(),pl3);
        tr->printBT();
        delete tr;
        return true;
    }

    bool RLTreeTest()
    {
        AVLTree<int,Player*>* tr = new AVLTree<int,Player*>();

        Player* pl1 = new Player(20,5,5,5,5,false);
        Player* pl2 = new Player(22,5,5,5,5,false);
        Player* pl3 = new Player(21,5,5,5,5,false);

        tr->insert(pl1->getId(),pl1);
        tr->insert(pl2->getId(),pl2);
        tr->insert(pl3->getId(),pl3);
        delete tr;
        return true;
    }

    bool LRTreeTest()
    {
        AVLTree<int,Player*>* tr = new AVLTree<int,Player*>();

        Player* pl1 = new Player(20,5,5,5,5,false);
        Player* pl2 = new Player(10,5,5,5,5,false);
        Player* pl3 = new Player(15,5,5,5,5,false);

        tr->insert(pl1->getId(),pl1);
        tr->insert(pl2->getId(),pl2);
        tr->insert(pl3->getId(),pl3);
        tr->printBT();
        delete tr;
        return true;
    }

    bool caseDelete(int value, AVLTree<int,int> *tr)
    {
        tr->printBT();

        tr->deleteByKey(value);
        tr->printBT();
        return true;

    }
    bool caseInsert(int value, AVLTree<int,int> *tr)
    {
        tr->printBT();

        tr->insert(value, value);
        tr->printBT();
        return true;

    }

    bool insertTestCase1()
    {
        // first tree
        AVLTree<int,int>* tr1 = new AVLTree<int,int>();

        tr1->insert(20,20);
        tr1->insert(4,4);
//        caseInsert(15, *tr1);
        caseInsert(8, tr1);

        delete tr1;
        return true;
    }

    bool insertTestCase2()
    {
        // first tree
        AVLTree<int,int>* tr1 = new AVLTree<int,int>();

        tr1->insert(20,20);
        tr1->insert(26,26);
        tr1->insert(4,4);
        tr1->insert(3,3);
        tr1->insert(9,9);
        caseInsert(15, tr1);
//        caseInsert(8, tr1);

        delete tr1;
        return true;
    }

    bool insertTestCase3()
    {
        // first tree
        AVLTree<int,int>* tr1 = new AVLTree<int,int>();

        tr1->insert(20,20);
        tr1->insert(26,26);
        tr1->insert(4,4);
        tr1->insert(3,3);
        tr1->insert(9,9);
        tr1->insert(21,21);
        tr1->insert(30,30);
        tr1->insert(2,2);
        tr1->insert(7,7);
        TreeNode<int,int>* node = tr1->find(10);
        if(!node)
            std::cout << "Node not found" << std::endl;
        else
            std::cout << "Found node: " << node->m_data << std::endl;
        tr1->insert(11,11);


//        caseInsert(15, tr1);
        caseInsert(8, tr1);

        delete tr1;
        return true;
    }

    bool deleteTestCase1()
    {
        // first tree
        AVLTree<int,int>* tr1 = new AVLTree<int,int>();

        tr1->insert(2,2);
        tr1->insert(1,1);
        tr1->insert(4,4);
        tr1->insert(3,3);
        tr1->insert(5,5);
        caseDelete(1, tr1);
        delete tr1;
        return true;
    }

    bool deleteTestCase2()
    {
        // first tree
        AVLTree<int,int>* tr1 = new AVLTree<int,int>();

        tr1->insert(10,10);
        tr1->insert(5,5);
        tr1->insert(15,15);
        tr1->insert(1,1);
        tr1->insert(7,7);
        tr1->insert(14,14);
        tr1->insert(18,18);
        tr1->insert(8,8);
        tr1->insert(6,6);
        tr1->insert(13,13);
        tr1->insert(17,17);
        tr1->insert(19,19);
        tr1->insert(20,20);
        caseDelete(1, tr1);
        delete tr1;
        return true;
    }

    bool deleteTestCase3()
    {
        // first tree
        AVLTree<int,int>* tr1 = new AVLTree<int,int>();

        tr1->insert(10,10);
        tr1->insert(5,5);
        tr1->insert(15,15);
        tr1->insert(1,1);
        tr1->insert(7,7);
        tr1->insert(14,14);
        tr1->insert(18,18);
        tr1->insert(8,8);
        tr1->insert(13,13);
        tr1->insert(17,17);
        tr1->insert(19,19);
        tr1->insert(20,20);
        caseDelete(1, tr1);
        delete tr1;
        return true;
    }
    bool basicTest()
    {
        AVLTree<int,Player>* tr = new AVLTree<int,Player>();
        Player pl1(20,5,5,5,5,false);
        Player pl2(20,5,5,5,5,false);
        Player pl3(20,5,5,5,5,false);
        tr->insert(1,pl1);
        tr->insert(2,pl2);
        tr->insert(3, pl3);
        tr->printBT();
        tr->deleteByKey(2);
        tr->printBT();
        tr->deleteByKey(3);
        tr->printBT();
//        tr->insert(30,pl1);
//
//
//        tr->insert(8,pl1);
//        tr->insert(45,pl1);
//
//        tr->insert(46,pl1);
//        tr->insert(49,pl1);
//        tr->insert(2,pl1);
//
//        tr->deleteByKey(20);
//        tr->deleteByKey(49);
//        tr->deleteByKey(46);
//        tr->deleteByKey(30);
//        tr->deleteByKey(45);
//        tr->deleteByKey(8);
//        tr->deleteByKey(22);

        delete tr;
        return true;
    }
    bool checkTree()
    {
//        RRTreeTest();
//        LLTreeTest();
//        RLTreeTest();
//        LRTreeTest();
        basicTest();
//        insertTestCase1();
//        insertTestCase2();
//        insertTestCase3();
//        deleteTestCase1();
//        deleteTestCase2();
//        deleteTestCase3();

        return true;
    }
}

//
//  Astar->cpp
//  AStarA
//
//  Created by yiyang yuan on 8/24/12->
//  Copyright (c) 2012 __MyCompanyName__-> All rights reserved->
//

#include <iostream>
#include "Astar.h"

MapPoint* Astar::recordPoint =new MapPoint();

Astar::~Astar()
{
    
    for (int i = 0; i < m_OpenList.size(); i++) {
        MapPoint* p = m_OpenList[i];
        delete p;
    }
    for (int i = 0; i < m_CloseList.size(); i++) {
        MapPoint* p = m_CloseList[i];
        delete p;
    }
}

void Astar::start()
{
    m_map.pStart->G = 0;
    m_map.pStart->H = 0;
    m_map.pStart->F = m_map.GetF(m_map.pStart);
    m_OpenList.push_back(m_map.pStart);
    m_map.pStart->parent = NULL;
    curPoint = m_map.pStart;
    //Search();
}

void Astar::Search()
{
    //vector<MapPoint*>::iterator it = std::find(m_OpenList.begin(), m_OpenList.end(), m_map.pEnd);
    if (m_OpenList.size() <= 0 ) {
        if ( ContainInOpenlist(m_map.pEnd)) {
            stop = true;
            //break;
        }else {
            printf("没找到路径");
            stop = true;
            //break;
        }
    }
    if (m_OpenList.size() > 0) {
        if (ContainInCloselist(m_map.pEnd)) {
            printf("找到路径了");
            //m_parentsList.clear();
            /*
            MapPoint *p = m_map.pEnd ;
            while (p->parent != NULL) {
                printf("parent G value :%d\n",p->G);
                m_parentsList.push_back(p);
                p = p->parent;
            }*/
            
            printf("parent count :%lu",m_parentsList.size());
            stop = true;
            return;
        }
    }
    //sort(m_OpenList.begin(), m_OpenList.end());
    curPoint = FindSmallestFInOpenList();
    recordPoint = curPoint;
    printf("curPoint value :%d %d\n",curPoint->x,curPoint->y);
    for (vector<MapPoint*>::iterator it = m_OpenList.begin(); it != m_OpenList.end();) {
        if (*it == curPoint) {
            m_OpenList.erase(it);
        }else {
            ++it;
        }
    }
    m_CloseList.push_back(curPoint);
    TestEightSide(curPoint);
    
    m_parentsList.clear();
    while (curPoint->parent != NULL) {
        printf("parent G value :%d\n",curPoint->G);
        m_parentsList.push_back(curPoint);
        curPoint = curPoint->parent;
    }

}

void Astar::TestEightSide(MapPoint* p)
{
    for (int i = 0; i < 8; i++) {
        MapPoint* tempP ;
        if (i == 0) {
            if (p->x - 1 < 0) {
                continue;
            }
            tempP = new MapPoint(p->x-1,p->y);    //L
        }
        else if (i == 1) {
            if (p->x - 1 < 0 || p->y - 1 < 0) {
                continue;
            }
            tempP = new MapPoint(p->x-1,p->y - 1);//L,U
        }
        else if (i==2) {
            if (p->x - 1 < 0 || p->y + 1 > MAPHEIGHT) {
                continue;
            }
           tempP = new MapPoint(p->x-1,p->y + 1);//L,D
        }
        else if (i==3) {
            if (p->x + 1 > MAPWIDTH) {
                continue;
            }
            tempP = new MapPoint(p->x+1,p->y);//R
        }
        else if (i==4) {
            if (p->x + 1 > MAPWIDTH || p->y - 1 < 0) {
                continue;
            }
            tempP = new MapPoint(p->x+1,p->y - 1);//R,U
        }
        else if (i==5) {
            if (p->x + 1 > MAPWIDTH || p->y + 1 > MAPHEIGHT) {
                continue;
            }
            tempP = new MapPoint(p->x+1,p->y + 1);//R,D
        }
        else if (i==6) {
            if (p->y - 1 < 0) {
                continue;
            }
            tempP = new MapPoint(p->x,p->y-1);//U
        }
        else if (i== 7) {
            if (p->y + 1 > MAPHEIGHT) {
                continue;
            }
            tempP = new MapPoint(p->x,p->y + 1);//D
        }
        if (m_map.templateMap[tempP->y][tempP->x] == 1) {
            continue;
        }
        bool isInCloseList = false;
        for (int i = 0; i < m_CloseList.size(); i++) {
            if (*tempP == *m_CloseList[i]) {
                isInCloseList = true;
                break;
            }
        }
        if (isInCloseList) {
            continue;
        }
        tempP->parent = p;
        if (*tempP == *m_map.pEnd) {
            printf("add end in open list");
        }
        int G = 0;
        if (p->x != curPoint->x && p->y != curPoint->y) {
            G = 14;
        }else {
            G = 10;
        }
        tempP->G = curPoint->G + G;
        calculatePoint(tempP);
    }
    
    //printf("open list count :%lu\n",m_OpenList->size());
    //printf("close list count :%lu\n",m_CloseList->size());
    
}

void Astar::calculatePoint(MapPoint* p)
{
    bool canUpdate = false;
    //vector<MapPoint*>::iterator it = std::find(m_OpenList.begin(), m_OpenList.end(), p);
    if (!ContainInOpenlist(p)) {//开放列表里没有这个节点

        p->parent = curPoint;
        m_OpenList.push_back(p);
        canUpdate = true;
        return;
    }else {
        MapPoint *temp;
        for (int i = 0; i < m_OpenList.size(); i++) {
            if (*p == *m_OpenList[i]) {
                temp = m_OpenList[i];
                printf("found point G :%d",temp->G);
            }
        }
        
        if (p->G < temp->G) {
            curPoint = p->parent;
            canUpdate = true;
            
            (temp)->G = p->G;
            (temp)->H = p->H;
            (temp)->F = p->F;
            //sort(m_OpenList.begin(), m_OpenList.end());
            //SortOpenlist();
            for (int i = 0; i < m_OpenList.size(); i++) {
                if (*p == *m_OpenList[i]) {
                    temp = m_OpenList[i];
                    printf("更小的G point :%d",temp->G);
                }
            }
        }
        if (canUpdate) {
            p->H = (abs(p->x - m_map.pEnd->x)+abs(p->y - m_map.pEnd->y))*10;
            p->F = m_map.GetF(p);
        }
        
        return ;
    }
}

MapPoint* Astar::FindSmallestFInOpenList()
{
    MapPoint *p = m_OpenList[0];
    for (int i = 0; i < m_OpenList.size(); i++) {
        if (p->F > m_OpenList[i]->F) {
            p = m_OpenList[i];
        }
    }
    return p;
}

void Astar::SortOpenlist()
{
    for (int i = 0; i < m_OpenList.size(); i++) {
        for (int j = m_OpenList.size()-1; j > i; j--) {
            if (m_OpenList[i]->F > m_OpenList[j]->F) {
                MapPoint *temp = m_OpenList[i];
                m_OpenList[i] = m_OpenList[j];
                m_OpenList[j] = temp;
            }
        }
    }
}

bool Astar::ContainInOpenlist(MapPoint *p)
{
    for (int i = 0; i < m_OpenList.size(); i++) {
        if (*p == *m_OpenList[i]) {
            return true;
        }
    }
    return false;
}

bool Astar::ContainInCloselist(MapPoint *p)
{
    for (int i = 0; i < m_CloseList.size(); i++) {
        if (*p == *m_CloseList[i]) {
            return true;
        }
    }
    return false;
}


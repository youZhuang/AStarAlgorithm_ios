//
//  Astar.cpp
//  AStarA
//
//  Created by yiyang yuan on 8/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Astar.h"


void Astar::start()
{
    m_map.pStart.G = 0;
    m_map.pStart.H = 0;
    m_map.pStart.F = m_map.GetF(m_map.pStart);
    m_OpenList.push_back(m_map.pStart);
    m_map.pStart.parent = NULL;
    curPoint = m_map.pStart;
    //Search();
}

void Astar::Search()
{
    vector<MapPoint>::iterator it = std::find(m_OpenList.begin(), m_OpenList.end(), m_map.pEnd);
    if (m_OpenList.size() <= 0 ) {
        if ( it != m_OpenList.end()) {
            
            //break;
        }else {
            printf("没找到路径");
            stop = true;
            //break;
        }
    }
    if (it != m_OpenList.end()) {
        
//        MapPoint temp = curPoint;
//        m_parentsList.clear();
//        while (temp.parent != NULL) {
//            temp = *temp.parent;
//            printf("parent value :%d %d",temp.x,temp.y);
//            m_parentsList.push_back(temp);
//        }
//        printf("找到路径了");
        stop = true;
        /*
         for (int i = 0; i < m_OpenList.size(); i++) {
         MapPoint p = m_OpenList[i];
         delete p.parent;
         }
         for (int i = 0; i < m_CloseList.size(); i++) {
         MapPoint p = m_CloseList[i];
         delete p.parent;
         }*/
    }
    sort(m_OpenList.begin(), m_OpenList.end());
    curPoint = m_OpenList[0];
    printf("curPoint value :%d %d\n",curPoint.x,curPoint.y);
    for (vector<MapPoint>::iterator it = m_OpenList.begin(); it != m_OpenList.end();) {
        if (*it == curPoint) {
            m_OpenList.erase(it);
        }else {
            ++it;
        }
    }
    m_CloseList.push_back(curPoint);
    TestEightSide(curPoint);
    
    m_parentsList.clear();
    while (curPoint.parent != NULL) {
        printf("parent G value :%d\n",(curPoint).G);
        m_parentsList.push_back(curPoint);
        curPoint = *curPoint.parent;
    }
 
}

void Astar::find(MapPoint p)
{
    
}

void Astar::TestEightSide(MapPoint p)
{
    for (int i = 0; i < 8; i++) {
        MapPoint tempP;
        if (i == 0) {
            if (p.x - 1 < 0) {
                continue;
            }
            tempP = MapPoint(p.x-1,p.y);    //L
        }else if (i == 1) {
            if (p.x - 1 < 0 || p.y - 1 < 0) {
                continue;
            }
            tempP = MapPoint(p.x-1,p.y - 1);//L,D
        }else if (i==2) {
            if (p.x - 1 < 0 || p.y + 1 > MAPHEIGHT) {
                continue;
            }
           tempP = MapPoint(p.x-1,p.y + 1);//L,U
        }else if (i==3) {
            if (p.x + 1 > MAPWIDTH) {
                continue;
            }
            tempP = MapPoint(p.x+1,p.y);//R
        }else if (i==4) {
            if (p.x + 1 > MAPWIDTH || p.y - 1 < 0) {
                continue;
            }
            tempP = MapPoint(p.x+1,p.y - 1);//R,D
        }else if (i==5) {
            if (p.x + 1 > MAPWIDTH || p.y + 1 > MAPHEIGHT) {
                continue;
            }
            tempP = MapPoint(p.x+1,p.y + 1);//R,U
        }else if (i==6) {
            if (p.y - 1 < 0) {
                continue;
            }
            tempP = MapPoint(p.x,p.y-1);//D
        }else if (i==7) {
            if (p.y + 1 > MAPHEIGHT) {
                continue;
            }
            MapPoint tempP = MapPoint(p.x,p.y+1);//U
        }
        if (m_map.templateMap[tempP.y][tempP.x] == 1) {
            continue;
        }
        bool isInCloseList = false;
        for (int i = 0; i < m_CloseList.size(); i++) {
            if (tempP == m_CloseList[i]) {
                isInCloseList = true;
                break;
            }
        }
        if (isInCloseList) {
            continue;
        }
        tempP.parent = &p;
        if (tempP == m_map.pEnd) {
            printf("add end in open list");
        }
        calculatePoint(tempP);
    }
    
    //printf("open list count :%lu\n",m_OpenList.size());
    //printf("close list count :%lu\n",m_CloseList.size());
    
}

void Astar::calculatePoint(MapPoint p)
{
    vector<MapPoint>::iterator it = std::find(m_OpenList.begin(), m_OpenList.end(), p);
    if (it == m_OpenList.end()) {//开放列表里没有这个节点
        p.parent = new MapPoint();
        memcpy(p.parent, &curPoint, sizeof(MapPoint));
        int G = 0;
        if (abs(p.x - curPoint.x)+abs(p.y - curPoint.y) ==2) {
            G = 14;
        }else {
            G = 10;
        }
        p.G = curPoint.G + G;
        p.H = (abs(p.x - m_map.pEnd.x)+abs(p.y - m_map.pEnd.y))*10;
        p.F = m_map.GetF(p);
        m_OpenList.push_back(p);
        return;
    }else {
        MapPoint temp = *it;
        int G = 0;
        if (abs(p.x - curPoint.x)+abs(p.y - curPoint.y) ==2) {
            G = 14;
        }else {
            G = 10;
        }
        p.G = curPoint.G + G;
        p.H = (abs(p.x - m_map.pEnd.x)+abs(p.y - m_map.pEnd.y))*10;
        p.F = m_map.GetF(p);
        if (p.G < temp.G) {
            curPoint = *p.parent;
        }
        (*it).G = p.G;
        (*it).H = p.H;
        (*it).F = p.F;
        sort(m_OpenList.begin(), m_OpenList.end());
        return ;
    }
}

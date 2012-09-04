//
//  Astar.h
//  AStarA
//
//  Created by yiyang yuan on 8/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef AStarA_Astar_h
#define AStarA_Astar_h

#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include "Map.h"

class Astar{
    Map  m_map;
    vector<MapPoint> m_OpenList;
    vector<MapPoint> m_CloseList;
    vector<MapPoint> m_parentsList;
    MapPoint curPoint;
public:
    
    bool stop;
    
    Astar(){}
    ~Astar(){}
    
    void start();
    void Search();
    void find(MapPoint p);
    
    vector<MapPoint> getParentsList(){return m_parentsList;}
    
    void TestEightSide(MapPoint p);
    
    void calculatePoint(MapPoint p);
    
    Map GetMap(){return m_map;}
};

#endif

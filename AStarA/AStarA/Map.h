//
//  Map.h
//  AStarA
//
//  Created by yiyang yuan on 8/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef AStarA_Map_h
#define AStarA_Map_h

#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

#define MAPWIDTH  10
#define MAPHEIGHT 15

typedef struct MapPoint{
    int x;
    int y;
    int F,G,H;//G 起点到改点的消耗,H 改点到终点的消耗 F 路径评分 F = G + H;
    struct MapPoint* parent;
    MapPoint(){parent = NULL;F=G=H = 0;}
    MapPoint(int x_,int y_):x(x_),y(y_){ parent = NULL;F=G=H = 0;}
    bool operator<(const MapPoint& p) const {return F < p.F;}
    bool operator==(const MapPoint& p) const {return (p.x==x&&p.y==y);}
    bool operator!=(const MapPoint& p) const {return (p.x!=x||p.y!=y);}
} MapPoint;

class Map{
    
public:
    static int templateMap[MAPHEIGHT][MAPWIDTH];//only for debug
    vector<vector<int> > m_sMap;
    
    MapPoint *pStart;
    MapPoint *pEnd;
    
public:
    Map(){initMap();}
    ~Map(){}
    vector<vector<int> > initMap();//we should rand map value
    
    MapPoint* GetStart(){return pStart;}
    MapPoint* GetEndY(){return pEnd;}
    
    int GetF(MapPoint* p){return p->G+p->H;}
    int GetH(MapPoint* p){p->H = (abs(p->x - pEnd->x)+abs(p->y - pEnd->y))*10; return p->H;}
    
};

#endif

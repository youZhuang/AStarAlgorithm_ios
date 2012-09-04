//
//  Map.cpp
//  AStarA
//
//  Created by yiyang yuan on 8/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Map.h"

#define STARTVALUE 8
#define ENDVALUE   5

int Map::templateMap[MAPHEIGHT][MAPWIDTH] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 
    8, 0, 0, 0, 0, 0, 0, 0, 1, 1, 
    1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 
    1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 
    1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 
    1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 
    1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 
    1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 
    1, 0, 1, 1, 1, 1, 1, 1, 0, 5, 
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
    1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

vector<vector<int> > Map::initMap()
{
    //pStart.x = 0;pStart.y = 2;
    //pEnd.x = MAPWIDTH - 2;pEnd.y = MAPHEIGHT - 1;
    printf("map:\n");
    
    /*
    srand((unsigned)time(NULL));
    for (int i = 0; i < MAPHEIGHT; i++) {
        vector<int> v_Element;
        for (int j = 0; j < MAPWIDTH; j++) {
            
            int value = rand()%2;
            if (i == m_iStartY && j == m_iStartX) {
                v_Element.push_back(8);
            }else if (i == m_iEndY && j == m_iEndX) {
                v_Element.push_back(5);
            }else {
                v_Element.push_back(value);
            }
            printf("%d",v_Element[j]);
            
        }
        printf("\n");
        m_sMap.push_back(v_Element);
    }*/
    
    for (int i = 0; i < MAPHEIGHT; i++) {
        vector<int> v_Element;
        for (int j = 0; j < MAPWIDTH; j++) {
            
            v_Element.push_back(templateMap[i][j]);
            if (templateMap[i][j] == STARTVALUE) {
                pStart.x = j; pStart.y = i;
            }
            if (templateMap[i][j] == ENDVALUE) {
                pEnd.x = j;pEnd.y = i;
            }
            printf("%d",v_Element[j]);
        }
        printf("\n");
        m_sMap.push_back(v_Element);
    }
    return m_sMap;
}

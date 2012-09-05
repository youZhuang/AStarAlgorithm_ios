//
//  AStarView.m
//  AStarA
//
//  Created by yiyang yuan on 8/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AStarView.h"

#import "Astar.h"

static Astar *star = nil;
@implementation AStarView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        star = new Astar();
        star->start();
        [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(handleSearchWithTimer:) userInfo:nil repeats:YES];
    }
    return self;
}

-(void)handleSearchWithTimer:(NSTimer*)timer
{
    if (!star->stop) {
        star->Search();
        NSLog(@"cur point :%d,%d",star->recordPoint->x,star->recordPoint->y);
        [self setNeedsDisplay];
    }
}

-(void)drawPhotoCircleWith:(CGContextRef)context withRect:(CGRect)rect lineWidth:(CGFloat)width fillColor:(UIColor*)color
{
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathAddRect(path, NULL, rect);
    CGContextAddPath(context, path);
    [color setFill];
    UIColor *strokeColor = [UIColor colorWithRed:183.0/255.0 green:183.0/255.0 blue:183.0/255.0 alpha:1.0];
    [strokeColor setStroke];
    CGContextSetLineWidth(context, width);
    CGContextDrawPath(context, kCGPathFillStroke);
    CGPathRelease(path);
}

-(void)drawColorWith:(CGContextRef)context withRect:(CGRect)rect withColor:(UIColor*)color
{
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathAddRect(path, NULL, rect);
    CGContextAddPath(context, path);
    [color setFill];
    CGContextDrawPath(context, kCGPathFill);
    CGPathRelease(path);
}

-(void)renderMapWith:(CGFloat)width height:(CGFloat)height withContext:(CGContextRef)context
{
    CGFloat offset = 0;
    CGFloat blockWidth = (width - 2 * offset)/MAPWIDTH;
    CGFloat blockHeight = (height - 2 * offset)/MAPHEIGHT;
    for (int j = 0; j < MAPHEIGHT; j++) {
        for (int i = 0; i < MAPWIDTH; i++) {
            if (star->GetMap().m_sMap[j][i] == 1) {
                [self drawColorWith:context withRect:CGRectMake(i * blockWidth + offset, j*blockHeight + offset, blockWidth, blockHeight) withColor:[UIColor blackColor]];
            }
            if (star->GetMap().m_sMap[j][i] == 0) {
                [self drawColorWith:context withRect:CGRectMake(i * blockWidth + offset, j*blockHeight + offset, blockWidth, blockHeight) withColor:[UIColor grayColor]];
            }
            if (star->GetMap().m_sMap[j][i] == 5 || star->GetMap().m_sMap[j][i] == 8) {
                [self drawColorWith:context withRect:CGRectMake(i * blockWidth + offset, j*blockHeight + offset, blockWidth, blockHeight) withColor:[UIColor redColor]];
            }
        }
    }
    for (int i = 0; i < star->getParentsList().size(); i++) {
        MapPoint* p = star->getParentsList()[i];
        [self drawColorWith:context withRect:CGRectMake(p->x * blockWidth + offset, p->y*blockHeight + offset, blockWidth, blockHeight) withColor:[UIColor blueColor]];
    }
    [self drawColorWith:context withRect:CGRectMake(star->recordPoint->x * blockWidth + offset, star->recordPoint->y*blockHeight + offset, blockWidth, blockHeight) withColor:[UIColor greenColor]];
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    CGContextRef currentContext = UIGraphicsGetCurrentContext();
    CGContextSaveGState(currentContext);
    //绘制地图
    [self renderMapWith:rect.size.width height:rect.size.height withContext:currentContext];
    
}

@end

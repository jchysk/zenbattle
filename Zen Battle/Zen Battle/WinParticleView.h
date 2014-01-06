//
//  WinParticleView.h
//  QuadCrush
//
//  Created by Ryan Bigger on 5/22/13.
//  Copyright (c) 2013 Raster Media. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface WinParticleView : UIView

@property (nonatomic) CGFloat time;

-(void)configurateEmmiter;
-(void)setIsEmitting:(BOOL)isEmitting andPoint:(CGPoint)point;

@end

//
//  WinParticleView.m
//  QuadCrush
//
//  Created by Ryan Bigger on 5/22/13.
//  Copyright (c) 2013 Raster Media. All rights reserved.
//

#import "WinParticleView.h"
#import <QuartzCore/QuartzCore.h>

@implementation WinParticleView
{
    CAEmitterLayer * fireEmitter;
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

-(void)configurateEmmiter
{
    //set ref to the layer
    fireEmitter = (CAEmitterLayer*)self.layer;
    
    //configure the emitter layer
    fireEmitter.emitterPosition = CGPointMake(50, 50);
    fireEmitter.emitterSize = CGSizeMake(5, 5);
    
    CAEmitterCell* fire = [CAEmitterCell emitterCell];
    fire.birthRate = 0;
    fire.lifetime = 5.0f;
    fire.lifetimeRange = 0.5;
    fire.contents = (id)[[UIImage imageNamed:@"burst.png"] CGImage];
    [fire setName:@"burst"];
    
    fire.velocity = 640;
    fire.velocityRange = 160;
    
    fire.emissionRange = M_PI * 2.0f;
    
    fire.scaleSpeed = 0.1;
    fire.spin = 0.5;
    fire.spinRange = M_PI;
    
    //add the cell to the layer and we're done
    fireEmitter.emitterCells = [NSArray arrayWithObject:fire];
    fireEmitter.renderMode = kCAEmitterLayerCircle;
}

+ (Class) layerClass
{
    return [CAEmitterLayer class];
}

-(void)setIsEmitting:(BOOL)isEmitting andPoint:(CGPoint)point
{
    fireEmitter.emitterPosition = point;
    
    //turn on/off the emitting of particles
    [fireEmitter setValue:[NSNumber numberWithInt:isEmitting?160:0]
               forKeyPath:@"emitterCells.burst.birthRate"];
    
    
    [self performSelector:@selector(decayStep) withObject:nil afterDelay:self.time];
}

- (void)decayStep
{
    [fireEmitter setValue:[NSNumber numberWithInt:0]
               forKeyPath:@"emitterCells.burst.birthRate"];
}

@end

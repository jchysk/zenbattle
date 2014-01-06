//
//  LineChartSeries.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import "SChartGLCommon.h"

@interface SChartGLView (LineChartSeries)

- (void)horizontalFill:(float*)series
             forSeries:(SChartSeries *)s
              forIndex:(int *)index
              withSize:(NSInteger)size
             withColor:(UIColor*)fillColour
withColorBelowBaseline:(UIColor*)fillColourBelowBaseline
 withGradientFillColor:(UIColor*)gradientFillColour
withGradientFillColorBelowBaseline:(UIColor*)gradientFillColourBelowBaseline
          withBaseline:(float)baseline
withMaxOffsetAboveBaseline:(float)maxOffsetAboveBaseline
withMaxOffsetBelowBaseline:(float)maxOffsetBelowBaseline
     withFillDirection:(NSInteger)fillDirection
      withGradientFill:(BOOL)gradientFill
        andTranslation:(const SChartGLTranslation *)transform;

- (void)drawLineStrip:(float*)series
            forSeries:(SChartSeries *)s
        forLinesIndex:(int *)linesIndex
forIndexedOffsetTrianglesIndex:(int *)indexedOffsetTrianglesIndex
      forPointsOffset:(int *)pointsIndex
             withSize:(NSInteger)size
            withColor:(UIColor*)lineColour
withColorBelowBaseline:(UIColor*)lineColourBelowBaseline
            withWidth:(float)width
         withBaseline:(float)baseline
    withFillDirection:(NSInteger)fillDirection
       andTranslation:(const SChartGLTranslation *)transform;

- (void)drawDataPoints:(float *)series
             forSeries:(SChartSeries *)s
              forIndex:(int *)index
     withPointTextures:(UIImage **)textures
              withSize:(NSInteger)size
             withColor:(UIColor *)pointColour
withColorBelowBaseline:(UIColor*)pointColourBelowBaseline
            withRadius:(float)radius
       withRadiusArray:(float*)radii
          withBaseline:(float)baseline
     withFillDirection:(NSInteger)fillDirection
        andTranslation:(const SChartGLTranslation *)translation;

@end

//
//  BarColumnChartSeries.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#import "SChartGLCommon.h"

@interface SChartGLView (BarColumnChartSeries)

- (void)barColumnFill               :(float*)series
                           forSeries:(SChartSeries *)s
                      withBaseSeries:(float*)baseSeries
                            forIndex:(int *)trianglesIndex
                            withSize:(GLuint)size
                           withColor:(UIColor*)fillColour
              withColorBelowBaseline:(UIColor*)fillColourBelowBaseline
                   withColorGradient:(UIColor*)fillColourGradient
      withColorGradientBelowBaseline:(UIColor*)fillColourGradientBelowBaseline
                  withBarColumnWidth:(float)barColumnWidth
                      withGLBaseline:(float)glBaseline
                      andOrientation:(NSInteger)orientation
                    willDrawLinesToo:(BOOL)willDrawLines
                      andTranslation:(const SChartGLTranslation *)transform;

- (void)barColumnLine               :(float*)series
                           forSeries:(SChartSeries *)s
                      withBaseSeries:(float*)baseSeries
                            forIndex:(int *)linesIndex
                            withSize:(GLuint)i
                           withColor:(UIColor*)lineColor
              withColorBelowBaseline:(UIColor*)lineColourBelowBaseline
                  withBarColumnWidth:(float)barColumnWidth
                       withLineWidth:(float)lineWidth
                      withGLBaseline:(float)glBaseline
                      andOrientation:(NSInteger)orientation
                      andTranslation:(const SChartGLTranslation *)transform;

@end

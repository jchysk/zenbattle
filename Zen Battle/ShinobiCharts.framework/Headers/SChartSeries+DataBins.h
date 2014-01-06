//
//  SChartSeries+DataBins.h
//  ShinobiCharts
//
//  Copyright 2013 Scott Logic Ltd. All rights reserved.
//
//

#import "SChartSeries.h"

@interface SChartSeries (DataBins)

- (NSInteger)numberOfDataPointsInBin;

- (void)setNumberOfDataPointsInBin:(NSInteger)numberOfDataPoints;

@end

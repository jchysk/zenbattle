#import "SChartPointStruct.h"
#import "SChartSeriesDataBin.h"

typedef struct SChartSeriesDistanceInfo
{
    double distance;
    SChartInternalDataPoint *__unsafe_unretained point;
    SChartSeriesDataBin *__unsafe_unretained bin;
    SChartCartesianSeries *__unsafe_unretained const series;
    SChartPoint resolvedPoint;
} SChartSeriesDistanceInfo;

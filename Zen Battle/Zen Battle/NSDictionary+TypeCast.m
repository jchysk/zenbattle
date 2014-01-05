//
//  NSDictionary+TypeCast.m
//  tabeso-ios
//
//  Created by Ryan Bigger on 9/17/12.
//  Copyright (c) 2012 Raster Media LLC. All rights reserved.
//

#import "NSDictionary+TypeCast.h"

static NSDateFormatter *dateFormatterDate;
static NSDateFormatter *dateFormatterTime;

@implementation NSDictionary (TypeCast)

- (id)nonNilValueForKey:(NSString *)key
{
    id value = [self objectForKey:key];
    if (value) {
        return value;
    }
    
    return @"";
}

- (NSDate *)dateForKey:(NSString *)key
{
    id value = [self objectForKey:key];
    if ([value isKindOfClass:[NSDate class]]) {
        return value;
    }
    
    if (dateFormatterDate == nil) {
        dateFormatterDate = [[NSDateFormatter alloc] init];
        [dateFormatterDate setDateFormat:@"yyyy-MM-dd"];
    }
    
    if ([value isKindOfClass:[NSString class]]) {
        NSString *strValue = value;
        NSDate *dateFromString = [dateFormatterDate dateFromString:strValue];
        return dateFromString;
    }
    
    return nil;
}

- (NSDate *)datetimeForKey:(NSString *)key
{
    id value = [self objectForKey:key];
    if ([value isKindOfClass:[NSDate class]]) {
        return value;
    }
    
    if ([value isKindOfClass:[NSString class]]) {
        NSString *time = (NSString *)value;
        
        // [RMUtils logWithNamespace:@"TypeCast" withMessage:@"Time: %@", time];
        
        if (dateFormatterTime == nil) {
            dateFormatterTime = [[NSDateFormatter alloc] init];
            [dateFormatterTime setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
            [dateFormatterTime setTimeZone:[NSTimeZone timeZoneWithAbbreviation:@"GMT"]];
        }
        
        NSDate *dateFromString = [dateFormatterTime dateFromString:time];
        // [RMUtils logWithNamespace:@"TypeCast" withMessage:@"Date: %@", dateFromString];
        return dateFromString;
    }
    
    return nil;
}

- (NSNumber *)numberForKey:(NSString *)key
{
    id value = [self objectForKey:key];
    if ([value isKindOfClass:[NSNumber class]]) {
        return value;
    }
    
    if ([value isKindOfClass:[NSString class]]) {
        NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
        [numberFormatter setAllowsFloats:YES];
        [numberFormatter setNumberStyle:NSNumberFormatterNoStyle];
        NSNumber *numberFromString = [numberFormatter numberFromString:value];
        
        return numberFromString;
    }
    
    return nil;
}

- (NSString *)stringForKey:(NSString *)key
{
    id value = [self objectForKey:key];
    if ([value isKindOfClass:[NSString class]]) {
        return value;
    }
    
    if ([value isKindOfClass:[NSNumber class]]) {
        NSString *stringFromNumber = [value stringValue];
        return stringFromNumber;
    }
    
    return nil;
}

@end

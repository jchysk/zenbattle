//
//  NSDictionary+TypeCast.h
//  tabeso-ios
//
//  Created by Ryan Bigger on 9/17/12.
//  Copyright (c) 2012 Raster Media LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (TypeCast)

- (id)nonNilValueForKey:(NSString *)key;
- (NSDate *)dateForKey:(NSString *)key;
- (NSDate *)datetimeForKey:(NSString *)key;
- (NSNumber *)numberForKey:(NSString *)key;
- (NSString *)stringForKey:(NSString *)key;

@end

//
//  ServerConnection.m
//  Speaker Replay
//
//  Created by Ryan Bigger on 9/5/12.
//  Copyright (c) 2012 Raster Media. All rights reserved.
//

#import "ServerConnection.h"

@implementation ServerConnection
{
    void (^_completionHandler)(BOOL success, NSData *data,  NSDictionary *json);
    BOOL _shouldReturnJSON;
}

@synthesize dataFile;
@synthesize dataJSON;

- (id)initWithURL:(NSString *)path method:(NSString *)method
{
    return [self initWithURL:path method:method delegate:nil reference:nil];
}

- (id)initWithURL:(NSString *)path method:(NSString *)method delegate:(id)delegate reference:(NSString *)reference
{
    if (self = [super init]) {
        _shouldReturnJSON = YES;
        
        responseData = [[NSMutableData alloc] init];
        [self setPathURL:path];
        [self setDelegate:delegate];
        [self setMethod:method];
        [self setReference:reference];
    }
    return self;
}

#pragma mark - Request methods

- (void)startFileUpload
{
    [self startFileUploadWithCompletionHandler:nil];
}

- (void)startFileUploadWithCompletionHandler:(void (^)(BOOL success, NSData *data,  NSDictionary *json))completionHandler
{
    _completionHandler = completionHandler;
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    [RMUtils logWithNamespace:[[self class] description] withMessage:@"%@: %@", self.method, self.pathURL];
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    [request setURL:[NSURL URLWithString:self.pathURL]];
    [request setHTTPMethod:self.method];
    
    NSString *auth_token = [[NSUserDefaults standardUserDefaults] valueForKey:@"auth_token"];
    if (auth_token) {
        [RMUtils logWithNamespace:[[self class] description] withMessage:@"Token: %@", auth_token];
        [request addValue:auth_token forHTTPHeaderField:@"token"];
    }
    
    [request addValue:@"multipart/form-data; boundary=---------------------------382770706151373297771378430" forHTTPHeaderField: @"Content-Type"];
    
    NSMutableData *body = [NSMutableData data];
    [body appendData:[@"\r\n-----------------------------382770706151373297771378430\r\n" dataUsingEncoding:NSUTF8StringEncoding]];
    
    for (NSString *key in self.dictContent) {
        [body appendData:[[NSString stringWithFormat:@"Content-Disposition: form-data; name=\"photo[%@]\"\r\n", key] dataUsingEncoding:NSUTF8StringEncoding]];
        [body appendData:[@"Content-Type: application/json\r\n\r\n" dataUsingEncoding:NSUTF8StringEncoding]];
        [body appendData:[[_dictContent objectForKey:key] dataUsingEncoding:NSUTF8StringEncoding]];
        [body appendData:[@"\r\n-----------------------------382770706151373297771378430\r\n" dataUsingEncoding:NSUTF8StringEncoding]];
    }
    
    [body appendData:[@"Content-Disposition: form-data; name=\"photo[photo_bn]\"; filename=\"image.png\"\r\n" dataUsingEncoding:NSUTF8StringEncoding]];
    [body appendData:[@"Content-Type: application/octet-stream\r\n\r\n" dataUsingEncoding:NSUTF8StringEncoding]];
    [body appendData:self.dataFile];
    [body appendData:[@"\r\n-----------------------------382770706151373297771378430--" dataUsingEncoding:NSUTF8StringEncoding]];
    
    //    NSLog(@"%@", [[NSString alloc] initWithData:body encoding:NSASCIIStringEncoding]);
    
    // set request body
    [request setHTTPBody:body];
    urlConnection = [[NSURLConnection alloc] initWithRequest:request delegate:self];
}

- (void)startFileDownload
{
    [self startFileDownloadWithCompletionHandler:nil];
}

- (void)startFileDownloadWithCompletionHandler:(void (^)(BOOL success, NSData *data,  NSDictionary *json))completionHandler
{
    _shouldReturnJSON = NO;
    _completionHandler = completionHandler;
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
    NSURL *url = [NSURL URLWithString:self.pathURL];
    [RMUtils logWithNamespace:[[self class] description] withMessage:@"URL: %@", self.pathURL];
    
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url
                                                           cachePolicy:NSURLRequestUseProtocolCachePolicy
                                                       timeoutInterval:40];
    urlConnection = [[NSURLConnection alloc] initWithRequest:request delegate:self];
}

- (void)startRequest
{
    [self startRequestWithCompletionHandler:nil];
}

- (void)startRequestWithCompletionHandler:(void (^)(BOOL success, NSData *data,  NSDictionary *json))completionHandler
{
    _completionHandler = completionHandler;
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
    NSURL *url = [NSURL URLWithString:self.pathURL];
    RMLogSave(@"%@: %@", self.method, self.pathURL);
    
    NSString *authToken = [[NSUserDefaults standardUserDefaults] valueForKey:@"auth_token"];
    if (authToken == nil || [authToken isEqualToString:@""]) {
        authToken = [[NSUserDefaults standardUserDefaults] valueForKey:@"default_auth_token"];
    }
    RMLogSave(@"Token: %@", authToken);
    
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url
                                                           cachePolicy:NSURLRequestReloadIgnoringCacheData
                                                       timeoutInterval:40];
    [request setHTTPMethod:self.method];
    [request setValue:@"application/json; charset=UTF-8" forHTTPHeaderField:@"Content-Type"];
//    [request setValue:authToken forHTTPHeaderField:@"auth_token"];
//    [request setValue:@"2.0" forHTTPHeaderField:@"api-version"];
    
    if (self.dataJSON) {
        RMLogSave(@"JSON: %@", [[NSString alloc] initWithData:self.dataJSON encoding:NSUTF8StringEncoding]);
        [request setHTTPBody:dataJSON];
    }
    urlConnection = [[NSURLConnection alloc] initWithRequest:request delegate:self];
}

- (void)cancelRequest
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    
    [urlConnection cancel];
    urlConnection      = nil;
    responseData       = nil;
}

#pragma mark - Return methods

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [responseData appendData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    RMLogSave(@"Connection did fail with error: %@ \nFailing URL: %@",
          [error localizedDescription],
          [[error userInfo] objectForKey:NSURLErrorFailingURLErrorKey]);
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    if (_delegate != nil && [_delegate respondsToSelector:@selector(connectionDidFailWithError:reference:)]) {
        [_delegate connectionDidFailWithError:error reference:self.reference];
    }
    
    if (_completionHandler) {
        _completionHandler(NO, nil, nil);
        _completionHandler = nil;
    }
    
    responseData = nil;
    urlConnection = nil;
}

- (void)connectionDidFinishLoading:(NSURLConnection*)connection
{
    // [RMUtils logWithNamespace:[[self class] description] withMessage:@"Response: %@", [[NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding]];
    
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    if (_delegate != nil && [_delegate respondsToSelector:@selector(connectionDidFinishLoading:reference:)]) {
        [_delegate connectionDidFinishLoading:responseData reference:self.reference];
    }
    
    if (_completionHandler) {
        
        if (_shouldReturnJSON) {
            NSError *error;
            NSDictionary *json = [NSJSONSerialization JSONObjectWithData:responseData options:NSJSONReadingMutableContainers error:&error];
            
            if (error) {
//                [RMUtils showAlertViewWithTitle:@""
//                                        message:@"Server Response Error.  Please try again."
//                                  cancelMessage:NSLocalizedString(@"OK", @"OK")];
                
                RMLogSave(@"JSON serialization error: %@, Response body: %@",
                      [error localizedDescription],
                      [[NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding]);
                
                _completionHandler(NO, responseData, nil);
            } else {
                if (kOutputAPIResponse) {
                    [RMUtils logWithNamespace:[[self class] description] withMessage:@"Response: %@", json];
                }
                _completionHandler(YES, responseData, json);
            }
        } else {
            if (kOutputAPIResponse) {
                [RMUtils logWithNamespace:[[self class] description] withMessage:@"Response length: %i", responseData.length];
            }
            _completionHandler(YES, responseData, nil);
        }
        
        _completionHandler = nil;
    }
    
    responseData = nil;
    urlConnection = nil;
}

@end

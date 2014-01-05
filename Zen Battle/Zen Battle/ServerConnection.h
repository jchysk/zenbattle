//
//  ServerConnection.h
//  Speaker Replay
//
//  Created by Ryan Bigger on 9/5/12.
//  Copyright (c) 2012 Raster Media. All rights reserved.
//

@protocol ServerConnectionDelegate;

@interface ServerConnection : NSObject
{
    NSData *dataJSON;
    NSData *dataFile;
    
    NSMutableData *responseData;
    NSURLConnection *urlConnection;
}

@property (strong, nonatomic) id delegate;

@property (strong, nonatomic) NSData   * dataJSON;
@property (strong, nonatomic) NSData   * dataFile;
@property (strong, nonatomic) NSString * pathURL;
@property (strong, nonatomic) NSString * method;
@property (strong, nonatomic) NSString * reference;
@property (strong, nonatomic) NSDictionary * dictContent;

- (id)initWithURL:(NSString *)path method:(NSString *)method;
- (id)initWithURL:(NSString *)path method:(NSString *)method delegate:(id)delegate reference:(NSString *)reference;

- (void)startFileUpload;
- (void)startFileUploadWithCompletionHandler:(void (^)(BOOL success, NSData *data,  NSDictionary *json))completionHandler;

- (void)startFileDownload;
- (void)startFileDownloadWithCompletionHandler:(void (^)(BOOL success, NSData *data,  NSDictionary *json))completionHandler;

- (void)startRequest;
- (void)startRequestWithCompletionHandler:(void (^)(BOOL success, NSData *data, NSDictionary *json))completionHandler;

- (void)cancelRequest;

@end

@protocol ServerConnectionDelegate

@optional
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;
- (void)connectionDidFailWithError:(NSError *)error reference:(NSString *)ref;
- (void)connectionDidFinishLoading:(NSMutableData *)response reference:(NSString *)ref;

@end

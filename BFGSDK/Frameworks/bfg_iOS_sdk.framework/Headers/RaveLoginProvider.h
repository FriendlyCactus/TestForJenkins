//
//  RaveLoginProvider.h
//  RaveSocial
//
//  Created by gwilliams on 12/6/13.
//  Copyright (c) 2013 Rave, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <bfg_iOS_sdk/RaveUtilities.h>

extern NSString * const RaveConnectPluginFacebook;
extern NSString * const RaveConnectPluginGooglePlus;

@protocol RaveLoginProvider;
typedef id<RaveLoginProvider>(^RaveProviderFactoryCallback)(void);

@protocol RaveLoginProvider <NSObject>
- (void)useTokenForRaveUpgrade:(id)token;
- (void)loginWithCallback:(RaveCompletionCallback)callback;
- (void)connectToWithCallback:(RaveCompletionCallback)callback;
- (BOOL)isReady;
- (void)checkReadinessWithCallback:(RaveReadinessCallback)callback;
- (void)disconnectWithCallback:(RaveCompletionCallback)callback;
- (void)logOut;

- (BOOL)supportsExternalContacts;
- (void)fetchContacts:(RaveContactsCallback)callback;
- (void)shareText:(NSString *)text withImageURL:(NSString *)imageURL withCallback:(RaveCompletionCallback)callback;
- (void)shareWithByIds:(NSArray *)contactIds subject:(NSString *)subject message:(NSString *)message withCallback:(RaveProviderShareRequestCallback)callback;
- (NSString *)extractExternalIdFromUrl:(NSString *)appCallUrl;
@end

//  consider private
@protocol RaveLoginProviderWithFriends <RaveLoginProvider>
- (BOOL)AutoSyncFriends;
- (void)addFriends:(dispatch_block_t)callback;
@end

@interface RaveFacebookLoginProvider : NSObject<RaveLoginProvider>
+ (void)createAndRegister;
@end

@interface RaveGooglePlusLoginProvider : NSObject<RaveLoginProvider>
+ (void)createAndRegister;
@end

@interface RaveLoginProviderManager : NSObject
- (id)providers;
- (id<RaveLoginProvider>) providerByName:(NSString *)pluginKeyName;
- (void)logOut;
- (void)registerProviderWithName:(NSString *)pluginKeyName factoryCallback:(RaveProviderFactoryCallback)factoryCallback;
@end

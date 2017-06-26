//
//  bfgRave.h
//  bfg_iOS_sdk
//
//  Created by Jason Booth on 6/30/16.
//  Copyright © 2016 Big Fish Games, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <bfg_iOS_sdk/RaveSocial.h>

@protocol bfgRaveDelegate;
FOUNDATION_EXPORT NSString * const BFGRaveErrorDomain;
typedef NS_ENUM(NSInteger, BFGRaveErrorCode)
{
    BFGRaveErrorCodeInternalError = 1
};

///
/// \brief Provides methods for getting information about the current user.
///
@interface bfgRave : NSObject <RaveCurrentUserObserver>

///
/// \details Sets a delegate for bfgRave.  The delegate will be informed of login changes.
///
/// \param delegate The delegate for bfgRave.
///
+ (void)setDelegate:(id<bfgRaveDelegate>)delegate;

///
/// \details Call this to directly observe status changes in Rave
///
/// \param externalCallback The block of code to be called when there's a change in login status.
///
+ (void)setupLoginStatusCallbackWithExternalCallback:(RaveLoginStatusCallback)externalCallback;

///
/// \details Get the Rave ID of the current user.
///
/// \returns The Rave ID of the current user or nil if there isn't one.
///
+ (NSString *)currentRaveId;

///
/// \details Get whether the current user is a guest (unauthenticated).
///
/// \returns YES if the current user is a guest, NO if authenticated.
///
+ (BOOL)isCurrentGuest;

///
/// \details Get the Rave ID of the last user that is not the same as the current user.
///
/// \returns The Rave ID of the last user or nil if there isn't one.
///
+ (NSString *)lastRaveId;

///
/// \details Get whether the last user is a guest (unauthenticated).
///
/// \returns YES if the last user is a guest, NO if authenticated.
///
+ (BOOL)isLastGuest;

///
/// \details Logs out the current user if that user is not a guest.
///
+ (void)logoutCurrentUser;

///
/// \details Presents the standard sign-in screen if the current user is a guest.
///
+ (void)presentSignIn;

///
/// \details Presents the standard profile screen if the current user is not a guest.
///
+ (void)presentProfile;

///
/// \details Returns whether rave is initialized or not.
///
+ (BOOL)isRaveInitialized;

@end

@protocol bfgRaveDelegate <NSObject>

@optional

///
/// \details Informs the delegate when there has been an error with the profile screen
///
/// \param loginError The error, if any, that was encountered.
///
- (void)bfgRaveProfileFailedWithError:(NSError *)error;

///
/// \details Informs the delegate that the profile updated successfully
///
- (void)bfgRaveProfileSucceeded;

///
/// \details Informs the delegate that the user cancelled the profile screen
///
- (void)bfgRaveProfileCancelled;

///
/// \details Informs the delegate of the COPPA status after a successful signin
///
/// \param passedCOPPA YES if the user passed the COPPA check, NO if the user failed the COPPA check
///
- (void)bfgRaveSignInCOPPAResult:(BOOL)passedCOPPA;

///
/// \details Informs the delegate that the signin succeeded
///
- (void)bfgRaveSignInSucceeded;

///
/// \details Informs the delegate that the signin was cancelled by the user
///
- (void)bfgRaveSignInCancelled;

///
/// \details Informs the delegate when there has been an error with the signin screen
///
/// \param loginError The error, if any, that was encountered.
///
- (void)bfgRaveSignInFailedWithError:(NSError *)error;

///
/// \details Informs the delegate when a user has logged in
///
- (void)bfgRaveUserDidLogin;

///
/// \details Informs the delegate when a user has logged out
///
- (void)bfgRaveUserDidLogout;

///
/// \details Informs the delegate when there has been an error in the login process
///
/// \param loginError The error, if any, that was encountered.
///
- (void)bfgRaveUserLoginError:(NSError *)loginError;

@end
///
/// \file bfgManager.h
/// \brief Interface for performing core Big Fish SDK tasks
///
// \author Created by Sean Hummel on 10/30/10.
// \author Updated by Ben Flynn 12/18/12.
// \author Updated by Ben Flynn 7/13/15.
// \copyright Copyright 2013 Big Fish Games, Inc. All rights reserved.
///

#import "bfglibPrefix.h"

/*
 NOTIFICATIONS
 */

/// Sent after GDN play button is selected.
#define    BFGPROMODASHBOARD_NOTIFICATION_COLDSTART            @"BFGPROMODASHBOARD_NOTIFICATION_CONTINUE"

/// Sent after GDN resume button is selected.
#define BFGPROMODASHBOARD_NOTIFICATION_WARMSTART            @"BFGPROMODASHBOARD_NOTIFICATION_APPLICATION_RESUMED"

/// An internal web browser has closed.
#define BFGPROMODASHBOARD_NOTIFICATION_WEBBROWSER_CLOSED    @"BFGPROMODASHBOARD_NOTIFICATION_WEBBROWSER_CLOSED"

/*
 Settings
 */

#define BFGDASH_UI_TYPE_NONE_STRING                     @"no"
#define BFGDASH_UI_TYPE_DASHFULL_STRING                 @"fs"
#define BFGDASH_UI_TYPE_ADS_STRING                      @"ad"

/// Whether the SDK is displaying UI and what UI is displayed.
typedef enum
{
    BFGDASH_UI_TYPE_NONE = 0, /**< The SDK is not displaying any UI. */
    BFGDASH_UI_TYPE_DASHFULL = 1, /**< The full Dashboard is displayed. */
    BFGDASH_UI_TYPE_DASHWIN __attribute__((deprecated)) = BFGDASH_UI_TYPE_DASHFULL /**< No longer possible */
}
BFGDASH_UI_TYPE;

@protocol bfgManagerPauseResumeDelegate;

/**
 @brief Initialize the Big Fish Game Components.
 
 Initialize bfgManager to enable the Big Fish Game Discovery Network (GDN).
 
 You should initialize the bfgManager when your application finishes launching with either your root view controller
 or your main window.  If your main window is ready inside the AppDelegate then you will use this call:
 
 \code
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 {
 ...
 [bfgManager startWithLaunchOptions:launchOptions parentViewController:myRootViewController];
 ...
 }
 
 \endcode
 
 If your main window won't be ready until later then you will do the following.  In the AppDelegate:
 
 \code
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 {
 ...
 [bfgManager initWithLaunchOptions:launchOptions];
 ...
 }
 
 \endcode
 
 Then, whenever your main window is ready:
 
 \code
 - (void)myMainWindowReady
 {
 ...
 [bfgManager startWithParentViewController:myMainViewController];
 ...
 }
 
 \endcode


 If you are using these APIs, you should become an observer for the following events:
 
 <UL>
 <LI>BFGPROMODASHBOARD_NOTIFICATION_COLDSTART - Sent after the GDN play button is selected.
 <LI>BFGPROMODASHBOARD_NOTIFICATION_WARMSTART - Sent after the GDN resume button is selected.
 </UL>

 Lastly, if you are interested in pausing and resuming your game when the SDK is doing something that will
 obscure your game window (e.g. presenting an upsell), you can become a delegate for these events by implementing
 the bfgManagerPauseResumeDelegate protocol.
 
 */
@interface bfgManager : NSObject


///
/// \details Number of session for the application. Incremented on each UIApplicationDidBecomeActiveNotification.
///
+ (NSInteger)sessionCount;


///
/// \details It is the initial launch or "install" of the application.
///
+ (BOOL)isInitialLaunch;


///
/// \details Application has been started from a cold-started.
///
+ (BOOL)isFirstTime;


///
/// \return
/// \retval YES if bfgManger initialized.
/// \retval NO if bfgManger did not initialize.
///
+ (BOOL)isInitialized;


///
/// \details Gets the unique integer identifying this user. Used in all reporting calls to services.
/// Obtains the GameUID, and defaults to UID if it doesn't exist.
/// If UID doesn't exist it defaults to zero.
///
+ (NSNumber *)userID;


///
/// \details Sets gameUID, the unique integer identifying this user. Used in all reporting calls to services.
/// If nil is passed, GameUID will be set back to the current UID value.
///
/// @param
/// userID
+ (void)setUserID:(NSNumber *)userID;


///
/// \details This method tries to open the Big Fish Games App to allow the user to browse other Big Fish games.
/// If the app is not installed, it will prompt the user to install it. Your app will be backgrounded in order
/// to show the Big Fish Games App, if it is installed.
///
/// \updated 5.0
///
+ (void)showMoreGames;


///
/// \details Show the Support page with the in-game browser.
///
+ (void)showSupport;


///
/// \details Shows the Privacy page in Mobile Safari.
///
+ (void)showPrivacy;


///
/// \details Shows the Terms of Use page in Mobile Safari.
///
+ (void)showTerms;


///
/// \details Shows an in-game browser displaying startPage.
///
/// \return Web browser can be created.
///
+ (BOOL)showWebBrowser:(NSString *)startPage;


///
/// \details Removes the in-game browser shown via showWebBrowser:
///
+ (void)removeWebBrowser;


///
///
///
+ (UIInterfaceOrientation)currentOrientation;


///
/// \return
/// \retval YES if there is a connection to the Internet.
/// \retval NO if there is not a connection to the Internet, and displays alert.
///
+ (BOOL)checkForInternetConnection;


///
/// \param displayAlert If YES, displays a UIAlert that it cannot connect to the Internet.
/// \return
/// \retval YES if can connect to the Internet.
/// \retval NO if cannot connect to the Internet.
///
+ (BOOL)checkForInternetConnectionAndAlert:(BOOL)displayAlert;


///
/// \details The view controller to use when showing the GDN,
/// for both startup and resume UI. If you change your root ViewController
/// for your application, you should update bfgManager.
///
+ (void)setParentViewController:(UIViewController *)parent;
+ (UIViewController *)getParentViewController __deprecated;
+ (UIViewController *)parentViewController;


///
/// \details Starts branding animation running based on contents of bfgbranding_resources.zip.
///
+ (BOOL)startBranding;


///
/// \details Stops the branding animation. The BFGBRANDING_NOTIFICATION_COMPLETED notification will be sent.
///
+ (void)stopBranding;


///
/// \details Returns enum value for the current UI displayed by the SDK.
/// \return
/// \ref BFGDASH_UI_TYPE
///
///    \ref BFGDASH_UI_TYPE_NONE = 0
///
///    \ref BFGDASH_UI_TYPE_DASHFULL = 1
///
///    \ref BFGDASH_UI_TYPE_DASHWIN = 2
///
///    \ref BFGDASH_UI_TYPE_MOREGAMES = 3

+ (BFGDASH_UI_TYPE)currentUIType;


#define BFG_LAUNCH_ISPLASH                      @"bfg_launch_isplash"
#define BFG_LAUNCH_MORE_GAMES                   @"bfg_launch_more_games"
#define BFG_LAUNCH_LOGIN                        @"bfg_launch_login"
#define BFG_LAUNCH_WEBBROWSER                   @"bfg_launch_webbrowser"

///
///
/// \details Trims URL Scheme and launches by keyword.
+(BOOL)launchSDKByURLScheme:(NSString *)urlScheme;

///
/// \details Certain aspects of the SDK can be flagged for debugging either in
/// bfgSettings or with a bfgDebug.json file placed in the Documents folder. To
/// programmatically set flags, you can make changes directly to this dictionary.
///
/// \returns A mutable dictionary of debug settings.
///
/// \since 5.7
+ (NSMutableDictionary *)debugDictionary;

#pragma mark - UIApplicationDelegate Wrappers

///
/// \details Call this method from your app delegate at the beginning of
/// application:didReceiveLocalNotification:
///
/// \since 5.8
+ (void)applicationDidReceiveLocalNotification;

///
/// \brief Call this method from your app delegate at the beginning of
/// application:openURL:sourceApplication:annotation
///
/// \details The app delegate may be asked to open a resource via a URL.
/// Some URLs can be handled by the Big Fish SDK. This method exists to
/// support versions of iOS pre-iOS 9.
///
/// \param url From the delegate call.
/// \param sourceApplication From the delegate call.
/// \param annotation From the delegate call.
///
/// \retval YES The SDK acted upon the App Link.
/// \retval NO The SDK did not act upon the App Link.
///
/// \since 5.10
+ (BOOL)applicationOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

///
/// \brief Call this method from your app delegate at the beginning of
/// application:openURL:sourceApplication:annotation
///
/// \details The app delegate may be asked to open a resource via a URL.
/// Some URLs can be handled by the Big Fish SDK. This method supports
/// versions of iOS 9+.
///
/// \param url From the delegate call.
/// \param options From the delegate call.
///
/// \retval YES The SDK acted upon the App Link.
/// \retval NO The SDK did not act upon the App Link.
///
/// \since 5.10
+ (BOOL)applicationOpenURL:(NSURL *)url options:(NSDictionary<NSString *,id> *)options;

/// \brief Call this method from your app delegate at the beginning of
/// application:continueUserActivity:userActivity restorationHandler
///
/// \details Universal deeplinks trigger this delegate method instead of
/// openURL.
///
/// \param userActivity From the delegate call.
/// \param restorationHandler From the delegate call.
///
/// \retval YES The SDK acted upon the App Link.
/// \retval NO The SDK did not act upon the App Link.
///
/// \since 5.11
+ (BOOL)applicationContinueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray *restorableObjects))restorationHandler;


#pragma mark Remote notifications

///
/// \brief Call this method from your app delegate at the beginning of
/// application:didRegisterForRemoteNotificationsWithDeviceToken:
///
/// \details This method is critical for Big Fish to set up push notifications
/// for your app.
///
/// \param deviceToken From the delegate call.
///
/// \since 5.10
+ (void)applicationDidRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

/// \brief Call this method from your app delegate at the beginning of
/// application:didFailToRegisterForRemoteNotificationsWithError:
///
/// \param error From delegate call
///
/// \since 5.10
+ (void)applicationDidFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

/// \brief Call this method from your app delegate at the beginning of
/// application:didReceiveRemoteNotification:
///
/// \param userInfo From the delegate call.
///
/// \since 5.10
+ (void)applicationDidReceiveRemoteNotification:(NSDictionary *)userInfo;

/// \brief Call this method from your app delegate at the beginning of
/// application:didRegisterUserNotificationSettings:
///
/// \param notificationSettings From the delegate call
///
/// \since 5.10
+ (void)applicationDidRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings;

/// \details Call this method to add a delegate to listen for pause/resume events from the SDK
///
/// \param delegate The object which will act as a delegate for pause/resume events.  Needs to conform to the bfgManagerPauseResumeDelegate protocol
///
/// \since 6.0
+ (void)addPauseResumeDelegate:(id<bfgManagerPauseResumeDelegate>)delegate;

/// \details Call this method to remove a pause/resume event delegate
///
/// \param delegate The delegate you wish to remove.  Needs to conform to the bfgManagerPauseResumeDelegate protocol
///
/// \since 6.0
+ (void)removePauseResumeDelegate:(id<bfgManagerPauseResumeDelegate>)delegate;


/// \details Test to see if game should be paused
///
/// \retval YES The game should be paused.
/// \retval NO The game should not be paused.
///
/// \since 6.0
+ (BOOL)isPaused;

///
/// \details Call this method from your app delegate in
/// application:didFinishLaunchingWithOption: when the view controller for the SDK is available
///
/// \param launchOptions The launch options sent to the delegate call.
/// \param parentViewController The view controller the SDK should use
///
/// \since 6.0
+ (BOOL)startWithLaunchOptions:(NSDictionary *)launchOptions parentViewController:(UIViewController *)parentViewController;

///
/// \details Call this method from your app delegate in
/// application:didFinishLaunchingWithOption: when your SDK view controller IS NOT available
///
/// \param launchOptions The launch options sent to the delegate call.
///
/// \since 6.0
+ (BOOL)initWithLaunchOptions:(NSDictionary *)launchOptions;

///
/// \details Call this method when your view controller was not ready in
/// application:didFinishLaunchingWithOption: and it has finally been initialized
///
/// \param parentViewController The view controller the SDK should use
///
/// \since 6.0
+ (BOOL)startWithParentViewController:(UIViewController *)parentViewController;

@end

@protocol bfgManagerPauseResumeDelegate <NSObject>

@optional

/// \details Received by the delegate when the SDK is about to do something which requires a pause in the game
///
/// \since 6.0
- (void)bfgManagerShouldPauseGame;

/// \details Received by the delegate when it is okay to resume gameplay
///
/// \since 6.0
- (void)bfgManagerShouldResumeGame;

@end

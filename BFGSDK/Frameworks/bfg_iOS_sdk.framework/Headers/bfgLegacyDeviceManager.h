///
/// \file bfgLegacyDeviceManager.h
/// \brief Utility for determining whether current device meets recommended hardware specifications for the app.
/// \since 6.0
///
// \author Anton Rivera 8/11/16
// \copyright Copyright 2016 Big Fish Games, Inc. All rights reserved.
///

#import <Foundation/Foundation.h>

/// List of identifiers of iOS devices
typedef NS_OPTIONS(unsigned long long, BFGDeviceIdentifier)
{
    BFGDeviceIdentifier_iPhone4_31      = 1llu << 0,
    BFGDeviceIdentifier_iPhone4_32      = 1llu << 1,
    BFGDeviceIdentifier_iPhone4_33      = 1llu << 2,
    BFGDeviceIdentifier_iPhone4_All     = BFGDeviceIdentifier_iPhone4_31 | BFGDeviceIdentifier_iPhone4_32 | BFGDeviceIdentifier_iPhone4_33,
    BFGDeviceIdentifier_iPhone4S        = 1llu << 3,
    BFGDeviceIdentifier_iPhone5_51      = 1llu << 4,
    BFGDeviceIdentifier_iPhone5_52      = 1llu << 5,
    BFGDeviceIdentifier_iPhone5_All     = BFGDeviceIdentifier_iPhone5_51 | BFGDeviceIdentifier_iPhone5_52,
    BFGDeviceIdentifier_iPhone5C_53     = 1llu << 6,
    BFGDeviceIdentifier_iPhone5C_54     = 1llu << 7,
    BFGDeviceIdentifier_iPhone5C_All    = BFGDeviceIdentifier_iPhone5C_53 | BFGDeviceIdentifier_iPhone5C_54,
    BFGDeviceIdentifier_iPhone5S_61     = 1llu << 8,
    BFGDeviceIdentifier_iPhone5S_62     = 1llu << 9,
    BFGDeviceIdentifier_iPhone5S_All    = BFGDeviceIdentifier_iPhone5S_61 | BFGDeviceIdentifier_iPhone5S_62,
    BFGDeviceIdentifier_iPhone6Plus     = 1llu << 10,
    BFGDeviceIdentifier_iPhone6         = 1llu << 11,
    BFGDeviceIdentifier_iPhone6S        = 1llu << 12,
    BFGDeviceIdentifier_iPhone6SPlus    = 1llu << 13,
    BFGDeviceIdentifier_iPhoneSE        = 1llu << 14,
    BFGDeviceIdentifier_iPhone7         = 1llu << 15,
    BFGDeviceIdentifier_iPhone7Plus     = 1llu << 16,
    
    BFGDeviceIdentifier_iPad2_21        = 1llu << 17,
    BFGDeviceIdentifier_iPad2_22        = 1llu << 18,
    BFGDeviceIdentifier_iPad2_23        = 1llu << 19,
    BFGDeviceIdentifier_iPad2_24        = 1llu << 20,
    BFGDeviceIdentifier_iPad2_All       = BFGDeviceIdentifier_iPad2_21 | BFGDeviceIdentifier_iPad2_22 | BFGDeviceIdentifier_iPad2_23 | BFGDeviceIdentifier_iPad2_24,
    BFGDeviceIdentifier_iPad3_31        = 1llu << 21,
    BFGDeviceIdentifier_iPad3_32        = 1llu << 22,
    BFGDeviceIdentifier_iPad3_33        = 1llu << 23,
    BFGDeviceIdentifier_iPad3_All       = BFGDeviceIdentifier_iPad3_31 | BFGDeviceIdentifier_iPad3_32 | BFGDeviceIdentifier_iPad3_33,
    BFGDeviceIdentifier_iPad4_34        = 1llu << 24,
    BFGDeviceIdentifier_iPad4_35        = 1llu << 25,
    BFGDeviceIdentifier_iPad4_36        = 1llu << 26,
    BFGDeviceIdentifier_iPad4_All       = BFGDeviceIdentifier_iPad4_34 | BFGDeviceIdentifier_iPad4_35 | BFGDeviceIdentifier_iPad4_36,
    BFGDeviceIdentifier_iPadAir_41      = 1llu << 27,
    BFGDeviceIdentifier_iPadAir_42      = 1llu << 28,
    BFGDeviceIdentifier_iPadAir_43      = 1llu << 29,
    BFGDeviceIdentifier_iPadAir_All     = BFGDeviceIdentifier_iPadAir_41 | BFGDeviceIdentifier_iPadAir_42 | BFGDeviceIdentifier_iPadAir_43,
    BFGDeviceIdentifier_iPadAir2_53     = 1llu << 30,
    BFGDeviceIdentifier_iPadAir2_54     = 1llu << 31,
    BFGDeviceIdentifier_iPadAir2_All    = BFGDeviceIdentifier_iPadAir2_53 | BFGDeviceIdentifier_iPadAir2_54,
    BFGDeviceIdentifier_iPadPro12in_67  = 1llu << 32,
    BFGDeviceIdentifier_iPadPro12in_68  = 1llu << 33,
    BFGDeviceIdentifier_iPadPro12in_All = BFGDeviceIdentifier_iPadPro12in_67 | BFGDeviceIdentifier_iPadPro12in_68,
    BFGDeviceIdentifier_iPadPro9in_63   = 1llu << 34,
    BFGDeviceIdentifier_iPadPro9in_64   = 1llu << 35,
    BFGDeviceIdentifier_iPadPro9in_All  = BFGDeviceIdentifier_iPadPro9in_63 | BFGDeviceIdentifier_iPadPro9in_64,
    
    BFGDeviceIdentifier_iPadMini_25     = 1llu << 36,
    BFGDeviceIdentifier_iPadMini_26     = 1llu << 37,
    BFGDeviceIdentifier_iPadMini_27     = 1llu << 38,
    BFGDeviceIdentifier_iPadMini_All    = BFGDeviceIdentifier_iPadMini_25 | BFGDeviceIdentifier_iPadMini_26 | BFGDeviceIdentifier_iPadMini_27,
    BFGDeviceIdentifier_iPadMini2_44    = 1llu << 39,
    BFGDeviceIdentifier_iPadMini2_45    = 1llu << 40,
    BFGDeviceIdentifier_iPadMini2_46    = 1llu << 41,
    BFGDeviceIdentifier_iPadMini2_All   = BFGDeviceIdentifier_iPadMini2_44 | BFGDeviceIdentifier_iPadMini2_45 | BFGDeviceIdentifier_iPadMini2_46,
    BFGDeviceIdentifier_iPadMini3_47    = 1llu << 42,
    BFGDeviceIdentifier_iPadMini3_48    = 1llu << 43,
    BFGDeviceIdentifier_iPadMini3_49    = 1llu << 44,
    BFGDeviceIdentifier_iPadMini3_All   = BFGDeviceIdentifier_iPadMini3_47 | BFGDeviceIdentifier_iPadMini3_48 | BFGDeviceIdentifier_iPadMini3_49,
    BFGDeviceIdentifier_iPadMini4_51    = 1llu << 45,
    BFGDeviceIdentifier_iPadMini4_52    = 1llu << 46,
    BFGDeviceIdentifier_iPadMini4_All   = BFGDeviceIdentifier_iPadMini4_51 | BFGDeviceIdentifier_iPadMini4_52,
    
    BFGDeviceIdentifier_iPodTouch5G     = 1llu << 47,
    BFGDeviceIdentifier_iPodTouch6G     = 1llu << 48,
    
    BFGDeviceIdentifier_Unknown         = 0
};

/// List of identifiers of unsupported iOS devices (max iOS 6.0 and below)
/// This value is only for completeness.  It should not be used.
typedef NS_ENUM(unsigned long long, BFGDeviceIdentifier_pre_minimum_ios_supported)
{
    BFGDeviceIdentifier_pre_minimum_iPhone,
    BFGDeviceIdentifier_pre_minimum_iPhone3G,
    BFGDeviceIdentifier_pre_minimum_iPhone3GS,
    
    BFGDeviceIdentifier_pre_minimum_iPad,
    
    BFGDeviceIdentifier_pre_minimum_iPodTouch,
    BFGDeviceIdentifier_pre_minimum_iPodTouch2G,
    BFGDeviceIdentifier_pre_minimum_iPodTouch3G,
    BFGDeviceIdentifier_pre_minimum_iPodTouch4G
};

///
/// \brief Utility for determining whether current device meets recommended hardware specifications for the app.
/// \since 6.0
///
@interface bfgLegacyDeviceManager : NSObject

///
/// \brief Identify whether the current device matches the deviceIdentifier(s). Might be used to
/// tailor game experience or warn user that their experience might not be great on their current
/// hardware.
///
/// \param deviceIdentifier Device identifier(s) to be checked against
/// \return
/// \retval YES if deviceIdentifier matches current device.
/// \retval NO if deviceIdentifier does not match current device.
/// \since 6.0
///
+ (BOOL)checkForDeviceGeneration:(BFGDeviceIdentifier)deviceIdentifier;

///
/// \brief Identify whether the current device matches the deviceIdentifier(s). Might be used to
/// tailor game experience or warn user that their experience might not be great on their current
/// hardware.
///
/// \param deviceIdentifier Device identifier(s) to be checked against
/// \param andAlertWithTitle If device too old, show an alert with this title
/// \param message If device too old, show an alert with this message
/// \param dismissButtonTitle If device too old, show an alert with this dismiss button title
/// \return
/// \retval YES if deviceIdentifier matches current device.
/// \retval NO if deviceIdentifier does not match current device.
/// \since 6.0
///
+ (BOOL)checkForDeviceGeneration:(BFGDeviceIdentifier)deviceIdentifier andAlert:(BOOL)displayAlert withTitle:(NSString *)title message:(NSString *)message dismissButtonTitle:(NSString *)dismissButtonTitle;


///
/// \return The common name (such as iPhone4 or iPhone6Plus) of a device.
/// \since 6.0
///
+ (NSString *)commonDeviceNameForIdentifier:(BFGDeviceIdentifier)deviceIdentifer;

///
/// \return The models of the device currently running the app.
/// \since 6.0
///
+ (BFGDeviceIdentifier)currentDeviceIdentifier;

@end

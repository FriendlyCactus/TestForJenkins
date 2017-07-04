using UnityEngine;
using UnityEditor;
using UnityEditor.Callbacks;
using System.Collections;
using UnityEditor.iOS.Xcode;
using System.IO;

public class IntroduceXCodeSettings
{
	[PostProcessBuild]
	public static void OnPostprocessBuild(BuildTarget buildTarget, string pathToBuiltProject)
	{
		if (buildTarget == BuildTarget.iOS)
		{
			ChangeInfoPlist(buildTarget, pathToBuiltProject);
			AddFrameworks(buildTarget, pathToBuiltProject);
		}
	}

	private static void ChangeInfoPlist(BuildTarget buildTarget, string pathToBuiltProject)
	{
		// Get plist
		string plistPath = pathToBuiltProject + "/Info.plist";
		PlistDocument plist = new PlistDocument();
		plist.ReadFromString(File.ReadAllText(plistPath));

		// Get root
		PlistElementDict rootDict = plist.root;

		PlistElementArray arrayDeviceCapabilities = rootDict.CreateArray("UIRequiredDeviceCapabilities");
		arrayDeviceCapabilities.AddString("armv7");


		rootDict.SetString("CFBundleIdentifier", Application.bundleIdentifier);

		rootDict.SetString("NSCameraUsageDescription", "${PRODUCT_NAME} would like to access your camera.");
		rootDict.SetString("NSPhotoLibraryUsageDescription", "${PRODUCT_NAME} would like to access your photos.");
		rootDict.SetString("FacebookDisplayName", "Bake Shop Blast");
		//rootDict.SetString("FacebookAppID", BFGSettings.FacebookAppID);

		rootDict.SetString("CFBundleName", "Bake Shop Blast");

		rootDict.SetString("BFGEnviron", "Test");

		PlistElementArray urlArray = rootDict.CreateArray("CFBundleURLTypes");
		PlistElementDict itemDic = urlArray.AddDict();
		itemDic.SetString("CFBundleURLName", "$(PRODUCT_BUNDLE_IDENTIFIER)");

		PlistElementArray itemsArray = itemDic.CreateArray("CFBundleURLSchemes");
		//itemsArray.AddString("fb" + BFGSettings.FacebookAppID);
		itemsArray.AddString("$(PRODUCT_BUNDLE_IDENTIFIER)");
		//itemsArray.AddString("com.bigfishgames.bakeshopblastuniversalf2p://");

		//rootDict.SetString("UpsightAppToken", BFGSettings.UpsightAppToken);
		//rootDict.SetString("UpsightPublicKey", BFGSettings.UpsightPublicKey);

		PlistElementArray array = rootDict.CreateArray("LSApplicationQueriesSchemes");
		array.AddString("com.bigfishgames.gamefinder");
		array.AddString("fbauth2");
		array.AddString("fb-messenger-api");
		array.AddString("fbapi");
		array.AddString("fbshareextension");
		array.AddString("${PRODUCT_BUNDLE_IDENTIFIER}"+"://");

		//crashlitics
		//PlistElementDict fabric = rootDict.CreateDict("Fabric");
		//fabric.SetString("APIKey", BFGSettings.Fabric_APIKey);
		//PlistElementArray arrayKits = fabric.CreateArray("Kits");
		//PlistElementDict kitInfo = arrayKits.AddDict();
		//kitInfo = kitInfo.CreateDict("KitInfo");
		//kitInfo.SetString("KitName","Crashlytics");

		PlistElementDict transportSecurityDict = rootDict.CreateDict("NSAppTransportSecurity");

		transportSecurityDict.SetBoolean("NSAllowsArbitraryLoads", true);

		PlistElementDict exceptionDomainsDict = transportSecurityDict.CreateDict("NSExceptionDomains");

		PlistElementDict mediaDict = exceptionDomainsDict.CreateDict("media.playhaven.com");
		mediaDict.SetBoolean("NSThirdPartyExceptionAllowsInsecureHTTPLoads", true);

		PlistElementDict upsightDict = exceptionDomainsDict.CreateDict("upsight.com");
		upsightDict.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		upsightDict.SetBoolean("NSIncludesSubdomains", true);

		PlistElementDict upsightApiDict = exceptionDomainsDict.CreateDict("upsight-api.com");
		upsightApiDict.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		upsightApiDict.SetBoolean("NSIncludesSubdomains", true);

		PlistElementDict akamaihdDict = exceptionDomainsDict.CreateDict("akamaihd.net");
		akamaihdDict.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		akamaihdDict.SetBoolean("NSIncludesSubdomains", true);

		PlistElementDict mobileapptrackingDict = exceptionDomainsDict.CreateDict("mobileapptracking.com");
		mobileapptrackingDict.SetBoolean("NSThirdPartyExceptionRequiresForwardSecrecy", false);
		mobileapptrackingDict.SetBoolean("NSIncludesSubdomains", true);

		PlistElementDict kontagentDict = exceptionDomainsDict.CreateDict("kontagent.net");
		kontagentDict.SetBoolean("NSThirdPartyExceptionRequiresForwardSecrecy", false);
		kontagentDict.SetBoolean("NSIncludesSubdomains", true);

//		PlistElementDict facebookGraph = exceptionDomainsDict.CreateDict("graph.facebook.com");
//		facebookGraph.SetBoolean("NSThirdPartyExceptionRequiresForwardSecrecy", false);
//		facebookGraph.SetBoolean("NSIncludesSubdomains", true);

//		PlistElementDict amazon = exceptionDomainsDict.CreateDict("rave-prod-users.s3.amazonaws.com");
//		amazon.SetBoolean("NSThirdPartyExceptionRequiresForwardSecrecy", false);
//		amazon.SetBoolean("NSIncludesSubdomains", true);

		PlistElementDict kochavaDict = exceptionDomainsDict.CreateDict("kochava.com");
		kochavaDict.SetBoolean("NSThirdPartyExceptionRequiresForwardSecrecy", false);
		kochavaDict.SetBoolean("NSIncludesSubdomains", true);


		PlistElementDict kontagentComDict = exceptionDomainsDict.CreateDict("kontagent.com");
		kontagentComDict.SetBoolean("NSThirdPartyExceptionRequiresForwardSecrecy", false);
		kontagentComDict.SetBoolean("NSIncludesSubdomains", true);
		kontagentComDict.SetString("NSThirdPartyExceptionMinimumTLSVersion", "TLSv1.0");

		PlistElementDict bigfishgamesDict = exceptionDomainsDict.CreateDict("bigfishgames.com");
		bigfishgamesDict.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		bigfishgamesDict.SetBoolean("NSIncludesSubdomains", true);

		PlistElementDict apiKontagentDict = exceptionDomainsDict.CreateDict("api.geo.kontagent.net");
		apiKontagentDict.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		apiKontagentDict.SetBoolean("NSIncludesSubdomains", true);
		apiKontagentDict.SetBoolean("NSExceptionAllowsInsecureHTTPLoads", true);

		PlistElementDict testServerDict = exceptionDomainsDict.CreateDict("test-server.upsight.com");
		testServerDict.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		testServerDict.SetBoolean("NSIncludesSubdomains", true);
		testServerDict.SetBoolean("NSExceptionAllowsInsecureHTTPLoads", true);

		PlistElementDict testServerKontagentDict = exceptionDomainsDict.CreateDict("test-server.kontagent.com");
		testServerKontagentDict.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		testServerKontagentDict.SetBoolean("NSIncludesSubdomains", true);
		testServerKontagentDict.SetBoolean("NSExceptionAllowsInsecureHTTPLoads", true);

		PlistElementDict jquerryDict = exceptionDomainsDict.CreateDict("code.jquery.com");
		jquerryDict.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		jquerryDict.SetBoolean("NSIncludesSubdomains", true);
		jquerryDict.SetBoolean("NSExceptionAllowsInsecureHTTPLoads", true);

		PlistElementDict mobileApi = exceptionDomainsDict.CreateDict("mobile-api.geo.kontagent.net");
		mobileApi.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		mobileApi.SetBoolean("NSIncludesSubdomains", true);
		mobileApi.SetBoolean("NSExceptionAllowsInsecureHTTPLoads", true);


		PlistElementDict apiFB = exceptionDomainsDict.CreateDict("facebook.com");
		apiFB.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		apiFB.SetBoolean("NSIncludesSubdomains", true);
		apiFB.SetBoolean("NSExceptionAllowsInsecureHTTPLoads", true);

		PlistElementDict apiRaveIcon = exceptionDomainsDict.CreateDict("rave-prod-users.s3.amazonaws.com");
		apiRaveIcon.SetBoolean("NSExceptionRequiresForwardSecrecy", false);
		apiRaveIcon.SetBoolean("NSIncludesSubdomains", true);
		apiRaveIcon.SetBoolean("NSExceptionAllowsInsecureHTTPLoads", true);

		// Write to file
		File.WriteAllText(plistPath, plist.WriteToString());
	}

	private static void AddFrameworks(BuildTarget buildTarget, string pathToBuiltProject)
	{
		string projPath = pathToBuiltProject + "/Unity-iPhone.xcodeproj/project.pbxproj";

		PBXProject pbxProject = new PBXProject();
		pbxProject.ReadFromFile(projPath);

		string target = pbxProject.TargetGuidByName("Unity-iPhone");
		Debug.Log("IOS Target: " + target);


		pbxProject.AddFrameworkToProject(target, "Accounts.framework", true);
		pbxProject.AddFrameworkToProject(target, "AddressBook.framework", true);
		pbxProject.AddFrameworkToProject(target, "AdSupport.framework", true);
		pbxProject.AddFrameworkToProject(target, "CFNetwork.framework", true);
		pbxProject.AddFrameworkToProject(target, "CoreData.framework", true);
		pbxProject.AddFrameworkToProject(target, "CoreGraphics.framework", true);
		pbxProject.AddFrameworkToProject(target, "CoreLocation.framework", true);
		pbxProject.AddFrameworkToProject(target, "CoreSpotlight.framework", true);
		pbxProject.AddFrameworkToProject(target, "CoreTelephony.framework", true);
		pbxProject.AddFrameworkToProject(target, "CoreText.framework", true);
		pbxProject.AddFrameworkToProject(target, "Foundation.framework", true);
		pbxProject.AddFrameworkToProject(target, "GameKit.framework", true);
		pbxProject.AddFrameworkToProject(target, "MediaPlayer.framework", true);
		pbxProject.AddFrameworkToProject(target, "iAd.framework", true);
		pbxProject.AddFrameworkToProject(target, "MessageUI.framework", true);
		pbxProject.AddFrameworkToProject(target, "MobileCoreServices.framework", true);
		pbxProject.AddFrameworkToProject(target, "QuartzCore.framework", true);
		pbxProject.AddFrameworkToProject(target, "OpenGLES.framework", true);
		pbxProject.AddFrameworkToProject(target, "SafariServices.framework", true);
		pbxProject.AddFrameworkToProject(target, "Security.framework", true);
		pbxProject.AddFrameworkToProject(target, "Social.framework", true);
		pbxProject.AddFrameworkToProject(target, "StoreKit.framework", true);
		pbxProject.AddFrameworkToProject(target, "SystemConfiguration.framework", true);
		pbxProject.AddFrameworkToProject(target, "UIKit.framework", true);
		pbxProject.AddFrameworkToProject(target, "AssetsLibrary.framework", true);

		pbxProject.AddBuildProperty (target, "OTHER_LDFLAGS", "-ObjC");
		pbxProject.SetBuildProperty(target, "ENABLE_BITCODE", "NO");

		AddUsrLib(pbxProject, target, "libc.tbd");
		AddUsrLib(pbxProject, target, "libc++.tbd");
		AddUsrLib(pbxProject, target, "libicucore.tbd");
		AddUsrLib(pbxProject, target, "libsqlite3.tbd");
		AddUsrLib(pbxProject, target, "libxml2.tbd");
		AddUsrLib(pbxProject, target, "libz.tbd");

		pbxProject.WriteToFile (projPath);
		File.WriteAllText(projPath, pbxProject.WriteToString());
	}

	private static void AddUsrLib(PBXProject proj, string targetGuid, string framework)
	{
		string fileGuid = proj.AddFile("usr/lib/"+framework, "Frameworks/"+framework, PBXSourceTree.Sdk);
		proj.AddFileToBuild(targetGuid, fileGuid);
	}
}

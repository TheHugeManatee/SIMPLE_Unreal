// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SIMPLE.h"
#include "Core.h"
#include "IPluginManager.h"
#include "ModuleManager.h"

#define LOCTEXT_NAMESPACE "FSIMPLEModule"

DEFINE_LOG_CATEGORY(SIMPLE);

void FSIMPLEModule::StartupModule() {
  // Get the base directory of this plugin
  FString BaseDir = IPluginManager::Get().FindPlugin("SIMPLE")->GetBaseDir();

  // Add on the relative location of the third party dll and load it
  FString LibraryPath;
#if PLATFORM_WINDOWS
  LibraryPath = FPaths::Combine(*BaseDir, TEXT("ThirdParty/simple/bin/simple.dll"));
//#elif PLATFORM_MAC
// LibraryPath =
//    FPaths::Combine(*BaseDir, TEXT("ThirdParty/simple/Mac/bin/simple.dylib"));
#else
  static_assert(false, "Other platforms are currently not supported!");
#endif

  SIMPLELibraryHandle =
      !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

  if (SIMPLELibraryHandle) {
    UE_LOG(SIMPLE, Log, TEXT("Loaded SIMPLE Libraryh"))
  } else {
    UE_LOG(SIMPLE, Error,
           TEXT("Failed to load SIMPLE library! Check your include/lib paths and make sure "
                "simple.dll along with its dependencies is deployed!"))
  }
}

void FSIMPLEModule::ShutdownModule() {
  // Free the dll handle
  FPlatformProcess::FreeDllHandle(SIMPLELibraryHandle);
  SIMPLELibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSIMPLEModule, SIMPLE)

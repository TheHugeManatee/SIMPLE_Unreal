// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SIMPLE.h"
#include "Core.h"
#include "IPluginManager.h"
#include "ModuleManager.h"

THIRD_PARTY_INCLUDES_START
#include <simple/context_manager.hpp>
THIRD_PARTY_INCLUDES_END

#define LOCTEXT_NAMESPACE "FSIMPLEModule"

DEFINE_LOG_CATEGORY(SIMPLE);

void FSIMPLEModule::StartupModule() {
  // Get the base directory of this plugin
  FString BaseDir = IPluginManager::Get().FindPlugin("SIMPLE")->GetBaseDir();

  // Add on the relative location of the third party dll and load it
  FString LibraryPath;
#if PLATFORM_WINDOWS
  LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/Win64/simple.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/Mac/libsimple.dylib"));
#else
  static_assert(false, "Other platforms are currently not supported!");
#endif

  SIMPLELibraryHandle =
      !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

  if (SIMPLELibraryHandle) {
    UE_LOG(SIMPLE, Log, TEXT("Loaded SIMPLE Libraryh"))
  } else {

      FString text = "Couldn't find dll @ " + LibraryPath;
    UE_LOG(SIMPLE, Error, TEXT("%s"), *text)
  }
}

void FSIMPLEModule::ShutdownModule() {
  simple::ContextManager::destroy();
  // Free the dll handle
  FPlatformProcess::FreeDllHandle(SIMPLELibraryHandle);
  SIMPLELibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSIMPLEModule, SIMPLE)

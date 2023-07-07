// Extract.h

#ifndef ZIP7_INC_EXTRACT_H
#define ZIP7_INC_EXTRACT_H

#include "../../../Windows/FileFind.h"

#include "../../Archive/IArchive.h"

#include "ArchiveExtractCallback.h"
#include "ArchiveOpenCallback.h"
#include "ExtractMode.h"
#include "Property.h"

#include "../Common/LoadCodecs.h"

struct CExtractOptionsBase
{
  CBoolPair ElimDup;

  bool ExcludeDirItems;
  bool ExcludeFileItems;

  bool PathMode_Force;
  bool OverwriteMode_Force;
  NExtract::NPathMode::EEnum PathMode;
  NExtract::NOverwriteMode::EEnum OverwriteMode;
  NExtract::NZoneIdMode::EEnum ZoneMode;
  
  FString OutputDir;
  CExtractNtOptions NtOptions;
  UString HashDir;

  CExtractOptionsBase():
      ExcludeDirItems(false),
      ExcludeFileItems(false),
      PathMode_Force(false),
      OverwriteMode_Force(false),
      PathMode(NExtract::NPathMode::kFullPaths),
      OverwriteMode(NExtract::NOverwriteMode::kAsk),
      ZoneMode(NExtract::NZoneIdMode::kNone)
      {}
};

struct CExtractOptions: public CExtractOptionsBase
{
  bool StdInMode;
  bool StdOutMode;
  bool YesToAll;
  bool TestMode;
  
  // bool ShowDialog;
  // bool PasswordEnabled;
  // UString Password;
  #ifndef Z7_SFX
  CObjectVector<CProperty> Properties;
  #endif

  /*
  #ifdef Z7_EXTERNAL_CODECS
  CCodecs *Codecs;
  #endif
  */

  CExtractOptions():
      StdInMode(false),
      StdOutMode(false),
      YesToAll(false),
      TestMode(false)
      {}
};

struct CDecompressStat
{
  UInt64 NumArchives;
  UInt64 UnpackSize;
  UInt64 AltStreams_UnpackSize;
  UInt64 PackSize;
  UInt64 NumFolders;
  UInt64 NumFiles;
  UInt64 NumAltStreams;

  void Clear()
  {
    NumArchives = UnpackSize = AltStreams_UnpackSize = PackSize = NumFolders = NumFiles = NumAltStreams = 0;
  }
};

HRESULT Extract(
    // DECL_EXTERNAL_CODECS_LOC_VARS
    CCodecs *codecs,
    const CObjectVector<COpenType> &types,
    const CIntVector &excludedFormats,
    UStringVector &archivePaths, UStringVector &archivePathsFull,
    const NWildcard::CCensorNode &wildcardCensor,
    const CExtractOptions &options,
    IOpenCallbackUI *openCallback,
    IExtractCallbackUI *extractCallback,
    IFolderArchiveExtractCallback *faeCallback,
    #ifndef Z7_SFX
    IHashCalc *hash,
    #endif
    UString &errorMessage,
    CDecompressStat &st);

void SetErrorMessage(const char *message,
                            const FString &path, HRESULT errorCode,
                            UString &s);
int Find_FileName_InSortedVector(const UStringVector &fileNames, const UString &name);
HRESULT DecompressArchive(
        CCodecs *codecs,
        const CArchiveLink &arcLink,
        UInt64 packSize,
        const NWildcard::CCensorNode &wildcardCensor,
        const CExtractOptions &options,
        bool calcCrc,
        IExtractCallbackUI *callback,
        IFolderArchiveExtractCallback *callbackFAE,
        CArchiveExtractCallback *ecs,
        UString &errorMessage,
        UInt64 &stdInProcessed);


#endif

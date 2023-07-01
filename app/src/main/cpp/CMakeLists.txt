cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("sz23binding")
set(TARGET sz23binding)

set(ROOT src/main/cpp)
set(SEVEN_ZIP_SRC ${ROOT}/7z2301-src)

set(7Z_DIR ${CMAKE_SOURCE_DIR}/7z2301-src)

set(MT_SRC
        ${7Z_DIR}/C/LzFind.c
        ${7Z_DIR}/C/LzFindOpt.c
        ${7Z_DIR}/C/Threads.c
        ${7Z_DIR}/CPP/7zip/Common/StreamBinder.cpp
        ${7Z_DIR}/CPP/Windows/Synchronization.cpp
        ${7Z_DIR}/CPP/7zip/Common/VirtThread.cpp
        ${7Z_DIR}/CPP/7zip/Common/MemBlocks.cpp
        ${7Z_DIR}/CPP/7zip/Common/OutMemStream.cpp
        ${7Z_DIR}/CPP/7zip/Common/ProgressMt.cpp
        )

set(COMMON_SRC
        ${7Z_DIR}/CPP/Common/CRC.cpp
        ${7Z_DIR}/CPP/Common/CrcReg.cpp
        ${7Z_DIR}/CPP/Common/DynLimBuf.cpp
        ${7Z_DIR}/CPP/Common/IntToString.cpp
        ${7Z_DIR}/CPP/Common/LzFindPrepare.cpp
        ${7Z_DIR}/CPP/Common/MyMap.cpp
        ${7Z_DIR}/CPP/Common/MyString.cpp
        ${7Z_DIR}/CPP/Common/MyVector.cpp
        ${7Z_DIR}/CPP/Common/MyXml.cpp
        ${7Z_DIR}/CPP/Common/NewHandler.cpp
        ${7Z_DIR}/CPP/Common/Sha1Prepare.cpp
        ${7Z_DIR}/CPP/Common/Sha1Reg.cpp
        ${7Z_DIR}/CPP/Common/Sha256Prepare.cpp
        ${7Z_DIR}/CPP/Common/Sha256Reg.cpp
        ${7Z_DIR}/CPP/Common/StringConvert.cpp
        ${7Z_DIR}/CPP/Common/StringToInt.cpp
        ${7Z_DIR}/CPP/Common/UTFConvert.cpp
        ${7Z_DIR}/CPP/Common/Wildcard.cpp
        ${7Z_DIR}/CPP/Common/XzCrc64Init.cpp
        ${7Z_DIR}/CPP/Common/XzCrc64Reg.cpp
        )

set(WIN_SRC
        ${7Z_DIR}/CPP/Windows/FileDir.cpp
        ${7Z_DIR}/CPP/Windows/FileFind.cpp
        ${7Z_DIR}/CPP/Windows/FileIO.cpp
        ${7Z_DIR}/CPP/Windows/FileName.cpp
        ${7Z_DIR}/CPP/Windows/PropVariant.cpp
        ${7Z_DIR}/CPP/Windows/PropVariantUtils.cpp
        ${7Z_DIR}/CPP/Windows/System.cpp
        ${7Z_DIR}/CPP/Windows/TimeUtils.cpp
        )

set(7ZIP_COMMON_SRC
        ${7Z_DIR}/CPP/7zip/Common/CreateCoder.cpp
        ${7Z_DIR}/CPP/7zip/Common/CWrappers.cpp
        ${7Z_DIR}/CPP/7zip/Common/InBuffer.cpp
        ${7Z_DIR}/CPP/7zip/Common/InOutTempBuffer.cpp
        ${7Z_DIR}/CPP/7zip/Common/FilterCoder.cpp
        ${7Z_DIR}/CPP/7zip/Common/LimitedStreams.cpp
        ${7Z_DIR}/CPP/7zip/Common/LockedStream.cpp
        ${7Z_DIR}/CPP/7zip/Common/MethodId.cpp
        ${7Z_DIR}/CPP/7zip/Common/MethodProps.cpp
        ${7Z_DIR}/CPP/7zip/Common/OffsetStream.cpp
        ${7Z_DIR}/CPP/7zip/Common/OutBuffer.cpp
        ${7Z_DIR}/CPP/7zip/Common/ProgressUtils.cpp
        ${7Z_DIR}/CPP/7zip/Common/PropId.cpp
        ${7Z_DIR}/CPP/7zip/Common/StreamObjects.cpp
        ${7Z_DIR}/CPP/7zip/Common/StreamUtils.cpp
        ${7Z_DIR}/CPP/7zip/Common/UniqBlocks.cpp
        )

set(AR_SRC
        ${7Z_DIR}/CPP/7zip/Archive/ApfsHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/ApmHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/ArHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/ArjHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Base64Handler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Bz2Handler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/ComHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/CpioHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/CramfsHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/DeflateProps.cpp
        ${7Z_DIR}/CPP/7zip/Archive/DmgHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/ElfHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/ExtHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/FatHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/FlvHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/GzHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/GptHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/HandlerCont.cpp
        ${7Z_DIR}/CPP/7zip/Archive/HfsHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/IhexHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/LpHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/LzhHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/LzmaHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/MachoHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/MbrHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/MslzHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/MubHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/NtfsHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/PeHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/PpmdHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/QcowHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/RpmHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/SparseHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/SplitHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/SquashfsHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/SwfHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/UefiHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/VdiHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/VhdHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/VhdxHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/VmdkHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/XarHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/XzHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/ZHandler.cpp
        )

set(AR_COMMON_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Common/CoderMixer2.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Common/DummyOutStream.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Common/FindSignature.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Common/InStreamWithCRC.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Common/ItemNameUtils.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Common/MultiStream.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Common/OutStreamWithCRC.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Common/OutStreamWithSha1.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Common/HandlerOut.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Common/ParseProperties.cpp
        )

set(7Z_SRC
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zCompressionMode.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zDecode.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zEncode.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zExtract.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zFolderInStream.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zHandlerOut.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zHeader.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zIn.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zOut.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zProperties.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zSpecStream.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zUpdate.cpp
        ${7Z_DIR}/CPP/7zip/Archive/7z/7zRegister.cpp
        )

set(CAB_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Cab/CabBlockInStream.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Cab/CabHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Cab/CabHeader.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Cab/CabIn.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Cab/CabRegister.cpp
        )

set(CHM_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Chm/ChmHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Chm/ChmIn.cpp
        )

set(ISO_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Iso/IsoHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Iso/IsoHeader.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Iso/IsoIn.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Iso/IsoRegister.cpp
        )

set(NSIS_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Nsis/NsisDecode.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Nsis/NsisHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Nsis/NsisIn.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Nsis/NsisRegister.cpp
        )

set(RAR_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Rar/RarHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Rar/Rar5Handler.cpp
        )

set(TAR_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Tar/TarHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Tar/TarHandlerOut.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Tar/TarHeader.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Tar/TarIn.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Tar/TarOut.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Tar/TarUpdate.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Tar/TarRegister.cpp
        )

set(UDF_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Udf/UdfHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Udf/UdfIn.cpp
        )

set(WIM_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Wim/WimHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Wim/WimHandlerOut.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Wim/WimIn.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Wim/WimRegister.cpp
        )

set(ZIP_SRC
        ${7Z_DIR}/CPP/7zip/Archive/Zip/ZipAddCommon.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Zip/ZipHandler.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Zip/ZipHandlerOut.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Zip/ZipIn.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Zip/ZipItem.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Zip/ZipOut.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Zip/ZipUpdate.cpp
        ${7Z_DIR}/CPP/7zip/Archive/Zip/ZipRegister.cpp
        )

set(COMPRESS_SRC
        ${7Z_DIR}/CPP/7zip/Compress/Bcj2Coder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Bcj2Register.cpp
        ${7Z_DIR}/CPP/7zip/Compress/BcjCoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/BcjRegister.cpp
        ${7Z_DIR}/CPP/7zip/Compress/BitlDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/BranchMisc.cpp
        ${7Z_DIR}/CPP/7zip/Compress/BranchRegister.cpp
        ${7Z_DIR}/CPP/7zip/Compress/ByteSwap.cpp
        ${7Z_DIR}/CPP/7zip/Compress/BZip2Crc.cpp
        ${7Z_DIR}/CPP/7zip/Compress/BZip2Decoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/BZip2Encoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/BZip2Register.cpp
        ${7Z_DIR}/CPP/7zip/Compress/CopyCoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/CopyRegister.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Deflate64Register.cpp
        ${7Z_DIR}/CPP/7zip/Compress/DeflateDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/DeflateEncoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/DeflateRegister.cpp
        ${7Z_DIR}/CPP/7zip/Compress/DeltaFilter.cpp
        ${7Z_DIR}/CPP/7zip/Compress/ImplodeDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/LzfseDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/LzhDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Lzma2Decoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Lzma2Encoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Lzma2Register.cpp
        ${7Z_DIR}/CPP/7zip/Compress/LzmaDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/LzmaEncoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/LzmaRegister.cpp
        ${7Z_DIR}/CPP/7zip/Compress/LzmsDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/LzOutWindow.cpp
        ${7Z_DIR}/CPP/7zip/Compress/LzxDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/PpmdDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/PpmdEncoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/PpmdRegister.cpp
        ${7Z_DIR}/CPP/7zip/Compress/PpmdZip.cpp
        ${7Z_DIR}/CPP/7zip/Compress/QuantumDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/ShrinkDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/XpressDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/XzDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/XzEncoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/ZlibDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/ZlibEncoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/ZDecoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Rar1Decoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Rar2Decoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Rar3Decoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Rar3Vm.cpp
        ${7Z_DIR}/CPP/7zip/Compress/Rar5Decoder.cpp
        ${7Z_DIR}/CPP/7zip/Compress/RarCodecsRegister.cpp
        )

set(CRYPTO
        ${7Z_DIR}/CPP/7zip/Crypto/7zAes.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/7zAesRegister.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/HmacSha1.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/HmacSha256.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/MyAes.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/MyAesReg.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/Pbkdf2HmacSha1.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/RandGen.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/WzAes.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/ZipCrypto.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/ZipStrong.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/Rar20Crypto.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/Rar5Aes.cpp
        ${7Z_DIR}/CPP/7zip/Crypto/RarAes.cpp
        )

set(C_SRC
        ${7Z_DIR}/C/7zBuf2.c
        ${7Z_DIR}/C/7zStream.c
        ${7Z_DIR}/C/Alloc.c
        ${7Z_DIR}/C/Bcj2.c
        ${7Z_DIR}/C/Bcj2Enc.c
        ${7Z_DIR}/C/Blake2s.c
        ${7Z_DIR}/C/Bra.c
        ${7Z_DIR}/C/Bra86.c
        ${7Z_DIR}/C/BraIA64.c
        ${7Z_DIR}/C/BwtSort.c
        ${7Z_DIR}/C/CpuArch.c
        ${7Z_DIR}/C/Delta.c
        ${7Z_DIR}/C/HuffEnc.c
        ${7Z_DIR}/C/LzFind.c
        ${7Z_DIR}/C/Lzma2Dec.c
        ${7Z_DIR}/C/Lzma2DecMt.c
        ${7Z_DIR}/C/Lzma2Enc.c
        ${7Z_DIR}/C/LzmaDec.c
        ${7Z_DIR}/C/LzmaEnc.c
        ${7Z_DIR}/C/MtCoder.c
        ${7Z_DIR}/C/MtDec.c
        ${7Z_DIR}/C/Ppmd7.c
        ${7Z_DIR}/C/Ppmd7Dec.c
        ${7Z_DIR}/C/Ppmd7aDec.c
        ${7Z_DIR}/C/Ppmd7Enc.c
        ${7Z_DIR}/C/Ppmd8.c
        ${7Z_DIR}/C/Ppmd8Dec.c
        ${7Z_DIR}/C/Ppmd8Enc.c
        ${7Z_DIR}/C/Sort.c
        ${7Z_DIR}/C/Xz.c
        ${7Z_DIR}/C/XzDec.c
        ${7Z_DIR}/C/XzEnc.c
        ${7Z_DIR}/C/XzIn.c
        ${7Z_DIR}/C/XzCrc64.c
        ${7Z_DIR}/C/XzCrc64Opt.c
        ${7Z_DIR}/C/7zCrc.c
        ${7Z_DIR}/C/7zCrcOpt.c
        ${7Z_DIR}/C/Aes.c
        #${7Z_DIR}/C/AesOpt.c
        ${7Z_DIR}/C/Sha256.c
        ${7Z_DIR}/C/Sha256Opt.c
        ${7Z_DIR}/C/Sha1.c
        ${7Z_DIR}/C/Sha1Opt.c
        ${7Z_DIR}/C/SwapBytes.c
        )

set(UI_COMMON_SRC
        ${7Z_DIR}/CPP/7zip/UI/Common/ArchiveCommandLine.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/ArchiveExtractCallback.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/ArchiveOpenCallback.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/Bench.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/DefaultName.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/EnumDirItems.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/Extract.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/ExtractingFilePath.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/HashCalc.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/LoadCodecs.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/OpenArchive.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/PropIDUtils.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/SetProperties.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/SortUtils.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/TempFiles.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/Update.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/UpdateAction.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/UpdateCallback.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/UpdatePair.cpp
        ${7Z_DIR}/CPP/7zip/UI/Common/UpdateProduce.cpp
        )

set(CONSOLE_SRC
        ${7Z_DIR}/CPP/7zip/UI/Console/BenchCon.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/ConsoleClose.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/ExtractCallbackConsole.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/HashCon.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/List.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/Main.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/MainAr.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/OpenCallbackConsole.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/PercentPrinter.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/UpdateCallbackConsole.cpp
        ${7Z_DIR}/CPP/7zip/UI/Console/UserInputUtils.cpp
        )

set(COMMON_SRC_2
        ${7Z_DIR}/CPP/Common/CommandLineParser.cpp
        ${7Z_DIR}/CPP/Common/ListFileUtils.cpp
        ${7Z_DIR}/CPP/Common/StdInStream.cpp
        ${7Z_DIR}/CPP/Common/StdOutStream.cpp
        )

set(WIN_SRC_2
        ${7Z_DIR}/CPP/Windows/ErrorMsg.cpp
        ${7Z_DIR}/CPP/Windows/FileLink.cpp
        ${7Z_DIR}/CPP/Windows/SystemInfo.cpp
        ${7Z_DIR}/CPP/Windows/PropVariantConv.cpp
        ${7Z_DIR}/CPP/Common/MyWindows.cpp
        )

set(7Z_COMMON_SRC_2
        ${7Z_DIR}/CPP/7zip/Common/FilePathAutoRename.cpp
        ${7Z_DIR}/CPP/7zip/Common/FileStreams.cpp
        ${7Z_DIR}/CPP/7zip/Common/MultiOutStream.cpp
        )

set(COD_OPT
        ${7Z_DIR}/C/7zCrcOpt.c
        ${7Z_DIR}/C/XzCrc64Opt.c
        ${7Z_DIR}/C/Sha1Opt.c
        ${7Z_DIR}/C/Sha256Opt.c
        #${7Z_DIR}/C/AesOpt.c
        ${7Z_DIR}/C/LzFindOpt.c
        ${7Z_DIR}/C/LzmaDec.c
        )

set(ASM_SRC
        ${7Z_DIR}/Asm/arm64/LzmaDecOpt.S
        ${7Z_DIR}/Asm/arm64/7zAsm.S
        )



include_directories(C)
include_directories(${7Z_DIR}/C/Util/7z)
include_directories(${7Z_DIR}/C/Util/7zipInstall)
include_directories(${7Z_DIR}/C/Util/7zipUninstall)
include_directories(${7Z_DIR}/C/Util/Lzma)
include_directories(${7Z_DIR}/C/Util/LzmaLib)
include_directories(${7Z_DIR}/C/Util/SfxSetup)
include_directories(${7Z_DIR}/CPP/7zip)
include_directories(${7Z_DIR}/CPP/7zip/Archive)
include_directories(${7Z_DIR}/CPP/7zip/Archive/7z)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Cab)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Chm)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Common)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Iso)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Nsis)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Rar)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Tar)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Udf)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Wim)
include_directories(${7Z_DIR}/CPP/7zip/Archive/Zip)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/Alone)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/Alone2)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/Alone7z)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/Fm)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/Format7z)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/Format7zExtract)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/Format7zExtractR)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/Format7zF)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/Format7zR)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/LzmaCon)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/SFXCon)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/SFXSetup)
include_directories(${7Z_DIR}/CPP/7zip/Bundles/SFXWin)
include_directories(${7Z_DIR}/CPP/7zip/Common)
include_directories(${7Z_DIR}/CPP/7zip/Compress)
include_directories(${7Z_DIR}/CPP/7zip/Crypto)
include_directories(${7Z_DIR}/CPP/7zip/UI/Agent)
include_directories(${7Z_DIR}/CPP/7zip/UI/Client7z)
include_directories(${7Z_DIR}/CPP/7zip/UI/Common)
include_directories(${7Z_DIR}/CPP/7zip/UI/Console)
include_directories(${7Z_DIR}/CPP/7zip/UI/Explorer)
include_directories(${7Z_DIR}/CPP/7zip/UI/Far)
include_directories(${7Z_DIR}/CPP/7zip/UI/FileManager)
include_directories(${7Z_DIR}/CPP/7zip/UI/GUI)
include_directories(${7Z_DIR}/CPP/Common)
include_directories(${7Z_DIR}/CPP/Windows)
include_directories(${7Z_DIR}/CPP/Windows/Control)



add_definitions(
        -fmessage-length=0
        -DZ7_ST
        #-D__ARM_ARCH=8
        #-D__ARM_FEATURE_AES
        -O2
        -c
        -Werror
        -v
        -Wall
        -Wextra
        -Weverything
        -Wno-c++98-compat-pedantic
        -Wno-reserved-id-macro
        -Wno-sign-conversion
        -Wno-unused-macros
        -Wno-unused-variable
        -Wno-reserved-identifier
        -Wno-unknown-warning-option
        -Wno-old-style-cast
        -Wno-unused-parameter
        -Wno-implicit-function-declaration
        -Wfatal-errors
        -Wno-poison-system-directories
        -Wno-language-extension-token
        -Wno-vector-conversion
        -DNDEBUG -D_REENTRANT
        -D_FILE_OFFSET_BITS=64
        -D_LARGEFILE_SOURCE
        -Wno-strict-prototypes
        -Wno-unused-but-set-variable
        -Wno-zero-as-null-pointer-constant
        -Wno-conversion
        -fPIC
)

#add_definitions(
#        -DBREAK_HANDLER
#        -DENV_HAVE_GCCVISIBILITYPATCH
#        -DENV_UNIX
#        -DUNICODE
#        -DUNIX_USE_WIN_FILE
#        -D_7_Zip_JBinding_EXPORTS
#        -D_FILE_OFFSET_BITS=64
#        -D_LARGEFILE_SOURCE
#        -D_REENTRANT
#        -D_UNICODE
#        # -D_7ZIP_ST    #加这个避免线程错误,但开启会有编译错误
#        #-DDEBUG_MODE
#)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0 -Wno-narrowing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0 -Wno-narrowing")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        sz23binding

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
#        native-lib.cpp
        ${COMMON_SRC}
        ${WIN_SRC}
        ${7ZIP_COMMON_SRC}
        ${AR_SRC}
        ${AR_COMMON_SRC}
        ${7Z_SRC}
        ${CAB_SRC}
        ${CHM_SRC}
        ${ISO_SRC}
        ${NSIS_SRC}
        ${RAR_SRC}
        ${TAR_SRC}
        ${UDF_SRC}
        ${WIM_SRC}
        ${ZIP_SRC}
        ${COMPRESS_SRC}
        ${CRYPTO}
        ${C_SRC}
        ${UI_COMMON_SRC}
        ${CONSOLE_SRC}
        ${COMMON_SRC_2}
        ${WIN_SRC_2}
        ${7Z_COMMON_SRC_2}
        ${COD_OPT}
        ${ASM_SRC}
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

set_target_properties(sz23binding
        PROPERTIES
        LINK_FLAGS
        #"-Wl,-z,defs -Wl,--no-undefined -DNDEBUG -lpthread -ldl"
        "-DNDEBUG -ldl"
        )

#set_target_properties(sz23binding PROPERTIES COMPILE_FLAGS -mfpu=neon)
find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        sz23binding

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}

        )
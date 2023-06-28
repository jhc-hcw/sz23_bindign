PLATFORM=arm64
O=b/c_$(PLATFORM)
IS_X64=
IS_X86=
IS_ARM64=1
CROSS_COMPILE=
MY_ARCH=
USE_ASM=1
CC=$(CROSS_COMPILE)clang
CXX=$(CROSS_COMPILE)clang++
USE_CLANG=1

ifdef IS_64
$(info "呵呵呵呵呵呵呵呵呵呵呵 呵呵呵呵呵空定义也算定义")
endif 


ifdef IS_ARM64
$(info "呵呵呵呵呵呵呵呵呵呵呵 呵呵呵呵呵定义为1才算定义")
endif 


##############################################################################
#####                 This makefile generates ELWBR.DLL                  #####
##############################################################################
!include $(WGDEV)\src\gcrules.mak

!if $(OS) == DOS
!    if $(MODEL) == LARGE
!         error GALFIL not supported in Large Model under DOS!
!    endif
     DLLLIB = $(DLLLIB) $(COMPILER)\lib\mathh.lib
     PRODLL = $(PRODLL) $(DOSEXT)\bc5\lib\fpdmy
!else
     PARSEOPTS = $(PARSEOPTS) -I. -DIS30
!endif

DEFILE =

VIRFILES =

DLLLIB =            \
     $(DLLLIB)      \
     wgserver.lib   \
     galme.lib      \
     galgsbl.lib

OBJFILES =          \
     elwbr.obj

start:              \
     $(GCBUILD)     \
     elwbr.dll

elwbr.dll:          \
     $(GCBUILD)     \
     elwbrinc.h     \
     elwbr.h        \
     $(OBJFILES)    \
     $(DLLLIB)      \
     $(DEFILE)      \
     $(VIRFILES)
     $(LINK) $(LIBCMD) @&&|
$(PRODLL) $(OBJFILES)
$(RUNDIR)\$&
$(RUNDIR)\$&
$(DLLLIB) $(LINKDLL)
$(DEFILE)
|

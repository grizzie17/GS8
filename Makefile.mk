#
# Sample workspace (top-level) makefile
#
# Usage:
#
#	make -f thismakefile.mk
#		Make sure that all projects and all special targets are up to date
#
#	make -f thismakefile.mk clean
#		Clean all projects and temporary build files
#
#	make -f thismakefile.mk rebuild
#		clean then rebuild all
#
#	make -f thismakefile.mk PROJECT=someprojectname
#	make -f thismakefile.mk PROJECT=someprojectname clean
#	make -f thismakefile.mk PROJECT=someprojectname rebuild
#		perform operation (target) on project and its dependencies
#
#	make -f thismakefile.mk SINGLEPROJECT=someprojectname
#	make -f thismakefile.mk SINGLEPROJECT=someprojectname clean
#	make -f thismakefile.mk SINGLEPROJECT=someprojectname rebuild
#		perform operation (target) on a single project only
#
#	make -f thismakefile.mk SINGLEPROJECT=someprojectname SINGLEFILE=somesourcefile
#	make -f thismakefile.mk SINGLEPROJECT=someprojectname SINGLEFILE=somesourcefile clean
#	make -f thismakefile.mk SINGLEPROJECT=someprojectname SINGLEFILE=somesourcefile rebuild
#		perform operation (target) on a single file only (note: this compiles only, no link)
#
#		you can also specify the configuration by including 'CONFIGURATION=somename' on the command line
#


# false is absence of value
export Option-ShowDependency :=
export Option-ShowPreprocess := true
export Option-ShowCommands :=


# import "active" ConfigurationName
ConfigurationName      :=$(or $(CONFIGURATION),Debug)
WorkspaceName          :=Workbench
WorkspacePath          := .
WorkingDirectory       := $(WorkspacePath)/.build



# ProjectsList - a simple database for what to build
#				each record is delimited by spaces
#				each field is delimited by semicolons
#				each sub-field is delimted by commas
#
#	makefilepath;predecessors;configuration

ProjectsList.Debug := \
	CmdPlugins/CmdCameraSelector/CmdCameraSelector.mk;Common,LogFile,VSAShared,Gadget	\
	CmdPlugins/CmdConstant/CmdConstant.mk;Common,LogFile,VSAShared	\
	CmdPlugins/CmdConstantD/CmdConstantD.mk;Common,LogFile,VSAShared	\
	CmdPlugins/CmdCopyToD/CmdCopyToD.mk;Common,LogFile,VSAShared	\
	CmdPlugins/CmdEptm/CmdEptm.mk;Common,LogFile,VSAShared	\
	CmdPlugins/CmdKeyName/CmdKeyName.mk;Common,LogFile,VSAShared,Gadget	\
	CmdPlugins/CmdOmniScapeESS/CmdOmniScapeESS.mk;Common,LogFile,VSAShared	\
	CmdPlugins/CmdReturnTrue/CmdReturnTrue.mk;Common,LogFile,VSAShared	\
	CmdPlugins/CmdServiceClog/CmdServiceClog.mk;Common,LogFile,VSAShared	\
	CmdPlugins/CmdSystemShutdown/CmdSystemShutdown.mk;Common,VSAShared,LogFile,Gadget	\
	CmdPlugins/CmdTouchCalibrate/CmdTouchCalibrate.mk;Common,LogFile,VSAShared	\
	CmdPlugins/CmdVehicleDataLoader/CmdVehicleDataLoader.mk;Common,LogFile,VSAShared,Gadget	\
	CmdPlugins/CmdVehicleDataSample/CmdVehicleDataSample.mk;Common,LogFile,VSAShared	\
	Common/Common.mk	\
	Common/Common_specs/Common_specs.mk;Common,LogFile	\
	Draw/CDrawOpenGL/CDrawOpenGL.mk;Common,LogFile,VSAShared,VDraw,SOIL	\
	Draw/CDrawTmxWin/CDrawTmxWin.mk;Common,LogFile,VDraw	\
	Draw/CDrawWorkbench/CDrawWorkbench.mk;Common,LogFile,VDraw	\
	Draw/VDraw/VDraw.mk	\
	ExternalXML/ExternalXML.mk	\
	ExternalXML/XMLEverythingAlert/XMLEverythingAlert.mk;Common,LogFile,VSAShared,Gadget,ExternalXML	\
	ExternalXML/XMLEverythingColor/XMLEverythingColor.mk;Common,LogFile,VSAShared,Gadget,ExternalXML	\
	ExternalXML/XMLEverythingGauge/XMLEverythingGauge.mk;Common,LogFile,VSAShared,Gadget,ExternalXML	\
	Gadget/Gadget.mk	\
	Gadget/Gadget_specs/Gadget_specs.mk;Common,Gadget,LogFile	\
	GenericContainer/GenericContainer.mk;Common,LogFile,VSAShared	\
	LogFile/LogFile.mk;Common	\
	Services/ServiceClogTest/ServiceClogTest.mk;Common,LogFile,VSAShared,Gadget	\
	Services/ServiceCycler/ServiceCycler.mk;Common,LogFile,VSAShared,Gadget	\
	Services/ServiceRstaEptm/ServiceRstaEptm.mk;Common,LogFile,VSAShared,Gadget	\
	Services/ServiceVehicleDataSample/ServiceVehicleDataSample.mk;Common,LogFile,VSAShared,Gadget	\
	Services/ServiceVehicleDirectLoad/ServiceVehicleDirectLoad.mk;Common,LogFile,VSAShared,Gadget	\
	Services/ServiceVehicleSocket/ServiceVehicleSocket.mk;Common,LogFile,VSAShared,Gadget	\
	VSAShared/VSAShared.mk	\
	VSAShared/VSAShared_specs/VSAShared_specs.mk;Common,VSAShared,LogFile	\
	WorkbenchShared/WorkbenchShared.mk	\
	WorkbenchGLUT/WorkbenchGLUT.mk;Common,Gadget,LogFile,VSAShared,ExternalXML,WorkbenchShared,VDraw	\
	WorkbenchGTK/WorkbenchGTK.mk;Common,Gadget,LogFile,VSAShared,ExternalXML,WorkbenchShared,VDraw



ProjectsList.Release := $(ProjectsList.Debug)

ifeq (Debug,$(ConfigurationName))
ProjectsList := $(ProjectsList.$(ConfigurationName))
else ifeq (Release,$(ConfigurationName))
ProjectsList := $(ProjectsList.$(ConfigurationName))
else
$(error Unrecognized ConfigurationName = $(ConfigurationName))
endif
ProjectsList := $(ProjectsList.$(ConfigurationName))


ifneq (,$(findstring /cygdrive/,$(PATH)))
UNAME := Cygwin
GRAYTEXT :=
NORMTEXT :=
else ifneq (,$(findstring Windows,$(PATH)))
UNAME := Windows
GRAYTEXT :=
NORMTEXT :=
else
UNAME := $(shell uname -s)
GRAYTEXT := \033[0;37m
NORMTEXT := \033[0m
endif

##
## environment variables (from codelite workspace and global)
##
export PlatformName:=$(if $(findstring Windows,$(OS)),Windows,$(shell uname -s)-$(shell uname -m))
export CXXFLAGS_GLOBAL=-Wno-non-virtual-dtor


export SINGLEFILE


# a few needed constants
COMMA := ,
SPACE :=
SPACE +=
EQUALS := =
HASH := \#

# if SingleProject is specified then get rid of other projects from the list
ifneq (,$(strip $(SINGLEPROJECT)))
Projects := $(subst ;;,;Dummy_SingleProject;,$(foreach prj,$(ProjectsList),$(if $(findstring /$(SINGLEPROJECT).mk,$(prj)),$(prj))))
else
Projects := $(subst ;;,;Dummy_SingleProject;,$(ProjectsList))
endif

# patterns from codelite's builder
SUMMARY:=awk 'BEGIN { w=0; e=0; n=0; z=0; } \
	/has modification time [0-9\.]+ *s in the future/ \
	|| /[Cc]lock skew detected/ { next } \
	/[Ww]arning:/ \
	|| /([a-zA-Z:]{0,2}[ a-zA-Z\.0-9_\/\+\-]+ *)(:)([0-9]+ *)(:)([0-9:]*)?( warning)/ \
	|| /([a-zA-Z:]{0,2}[ a-zA-Z\.0-9_\/\+\-]+ *)(:)([0-9]+ *)(:)([0-9:]*)?( note)/ \
	|| /([a-zA-Z:]{0,2}[ a-zA-Z\.0-9_\/\+\-]+ *)(:)([0-9]+ *)(:)([0-9:]*)?([ ]+instantiated)/ \
	|| /(In file included from *)([a-zA-Z:]{0,2}[ a-zA-Z\.0-9_\/\+\-]+ *)(:)([0-9]+ *)(:)([0-9:]*)?/ { ++w; next } \
	/[Ee]rror:/ \
	|| /^([^ ][a-zA-Z:]{0,2}[ a-zA-Z\.0-9_\/\+\-]+ *)(:)([0-9]*)([:0-9]*)(: )((fatal error)|(error)|(undefined reference))/ \
	|| /^([^ ][a-zA-Z:]{0,2}[ a-zA-Z\.0-9_\/\+\-]+ *)(:)([^ ][a-zA-Z:]{0,2}[ a-zA-Z\.0-9_/\+\-]+ *)(:)(\(\.text\+[0-9a-fx]*\))/ \
	|| /^([^ ][a-zA-Z:]{0,2}[ a-zA-Z\.0-9_\/\+\-]+ *)(:)([^ ][a-zA-Z:]{0,2}[ a-zA-Z\.0-9_/\+\-]+ *)(:)([0-9]+)(:)/ \
	|| /undefined reference to/ \
	|| /cannot find/ \
	|| /No such file/ \
	|| /ld returned [1-9][0-9]* exit status/ \
	|| /\*+ \[..*\] [Ee]rror [1-9][0-9]*/ \
	|| /error: [a-zA-Z]+ returned [1-9][0-9]* exit status/ \
	|| / [1-9][0-9]* [Ff]ailed/ { ++e; next } \
	/[Nn]othing to be done for .all./ { ++n; next } \
	/ 0 Errors, 0 Warnings / { ++z; next } \
	END { if ( 1 == (n+z) ) { print "$(GRAYTEXT)Nothing to be done$(NORMTEXT)" } else { print e " Errors, " w " Warnings" } }'



BldSuffix	:=.build
ClnSuffix	:=.clean
TicSuffix	:=.tickle
EndSuffix	:=.log
TimSuffix	:=.time

TICKLETIME := $(shell awk 'BEGIN { print strftime("%FT%T")}')
TICKLE	:= $(subst -,,$(subst :,,$(TICKLETIME)))
TICS := $(WorkingDirectory)/$(TICKLE)$(TicSuffix)
CTCS := $(WorkingDirectory)/$(TICKLE)_clean$(TicSuffix)
TIMS := $(WorkingDirectory)/$(WorkspaceName)$(TimSuffix)
ENDS := $(WorkingDirectory)/$(if $(LOGFILE),$(LOGFILE),$(WorkspaceName))$(EndSuffix)
CLDS := $(WorkingDirectory)/$(if $(LOGFILE),$(LOGFILE),$(WorkspaceName))_clean$(EndSuffix)

MAKS := $(foreach prj,$(Projects),$(firstword $(subst ;,$(SPACE),$(prj))))
BLDS := $(addprefix $(WorkingDirectory)/,$(addsuffix $(BldSuffix),$(basename $(notdir $(MAKS)))))
CLNS := $(addprefix $(WorkingDirectory)/,$(addsuffix $(ClnSuffix),$(basename $(notdir $(MAKS)))))

#SUFFIXES = $(BldSuffix) $(TicSuffix) .mk

HIDE := $(if $(Option-ShowCommands),,@)


##
## all
##
.PHONY: all
all: $(or $(PROJECT),$(ENDS))

.PHONY: Build
Build: all

$(ENDS): $(TICS) $(BLDS) $(MAKS)
	@cat $(TICS) $(BLDS) > $@
	@echo ----------[[[ End Build: `$(SUMMARY) $@``awk 'BEGIN { T2=systime() } /^[0-9]+$$/ { v = T2 - $$1; if ( 5 < v ) printf ", %02d:%02d:%02d Time",v/(60*60),v%(60*60)/60,v%60 }' $(TIMS)` ]]]---------- | tee -a $@


$(TICS): $(MAKS) $(TIMS)
	@$(RM) $(WorkingDirectory)/*$(TicSuffix)
	@$(RM) $(WorkingDirectory)/*$(EndSuffix)
	@echo ==========[[[ Start Build ]]]========== | tee $@
	@echo "$(TICKLETIME)" >> $@
	@awk 'BEGIN { print systime();}' > $(TIMS)

$(TICS): | $(WorkingDirectory)
$(BLDS): | $(WorkingDirectory)
$(ENDS): | $(WorkingDirectory)
$(TIMS): | $(WorkingDirectory)
$(CLNS): | $(WorkingDirectory)
$(CLDS): | $(WorkingDirectory)
$(CTCS): | $(WorkingDirectory)

$(WorkingDirectory):
	@mkdir -p $@

# BldName $1 = basename
define BldName
$(WorkingDirectory)/$(1)$(BldSuffix)
endef

SILENT:= awk '/[Nn]othing to be done for .all./ || /[Cc]lock skew detected/ || /has modification time [0-9.]+ *s in the future/ { next } { print }' -


# GenGenMake $1 = basename, $2 = makefilename, $3 = configuration
define GenGenMake
&& echo ==========[ Build: $(1) - $(3) ]========== | tee -a $$@ && $$(MAKE) -e -C $$(dir $(2)) --no-print-directory -f $$(notdir $(2)) $(if $(SINGLEFILE),SINGLEFILE=$$(SINGLEFILE)) CONFIGURATION=$(3) 2>&1 | tee -a $$@ | $$(SILENT)
endef

# GenMakes $1 = basename, $2 = makefilename, $3 = configuration
define GenMakes
$(foreach tgt,$(3),$(call GenGenMake,$(1),$(2),$(tgt)))
endef

# GenBuildProject $1 = basename, $2 = makefile, $3 = depends, $4 = configuration
define GenBuildProject
$(call BldName,$(1)): $(2) $$(TICS) $(if $(SINGLEPROJECT),,$(foreach dep,$(3),$(call BldName,$(dep))))
	@echo $(2) > $$@
	$(HIDE): $(call GenGenMake,$(1),$(2),$(4))
	@echo ----------[ $(1): `$$(SUMMARY) $$@` ]---------- | tee -a $$@
	@echo "" >> $$@

#	@echo ----------[ $(1): `$$(NOTHING_DONE) $$@``$$(COUNT_ERRORS) $$@` Errors$$(COMMA) `$$(COUNT_WARNINGS) $$@` Warnings ]---------- | tee -a $$@

# target to request build based on project
.PHONY: $(1)
$(1): $(call BldName,$(1))
	@cat $$(TICS) $$(WorkingDirectory)/*$$(BldSuffix) > $$(ENDS)
	@echo ----------[[[ `$$(SUMMARY) $$(ENDS)``awk 'BEGIN { T2=systime() } /^[0-9]+$$$$/ { v = T2 - $$$$1; if ( 5 < v ) printf ", %02d:%02d:%02d Time",v/(60*60),v%(60*60)/60,v%60 }' $(TIMS)` ]]]---------- | tee -a $$(ENDS)

endef

# GenGen $1 = makefile, $2 = depends, $3 = configuration
define GenGen
$(call GenBuildProject,$(basename $(notdir $(1))),$(1),$(subst $(COMMA),$(SPACE),$(2)),$(or $(3),$(ConfigurationName)))
endef

# Gen $1 = [space separated] makefile depends configuration
define Gen
$(call GenGen,$(word 1,$(1)),$(word 2,$(1)),$(word 3,$(1)))
endef
$(eval $(foreach prj,$(Projects),$(call Gen,$(subst ;,$(SPACE),$(prj)))))

$(call BldName,Dummy_SingleProject): $(TICS)
	@echo "" > $@




THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))

.PHONY: rebuild
rebuild:
	$(HIDE)$(MAKE) -e --no-print-directory -f $(THIS_MAKEFILE) CONFIGURATION=$(ConfigurationName) clean$(if $(PROJECT),_$(PROJECT))  &&  $(MAKE) --always-make -e --no-print-directory -f $(THIS_MAKEFILE) CONFIGURATION=$(ConfigurationName) $(PROJECT)







##
## clean
##

.PHONY: mostlyclean
mostlyclean: clean

.PHONY: clean
clean: $(if $(PROJECT),mostlyclean_$(PROJECT),$(CLDS))

ifeq (0, $(words $(findstring mostlyclean,$(MAKECMDGOALS))))
CLEAN_TARGET := clean
else
CLEAN_TARGET := mostlyclean
endif


$(CLDS): $(CTCS) $(CLNS) $(MAKS)
	@cat $(CTCS) $(CLNS) > $@
	@echo ----------[ End Clean ]----------


$(CTCS): $(MAKS) $(TIMS)
	$(HIDE)$(RM) $(WorkingDirectory)/*
	@echo ==========[ Begin Clean ]==========
	@echo "$(TICKLETIME)" >> $@
	@awk 'BEGIN { print systime() }' > $(TIMS)



# ClnName $1 = basename
define ClnName
$(WorkingDirectory)/$(1)$(ClnSuffix)
endef

# GenCleanProject $1 = basename, $2 = makefile, $3 = depends, $4 = configuration
define GenCleanProject
$(call ClnName,$(1)): $(2) $$(CTCS) $(if $(SINGLEPROJECT),,$(foreach dep,$(3),$(call ClnName,$(dep))))
	@echo $(2) > $$@
	$(HIDE)$$(MAKE) -e -C $$(dir $(2)) --no-print-directory -f $$(notdir $(2)) CONFIGURATION=$(4) $(if $(SINGLEFILE),SINGLEFILE=$$(SINGLEFILE)) $(CLEAN_TARGET)

# target to request build based on project
.PHONY: clean_$(1)
clean_$(1): $(call ClnName,$(1))
	@cat $$(CTCS) $$(WorkingDirectory)/*$$(ClnSuffix) > $$(CLDS)
	@echo ----------[ End Clean ]----------


endef

# CGenGen $1 = makefile, $2 = depends, $3 = configuration
define CGenGen
$(call GenCleanProject,$(basename $(notdir $(1))),$(1),$(subst $(COMMA),$(SPACE),$(2)),$(or $(3),$(ConfigurationName)))
endef

# CGen $1 = [space separated] makefile depends configuration
define CGen
$(call CGenGen,$(word 1,$(1)),$(word 2,$(1)),$(word 3,$(1)))
endef
$(eval $(foreach prj,$(Projects),$(call CGen,$(subst ;,$(SPACE),$(prj)))))





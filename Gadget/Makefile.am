



AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw
#AM_CXXFLAGS += -fPIC

srcApplication = \
		CApplicationGauge.cpp \
		CApplicationGaugeOpenGL.cpp \
		CApplicationGaugeWin.cpp \
		CCommandProcessor.cpp \
		CDrawQueue.cpp \
		CFunctionProcessor.cpp \
		CKeyProcessorOpenGL.cpp \
		CKeyProcessorWin.cpp \
		CMouseProcessorWin.cpp \
		IApplicationUser.cpp \
		IMouseTransform.cpp

srcComponents = \
		CAction.cpp \
		CChoose.cpp \
		CChooseWhen.cpp \
		CElement.cpp \
		CForLoop.cpp \
		CGauge.cpp \
		CKeyEventMap.cpp \
		CKeyNames.cpp \
		CMouseArea.cpp \
		CMouseAreaList.cpp \
		CMouseLocate.cpp \
		CPanel.cpp \
		CPosition.cpp \
		CQueue.cpp \
		CRotation.cpp \
		CScreen.cpp \
		CSelect.cpp \
		CSelectCase.cpp \
		CShift.cpp \
		CSize.cpp \
		CTrigger.cpp \
		CVisible.cpp \
		VControl.cpp \
		VControlEventMap.cpp \
		VElement.cpp \
		VOwnership.cpp \
		VPanelChild.cpp

disabledComponents = \
		CPanelDivision.cpp

srcDictionary = \
		CDictHandlerTime.cpp \
		CDictionary.cpp \
		CDictionaryMemory.cpp \
		CDictionarySelector.cpp \
		CDictPageActive.cpp \
		CDictPageAlerts.cpp \
		CDictPageCommands.cpp \
		CDictPageConfigWrapper.cpp \
		CDictPageEvents.cpp \
		CDictPageFunctions.cpp \
		CDictPageLazyLoad.cpp \
		CDictPageP.cpp \
		CDictPageSelector.cpp \
		CDictPageSystem.cpp \
		CDictPageT.cpp \
		CDictPageVariant.cpp \
		CDictPageVariantRead.cpp \
		CDictPageVariantWrite.cpp \
		IDictionaryUser.cpp \
		VDictionaryPage.cpp \
		VDictionaryPageServer.cpp

srcFactories = \
		CFactoryDictActive.cpp \
		CFactoryDictionary.cpp \
		CFactoryEquation.cpp \
		CFactoryExternalXML.cpp \
		CFactoryGauge.cpp \
		CFactoryPanel.cpp \
		CFactoryScreen.cpp \
		CFactoryVehicleData.cpp \
		VFactoryComponent.cpp

srcGraphics = \
		CArc.cpp \
		CAxis.cpp \
		CCircle.cpp \
		CEllipse.cpp \
		CGaugeString.cpp \
		CGaugeText.cpp \
		CImage.cpp \
		CLine.cpp \
		CPie.cpp \
		CPoint.cpp \
		CPolygon.cpp \
		CPolyline.cpp \
		CRectangle.cpp \
		CStyle.cpp \
		CVideo.cpp \
		VCoordinate.cpp \
		VGraphic.cpp \
		VPolylist.cpp

srcEquations = \
		CEqConstant.cpp \
		CEqConstGaugeHeight.cpp \
		CEqConstGaugeLeft.cpp \
		CEqConstGaugeTop.cpp \
		CEqConstGaugeWidth.cpp \
		CEqOpAbs.cpp \
		CEqOpAdd.cpp \
		CEqOpAnd.cpp \
		CEqOpBitAnd.cpp \
		CEqOpBitOr.cpp \
		CEqOpBoth.cpp \
		CEqOpCase.cpp \
		CEqOpCeil.cpp \
		CEqOpColorname.cpp \
		CEqOpDecrement.cpp \
		CEqOpDegFromRad.cpp \
		CEqOpDegreeNorm.cpp \
		CEqOpDivide.cpp \
		CEqOpEqual.cpp \
		CEqOpFind.cpp \
		CEqOpFloor.cpp \
		CEqOpFormatString.cpp \
		CEqOpGreaterOrEqual.cpp \
		CEqOpGreaterThan.cpp \
		CEqOpIncrement.cpp \
		CEqOpLessOrEqual.cpp \
		CEqOpLessThan.cpp \
		CEqOpMax.cpp \
		CEqOpMin.cpp \
		CEqOpModulo.cpp \
		CEqOpMultiply.cpp \
		CEqOpNear.cpp \
		CEqOpNegate.cpp \
		CEqOpNot.cpp \
		CEqOpNotEqual.cpp \
		CEqOpOr.cpp \
		CEqOpQuestion.cpp \
		CEqOpRadFromDeg.cpp \
		CEqOpRadianNorm.cpp \
		CEqOpRange.cpp \
		CEqOpRegisters.cpp \
		CEqOpRegLoad.cpp \
		CEqOpRegStore.cpp \
		CEqOpRGB.cpp \
		CEqOpRGBA.cpp \
		CEqOpSquare.cpp \
		CEqOpStrCat.cpp \
		CEqOpSubStr.cpp \
		CEqOpSubtract.cpp \
		CEqOpUnitAbbrev.cpp \
		CEqOpUnitConvert.cpp \
		CEqOpUnitName.cpp \
		CEqOpUnitPlural.cpp \
		CEqVariable.cpp \
		CEqVariableAssign.cpp \
		CEqVariableAssignCond.cpp \
		CEqVariableAssignIndirect.cpp \
		CEqVariableIndirect.cpp \
		CResultValue.cpp \
		VEqConstGauge.cpp \
		VEqOpBinary.cpp \
		VEqOpQuaternary.cpp \
		VEqOpTrinary.cpp \
		VEqOpUnary.cpp \
		VEquation.h



lib_LTLIBRARIES = libgadget.la

libgadget_la_SOURCES = \
		$(srcApplication) \
		$(srcComponents) \
		$(srcDictionary) \
		$(srcEquations) \
		$(srcFactories) \
		$(srcGraphics)
libgadget_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libgadget_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS) -DSHLIB_GADGET
libgadget_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la
libgadget_la_LIBADD = \
		-lpthread \
		-lstdc++ \
		-lc
libgadget_la_DEPENDENCIES = \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la





TESTS = Gadget_specs
bin_PROGRAMS = Gadget_specs
EXTRA_Gadget_specs_DEPENDENCIES = \
		libgadget.la \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la

CHKCPPFLAGS = \
		-I$(top_srcdir)/Platform/test \
		-I$(top_srcdir)/Common/test \
		-I$(top_srcdir)/3rdParty/igloo
CHKLDFLAGS = \
		-L$(top_builddir)/Common \
		-L$(top_builddir)/Platform \
		-L$(top_builddir)/Gadget

Gadget_specs_SOURCES = \
	test/Gadget_specs.cpp \
	\
	test/CKeyNames_spec.cpp \
	test/CQueue_spec.cpp \
	test/Equations_spec.cpp
Gadget_specs_CXXFLAGS = $(CHECK_FLAGS) $(CXXFLAGS) $(AM_CXXFLAGS)
Gadget_specs_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS) $(CHKCPPFLAGS)
Gadget_specs_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(CHKLDFLAGS) \
		$(top_builddir)/Gadget/libgadget.la \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la
Gadget_specs_LDADD = \
		-lpthread \
		-lstdc++ \
		-lc

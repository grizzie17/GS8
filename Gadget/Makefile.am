



AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw
#AM_CXXFLAGS += -fPIC



lib_LTLIBRARIES = libgadget.la

libgadget_la_SOURCES = \
		CAction.cpp \
		CApplicationGauge.cpp \
		CApplicationGaugeOpenGL.cpp \
		CApplicationGaugeWin.cpp \
		CArc.cpp \
		CAxis.cpp \
		CChoose.cpp \
		CChooseWhen.cpp \
		CCircle.cpp \
		CCommandProcessor.cpp \
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
		CDictPageP.cpp \
		CDictPageSelector.cpp \
		CDictPageSystem.cpp \
		CDictPageT.cpp \
		CDictPageVariant.cpp \
		CDictPageVariantRead.cpp \
		CDictPageVariantWrite.cpp \
		CDrawQueue.cpp \
		CElement.cpp \
		CEllipse.cpp \
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
		CFactoryDictActive.cpp \
		CFactoryDictionary.cpp \
		CFactoryEquation.cpp \
		CFactoryExternalXML.cpp \
		CFactoryGauge.cpp \
		CFactoryGaugeTester.cpp \
		CFactoryPanel.cpp \
		CFactoryPanelTester.cpp \
		CFactoryScreen.cpp \
		CFactoryScreenTester.cpp \
		CFactoryVehicleData.cpp \
		CForLoop.cpp \
		CFunctionProcessor.cpp \
		CGauge.cpp \
		CGaugeString.cpp \
		CGaugeText.cpp \
		CImage.cpp \
		CKeyEventMap.cpp \
		CKeyNames.cpp \
		CKeyProcessorOpenGL.cpp \
		CKeyProcessorWin.cpp \
		CLine.cpp \
		CMouseArea.cpp \
		CMouseAreaList.cpp \
		CMouseLocate.cpp \
		CMouseProcessorWin.cpp \
		CPanel.cpp \
		CPanelDivision.cpp \
		CPie.cpp \
		CPoint.cpp \
		CPolygon.cpp \
		CPolyline.cpp \
		CPosition.cpp \
		CQueue.cpp \
		CRectangle.cpp \
		CResultValue.cpp \
		CRotation.cpp \
		CScreen.cpp \
		CSelect.cpp \
		CSelectCase.cpp \
		CShift.cpp \
		CSize.cpp \
		CStyle.cpp \
		CTrigger.cpp \
		CVideo.cpp \
		CVisible.cpp \
		CXMLParser.cpp \
		IApplicationUser.cpp \
		IDictionaryUser.cpp \
		IMouseTransform.cpp \
		Stdafx.cpp \
		VControl.cpp \
		VControlEventMap.cpp \
		VCoordinate.cpp \
		VDictionaryPage.cpp \
		VDictionaryPageServer.cpp \
		VElement.cpp \
		VEqConstGauge.cpp \
		VEqOpBinary.cpp \
		VEqOpQuaternary.cpp \
		VEqOpTrinary.cpp \
		VEqOpUnary.cpp \
		VFactoryComponent.cpp \
		VGraphic.cpp \
		VOwnership.cpp \
		VPanelChild.cpp \
		VPolylist.cpp
libgadget_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libgadget_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS) -DBUILDING_SHAREDLIB
libgadget_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) \
		-L$(top_builddir)/Draw/VDraw \
		-L$(top_builddir)/Common \
		-L$(top_builddir)/Platform
libgadget_la_LIBADD = \
		-lvdraw \
		-lcommon \
		-lplatform





TESTS = gadget_specs
bin_PROGRAMS = gadget_specs
EXTRA_gadget_specs_DEPENDENCIES = libgadget.la

CHKCPPFLAGS = \
		-I$(top_srcdir)/Platform/test \
		-I$(top_srcdir)/Common/test \
		-I$(top_srcdir)/3rdParty/igloo
CHKLDFLAGS = \
		-L$(top_builddir)/Common \
		-L$(top_builddir)/Platform \
		-L$(top_builddir)/Gadget

gadget_specs_SOURCES = \
	test/Gadget_specs.cpp \
	\
	test/CKeyNames_spec.cpp \
	test/CQueue_spec.cpp \
	test/Equations_spec.cpp
gadget_specs_CXXFLAGS = $(CHECK_FLAGS) $(CXXFLAGS) $(AM_CXXFLAGS)
gadget_specs_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS) $(CHKCPPFLAGS)
gadget_specs_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(CHKLDFLAGS)
gadget_specs_LDADD = \
		-lgadget \
		-lcommon \
		-lplatform \
		-lpthread

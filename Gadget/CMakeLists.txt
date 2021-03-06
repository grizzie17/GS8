set( THIS Gadget )

project( ${THIS}
	VERSION 1.0.0
	DESCRIPTION "Gadget"
	)



set( SOURCES
	CAction.cpp
	CApplicationGauge.cpp
	CApplicationGaugeWin.cpp
	CArc.cpp
	CAxis.cpp
	CChoose.cpp
	CChooseWhen.cpp
	CCircle.cpp
	CCommandProcessor.cpp
	CDictHandlerTime.cpp
	CDictionary.cpp
	CDictionaryMemory.cpp
	CDictionarySelector.cpp
	CDictPageActive.cpp
	CDictPageAlerts.cpp
	CDictPageCommands.cpp
	CDictPageConfigWrapper.cpp
	CDictPageEvents.cpp
	CDictPageFunctions.cpp
	CDictPageLazyLoad.cpp
	CDictPageP.cpp
	CDictPageSelector.cpp
	CDictPageSystem.cpp
	CDictPageT.cpp
	CDictPageVariant.cpp
	CDictPageVariantRead.cpp
	CDictPageVariantWrite.cpp
	CDrawQueue.cpp
	CElement.cpp
	CEllipse.cpp
	CEqConstant.cpp
	CEqConstGaugeHeight.cpp
	CEqConstGaugeLeft.cpp
	CEqConstGaugeTop.cpp
	CEqConstGaugeWidth.cpp
	CEqOpAbs.cpp
	CEqOpAdd.cpp
	CEqOpAnd.cpp
	CEqOpBitAnd.cpp
	CEqOpBitOr.cpp
	CEqOpBoth.cpp
	CEqOpCase.cpp
	CEqOpCeil.cpp
	CEqOpColorname.cpp
	CEqOpDecrement.cpp
	CEqOpDegFromRad.cpp
	CEqOpDegreeNorm.cpp
	CEqOpDivide.cpp
	CEqOpEqual.cpp
	CEqOpFind.cpp
	CEqOpFloor.cpp
	CEqOpFormatString.cpp
	CEqOpGreaterOrEqual.cpp
	CEqOpGreaterThan.cpp
	CEqOpIncrement.cpp
	CEqOpLessOrEqual.cpp
	CEqOpLessThan.cpp
	CEqOpMax.cpp
	CEqOpMin.cpp
	CEqOpModulo.cpp
	CEqOpMultiply.cpp
	CEqOpNear.cpp
	CEqOpNegate.cpp
	CEqOpNot.cpp
	CEqOpNotEqual.cpp
	CEqOpOr.cpp
	CEqOpQuestion.cpp
	CEqOpRadFromDeg.cpp
	CEqOpRadianNorm.cpp
	CEqOpRange.cpp
	CEqOpRegisters.cpp
	CEqOpRegLoad.cpp
	CEqOpRegStore.cpp
	CEqOpRGB.cpp
	CEqOpRGBA.cpp
	CEqOpSquare.cpp
	CEqOpStrCat.cpp
	CEqOpSubStr.cpp
	CEqOpSubtract.cpp
	CEqOpUnitAbbrev.cpp
	CEqOpUnitConvert.cpp
	CEqOpUnitName.cpp
	CEqOpUnitPlural.cpp
	CEqVariable.cpp
	CEqVariableAssign.cpp
	CEqVariableAssignCond.cpp
	CEqVariableAssignIndirect.cpp
	CEqVariableIndirect.cpp
	CFactoryDictActive.cpp
	CFactoryDictionary.cpp
	CFactoryEquation.cpp
	CFactoryExternalXML.cpp
	CFactoryGauge.cpp
	CFactoryGaugeTester.cpp
	CFactoryPanel.cpp
	CFactoryPanelTester.cpp
	CFactoryScreen.cpp
	CFactoryScreenTester.cpp
	CFactoryVehicleData.cpp
	CForLoop.cpp
	CFunctionProcessor.cpp
	CGauge.cpp
	CGaugeString.cpp
	CGaugeText.cpp
	CImage.cpp
	CKeyEventMap.cpp
	CKeyNames.cpp
	CKeyProcessorOpenGL.cpp
	CKeyProcessorWin.cpp
	CLine.cpp
	CMouseArea.cpp
	CMouseAreaList.cpp
	CMouseLocate.cpp
	CMouseProcessorWin.cpp
	CPanel.cpp
	CPanelDivision.cpp
	CPie.cpp
	CPoint.cpp
	CPolygon.cpp
	CPolyline.cpp
	CPosition.cpp
	CQueue.cpp
	CRectangle.cpp
	CResultValue.cpp
	CRotation.cpp
	CScreen.cpp
	CSelect.cpp
	CSelectCase.cpp
	CShift.cpp
	CSize.cpp
	CStyle.cpp
	CTrigger.cpp
	CVideo.cpp
	CVisible.cpp
	CXMLParser.cpp
	IApplicationUser.cpp
	IDictionaryUser.cpp
	IMouseTransform.cpp
	VControl.cpp
	VControlEventMap.cpp
	VCoordinate.cpp
	VDictionaryPage.cpp
	VDictionaryPageServer.cpp
	VElement.cpp
	VEqConstGauge.cpp
	VEqOpBinary.cpp
	VEqOpQuaternary.cpp
	VEqOpTrinary.cpp
	VEqOpUnary.cpp
	VFactoryComponent.cpp
	VGraphic.cpp
	VOwnership.cpp
	VPanelChild.cpp
	VPolylist.cpp
	)

set( HEADERS
	CAction.h
	CApplicationGauge.h
	CApplicationGaugeOpenGL.h
	CApplicationGaugeWin.h
	CArc.h
	CAxis.h
	CChoose.h
	CChooseWhen.h
	CCircle.h
	CCommandProcessor.h
	CDictHandlerTime.h
	CDictionary.h
	CDictionaryMemory.h
	CDictionarySelector.h
	CDictPageActive.h
	CDictPageAlerts.h
	CDictPageCommands.h
	CDictPageConfigWrapper.h
	CDictPageEvents.h
	CDictPageFunctions.h
	CDictPageLazyLoad.h
	CDictPageP.h
	CDictPageSelector.h
	CDictPageSystem.h
	CDictPageT.h
	CDictPageVariant.h
	CDictPageVariantRead.h
	CDictPageVariantWrite.h
	CDrawQueue.h
	CElement.h
	CEllipse.h
	CEqConstant.h
	CEqConstGaugeHeight.h
	CEqConstGaugeLeft.h
	CEqConstGaugeTop.h
	CEqConstGaugeWidth.h
	CEqOpAbs.h
	CEqOpAdd.h
	CEqOpAnd.h
	CEqOpBitAnd.h
	CEqOpBitOr.h
	CEqOpBoth.h
	CEqOpCase.h
	CEqOpCeil.h
	CEqOpColorname.h
	CEqOpDecrement.h
	CEqOpDegFromRad.h
	CEqOpDegreeNorm.h
	CEqOpDivide.h
	CEqOpEqual.h
	CEqOpFind.h
	CEqOpFloor.h
	CEqOpFormatString.h
	CEqOpGreaterOrEqual.h
	CEqOpGreaterThan.h
	CEqOpIncrement.h
	CEqOpLessOrEqual.h
	CEqOpLessThan.h
	CEqOpMax.h
	CEqOpMin.h
	CEqOpModulo.h
	CEqOpMultiply.h
	CEqOpNear.h
	CEqOpNegate.h
	CEqOpNot.h
	CEqOpNotEqual.h
	CEqOpOr.h
	CEqOpQuestion.h
	CEqOpRadFromDeg.h
	CEqOpRadianNorm.h
	CEqOpRange.h
	CEqOpRegisters.h
	CEqOpRegLoad.h
	CEqOpRegStore.h
	CEqOpRGB.h
	CEqOpRGBA.h
	CEqOpSquare.h
	CEqOpStrCat.h
	CEqOpSubStr.h
	CEqOpSubtract.h
	CEqOpUnitAbbrev.h
	CEqOpUnitConvert.h
	CEqOpUnitName.h
	CEqOpUnitPlural.h
	CEqVariable.h
	CEqVariableAssign.h
	CEqVariableAssignCond.h
	CEqVariableAssignIndirect.h
	CEqVariableIndirect.h
	CFactoryDictActive.h
	CFactoryDictionary.h
	CFactoryEquation.h
	CFactoryExternalXML.h
	CFactoryGauge.h
	CFactoryGaugeTester.h
	CFactoryPanel.h
	CFactoryPanelTester.h
	CFactoryScreen.h
	CFactoryScreenTester.h
	CFactoryVehicleData.h
	CForLoop.h
	CFunctionProcessor.h
	CGauge.h
	CGaugeString.h
	CGaugeText.h
	CImage.h
	CKeyEventMap.h
	CKeyNames.h
	CKeyProcessorOpenGL.h
	CKeyProcessorWin.h
	CLine.h
	CMouseArea.h
	CMouseAreaList.h
	CMouseLocate.h
	CMouseProcessorWin.h
	CPanel.h
	CPanelDivision.h
	CPie.h
	CPoint.h
	CPolygon.h
	CPolyline.h
	CPosition.h
	CQueue.h
	CRectangle.h
	CResultValue.h
	CRotation.h
	CScreen.h
	CSelect.h
	CSelectCase.h
	CShift.h
	CSize.h
	CStyle.h
	CTrigger.h
	CVideo.h
	CVisible.h
	CXMLParser.h
	IApplicationUser.h
	IDictionaryUser.h
	IMouseTransform.h
	NamespaceGadget.h
	UDeclGadget.h
	UKeys.h
	UVehicleData.h
	VAction.h
	VControl.h
	VControlEventMap.h
	VCoordinate.h
	VDictionary.h
	VDictionaryPage.h
	VDictionaryPageServer.h
	VDrawQueue.h
	VElement.h
	VEqConstGauge.h
	VEqOpBinary.h
	VEqOpQuaternary.h
	VEqOpTrinary.h
	VEqOpUnary.h
	VEquation.h
	VFactoryComponent.h
	VFactoryGauge.h
	VFactoryPanel.h
	VFactoryScreen.h
	VFunctionProcessor.h
	VGraphic.h
	VMouseProcessorWin.h
	VOwnership.h
	VPanelChild.h
	VPolylist.h
	VRenderable.h
	VStyle.h
	)


add_library(${THIS} STATIC ${SOURCES} ${HEADERS})

set_target_properties(${THIS} PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION 1)

target_link_libraries(Common Platform)


add_subdirectory(test)

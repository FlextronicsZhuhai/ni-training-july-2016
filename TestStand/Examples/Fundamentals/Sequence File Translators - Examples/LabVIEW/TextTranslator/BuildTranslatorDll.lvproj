<?xml version="1.0" encoding="UTF-8"?>
<Project Type="Project" LVVersion="11008008">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="CCSymbols" Type="Str">OS,Win;CPU,x86;</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="TextTranslator" Type="Folder">
			<Item Name="HelperVIsforTextTranslator.llb" Type="Folder">
				<Item Name="TextReadfromStream.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextReadfromStream.vi"/>
				<Item Name="TextSplitStringonToken.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextSplitStringonToken.vi"/>
				<Item Name="TextGetNumProperties.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextGetNumProperties.vi"/>
				<Item Name="TextProcessReportProperty.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextProcessReportProperty.vi"/>
				<Item Name="TextAddReportProperty.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextAddReportProperty.vi"/>
				<Item Name="TextCreateLocalReportval.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextCreateLocalReportval.vi"/>
				<Item Name="TextSetPostStepExpr.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextSetPostStepExpr.vi"/>
				<Item Name="TextAddUsedTypes.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextAddUsedTypes.vi"/>
				<Item Name="TextProcessStepProperties.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextProcessStepProperties.vi"/>
				<Item Name="TextGetStepProperties.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextGetStepProperties.vi"/>
				<Item Name="Textarrayglobal.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/Textarrayglobal.vi"/>
				<Item Name="TextClosePropertyObjectAxReference.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextClosePropertyObjectAxReference.vi"/>
				<Item Name="TextCloseTypeUsageListAxReference.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextCloseTypeUsageListAxReference.vi"/>
				<Item Name="TextClosePropertyObjectFileAxReference.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextClosePropertyObjectFileAxReference.vi"/>
				<Item Name="TextCloseStepAxReference.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextCloseStepAxReference.vi"/>
				<Item Name="TextCloseSequenceReference.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextCloseSequenceReference.vi"/>
				<Item Name="TextReadHeaderLine.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextReadHeaderLine.vi"/>
				<Item Name="TextGetStepDetails.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextGetStepDetails.vi"/>
				<Item Name="TextGetResultString.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextGetResultString.vi"/>
				<Item Name="TextInsertStep.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextInsertStep.vi"/>
				<Item Name="TextInsertMainSeq.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextInsertMainSeq.vi"/>
				<Item Name="TextReadNextLine.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextReadNextLine.vi"/>
				<Item Name="TextGetStepPropertiesFromTokens.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextGetStepPropertiesFromTokens.vi"/>
				<Item Name="TextSetStepProperties.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextSetStepProperties.vi"/>
				<Item Name="TextLoadTypePalettes.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextLoadTypePalettes.vi"/>
				<Item Name="TextCreateStep.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextCreateStep.vi"/>
				<Item Name="TextCreateMainSequence.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextCreateMainSequence.vi"/>
				<Item Name="TextCloseAxReferences.vi" Type="VI" URL="../HelperVIsforTextTranslator.llb/TextCloseAxReferences.vi"/>
			</Item>
			<Item Name="TextTranslateToSequenceFile.vi" Type="VI" URL="../TextTranslateToSequenceFile.vi"/>
			<Item Name="TextIsCurrentFileVersion.vi" Type="VI" URL="../TextIsCurrentFileVersion.vi"/>
			<Item Name="TextGetFileVersion.vi" Type="VI" URL="../TextGetFileVersion.vi"/>
			<Item Name="TextGetFileFormatVersion.vi" Type="VI" URL="../TextGetFileFormatVersion.vi"/>
			<Item Name="TextGetExtension.vi" Type="VI" URL="../TextGetExtension.vi"/>
			<Item Name="TextGetDescription.vi" Type="VI" URL="../TextGetDescription.vi"/>
			<Item Name="TextCanTranslate.vi" Type="VI" URL="../TextCanTranslate.vi"/>
			<Item Name="TextGetTranslatorCount.vi" Type="VI" URL="../TextGetTranslatorCount.vi"/>
		</Item>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="TestStand API Numeric Constants.ctl" Type="VI" URL="/&lt;vilib&gt;/addons/TestStand/_TSUtility.llb/TestStand API Numeric Constants.ctl"/>
				<Item Name="TestStand API Numeric Constants.vi" Type="VI" URL="/&lt;vilib&gt;/addons/TestStand/_TSUtility.llb/TestStand API Numeric Constants.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="TestStand API String Constants.ctl" Type="VI" URL="/&lt;vilib&gt;/addons/TestStand/_TSUtility.llb/TestStand API String Constants.ctl"/>
				<Item Name="TestStand API String Constants.vi" Type="VI" URL="/&lt;vilib&gt;/addons/TestStand/_TSUtility.llb/TestStand API String Constants.vi"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="LabVIEWTextTranslator" Type="DLL">
				<Property Name="App_INI_aliasGUID" Type="Str">{1C2749A5-E4DE-4B3A-B730-A4AAB630FF0B}</Property>
				<Property Name="App_INI_GUID" Type="Str">{0A1AF7FA-1BBD-45E8-AA3C-C94C1E9F65B2}</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{A28A9728-563F-4E92-BE4E-CD922B65A285}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">LabVIEWTextTranslator</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeTypedefs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../TextTranslator</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{EB153131-CAF1-4589-968B-F434F6479FA8}</Property>
				<Property Name="Destination[0].destName" Type="Str">LabVIEWTextTranslator.dll</Property>
				<Property Name="Destination[0].path" Type="Path">../TextTranslator/LabVIEWTextTranslator.dll</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">data</Property>
				<Property Name="Destination[1].path" Type="Path">../TextTranslator/data</Property>
				<Property Name="Destination[2].destName" Type="Str">DestinationDirectory</Property>
				<Property Name="Destination[2].path" Type="Path">../TextTranslator</Property>
				<Property Name="Destination[3].destName" Type="Str">D</Property>
				<Property Name="Destination[3].path" Type="Path">../TextTranslator/D</Property>
				<Property Name="DestinationCount" Type="Int">4</Property>
				<Property Name="Dll_delayOSMsg" Type="Bool">true</Property>
				<Property Name="Dll_headerGUID" Type="Str">{974C66A1-60AC-49E8-A377-66CAD148CE20}</Property>
				<Property Name="Dll_libGUID" Type="Str">{A6B2036F-3C34-40D6-98A1-D4067E236C09}</Property>
				<Property Name="Source[0].Container.applyDestination" Type="Bool">true</Property>
				<Property Name="Source[0].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[0].Container.applyProperties" Type="Bool">true</Property>
				<Property Name="Source[0].itemID" Type="Str">{E4E490EE-1B5D-42B3-8F3B-C4494BF29EEB}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextReadfromStream.vi</Property>
				<Property Name="Source[1].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[1].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[1].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[1].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[1].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[1].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[1].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[10].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextGetStepProperties.vi</Property>
				<Property Name="Source[10].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[10].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[10].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[10].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[10].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[10].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[10].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[10].type" Type="Str">VI</Property>
				<Property Name="Source[11].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/Textarrayglobal.vi</Property>
				<Property Name="Source[11].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[11].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[11].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[11].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[11].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[11].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[11].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[11].type" Type="Str">VI</Property>
				<Property Name="Source[12].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextClosePropertyObjectAxReference.vi</Property>
				<Property Name="Source[12].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[12].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[12].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[12].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[12].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[12].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[12].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[12].type" Type="Str">VI</Property>
				<Property Name="Source[13].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextCloseTypeUsageListAxReference.vi</Property>
				<Property Name="Source[13].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[13].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[13].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[13].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[13].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[13].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[13].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[13].type" Type="Str">VI</Property>
				<Property Name="Source[14].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextClosePropertyObjectFileAxReference.vi</Property>
				<Property Name="Source[14].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[14].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[14].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[14].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[14].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[14].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[14].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[14].type" Type="Str">VI</Property>
				<Property Name="Source[15].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextCloseStepAxReference.vi</Property>
				<Property Name="Source[15].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[15].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[15].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[15].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[15].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[15].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[15].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[15].type" Type="Str">VI</Property>
				<Property Name="Source[16].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextCloseSequenceReference.vi</Property>
				<Property Name="Source[16].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[16].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[16].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[16].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[16].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[16].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[16].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[16].type" Type="Str">VI</Property>
				<Property Name="Source[17].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextReadHeaderLine.vi</Property>
				<Property Name="Source[17].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[17].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[17].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[17].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[17].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[17].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[17].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[17].type" Type="Str">VI</Property>
				<Property Name="Source[18].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextGetStepDetails.vi</Property>
				<Property Name="Source[18].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[18].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[18].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[18].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[18].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[18].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[18].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[18].type" Type="Str">VI</Property>
				<Property Name="Source[19].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextGetResultString.vi</Property>
				<Property Name="Source[19].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[19].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[19].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[19].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[19].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[19].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[19].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[19].type" Type="Str">VI</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextSplitStringonToken.vi</Property>
				<Property Name="Source[2].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[2].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[2].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[2].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[2].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[2].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[2].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[20].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextInsertStep.vi</Property>
				<Property Name="Source[20].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[20].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[20].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[20].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[20].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[20].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[20].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[20].type" Type="Str">VI</Property>
				<Property Name="Source[21].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextInsertMainSeq.vi</Property>
				<Property Name="Source[21].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[21].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[21].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[21].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[21].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[21].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[21].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[21].type" Type="Str">VI</Property>
				<Property Name="Source[22].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextReadNextLine.vi</Property>
				<Property Name="Source[22].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[22].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[22].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[22].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[22].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[22].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[22].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[22].type" Type="Str">VI</Property>
				<Property Name="Source[23].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextGetStepPropertiesFromTokens.vi</Property>
				<Property Name="Source[23].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[23].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[23].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[23].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[23].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[23].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[23].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[23].type" Type="Str">VI</Property>
				<Property Name="Source[24].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextSetStepProperties.vi</Property>
				<Property Name="Source[24].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[24].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[24].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[24].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[24].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[24].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[24].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[24].type" Type="Str">VI</Property>
				<Property Name="Source[25].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextLoadTypePalettes.vi</Property>
				<Property Name="Source[25].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[25].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[25].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[25].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[25].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[25].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[25].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[25].type" Type="Str">VI</Property>
				<Property Name="Source[26].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextCreateStep.vi</Property>
				<Property Name="Source[26].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[26].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[26].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[26].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[26].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[26].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[26].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[26].type" Type="Str">VI</Property>
				<Property Name="Source[27].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextCreateMainSequence.vi</Property>
				<Property Name="Source[27].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[27].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[27].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[27].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[27].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[27].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[27].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[27].type" Type="Str">VI</Property>
				<Property Name="Source[28].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">9</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">TranslationIndex</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">TSIEngineIn</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">7</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">5</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">TSSequenceFileIn</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">14</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">7</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[7]CallingConv" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[7]Name" Type="Str">TranslateToSequenceFile</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[7]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[7]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[7]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[7]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[7]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[7]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfo[7]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!'G!`!!%!%)#A!!!!!!!!!!!!IA!!!+!!!!#!!!!!!!!!!!!!E!#1!!7E"Q!!&gt;&amp;%!!!!!+S?5\WQ,92U*/=!##P;/C4!!!!",*Z4P8!NB(1EZQ!)+^I[*-!!!!"MHF/]]#W%&gt;#4H!!ALWDIEQ!!!!%!!!!!$624,EF&amp;&lt;G&gt;J&lt;G5A;7Y!"!!!!!1!!!!%!!!!"!!!!'"!=!!(22!!!!!#!!!!!!!!!!!!!!!!!!!!!!!!!!3S?5\ZQ,92U*/=!##P;/C4!!!!!&lt;*Z4P0!NB(1EZQ!)+^I[*-!!!!"!!!!!"*55SZ4:8&amp;V:7ZD:5:J&lt;'5A;7Y!!!1!!!"?1(!!"U51!!!!!A!!!!!!!!!!!!!!!!!!!!!!!!!%+&amp;GA1V)&gt;2@7PFU-C3'K_*A!!!!'S?5\TQ,92U*/=!##P;/C4!!!!!1!!!!!26&amp;-O37ZQ&gt;824&gt;(*F97UA;7Y!"!!!!":!!R"5=G&amp;O=WRB&gt;'FP&lt;EFO:'6Y!!!%!!!!"!!!!!1!!!!%!!!!%E!$$56S=G^S27ZV&lt;3"P&gt;81!&amp;E!Q`````QR&amp;=H*P=EVT:S"P&gt;81!</Property>
				<Property Name="Source[28].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">8</Property>
				<Property Name="Source[28].itemID" Type="Ref">/My Computer/TextTranslator/TextTranslateToSequenceFile.vi</Property>
				<Property Name="Source[28].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[28].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[28].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[28].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[28].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[28].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[28].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[28].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[28].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[29].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">7</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">Index</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Path</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">5</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">8</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">6</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[6]CallingConv" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[6]Name" Type="Str">IsCurrentFileVersion</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!%)!`!!%!%)#!!!!!!!!!!*!!I!!!!)!!E!!!!!!!!!!!!!!!!!#1!!$E!Q`````Q21982I!!!%!!!!"!!!!!1!!!!;1!-538.$&gt;8*S:7ZU2GFM:6:F=H.J&lt;WY!!&amp;Z!=!!(22!!!!!#!!!!!!!!!!!!!!!!!!!!!!!!!!1I7;"$5BV&amp;^;_81S*);LYG!!!!!&lt;*Z4P0!NB(1EZQ!)+^I[*-!!!!"!!!!!"&amp;55SZ*&lt;H"V&gt;&amp;.U=G6B&lt;3"J&lt;A!%!!!!#E!$"5FO:'6Y!"*!!QV&amp;=H*P=E6O&gt;7UA&lt;X6U!!1!!!!%!!!!"!!!!!1!!!!%!!!!"!!!!":!-0````]-28*S&lt;X*.=W=A&lt;X6U!!</Property>
				<Property Name="Source[29].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">7</Property>
				<Property Name="Source[29].itemID" Type="Ref">/My Computer/TextTranslator/TextIsCurrentFileVersion.vi</Property>
				<Property Name="Source[29].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[29].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[29].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[29].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[29].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[29].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[29].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[29].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[29].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextGetNumProperties.vi</Property>
				<Property Name="Source[3].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[3].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[3].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[3].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[3].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[3].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[3].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="Source[30].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">7</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">Index</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Path</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">5</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">5</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">FileVersionOut</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">8</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[7]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[7]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[7]VIProtoLenInput" Type="Int">8</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[7]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[7]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[7]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[7]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[8]CallingConv" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[8]Name" Type="Str">GetFileVersion</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[8]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[8]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[8]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[8]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[8]VIProtoName" Type="Str">len2</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[8]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfo[8]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!%'!`!!%!%)#!!!!!!!!!!*!!I!!!!)!!E!!!!!!!!!!!!!!!!!#1!!$E!Q`````Q21982I!!!%!!!!"!!!!!1!!!!91$$`````$E:J&lt;'67:8*T;7^O4X6U!!"?1(!!"U51!!!!!A!!!!!!!!!!!!!!!!!!!!!!!!!%+&amp;GA1V)&gt;2@7PFU-C3'K_*A!!!!'S?5\TQ,92U*/=!##P;/C4!!!!!1!!!!!26&amp;-O37ZQ&gt;824&gt;(*F97UA;7Y!"!!!!!J!!Q6*&lt;G2F?!!31!-.28*S&lt;X*&amp;&lt;H6N)'^V&gt;!!%!!!!"!!!!!1!!!!%!!!!"!!!!!1!!!!71$$`````$%6S=G^S48.H)'^V&gt;!!</Property>
				<Property Name="Source[30].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">9</Property>
				<Property Name="Source[30].itemID" Type="Ref">/My Computer/TextTranslator/TextGetFileVersion.vi</Property>
				<Property Name="Source[30].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[30].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[30].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[30].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[30].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[30].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[30].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[30].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[30].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[31].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">7</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">Index</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Path</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">5</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">FileFormatVersionOut</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">ErrorEnumIn</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">8</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[7]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[7]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[7]VIProtoLenInput" Type="Int">8</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[7]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[7]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[7]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[7]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[8]CallingConv" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[8]Name" Type="Str">GetFileFormatVersion</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[8]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[8]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[8]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[8]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[8]VIProtoName" Type="Str">len2</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[8]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfo[8]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfoCPTM" Type="Bin">#1#!!!!!!!A!8E"Q!!="!Q!!!!'S?5\TQ,92U*/=!##P;/C4!!!!!A!!!!!!!!!!!!!!!!!!!!!!!!!%+&amp;GA1V)&gt;2@7PFU-C3'K_*A!!!!%!!!!!%624,EFO=(6U5X2S:7&amp;N)'FO!!Z!-0````]%5'&amp;U;!!!"!!!!"Z!-0````]62GFM:5:P=GVB&gt;&amp;:F=H.J&lt;WYA&lt;X6U!!N!!Q!&amp;37ZE:8A!%U!$!!R&amp;=H*P=E6O&gt;7UA;7Y!!":!-0````]-28*S&lt;X*.=W=A&lt;X6U!!"-!0!!%!!!!!%!!A!#!!-!!A!#!!1!"1!#!!)!!A!#!!)!!A!'!Q!"#!A!#!!!!!!!#1!!!!!!#!!*!!!!!!!!!!!!!!!!!!E!!!!!!1!(</Property>
				<Property Name="Source[31].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">9</Property>
				<Property Name="Source[31].itemID" Type="Ref">/My Computer/TextTranslator/TextGetFileFormatVersion.vi</Property>
				<Property Name="Source[31].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[31].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[31].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[31].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[31].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[31].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[31].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[31].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[31].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[32].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">index</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">3</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Extension</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">8</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">6</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[6]CallingConv" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[6]Name" Type="Str">GetExtension</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">len2</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!#=!P!!%!%)#!!!!!!!!!!*!!!!!!!!!!E!!!!!!!!!!!!!!!!!#1!!#E!$"7FO:'6Y!!1!!!!%!!!!"!!!!"*!-0````]*28BU:7ZT;7^O!!1!!!!%!!!!"!!!!"*!!QV&amp;=H*P=E6O&gt;7UA&lt;X6U!!1!!!!%!!!!"!!!!!1!!!!%!!!!"!!!!":!-0````]-28*S&lt;X*.=W=A&lt;X6U!!</Property>
				<Property Name="Source[32].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">7</Property>
				<Property Name="Source[32].itemID" Type="Ref">/My Computer/TextTranslator/TextGetExtension.vi</Property>
				<Property Name="Source[32].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[32].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[32].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[32].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[32].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[32].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[32].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[32].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[32].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[33].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">index</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">3</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Description</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">8</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">6</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[6]CallingConv" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[6]Name" Type="Str">GetDescription</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">len2</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!#?!P!!%!%)#!!!!!!!!!!*!!!!!!!!!!E!!!!!!!!!!!!!!!!!#1!!#E!$"7FO:'6Y!!1!!!!%!!!!"!!!!"2!-0````],2'6T9X*J=(2J&lt;WY!"!!!!!1!!!!%!!!!%E!$$56S=G^S27ZV&lt;3"P&gt;81!"!!!!!1!!!!%!!!!"!!!!!1!!!!%!!!!&amp;E!Q`````QR&amp;=H*P=EVT:S"P&gt;81!</Property>
				<Property Name="Source[33].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">7</Property>
				<Property Name="Source[33].itemID" Type="Ref">/My Computer/TextTranslator/TextGetDescription.vi</Property>
				<Property Name="Source[33].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[33].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[33].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[33].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[33].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[33].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[33].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[33].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[33].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[34].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">5</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">extension</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">index</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">6</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">10</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">6</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[6]CallingConv" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[6]Name" Type="Str">CanTranslate</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!%%!`!!%!%)#A!!!!!!!!!*!!A!#1!!!!!!!!!*!!!!!!!!!!!!#1!!8E"Q!!&gt;&amp;%!!!!!)!!!!!!!!!!!!!!!!!!!!!!!!!"#B:I%.3(58VLZ&gt;$)EBKPC9!!!!"MHF/]]#W%&gt;#4H!!ALWDIEQ!!!!%!!!!!%624,EFO=(6U5X2S:7&amp;N)'FO!!1!!!!%!!!!"!!!!"*!!QR$97Z5=G&amp;O=WRB&gt;'5!!"*!-0````]*:8BU:7ZT;7^O!!J!!Q6J&lt;G2F?!!%!!!!"!!!!!1!!!!31!-.28*S&lt;X*&amp;&lt;H6N)'^V&gt;!!%!!!!"!!!!!1!!!!%!!!!&amp;E!Q`````QR&amp;=H*P=EVT:S"P&gt;81!</Property>
				<Property Name="Source[34].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">7</Property>
				<Property Name="Source[34].itemID" Type="Ref">/My Computer/TextTranslator/TextCanTranslate.vi</Property>
				<Property Name="Source[34].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[34].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[34].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[34].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[34].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[34].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[34].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[34].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[34].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[35].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfo[0]CallingConv" Type="Int">1</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfo[0]Name" Type="Str">GetTranslatorCount</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">8</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!#!!P!!%!%)!!!!!!!!!!!!!!!!!!!!!!E!!!!!!!!!!!!!!!!!!!!!"!!!!!1!!!!%!!!!"!!!!!1!!!!%!!!!"!!!!!1!!!!=1!-74H6N9G6S)%^G)&amp;2S97ZT&lt;'&amp;U;7^O=Q!!"!!!!!1!!!!%!!!!"!!!!!1!!!!%!!!!"!!!</Property>
				<Property Name="Source[35].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">1</Property>
				<Property Name="Source[35].itemID" Type="Ref">/My Computer/TextTranslator/TextGetTranslatorCount.vi</Property>
				<Property Name="Source[35].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[35].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[35].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[35].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[35].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[35].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[35].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[35].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[35].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextProcessReportProperty.vi</Property>
				<Property Name="Source[4].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[4].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[4].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[4].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[4].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[4].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[4].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[4].type" Type="Str">VI</Property>
				<Property Name="Source[5].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextAddReportProperty.vi</Property>
				<Property Name="Source[5].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[5].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[5].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[5].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[5].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[5].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[5].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[5].type" Type="Str">VI</Property>
				<Property Name="Source[6].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextCreateLocalReportval.vi</Property>
				<Property Name="Source[6].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[6].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[6].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[6].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[6].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[6].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[6].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[6].type" Type="Str">VI</Property>
				<Property Name="Source[7].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextSetPostStepExpr.vi</Property>
				<Property Name="Source[7].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[7].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[7].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[7].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[7].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[7].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[7].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[7].type" Type="Str">VI</Property>
				<Property Name="Source[8].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextAddUsedTypes.vi</Property>
				<Property Name="Source[8].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[8].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[8].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[8].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[8].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[8].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[8].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[8].type" Type="Str">VI</Property>
				<Property Name="Source[9].itemID" Type="Ref">/My Computer/TextTranslator/HelperVIsforTextTranslator.llb/TextProcessStepProperties.vi</Property>
				<Property Name="Source[9].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[9].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[9].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[9].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[9].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[9].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[9].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[9].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">36</Property>
				<Property Name="TgtF_companyName" Type="Str">[Your Company Here]
</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">[Your Copyright Here]
</Property>
				<Property Name="TgtF_productName" Type="Str">
				</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{CA704940-8F40-4F9D-A2CD-F0E0906ACF19}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">LabVIEWTextTranslator.dll</Property>
				<Property Name="TgtF_fileVersion.major" Type="Int">14</Property>
				<Property Name="TgtF_fileVersion.minor" Type="Int">0</Property>
				<Property Name="TgtF_fileVersion.patch" Type="Int">1</Property>
				<Property Name="TgtF_fileVersion.build" Type="Int">103</Property>
</Item>
		</Item>
	</Item>
</Project>

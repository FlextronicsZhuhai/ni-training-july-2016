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
		<Item Name="XMLTranslator" Type="Folder">
			<Item Name="XMLCanTranslate.vi" Type="VI" URL="../XMLCanTranslate.vi"/>
			<Item Name="XMLGetDescription.vi" Type="VI" URL="../XMLGetDescription.vi"/>
			<Item Name="XMLGetExtension.vi" Type="VI" URL="../XMLGetExtension.vi"/>
			<Item Name="XMLGetFileFormatVersion.vi" Type="VI" URL="../XMLGetFileFormatVersion.vi"/>
			<Item Name="XMLGetFileVersion.vi" Type="VI" URL="../XMLGetFileVersion.vi"/>
			<Item Name="XMLTranslateToSequenceFile.vi" Type="VI" URL="../XMLTranslateToSequenceFile.vi"/>
			<Item Name="XMLIsCurrentFileVersion.vi" Type="VI" URL="../XMLIsCurrentFileVersion.vi"/>
			<Item Name="XMLGetTranslatorCount.vi" Type="VI" URL="../XMLGetTranslatorCount.vi"/>
		</Item>
		<Item Name="Support" Type="Folder">
			<Item Name="XMLarrayglobal.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/XMLarrayglobal.vi"/>
			<Item Name="XMLGetAttributeVal.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/XMLGetAttributeVal.vi"/>
			<Item Name="XMLAddUsedTypes.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/XMLAddUsedTypes.vi"/>
			<Item Name="XMLLoadTypePalettes.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/XMLLoadTypePalettes.vi"/>
			<Item Name="StreamToXML.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/StreamToXML.vi"/>
			<Item Name="createSeqFileFromData.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/createSeqFileFromData.vi"/>
			<Item Name="Read Steps From File - XML.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/Read Steps From File - XML.vi"/>
			<Item Name="TestStand API - SetSequenceFileProperties.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/TestStand API - SetSequenceFileProperties.vi"/>
			<Item Name="TestStand API - NewSequence.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/TestStand API - NewSequence.vi"/>
			<Item Name="TestStand API - NewStep.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/TestStand API - NewStep.vi"/>
			<Item Name="TestStand API - SetStepProperties.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/TestStand API - SetStepProperties.vi"/>
			<Item Name="TestStand API - InsertSequenceIntoFile.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/TestStand API - InsertSequenceIntoFile.vi"/>
			<Item Name="TestStand API - InsertStepIntoSequence.vi" Type="VI" URL="../HelperVIsforXMLTranslator.llb/TestStand API - InsertStepIntoSequence.vi"/>
		</Item>
		<Item Name="TypeDefs" Type="Folder">
			<Item Name="SequenceData.ctl" Type="VI" URL="../HelperVIsforXMLTranslator.llb/SequenceData.ctl"/>
			<Item Name="StepGroup.ctl" Type="VI" URL="../HelperVIsforXMLTranslator.llb/StepGroup.ctl"/>
			<Item Name="StepData.ctl" Type="VI" URL="../HelperVIsforXMLTranslator.llb/StepData.ctl"/>
			<Item Name="StepProperties.ctl" Type="VI" URL="../HelperVIsforXMLTranslator.llb/StepProperties.ctl"/>
			<Item Name="SequenceFileData.ctl" Type="VI" URL="../HelperVIsforXMLTranslator.llb/SequenceFileData.ctl"/>
		</Item>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="TestStand API Numeric Constants.ctl" Type="VI" URL="/&lt;vilib&gt;/addons/TestStand/_TSUtility.llb/TestStand API Numeric Constants.ctl"/>
				<Item Name="TestStand API Numeric Constants.vi" Type="VI" URL="/&lt;vilib&gt;/addons/TestStand/_TSUtility.llb/TestStand API Numeric Constants.vi"/>
				<Item Name="NI_XML.lvlib" Type="Library" URL="/&lt;vilib&gt;/xml/NI_XML.lvlib"/>
			</Item>
			<Item Name="DOMUserDefRef.dll" Type="Document" URL="DOMUserDefRef.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="LabVIEWXMLTranslator" Type="DLL">
				<Property Name="App_INI_aliasGUID" Type="Str">{B16A7486-DC3D-4319-82DD-8EB87E8BEEC8}</Property>
				<Property Name="App_INI_GUID" Type="Str">{2BCD8578-6969-4394-B0C4-C3F6961AB741}</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{72B89BCD-4B0E-4183-A269-5B7560F2F8DE}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">LabVIEWXMLTranslator</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeTypedefs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../XMLTranslator</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{E4922E3F-4DA9-4A76-8FB1-800F40CA5256}</Property>
				<Property Name="Destination[0].destName" Type="Str">LabVIEWXMLTranslator.dll</Property>
				<Property Name="Destination[0].path" Type="Path">../XMLTranslator/LabVIEWXMLTranslator.dll</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">XMLTranslator</Property>
				<Property Name="Destination[1].path" Type="Path">../XMLTranslator</Property>
				<Property Name="Destination[2].destName" Type="Str">DestinationDirectory</Property>
				<Property Name="Destination[2].path" Type="Path">../XMLTranslator</Property>
				<Property Name="Destination[3].destName" Type="Str">data.llb</Property>
				<Property Name="Destination[3].path" Type="Path">../XMLTranslator/data.llb</Property>
				<Property Name="Destination[3].type" Type="Str">LLB</Property>
				<Property Name="DestinationCount" Type="Int">4</Property>
				<Property Name="Dll_delayOSMsg" Type="Bool">true</Property>
				<Property Name="Dll_headerGUID" Type="Str">{A818BF59-FEF3-4F13-8458-B92D5578A11C}</Property>
				<Property Name="Dll_libGUID" Type="Str">{1856CA67-F4F4-43A4-9BBA-D7C60056A740}</Property>
				<Property Name="Source[0].Container.applyDestination" Type="Bool">true</Property>
				<Property Name="Source[0].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[0].Container.applyProperties" Type="Bool">true</Property>
				<Property Name="Source[0].itemID" Type="Str">{3521F1A5-DACF-4F74-AC61-F23E21D54590}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Support/StreamToXML.vi</Property>
				<Property Name="Source[1].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[1].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[1].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[1].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[1].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[1].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[1].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[10].itemID" Type="Ref"></Property>
				<Property Name="Source[10].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[10].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[10].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[10].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[10].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[10].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[10].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[10].type" Type="Str">VI</Property>
				<Property Name="Source[11].itemID" Type="Ref"></Property>
				<Property Name="Source[11].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[11].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[11].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[11].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[11].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[11].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[11].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[11].type" Type="Str">VI</Property>
				<Property Name="Source[12].itemID" Type="Ref"></Property>
				<Property Name="Source[12].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[12].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[12].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[12].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[12].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[12].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[12].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[12].type" Type="Str">VI</Property>
				<Property Name="Source[13].itemID" Type="Ref"></Property>
				<Property Name="Source[13].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[13].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[13].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[13].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[13].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[13].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[13].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[13].type" Type="Str">VI</Property>
				<Property Name="Source[14].itemID" Type="Ref"></Property>
				<Property Name="Source[14].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[14].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[14].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[14].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[14].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[14].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[14].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[14].type" Type="Str">VI</Property>
				<Property Name="Source[15].itemID" Type="Ref"></Property>
				<Property Name="Source[15].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[15].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[15].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[15].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[15].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[15].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[15].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[15].type" Type="Str">VI</Property>
				<Property Name="Source[16].itemID" Type="Ref"></Property>
				<Property Name="Source[16].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[16].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[16].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[16].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[16].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[16].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[16].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[16].type" Type="Str">VI</Property>
				<Property Name="Source[17].itemID" Type="Ref"></Property>
				<Property Name="Source[17].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[17].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[17].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[17].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[17].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[17].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[17].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[17].type" Type="Str">VI</Property>
				<Property Name="Source[18].itemID" Type="Ref"></Property>
				<Property Name="Source[18].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[18].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[18].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[18].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[18].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[18].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[18].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[18].type" Type="Str">VI</Property>
				<Property Name="Source[19].itemID" Type="Ref"></Property>
				<Property Name="Source[19].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[19].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[19].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[19].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[19].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[19].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[19].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[19].type" Type="Str">VI</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/Support/XMLarrayglobal.vi</Property>
				<Property Name="Source[2].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[2].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[2].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[2].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[2].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[2].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[2].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[20].itemID" Type="Ref"></Property>
				<Property Name="Source[20].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[20].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[20].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[20].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[20].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[20].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[20].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[20].type" Type="Str">VI</Property>
				<Property Name="Source[21].itemID" Type="Ref"></Property>
				<Property Name="Source[21].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[21].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[21].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[21].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[21].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[21].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[21].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[21].type" Type="Str">VI</Property>
				<Property Name="Source[22].itemID" Type="Ref"></Property>
				<Property Name="Source[22].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[22].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[22].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[22].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[22].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[22].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[22].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[22].type" Type="Str">VI</Property>
				<Property Name="Source[23].itemID" Type="Ref"></Property>
				<Property Name="Source[23].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[23].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[23].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[23].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[23].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[23].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[23].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[23].type" Type="Str">VI</Property>
				<Property Name="Source[24].itemID" Type="Ref"></Property>
				<Property Name="Source[24].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[24].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[24].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[24].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[24].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[24].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[24].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[24].type" Type="Str">VI</Property>
				<Property Name="Source[25].itemID" Type="Ref"></Property>
				<Property Name="Source[25].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[25].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[25].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[25].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[25].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[25].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[25].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[25].type" Type="Str">VI</Property>
				<Property Name="Source[26].itemID" Type="Ref"></Property>
				<Property Name="Source[26].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[26].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[26].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[26].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[26].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[26].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[26].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[26].type" Type="Str">VI</Property>
				<Property Name="Source[27].itemID" Type="Ref"></Property>
				<Property Name="Source[27].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[27].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[27].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[27].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[27].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[27].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[27].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[27].type" Type="Str">VI</Property>
				<Property Name="Source[28].itemID" Type="Ref"></Property>
				<Property Name="Source[28].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[28].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[28].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[28].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[28].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[28].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[28].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[28].type" Type="Str">VI</Property>
				<Property Name="Source[29].itemID" Type="Ref"></Property>
				<Property Name="Source[29].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[29].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[29].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[29].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[29].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[29].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[29].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[29].type" Type="Str">VI</Property>
				<Property Name="Source[3].itemID" Type="Ref"></Property>
				<Property Name="Source[3].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[3].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[3].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[3].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[3].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[3].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[3].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="Source[30].itemID" Type="Ref"></Property>
				<Property Name="Source[30].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[30].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[30].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[30].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[30].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[30].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[30].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[30].type" Type="Str">VI</Property>
				<Property Name="Source[31].itemID" Type="Ref"></Property>
				<Property Name="Source[31].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[31].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[31].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[31].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[31].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[31].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[31].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[31].type" Type="Str">VI</Property>
				<Property Name="Source[32].itemID" Type="Ref"></Property>
				<Property Name="Source[32].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[32].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[32].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[32].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[32].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[32].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[32].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[32].type" Type="Str">VI</Property>
				<Property Name="Source[33].itemID" Type="Ref"></Property>
				<Property Name="Source[33].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[33].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[33].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[33].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[33].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[33].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[33].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[33].type" Type="Str">VI</Property>
				<Property Name="Source[34].itemID" Type="Ref"></Property>
				<Property Name="Source[34].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[34].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[34].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[34].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[34].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[34].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[34].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[34].type" Type="Str">VI</Property>
				<Property Name="Source[35].itemID" Type="Ref"></Property>
				<Property Name="Source[35].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[35].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[35].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[35].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[35].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[35].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[35].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[35].type" Type="Str">VI</Property>
				<Property Name="Source[36].itemID" Type="Ref">/My Computer/Support/XMLLoadTypePalettes.vi</Property>
				<Property Name="Source[36].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[36].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[36].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[36].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[36].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[36].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[36].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[36].type" Type="Str">VI</Property>
				<Property Name="Source[37].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">5</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">Extension</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">indexOut</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">6</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">8</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">6</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[6]CallingConv" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[6]Name" Type="Str">CanTranslate</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!%)!`!!%!%)#A!!!!!!!!!*!!A!#1!!!!E!!!!!!!!!!!!!!!!!#1!!8E"Q!!&gt;&amp;%!!!!!)!!!!!!!!!!!!!!!!!!!!!!!!!"#B:I%.3(58VLZ&gt;$)EBKPC9!!!!"MHF/]]#W%&gt;#4H!!ALWDIEQ!!!!%!!!!!%624,EFO=(6U5X2S:7&amp;N)'FO!!1!!!!%!!!!"!!!!"*!!QRD97Z5=G&amp;O=WRB&gt;'5!!"*!-0````]*28BU:7ZT;7^O!!Z!!QFJ&lt;G2F?#"P&gt;81!"!!!!"*!!QV&amp;=H*P=E6O&gt;7UA&lt;X6U!!1!!!!%!!!!"!!!!!1!!!!%!!!!"!!!!":!-0````]-28*S&lt;X*.=W=A&lt;X6U!!</Property>
				<Property Name="Source[37].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">7</Property>
				<Property Name="Source[37].itemID" Type="Ref">/My Computer/XMLTranslator/XMLCanTranslate.vi</Property>
				<Property Name="Source[37].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[37].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[37].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[37].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[37].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[37].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[37].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[37].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[37].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[38].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">index</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">3</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Description</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">10</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">6</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[6]CallingConv" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[6]Name" Type="Str">GetDescription</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">len2</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!#?!P!!%!%)#!!!!!!!!!!*!!!!!!!!!!!!!!!*!!!!!!!!!!!!#1!!#E!$"7FO:'6Y!!1!!!!%!!!!"!!!!"2!-0````],2'6T9X*J=(2J&lt;WY!"!!!!!1!!!!%!!!!"!!!!!1!!!!31!-.28*S&lt;X*&amp;&lt;H6N)'^V&gt;!!%!!!!"!!!!!1!!!!%!!!!&amp;E!Q`````QR&amp;=H*P=EVT:S"P&gt;81!</Property>
				<Property Name="Source[38].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">7</Property>
				<Property Name="Source[38].itemID" Type="Ref">/My Computer/XMLTranslator/XMLGetDescription.vi</Property>
				<Property Name="Source[38].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[38].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[38].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[38].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[38].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[38].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[38].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[38].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[38].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[39].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">index</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">3</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Extension</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">10</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">6</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[6]CallingConv" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[6]Name" Type="Str">GetExtension</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">len2</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!#=!P!!%!%)#!!!!!!!!!!*!!!!!!!!!!!!!!!*!!!!!!!!!!!!#1!!#E!$"7FO:'6Y!!1!!!!%!!!!"!!!!"*!-0````]*28BU:7ZT;7^O!!1!!!!%!!!!"!!!!!1!!!!%!!!!%E!$$56S=G^S27ZV&lt;3"P&gt;81!"!!!!!1!!!!%!!!!"!!!!":!-0````]-28*S&lt;X*.=W=A&lt;X6U!!</Property>
				<Property Name="Source[39].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">7</Property>
				<Property Name="Source[39].itemID" Type="Ref">/My Computer/XMLTranslator/XMLGetExtension.vi</Property>
				<Property Name="Source[39].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[39].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[39].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[39].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[39].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[39].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[39].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[39].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[39].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[4].itemID" Type="Ref"></Property>
				<Property Name="Source[4].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[4].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[4].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[4].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[4].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[4].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[4].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[4].type" Type="Str">VI</Property>
				<Property Name="Source[40].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">7</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">Index</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Path</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">5</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">5</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">FileFormatVersionOut</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">10</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[7]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[7]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[7]VIProtoLenInput" Type="Int">8</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[7]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[7]VIProtoName" Type="Str">ErrMsgOut</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[7]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[7]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[8]CallingConv" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[8]Name" Type="Str">GetFileFormatVersion</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[8]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[8]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[8]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[8]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[8]VIProtoName" Type="Str">len2</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[8]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfo[8]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!%+!`!!%!%)#!!!!!!!!!!*!!I!!!!)!!!!!!!*!!!!!!!!!!!!#1!!$E!Q`````Q21982I!!!%!!!!"!!!!!1!!!!?1$$`````&amp;5:J&lt;'6'&lt;X*N9827:8*T;7^O)'^V&gt;!"?1(!!"U51!!!!!A!!!!!!!!!!!!!!!!!!!!!!!!!%+&amp;GA1V)&gt;2@7PFU-C3'K_*A!!!!'S?5\TQ,92U*/=!##P;/C4!!!!!1!!!!!26&amp;-O37ZQ&gt;824&gt;(*F97UA;7Y!"!!!!!J!!Q6*&lt;G2F?!!%!!!!"!!!!"*!!QV&amp;=H*P=E6O&gt;7UA&lt;X6U!!1!!!!%!!!!"!!!!!1!!!!51$$`````#E6S=EVT:S"P&gt;81!</Property>
				<Property Name="Source[40].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">9</Property>
				<Property Name="Source[40].itemID" Type="Ref">/My Computer/XMLTranslator/XMLGetFileFormatVersion.vi</Property>
				<Property Name="Source[40].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[40].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[40].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[40].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[40].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[40].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[40].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[40].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[40].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[41].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">7</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">Index</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Path</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">5</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">5</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">FileVersionOut</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">8</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">10</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[7]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[7]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[7]VIProtoLenInput" Type="Int">8</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[7]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[7]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[7]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[7]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[8]CallingConv" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[8]Name" Type="Str">GetFileVersion</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[8]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[8]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[8]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[8]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[8]VIProtoName" Type="Str">len2</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[8]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfo[8]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!%'!`!!%!%)#!!!!!!!!!!!!!I!!!!)!!E!!!!*!!!!!!!!!!!!#1!!$E!Q`````Q21982I!!!%!!!!"!!!!!1!!!!%!!!!8E"Q!!&gt;&amp;%!!!!!)!!!!!!!!!!!!!!!!!!!!!!!!!"#B:I%.3(58VLZ&gt;$)EBKPC9!!!!"MHF/]]#W%&gt;#4H!!ALWDIEQ!!!!%!!!!!%624,EFO=(6U5X2S:7&amp;N)'FO!!1!!!!+1!-&amp;37ZE:8A!'%!Q`````Q^';7RF6G6S=WFP&lt;C"P&gt;81!"!!!!"*!!QV&amp;=H*P=E6O&gt;7UA&lt;X6U!!1!!!!%!!!!"!!!!!1!!!!71$$`````$%6S=G^S48.H)'^V&gt;!!</Property>
				<Property Name="Source[41].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">9</Property>
				<Property Name="Source[41].itemID" Type="Ref">/My Computer/XMLTranslator/XMLGetFileVersion.vi</Property>
				<Property Name="Source[41].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[41].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[41].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[41].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[41].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[41].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[41].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[41].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[41].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[42].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">7</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">TranslationIndex</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">TSIEngineIn</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">5</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">9</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">TSSequenceFileIn</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">10</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">7</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[7]CallingConv" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[7]Name" Type="Str">TranslateToSequenceFile</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[7]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[7]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[7]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[7]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[7]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[7]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfo[7]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!'G!`!!%!%)#A!!!!!!!!!!!!I!!!!)!!!!#A!*!!!!!!!!!!!!#1!!7E"Q!!&gt;&amp;%!!!!!+S?5\WQ,92U*/=!##P;/C4!!!!",*Z4P8!NB(1EZQ!)+^I[*-!!!!"MHF/]]#W%&gt;#4H!!ALWDIEQ!!!!%!!!!!$624,EF&amp;&lt;G&gt;J&lt;G5A;7Y!"!!!!!1!!!!%!!!!"!!!!&amp;Z!=!!(22!!!!!#!!!!!!!!!!!!!!!!!!!!!!!!!!1I7;"$5BV&amp;^;_81S*);LYG!!!!!&lt;*Z4P0!NB(1EZQ!)+^I[*-!!!!"!!!!!"&amp;55SZ*&lt;H"V&gt;&amp;.U=G6B&lt;3"J&lt;A!%!!!!&amp;E!$%&amp;2S97ZT&lt;'&amp;U;7^O37ZE:8A!!!1!!!"A1(!!"U51!!!!!A!!!!!!!!!!!!!!!!!!!!!!!!!%MHF/_=#W%&gt;#4H!!ALWDIEQ!!!!'S?5\TQ,92U*/=!##P;/C4!!!!!1!!!!!36&amp;-O5W6R&gt;76O9W6';7RF)'FO!!!31!-.28*S&lt;X*&amp;&lt;H6N)'^V&gt;!!%!!!!"!!!!!1!!!!%!!!!&amp;E!Q`````QR&amp;=H*P=EVT:S"P&gt;81!</Property>
				<Property Name="Source[42].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">8</Property>
				<Property Name="Source[42].itemID" Type="Ref">/My Computer/XMLTranslator/XMLTranslateToSequenceFile.vi</Property>
				<Property Name="Source[42].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[42].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[42].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[42].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[42].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[42].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[42].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[42].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[42].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[43].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[1]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[1]VIProtoInputIdx" Type="Int">9</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[1]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[1]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[1]VIProtoName" Type="Str">Index</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[1]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[1]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[2]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[2]VIProtoInputIdx" Type="Int">0</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[2]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[2]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[2]VIProtoName" Type="Str">Path</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[2]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[2]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[3]VIProtoDir" Type="Int">0</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[3]VIProtoInputIdx" Type="Int">5</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[3]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[3]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[3]VIProtoName" Type="Str">TSInputStreamIn</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[3]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[3]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[4]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[4]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[4]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[4]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[4]VIProtoName" Type="Str">ErrorEnumOut</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[4]VIProtoOutputIdx" Type="Int">15</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[4]VIProtoPassBy" Type="Int">0</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[5]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[5]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[5]VIProtoLenInput" Type="Int">6</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[5]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[5]VIProtoName" Type="Str">ErrorMsgOut</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[5]VIProtoOutputIdx" Type="Int">14</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[5]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[6]CallingConv" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[6]Name" Type="Str">IsCurrentFileVersion</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[6]VIProtoDir" Type="Int">3</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[6]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[6]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[6]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[6]VIProtoName" Type="Str">len</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[6]VIProtoOutputIdx" Type="Int">-1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfo[6]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!%)!`!!%!%)#!!!!!!!!!!*!!I!!!!!!!!!#!!!!!!!!!!!!!E!#1!!$E!Q`````Q21982I!!!%!!!!"!!!!!1!!!!;1!-538.$&gt;8*S:7ZU2GFM:6:F=H.J&lt;WY!!&amp;Z!=!!(22!!!!!#!!!!!!!!!!!!!!!!!!!!!!!!!!1I7;"$5BV&amp;^;_81S*);LYG!!!!!&lt;*Z4P0!NB(1EZQ!)+^I[*-!!!!"!!!!!"&amp;55SZ*&lt;H"V&gt;&amp;.U=G6B&lt;3"J&lt;A!%!!!!"!!!!!1!!!!+1!-&amp;37ZE:8A!"!!!!!1!!!!%!!!!"!!!!":!-0````]-28*S&lt;X*.=W=A&lt;X6U!!!31!-.28*S&lt;X*&amp;&lt;H6N)'^V&gt;!</Property>
				<Property Name="Source[43].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">7</Property>
				<Property Name="Source[43].itemID" Type="Ref">/My Computer/XMLTranslator/XMLIsCurrentFileVersion.vi</Property>
				<Property Name="Source[43].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[43].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[43].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[43].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[43].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[43].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[43].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[43].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[43].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[44].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfo[0]CallingConv" Type="Int">1</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfo[0]Name" Type="Str">GetTranslatorCount</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfo[0]VIProtoDir" Type="Int">1</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfo[0]VIProtoInputIdx" Type="Int">-1</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfo[0]VIProtoLenInput" Type="Int">-1</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfo[0]VIProtoLenOutput" Type="Int">-1</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfo[0]VIProtoName" Type="Str">return value</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfo[0]VIProtoOutputIdx" Type="Int">4</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfo[0]VIProtoPassBy" Type="Int">1</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfoCPTM" Type="Bin">"R#!!!#!!P!!%!%)!!!!!!!!!!!*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"!!!!!1!!!!%!!!!"!!!!"R!!R:/&gt;7VC:8)A4W9A6(*B&lt;H.M982J&lt;WZT!!!%!!!!"!!!!!1!!!!%!!!!"!!!!!1!!!!%!!!!"!!!!!1!!!!%!!!!"!!!</Property>
				<Property Name="Source[44].ExportedVI.VIProtoInfoVIProtoItemCount" Type="Int">1</Property>
				<Property Name="Source[44].itemID" Type="Ref">/My Computer/XMLTranslator/XMLGetTranslatorCount.vi</Property>
				<Property Name="Source[44].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[44].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[44].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[44].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[44].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[44].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[44].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[44].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[44].type" Type="Str">ExportedVI</Property>
				<Property Name="Source[5].itemID" Type="Ref"></Property>
				<Property Name="Source[5].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[5].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[5].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[5].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[5].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[5].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[5].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[5].type" Type="Str">VI</Property>
				<Property Name="Source[6].itemID" Type="Ref"></Property>
				<Property Name="Source[6].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[6].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[6].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[6].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[6].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[6].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[6].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[6].type" Type="Str">VI</Property>
				<Property Name="Source[7].itemID" Type="Ref"></Property>
				<Property Name="Source[7].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[7].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[7].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[7].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[7].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[7].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[7].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[7].type" Type="Str">VI</Property>
				<Property Name="Source[8].itemID" Type="Ref"></Property>
				<Property Name="Source[8].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[8].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[8].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[8].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[8].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[8].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[8].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[8].type" Type="Str">VI</Property>
				<Property Name="Source[9].itemID" Type="Ref"></Property>
				<Property Name="Source[9].properties[0].type" Type="Str">Allow debugging</Property>
				<Property Name="Source[9].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[9].properties[1].type" Type="Str">Remove block diagram</Property>
				<Property Name="Source[9].properties[1].value" Type="Bool">true</Property>
				<Property Name="Source[9].properties[2].type" Type="Str">Show Abort button</Property>
				<Property Name="Source[9].properties[2].value" Type="Bool">false</Property>
				<Property Name="Source[9].propertiesCount" Type="Int">3</Property>
				<Property Name="Source[9].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">45</Property>
				<Property Name="TgtF_companyName" Type="Str">[Your Company Here]
</Property>
				<Property Name="TgtF_fileVersion.major" Type="Int">14
</Property>
				<Property Name="TgtF_fileVersion.minor" Type="Int">0
</Property>
				<Property Name="TgtF_fileVersion.patch" Type="Int">1
</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">[Your Copyright Here]
</Property>
				<Property Name="TgtF_productName" Type="Str">
				</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{D7AC4EA9-C41B-46E3-BB9C-78BE5B137C24}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">LabVIEWXMLTranslator.dll</Property>
				<Property Name="TgtF_fileVersion.build" Type="Int">103</Property>
</Item>
		</Item>
	</Item>
</Project>

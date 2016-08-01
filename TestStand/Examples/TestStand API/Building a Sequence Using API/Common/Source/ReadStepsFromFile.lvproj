<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="11008008">
	<Item Name="My Computer" Type="My Computer">
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
		<Item Name="subVIs" Type="Folder">
			<Property Name="NI.SortType" Type="Int">3</Property>
			<Item Name="createSeqFileFromData.vi" Type="VI" URL="../HelperVIs.llb/createSeqFileFromData.vi"/>
			<Item Name="XMLGetAttributeVal.vi" Type="VI" URL="../XMLGetAttributeVal.vi"/>
		</Item>
		<Item Name="BuildSequenceFile - XML.vi" Type="VI" URL="../BuildSequenceFile - XML.vi"/>
		<Item Name="Read Steps From File - XML.vi" Type="VI" URL="../Read Steps From File - XML.vi"/>
		<Item Name="Read Steps From File.vi" Type="VI" URL="../Read Steps From File.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="8.6CompatibleGlobalVar.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/config.llb/8.6CompatibleGlobalVar.vi"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="NI_LVConfig.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/config.llb/NI_LVConfig.lvlib"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="NI_XML.lvlib" Type="Library" URL="/&lt;vilib&gt;/xml/NI_XML.lvlib"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
			<Item Name="DOMUserDefRef.dll" Type="Document" URL="DOMUserDefRef.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="SequenceData.ctl" Type="VI" URL="../HelperVIs.llb/SequenceData.ctl"/>
			<Item Name="SequenceFileData.ctl" Type="VI" URL="../HelperVIs.llb/SequenceFileData.ctl"/>
			<Item Name="StepGroup.ctl" Type="VI" URL="../HelperVIs.llb/StepGroup.ctl"/>
			<Item Name="StepProperties.ctl" Type="VI" URL="../HelperVIs.llb/StepProperties.ctl"/>
			<Item Name="TestStand API - InsertSequenceIntoFile.vi" Type="VI" URL="../HelperVIs.llb/TestStand API - InsertSequenceIntoFile.vi"/>
			<Item Name="TestStand API - InsertStepIntoSequence.vi" Type="VI" URL="../HelperVIs.llb/TestStand API - InsertStepIntoSequence.vi"/>
			<Item Name="TestStand API - NewSequence.vi" Type="VI" URL="../HelperVIs.llb/TestStand API - NewSequence.vi"/>
			<Item Name="TestStand API - NewStep.vi" Type="VI" URL="../HelperVIs.llb/TestStand API - NewStep.vi"/>
			<Item Name="TestStand API - SetSequenceFileProperties.vi" Type="VI" URL="../HelperVIs.llb/TestStand API - SetSequenceFileProperties.vi"/>
			<Item Name="TestStand API - SetStepProperties.vi" Type="VI" URL="../HelperVIs.llb/TestStand API - SetStepProperties.vi"/>
			<Item Name="XMLAddUsedTypes.vi" Type="VI" URL="../HelperVIs.llb/XMLAddUsedTypes.vi"/>
			<Item Name="XMLLoadTypePalettes.vi" Type="VI" URL="../HelperVIs.llb/XMLLoadTypePalettes.vi"/>
			<Item Name="StepData.ctl" Type="VI" URL="../HelperVIs.llb/StepData.ctl"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="Source Distribution" Type="Source Distribution">
				<Property Name="Bld_buildCacheID" Type="Str">{26E64BBD-9EE4-4653-B5EA-4725B8CC8ACB}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Source Distribution</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../NI_AB_PROJECTNAME.llb</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{5BF7FACF-CF12-481B-A4FA-79D44DE02395}</Property>
				<Property Name="Destination[0].destName" Type="Str">Destination Directory</Property>
				<Property Name="Destination[0].path" Type="Path">../NI_AB_PROJECTNAME.llb</Property>
				<Property Name="Destination[0].type" Type="Str">LLB</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../data</Property>
				<Property Name="Destination[2].destName" Type="Str">LabVIEW Specific</Property>
				<Property Name="Destination[2].path" Type="Path">/E/p4/TestStand/Dev/6.0/App/TestStandPublic/Examples/TestStand API/Building a Sequence Using API/LabVIEW/BuildSequenceFile.llb</Property>
				<Property Name="Destination[2].path.type" Type="Str">&lt;none&gt;</Property>
				<Property Name="Destination[2].type" Type="Str">LLB</Property>
				<Property Name="DestinationCount" Type="Int">3</Property>
				<Property Name="Source[0].Container.applyPrefix" Type="Bool">true</Property>
				<Property Name="Source[0].itemID" Type="Str">{49FF9568-E002-4118-AE59-15559AC8EF74}</Property>
				<Property Name="Source[0].newName" Type="Str">ReadStepsFromFile - </Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Read Steps From File - XML.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[1].VI.LLBtopLevel" Type="Bool">true</Property>
				<Property Name="Source[2].Container.applyPrefix" Type="Bool">true</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/subVIs</Property>
				<Property Name="Source[2].newName" Type="Str">ReadStepsFromFile - </Property>
				<Property Name="Source[2].type" Type="Str">Container</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">2</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/BuildSequenceFile - XML.vi</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/Read Steps From File.vi</Property>
				<Property Name="Source[4].newName" Type="Str">Read Steps From File - INI.vi</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">5</Property>
			</Item>
		</Item>
	</Item>
</Project>

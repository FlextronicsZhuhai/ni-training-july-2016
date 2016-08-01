<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="12008004">
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
		<Item Name="ChooseClassDialog.vi" Type="VI" URL="../ChooseClassDialog.vi"/>
		<Item Name="Demo.vi" Type="VI" URL="../Demo.vi"/>
		<Item Name="DMM.lvclass" Type="LVClass" URL="../DMM Base/DMM.lvclass"/>
		<Item Name="PCI-4070.lvclass" Type="LVClass" URL="../PCI-4070/PCI-4070.lvclass"/>
		<Item Name="Simulated DMM.lvclass" Type="LVClass" URL="../Simulated DMM/Simulated DMM.lvclass"/>
		<Item Name="Open Reference (Simulate).vi" Type="VI" URL="../simulated hardware driver/Open Reference (Simulate).vi"/>
		<Item Name="Close Reference (Simulate).vi" Type="VI" URL="../Simulated Hardware Driver/Close Reference (Simulate).vi"/>
		<Item Name="DMM Read (Simulate).vi" Type="VI" URL="../Simulated Hardware Driver/DMM Read (Simulate).vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>

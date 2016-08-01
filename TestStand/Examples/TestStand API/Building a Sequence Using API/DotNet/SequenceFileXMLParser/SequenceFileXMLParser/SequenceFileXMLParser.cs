using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml;
using System.IO;
using System.Text;
using System.Xml.Serialization;
using NationalInstruments.TestStand.Interop.API;

namespace SequenceFileXMLParser
{
	public class SequenceFileXMLParserClass
	{
		
		//Define classes to define basic data for a sequence file.  
		//These classes are used with the XML Serializer to read data from an XML file and translate it into a runnable sequence file.
		public class PropData
		{
			[XmlAttribute]
			public string LookupString;
			[XmlText]
			public string Value;

			public PropData() { }
			public PropData(string propLookupString, string propValue)
			{
				LookupString = propLookupString;
				Value = propValue;
			}

		}
		
		public class StepData
		{
			[XmlAttribute]
			public string Name;
			[XmlAttribute]
			public string Type;
			[XmlAttribute]
			public string Adapter;
			[XmlElement("Prop")]
			public List<PropData> stepProps = new List<PropData>();

			public StepData() { }
			public StepData(string stepName, string stepType, string stepAdapter)
			{
				Name = stepName;
				Type = stepType;
				Adapter = stepAdapter;
			}
		}

		public enum StepGroupName { setup, main, cleanup };
		public class StepGroupData
		{
			[XmlAttribute]

			public StepGroupName Name;
			[XmlElement("Step")]
			public List<StepData> steps = new List<StepData>();

			public StepGroupData() { }
			public StepGroupData(StepGroupName groupName)
			{
				Name = groupName;
			}
		}

		public class SequenceData
		{
			[XmlAttribute]
			public string Name;
			[XmlElement("StepGroup")]
			public StepGroupData[] stepGroups = new StepGroupData[3];
			public SequenceData() { }
			public SequenceData(string seqname)
			{
				Name = seqname;
				stepGroups[0] = new StepGroupData(StepGroupName.setup);
				stepGroups[1] = new StepGroupData(StepGroupName.main);
				stepGroups[2] = new StepGroupData(StepGroupName.cleanup);
			}

		}

		[XmlRootAttribute("SequenceFile")]
		public class SequenceFileData
		{
			[XmlAttribute]
			public string Name;
			[XmlElement("Sequence")]
			public List<SequenceData> sequences = new List<SequenceData>();
		}

		private SequenceContext seqContext;
		private Engine engine;
		private SequenceFile newSeqFile;

		public string parserXMLFilePath;


		//Constructor.  Stores sequenceContext and XMLFilePath for use by methods.  
		//Also creates a new sequence file which is released in the destructor.
		//Note: if no path is provided, the method launches the TestStand file dialog box to get the XML file location.
		public SequenceFileXMLParserClass(SequenceContext thisContext, out bool cancel, string XMLFilePath = "")
		{
			cancel = false;
			
			seqContext = thisContext;
			engine = seqContext.Engine;
			newSeqFile = engine.NewSequenceFile();

			if (XMLFilePath == "")
			{
				string[] selectedPaths;
				string[] absPaths;

				if (engine.DisplayFileDialog("Select an XML File to Convert", "Open", Path.GetDirectoryName(Path.GetDirectoryName(seqContext.SequenceFile.Path)) + "\\Common\\SampleSequenceData.xml", out selectedPaths, out absPaths, 0x82, "xml", 4100, "XML Files (*.xml)|*.xml||"))
					XMLFilePath = absPaths[0];
				else
				{
					cancel = true;
					return;
				}
			}
			parserXMLFilePath = XMLFilePath;
		}

		//Release the sequence file upon class destruction.
		~SequenceFileXMLParserClass()
		{
			engine.ReleaseSequenceFileEx(newSeqFile, 0);
		}

		//Deserializes the data in the XML file.  Obtains the SequenceFileData object used by the build method.
		public SequenceFileData deserializeXMLFile()
		{
				XmlSerializer serializer = new XmlSerializer(typeof(SequenceFileData));
				FileStream fs = new FileStream(parserXMLFilePath, FileMode.Open);
				return (SequenceFileData)serializer.Deserialize(fs);
		}

		//Translates a deserialized XML file into a TestStand sequence file, and returns a COM reference to this sequence file.
		//This file is released by the destructor for this class
		public void buildSequenceFileFromXMLData(SequenceFileData seqFileData)
		{
			//Iterate over each sequence in the sequence file data.
			foreach (SequenceData currentSeq in seqFileData.sequences)
			{
				Sequence newSeq;
				
				//New sequence files have MainSequence by default, so do not create it if the current sequence is MainSequence.
				if (currentSeq.Name == "MainSequence")
				{
					newSeq = newSeqFile.GetSequenceByName("MainSequence");
				}
				else
				{
					newSeq = engine.NewSequence();
					newSeq.Name = currentSeq.Name;
					newSeqFile.InsertSequenceEx(newSeqFile.NumSequences, newSeq);
				}

				//Iterate over each step group in the sequence.
				foreach (StepGroupData currentStepGroup in currentSeq.stepGroups)
				{
					StepGroups currentGroup = StepGroups.StepGroup_Main;
					
					switch (currentStepGroup.Name)
					{
						case StepGroupName.setup: currentGroup = StepGroups.StepGroup_Setup;
							break;
						case StepGroupName.main: currentGroup = StepGroups.StepGroup_Main;
							break;
						case StepGroupName.cleanup: currentGroup = StepGroups.StepGroup_Cleanup;
							break;
					}
					//Iterate over each step in the step group.
					foreach (StepData currentStep in currentStepGroup.steps)
					{ 
						Step newStep = engine.NewStep(currentStep.Adapter, currentStep.Type);
						newStep.Name = currentStep.Name;
						
						//Iterate over each step property
						foreach (PropData currentStepProp in currentStep.stepProps)
						{
							//Evaluate an expression to set the property at the lookupString to the specified value.
							//This method prevents the need to determine the data type of the property.
							newStep.AsPropertyObject().EvaluateEx(currentStepProp.LookupString + " = \"" + currentStepProp.Value + "\"", 0);
						}
						
						//Insert the step in the current step group.
						newSeq.InsertStep(newStep, newSeq.GetNumSteps(currentGroup), currentGroup);
					}
				}
			}
		}

		//Execute the sequence file using the specified entry point and process model.
		public void executeSequenceFile(string modelFilePath, string entryPointName)
		{
			//Open the specified process model.
			SequenceFile processModelFile = engine.GetSequenceFileEx(modelFilePath);
			//Start the execution.
			Execution newExecution = engine.NewExecution(newSeqFile, entryPointName, processModelFile , false, 0);
			//Wait for the execution to complete.
			newExecution.WaitForEndEx(-1, true, Type.Missing, seqContext);
			//Release the model sequence file.
			engine.ReleaseSequenceFileEx(processModelFile, 0);
		}

		//Save the file to the current seqeunce file directory.
		public void saveSequenceFile(string fileName)
		{
			string fullPath = Path.GetDirectoryName(seqContext.SequenceFile.Path) + "\\" + fileName;
			newSeqFile.Save(fullPath);
		}

		//Generate a sample XML file that can be translated by this parser.
		public void generateSampleSequenceFileXML()
		{
			XmlSerializer serializer = new XmlSerializer(typeof(SequenceFileData));
			TextWriter writer = new StreamWriter(parserXMLFilePath);
			SequenceFileData newFile = new SequenceFileData();

			SequenceData mainSequence = new SequenceData("MainSequence");
			SequenceData subSequence = new SequenceData("subSequence");

			//Use the StepTypes and AdapterKeyNames classes to access default step types and adapters.
			mainSequence.stepGroups[(int)StepGroupName.setup].steps.Add(new StepData("About", StepTypes.StepType_MessagePopup , AdapterKeyNames.NoneAdapterKeyName));
			//Because the MessageExpr field is an expression, the value must include escaped quotes: \"
			mainSequence.stepGroups[(int)StepGroupName.setup].steps.Last().stepProps.Add(new PropData("MessageExpr", "\\\"This Sequence was generated from an XML file using the TestStand API.\\\""));

			mainSequence.stepGroups[(int)StepGroupName.main].steps.Add(new StepData("Test 1", StepTypes.StepType_NumericMeasurement, AdapterKeyNames.NoneAdapterKeyName));
			mainSequence.stepGroups[(int)StepGroupName.main].steps.Last().stepProps.Add(new PropData("Limits.Low", "-1"));
			mainSequence.stepGroups[(int)StepGroupName.main].steps.Last().stepProps.Add(new PropData("Limits.High", "1"));

			mainSequence.stepGroups[(int)StepGroupName.main].steps.Add(new StepData("Test 2", StepTypes.StepType_StringMeasurement, AdapterKeyNames.NoneAdapterKeyName));
			mainSequence.stepGroups[(int)StepGroupName.main].steps.Last().stepProps.Add(new PropData("Limits.String", "Comparison String"));
			mainSequence.stepGroups[(int)StepGroupName.main].steps.Last().stepProps.Add(new PropData("Result.String", "Comparison String"));

			mainSequence.stepGroups[(int)StepGroupName.main].steps.Add(new StepData("Call subSequence", StepTypes.StepType_SequenceCall, AdapterKeyNames.SequenceAdapterKeyName));
			mainSequence.stepGroups[(int)StepGroupName.main].steps.Last().stepProps.Add(new PropData("Module.SeqName", "subSequence"));
			mainSequence.stepGroups[(int)StepGroupName.main].steps.Last().stepProps.Add(new PropData("Module.UseCurFile", "true"));

			mainSequence.stepGroups[(int)StepGroupName.cleanup].steps.Add(new StepData("Cleanup", StepTypes.StepType_Action, AdapterKeyNames.NoneAdapterKeyName));

			subSequence.stepGroups[(int)StepGroupName.main].steps.Add(new StepData("subTest 1", StepTypes.StepType_NumericMeasurement, AdapterKeyNames.NoneAdapterKeyName));
			subSequence.stepGroups[(int)StepGroupName.main].steps.Last().stepProps.Add(new PropData("Limits.Low", "-2"));
			subSequence.stepGroups[(int)StepGroupName.main].steps.Last().stepProps.Add(new PropData("Limits.High", "2"));

			newFile.sequences.Add(mainSequence);
			newFile.sequences.Add(subSequence);

			serializer.Serialize(writer, newFile);
			writer.Close();
		}
	}
}

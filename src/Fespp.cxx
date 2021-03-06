﻿/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "Fespp.h"

#include <exception>
#include <iostream>
#include <utility>
#include <algorithm>

#include <vtkDataArraySelection.h>
#include <vtkIndent.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkMultiProcessController.h>
#include <vtkObjectFactory.h>
#include <vtkOStreamWrapper.h>
#include <vtkSetGet.h>
#include <vtkSmartPointer.h>

// Fespp include
#include "VTK/VtkEpcDocument.h"
#include "VTK/VtkEpcDocumentSet.h"

#include <ctime>

vtkStandardNewMacro(Fespp);
vtkCxxSetObjectMacro(Fespp, Controller, vtkMultiProcessController);

//----------------------------------------------------------------------------
Fespp::Fespp() :
				FileName(nullptr), SubFileName(nullptr),
				uuidList(vtkDataArraySelection::New()), Controller(nullptr),
				loadedFile(false), fileNameSet(std::vector<std::string>()),
				epcDocumentSet(nullptr), isEpcDocument(false)
#ifdef WITH_ETP
, etpDocument(nullptr), isEtpDocument(false),
port(""), ip("")
#endif
{
	SetNumberOfInputPorts(0);
	SetNumberOfOutputPorts(1);

	SetController(vtkMultiProcessController::GetGlobalController());

	vtkMultiProcessController* controller = vtkMultiProcessController::GetGlobalController();
	if (controller)
	{
		idProc = controller->GetLocalProcessId();
		nbProc = controller->GetNumberOfProcesses();
	}
	else {
		idProc = 0;
		nbProc = 1;
	}
}

//----------------------------------------------------------------------------
Fespp::~Fespp()
{
	SetController(nullptr);
	fileNameSet.clear();
	uuidList->Delete();

	if (epcDocumentSet != nullptr) {
		delete epcDocumentSet;
		epcDocumentSet = nullptr;
	}

#ifdef WITH_ETP
	if (etpDocument != nullptr) {
		delete etpDocument;
		etpDocument = nullptr;
	}
#endif
}

//----------------------------------------------------------------------------
void Fespp::SetSubFileName(const char* name)
{
	const std::string nameStr = std::string(name);
#ifdef WITH_ETP
	if (isEtpDocument) {
		const auto it = nameStr.find(":");
		if (it != std::string::npos) {
			port = nameStr.substr(it+1);
			ip = nameStr.substr(0,it);
		}
	}
#endif
	if (isEpcDocument) {
		if (std::find(fileNameSet.begin(), fileNameSet.end(), nameStr) == fileNameSet.end())	{
			fileNameSet.push_back(nameStr);
			OpenEpcDocument(nameStr);
		}
	}
}

//----------------------------------------------------------------------------
int Fespp::GetuuidListArrayStatus(const char* uuid)
{
	return (uuidList->ArrayIsEnabled(uuid));
}
//----------------------------------------------------------------------------
void Fespp::SetUuidList(const char* uuid, int status)
{
	const std::string uuidStr = std::string(uuid);
	if (uuidStr == "connect") {
#ifdef WITH_ETP
		if(etpDocument == nullptr) {
			loadedFile = true;
			etpDocument = new VtkEtpDocument(ip, port, VtkEpcCommon::Representation);
		}
#endif
	} else if (uuidStr.find("allWell-") != std::string::npos) {
		if (status == 0) {
			epcDocumentSet->unvisualizeFullWell(uuidStr.substr(8));
		} else {
			epcDocumentSet->visualizeFullWell(uuidStr.substr(8));
		}
	} else if (status == 0) {
		if(isEpcDocument) {
			epcDocumentSet->unvisualize(uuidStr);
		}
#ifdef WITH_ETP
		if(isEtpDocument && etpDocument!=nullptr) {
			etpDocument->unvisualize(uuidStr);
		}
#endif
	}
	else {
		if(isEpcDocument) {
			auto msg = epcDocumentSet->visualize(uuidStr);
			if  (!msg.empty()){
				displayError(msg);
			}
		}
#ifdef WITH_ETP
		if(isEtpDocument && etpDocument!=nullptr) {
			etpDocument->visualize(uuidStr);
		}
#endif
	}

	Modified();
	Update();
	UpdateDataObject();
	UpdateInformation();
	UpdateWholeExtent();
}

//----------------------------------------------------------------------------
int Fespp::GetNumberOfuuidListArrays()
{
	return uuidList->GetNumberOfArrays();
}

//----------------------------------------------------------------------------
const char* Fespp::GetuuidListArrayName(int index)
{
	return uuidList->GetArrayName(index);
}

//----------------------------------------------------------------------------
void Fespp::displayError(const std::string & msg)
{

	vtkErrorMacro(<< msg.c_str());
}

//----------------------------------------------------------------------------
void Fespp::displayWarning(const std::string & msg)
{
	vtkWarningMacro(<< msg.c_str());
}

//----------------------------------------------------------------------------
int Fespp::RequestInformation(
		vtkInformation *request,
		vtkInformationVector **inputVector,
		vtkInformationVector *outputVector)
{
	if ( !loadedFile ) {
		std::string stringFileName = std::string(FileName);
		if (stringFileName == "EpcDocument") {
			isEpcDocument = true;
			loadedFile = true;
			epcDocumentSet = new VtkEpcDocumentSet(idProc, nbProc, VtkEpcCommon::Both);
		}
#ifdef WITH_ETP
		else if(stringFileName == "EtpDocument") {
			isEtpDocument = true;
		}
#endif
	}
	return 1;
}

//----------------------------------------------------------------------------
void Fespp::OpenEpcDocument(const std::string & name)
{
	const std::string msg = epcDocumentSet->addEpcDocument(name);
	if  (!msg.empty()){
		displayWarning(msg);
	}
}

//----------------------------------------------------------------------------
int Fespp::RequestData(vtkInformation *request,
		vtkInformationVector **inputVector,
		vtkInformationVector *outputVector)
{
#ifdef WITH_ETP
	if (isEtpDocument)	{
		RequestDataEtpDocument(request, inputVector, outputVector);
	}
#endif
	if (isEpcDocument)	{
		RequestDataEpcDocument(request, inputVector, outputVector);
	}
	return 1;
}
//----------------------------------------------------------------------------
void Fespp::RequestDataEpcDocument(vtkInformation *request,
		vtkInformationVector **inputVector,
		vtkInformationVector *outputVector)
{
	if (idProc == 0) {
		cout << "Running with " << nbProc << " processor(s)" << std::endl;
	}

	vtkInformation *outInfo = outputVector->GetInformationObject(0);
	vtkMultiBlockDataSet *output = vtkMultiBlockDataSet::SafeDownCast(outInfo->Get(vtkMultiBlockDataSet::DATA_OBJECT()));

	if (loadedFile)
	{
		try{
			output->DeepCopy(epcDocumentSet->getVisualization());
		}
		catch (const std::exception & e)
		{
			vtkErrorMacro("EXCEPTION in FESAPI library: " << e.what());
		}
	}
}

//----------------------------------------------------------------------------
#ifdef WITH_ETP
void Fespp::RequestDataEtpDocument(vtkInformation *request,
		vtkInformationVector **inputVector,
		vtkInformationVector *outputVector)
{
	vtkInformation *outInfo = outputVector->GetInformationObject(0);
	vtkMultiBlockDataSet *output = vtkMultiBlockDataSet::SafeDownCast(outInfo->Get(vtkMultiBlockDataSet::DATA_OBJECT()));
	if (loadedFile)	{
		output->DeepCopy(etpDocument->getVisualization());
	}
}
#endif
//----------------------------------------------------------------------------
void Fespp::PrintSelf(ostream& os, vtkIndent indent)
{
	Superclass::PrintSelf(os, indent);
	os << indent << "fileName: " << (FileName ? FileName : "(none)") << endl;
}

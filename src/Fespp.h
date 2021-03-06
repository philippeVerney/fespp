/*-----------------------------------------------------------------------
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
#ifndef __FESPP_h
#define __FESPP_h

#include "vtkMultiBlockDataSetAlgorithm.h"

// include system
#include <string>
#include <vector>

#ifdef WITH_ETP
	#include "etp/VtkEtpDocument.h"
#endif

class VtkEpcDocumentSet;
class vtkMultiProcessController;
class vtkDataArraySelection;

class Fespp : public vtkMultiBlockDataSetAlgorithm
{
public:
	static Fespp *New();
	vtkTypeMacro(Fespp, vtkMultiBlockDataSetAlgorithm);
	void PrintSelf(ostream& os, vtkIndent indent);
	
	// Description:
	// Specify file name of the .epc file.
	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);

	void SetSubFileName(const char* name);
	vtkGetStringMacro(SubFileName);

	// Description:
	// Get/set the multi process controller to use for coordinated reads.
	// By default, set to the global controller.
	vtkGetObjectMacro(Controller, vtkMultiProcessController);
	virtual void SetController(vtkMultiProcessController *);

	vtkGetObjectMacro(uuidList, vtkDataArraySelection);
	int GetuuidListArrayStatus(const char* name);
	int GetNumberOfuuidListArrays();
	const char* GetuuidListArrayName(int index);
	void SetUuidList(const char* name, int status);

	void displayError(const std::string&);
	void displayWarning(const std::string&);

protected:
	Fespp();
	~Fespp();

	int RequestInformation(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

	void RequestDataEpcDocument(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
#ifdef WITH_ETP
	void RequestDataEtpDocument(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
#endif

	void OpenEpcDocument(const std::string &);

	char* FileName;
	char* SubFileName;

	vtkDataArraySelection* uuidList;

	vtkMultiProcessController* Controller;

private:
	Fespp(const Fespp&);
	void operator=(const Fespp&);
	
	bool loadedFile;

	// id of process
	int idProc;
	// number of process
	int nbProc;

	std::vector<std::string> fileNameSet;

	VtkEpcDocumentSet* epcDocumentSet;
	bool isEpcDocument;

#ifdef WITH_ETP
	VtkEtpDocument* etpDocument;
	bool isEtpDocument;
	std::string port;
	std::string ip;
#endif
};
#endif

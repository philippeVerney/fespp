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
#ifndef __VtkWellboreTrajectoryRepresentation_h
#define __VtkWellboreTrajectoryRepresentation_h

#include "VtkResqml2MultiBlockDataSet.h"

#include "VtkWellboreTrajectoryRepresentationPolyLine.h"
#include "VtkWellboreTrajectoryRepresentationDatum.h"
#include "VtkWellboreTrajectoryRepresentationText.h"

namespace COMMON_NS
{
	class DataObjectRepository;
}

class VtkWellboreTrajectoryRepresentation : public VtkResqml2MultiBlockDataSet
{
public:
	/**
	* Constructor
	*/
	VtkWellboreTrajectoryRepresentation(const std::string & fileName, const std::string & name, const std::string & uuid, const std::string & uuidParent, COMMON_NS::DataObjectRepository *repoRepresentation, COMMON_NS::DataObjectRepository *repoSubRepresentation);
	
	/**
	* Destructor
	*/
	~VtkWellboreTrajectoryRepresentation();

	/**
	* method : createTreeVtk
	* variable : std::string uuid (Wellbore trajectory representation UUID)
	* create the vtk objects for represent Wellbore trajectory (polyline + datum + text).
	*/
	void createTreeVtk(const std::string & uuid, const std::string & parent, const std::string & name, VtkEpcCommon::Resqml2Type resqmlType);
	
	/**
	* method : visualize
	* variable : std::string uuid (Wellbore trajectory representation UUID)
	* Create & Attach the vtk objects for represent Wellbore trajectory (polyline + datum + text) to this object.
	*/
	void visualize(const std::string & uuid);
	
	/**
	* method : remove
	* variable : std::string uuid (Wellbore trajectory representation UUID)
	* delete the vtk objects for represent Wellbore trajectory (polyline + datum + text).
	*/
	void remove(const std::string & uuid);

	void addProperty(const std::string & uuidProperty, class vtkDataArray* dataProperty);

	long getAttachmentPropertyCount(const std::string & uuid, VtkEpcCommon::FesppAttachmentProperty propertyUnit);
protected:
	/**
	* method : createOutput
	* variable : std::string uuid (Wellbore trajectory representation UUID)
	* create the vtk objects for represent Wellbore trajectory (polyline + datum + text).
	*/
	int createOutput(const std::string & uuid);
	
	/**
	* method : attach
	* variable : --
	* Attach the vtk objects for represent Wellbore trajectory (polyline + datum + text) to this object
	*/
	void attach();
	
private:
	// EPC DOCUMENT
	COMMON_NS::DataObjectRepository *repositoryRepresentation;
	COMMON_NS::DataObjectRepository *repositorySubRepresentation;

	// VTK object
	VtkWellboreTrajectoryRepresentationPolyLine polyline;
	VtkWellboreTrajectoryRepresentationDatum head;
	VtkWellboreTrajectoryRepresentationText text;
};
#endif

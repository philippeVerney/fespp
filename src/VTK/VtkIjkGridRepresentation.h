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
#ifndef __VtkIjkGridRepresentation_h
#define __VtkIjkGridRepresentation_h

#include "VtkResqml2UnstructuredGrid.h"

namespace COMMON_NS
{
	class AbstractObject;
}

namespace RESQML2_0_1_NS
{
	class AbstractIjkGridRepresentation;
}

class VtkIjkGridRepresentation : public VtkResqml2UnstructuredGrid
{
public:
	/**
	* Constructor
	*/
	VtkIjkGridRepresentation(const std::string & fileName, const std::string & name, const std::string & uuid, const std::string & uuidParent, COMMON_NS::DataObjectRepository *pckRep, COMMON_NS::DataObjectRepository *pckSubRep, int idProc=0, int maxProc=0);

	/**
	* Destructor
	*/
	~VtkIjkGridRepresentation();
	
	/**
	* method : createOutput
	* variable : uuid (ijk Grid representation or property) 
	* description : 
	*    - if ijk uuid : create the vtk objects for represent ijk Grid 
	*    - if property uuid : add property to ijk Grid 
	*/
	void createOutput(const std::string & uuid);
	
	/**
	* method : addProperty
	* variable : uuid,  dataProperty
	* description :
	* add property to ijk Grid
	*/
	void addProperty(const std::string & uuidProperty, vtkDataArray* dataProperty);

	/**
	* method : getAttachmentPropertyCount
	* variable : uuid,  support property (CELLS or POINTS)
	* return : count 
	*/
	long getAttachmentPropertyCount(const std::string & uuid, VtkEpcCommon::FesppAttachmentProperty propertyUnit) ;

	int getICellCount(const std::string & uuid) const;

	int getJCellCount(const std::string & uuid) const;

	int getKCellCount(const std::string & uuid) const;

	int getInitKIndex(const std::string & uuid) const;

	void setICellCount(const int & value) {	iCellCount = value; }

	void setJCellCount(const int & value) { jCellCount = value; }

	void setKCellCount(const int & value) { kCellCount = value; }

	void setInitKIndex(const int & value) { initKIndex = value; }

	void setMaxKIndex(const int & value) { maxKIndex = value; }
	/**
	* method : createWithPoints
	* variable : points de l'ijkGrid,  ijkGrid or sub-rep
	* description :
	* create the vtk objects with points
	*/	
	void createWithPoints(const vtkSmartPointer<vtkPoints> & pointsRepresentation, COMMON_NS::AbstractObject* obj2);

	/**
	* method : createpoint
	* variable : 
	* return : vtk points of ijkGrid Representation
	* 	int iCellCount;
	*   int jCellCount;
	*   int kCellCount;
	*   int initKIndex;
	*   int maxKIndex;
	*/	
	vtkSmartPointer<vtkPoints> createpoint();

private:

	/**
	* method : checkHyperslabingCapacity
	* variable : ijkGridRepresentation
	* calc if ijkgrid isHyperslabed
	*/	
	void checkHyperslabingCapacity(RESQML2_0_1_NS::AbstractIjkGridRepresentation* ijkGridRepresentation);

	std::string lastProperty;

	int iCellCount;
	int jCellCount;
	int kCellCount;
	int initKIndex;
	int maxKIndex;

	bool isHyperslabed;

};
#endif

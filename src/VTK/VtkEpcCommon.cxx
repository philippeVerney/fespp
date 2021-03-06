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
#include "VtkEpcCommon.h"

//----------------------------------------------------------------------------
VtkEpcCommon::VtkEpcCommon() :
uuid(""),parent(""),name(""),myType(VtkEpcCommon::UNKNOW),parentType(VtkEpcCommon::UNKNOW),timeIndex(-1),timestamp(0)
{
}

//----------------------------------------------------------------------------
VtkEpcCommon::~VtkEpcCommon()
{

}

//----------------------------------------------------------------------------
std::string VtkEpcCommon::getUuid() const
{
	return uuid;
}

//----------------------------------------------------------------------------
std::string VtkEpcCommon::getParent() const
{
	return parent;
}

//----------------------------------------------------------------------------
std::string VtkEpcCommon::getName() const
{
	return name;
}

//----------------------------------------------------------------------------
VtkEpcCommon::Resqml2Type VtkEpcCommon::getType() const
{
	return myType;
}

//----------------------------------------------------------------------------
VtkEpcCommon::Resqml2Type VtkEpcCommon::getParentType() const
{
	return parentType;
}

//----------------------------------------------------------------------------
int VtkEpcCommon::getTimeIndex() const
{
	return timeIndex;
}

//----------------------------------------------------------------------------
time_t VtkEpcCommon::getTimestamp() const
{
	return timestamp;
}

//----------------------------------------------------------------------------
void VtkEpcCommon::setUuid(const std::string & value)
{
	uuid = value;
}

//----------------------------------------------------------------------------
void VtkEpcCommon::setParent(const std::string & value)
{
	parent = value;
}

//----------------------------------------------------------------------------
void VtkEpcCommon::setName(const std::string & value)
{
	name = value;
}

//----------------------------------------------------------------------------
void VtkEpcCommon::setType(VtkEpcCommon::Resqml2Type value)
{
	myType = value;
}

//----------------------------------------------------------------------------
void VtkEpcCommon::setParentType(VtkEpcCommon::Resqml2Type value)
{
	parentType = value;
}

//----------------------------------------------------------------------------
void VtkEpcCommon::setTimeIndex(int value )
{
	timeIndex = value;
}

//----------------------------------------------------------------------------
void VtkEpcCommon::setTimestamp(time_t value)
{
	timestamp = value;
}

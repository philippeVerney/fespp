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
#ifndef _PQDataLoadManager_H
#define _PQDataLoadManager_H

#include <QDialog>

class pqServer;
class pqPipelineSource;

class PQDataLoadManager : public QDialog
{
	Q_OBJECT;

public:
	PQDataLoadManager(QWidget* p, Qt::WindowFlags f = 0);
	~PQDataLoadManager();

	public slots:
	virtual void checkInputValid();
	virtual void setupPipeline();

	protected:
	pqServer* Server;

	private:
	Q_DISABLE_COPY(PQDataLoadManager)

	class pqUI;
	pqUI* ui;

};

#endif 

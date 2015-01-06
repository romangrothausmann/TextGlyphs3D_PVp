/*=========================================================================

  Program:   ParaView
  Module:    $RCSfile$

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkMySpecialRepresentation.h"

#include "vtkObjectFactory.h"
#include "vtkPVLODActor.h"

#include "TextGlyphs3D.h"
#include <vtkFollower.h>

vtkStandardNewMacro(vtkMySpecialRepresentation);
//----------------------------------------------------------------------------
vtkMySpecialRepresentation::vtkMySpecialRepresentation(){


    this->Mapper->SetInputConnection(TextGlyphs3D...);
    // this->Actor->Delete();

    // this->Actor = vtkFollower::New();
    // this->Actor->SetCamera(this->Renderer->GetActiveCamera());

    // this->SetupDefaults();
    }

//----------------------------------------------------------------------------
virtual bool vtkMySpecialRepresentation::AddToView(vtkView *view){

    vtkPVRenderView* rview = vtkPVRenderView::SafeDownCast(view);
    if (rview){
	//vtkActor follower= vtkFollower::New();
	vtkPVLODActor follower= vtkFollower::New();
	follower->SetCamera(rview->GetRenderer()->GetActiveCamera());

	this->Actor->Delete();
	this->Actor= follower;
	rview->GetRenderer()->AddActor(follower);
	}
    return this->Superclass::AddToView(view);
    }	

//----------------------------------------------------------------------------
vtkMySpecialRepresentation::~vtkMySpecialRepresentation()
{
//this->TextureMapToPlane->Delete();
}

//----------------------------------------------------------------------------
void vtkMySpecialRepresentation::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

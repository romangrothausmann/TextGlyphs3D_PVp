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

#include "vtkMySpecialPolyDataMapper.h"
#include "vtkObjectFactory.h"
#include "vtkPVUpdateSuppressor.h"
#include "vtkTextureMapToPlane.h"
#include "vtkPNGReader.h"
#include "vtkTexture.h"
#include "vtkPVLODActor.h"
#include "vtkImageData.h"

vtkStandardNewMacro(vtkMySpecialRepresentation);
//----------------------------------------------------------------------------
vtkMySpecialRepresentation::vtkMySpecialRepresentation()
{
  // Replace the mappers created by the superclass.
  this->Mapper->Delete();
  this->LODMapper->Delete();

  this->Mapper = vtkMySpecialPolyDataMapper::New();
  this->LODMapper = vtkMySpecialPolyDataMapper::New();

  this->TextureMapToPlane = vtkTextureMapToPlane::New();

  // Since we replaced the mappers, we need to call SetupDefaults() to ensure
  // the pipelines are setup correctly.
  this->SetupDefaults();

  this->TextureMapToPlane->SetInputConnection(this->UpdateSuppressor->GetOutputPort());
  this->Mapper->SetInputConnection(this->TextureMapToPlane->GetOutputPort());

  vtkPNGReader* reader = vtkPNGReader::New();
  reader->SetFileName("/tmp/Screenshot.png");
  vtkTexture* tex = vtkTexture::New();
  tex->SetInputData(reader->GetOutput());
  reader->Delete();

  this->Actor->SetTexture(tex);
  tex->Delete();
}

//----------------------------------------------------------------------------
vtkMySpecialRepresentation::~vtkMySpecialRepresentation()
{
  this->TextureMapToPlane->Delete();
}

//----------------------------------------------------------------------------
void vtkMySpecialRepresentation::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

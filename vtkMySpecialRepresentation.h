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
// .NAME vtkMySpecialRepresentation
// .SECTION Description
//

#ifndef __vtkMySpecialRepresentation_h
#define __vtkMySpecialRepresentation_h

#include "vtkGeometryRepresentation.h"

class VTK_EXPORT vtkMySpecialRepresentation : public vtkGeometryRepresentation
{
public:
  static vtkMySpecialRepresentation* New();
  vtkTypeMacro(vtkMySpecialRepresentation, vtkGeometryRepresentation);
  void PrintSelf(ostream& os, vtkIndent indent);

//BTX
protected:
  vtkMySpecialRepresentation();
  ~vtkMySpecialRepresentation();

  virtual bool AddToView(vtkView* view);

private:
  vtkMySpecialRepresentation(const vtkMySpecialRepresentation&); // Not implemented
  void operator=(const vtkMySpecialRepresentation&); // Not implemented
//ETX
};

#endif

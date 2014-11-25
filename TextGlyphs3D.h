// .NAME TextGlyphs3D - filter for paraview to render text from array data with z-depth
// .SECTION Description


#ifndef __TextGlyphs3D_h
#define __TextGlyphs3D_h

#include "vtkPolyDataAlgorithm.h"

class VTK_EXPORT TextGlyphs3D : public vtkPolyDataAlgorithm
{
public:
  static TextGlyphs3D *New();
  vtkTypeMacro(TextGlyphs3D,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  /* vtkSetVector3Macro(origin, double); */
  /* vtkGetVector3Macro(origin, double); */
  /* vtkSetVector3Macro(normal, double); */
  /* vtkGetVector3Macro(normal, double); */

  vtkSetMacro(TextArrayName, vtkStdString);
  vtkGetMacro(TextArrayName, vtkStdString);

  vtkSetMacro(Scale, double);
  vtkGetMacro(Scale, double);


protected:
  TextGlyphs3D();
  ~TextGlyphs3D() {};

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  vtkStdString TextArrayName;
  double Scale;

private:
  TextGlyphs3D(const TextGlyphs3D&);  // Not implemented.
  void operator=(const TextGlyphs3D&);  // Not implemented.

};

#endif



//////paraview plugin to render text from array data with z-depth
//////idea and implementation by Roman Grothausmann
////
////based on ~/vtk/py/textOrigin_01.py 
////based on https://github.com/Kitware/VTK/blob/master/Examples/Annotation/Python/textOrigin.py

//01: scale and translation working
//02: clean-up


//todo:
//add interaction like vtkFollower to orient text to camera in paraview


#include "TextGlyphs3D.h"

#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h>

#include <vtkSmartPointer.h>

#include <vtkStringArray.h>
#include <vtkPointData.h>
#include <vtkVectorText.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>
#include <vtkAppendPolyData.h>

vtkStandardNewMacro(TextGlyphs3D);

//----------------------------------------------------------------------------
// Description:
TextGlyphs3D::TextGlyphs3D(){
    this->TextArrayName= "text labels";
    this->Scale= 1;
    }

//----------------------------------------------------------------------------

int TextGlyphs3D::RequestData(
    vtkInformation *vtkNotUsed(request),
    vtkInformationVector **inputVector,
    vtkInformationVector *outputVector){
    // get the info objects
    vtkInformation *inInfo0 = inputVector[0]->GetInformationObject(0);
    vtkInformation *outInfo = outputVector->GetInformationObject(0);

    // get the input and ouptut
    vtkPolyData *input = vtkPolyData::SafeDownCast(
        inInfo0->Get(vtkDataObject::DATA_OBJECT()));
    vtkPolyData *output = vtkPolyData::SafeDownCast(
        outInfo->Get(vtkDataObject::DATA_OBJECT()));

    vtkStringArray* textArray= vtkStringArray::SafeDownCast(input->GetPointData()->GetAbstractArray(this->TextArrayName));

    if(!textArray){
	std::cerr << "Specified array could not be casted to vtkStringArray! Aborting." << std::endl;
	return EXIT_FAILURE;
	}


    vtkSmartPointer<vtkVectorText> text3d= vtkSmartPointer<vtkVectorText>::New();
	
    vtkSmartPointer<vtkTransformPolyDataFilter> tff= vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    tff->SetInputConnection(text3d->GetOutputPort());

    vtkSmartPointer<vtkAppendPolyData> append= vtkSmartPointer<vtkAppendPolyData>::New();

    for(vtkIdType i= 0; i < input->GetNumberOfPoints(); i++){
	text3d->SetText(textArray->GetValue(i));
	vtkSmartPointer<vtkTransform> tf= vtkSmartPointer<vtkTransform>::New();
	tf->Translate(input->GetPoint(i));
	tf->Scale(this->Scale, this->Scale, this->Scale);
	tff->SetTransform(tf);
	tff->Update();

	vtkSmartPointer<vtkPolyData> outputCopy = vtkSmartPointer<vtkPolyData>::New();
	outputCopy->ShallowCopy(tff->GetOutput());
	append->AddInputData(outputCopy);
	}

    append->Update();
    output->ShallowCopy(append->GetOutput());
    //output->GetActor();

    return 1;
    //return EXIT_SUCCESS; //apparently not good for pv
    }

//----------------------------------------------------------------------------
void TextGlyphs3D::PrintSelf(ostream& os, vtkIndent indent){

    this->Superclass::PrintSelf(os,indent);

    os << indent << "TextArrayName: " << this->TextArrayName << endl;
    os << indent << "Scale: " << this->Scale << endl;
    os << indent << endl;
    }

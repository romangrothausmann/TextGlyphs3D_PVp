//////paraview plugin to render text from array data with z-depth
////based on ~/vtk/py/textOrigin_01.py 
////based on https://github.com/Kitware/VTK/blob/master/Examples/Annotation/Python/textOrigin.py

//01: scale and translation working


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

    //vtkStringArray* textArray= dynamic_cast<vtkStringArray*>(input->GetPointData()->GetArray(this->TextArrayName));vtkIntArray::SafeDownCast
    // std::cerr << this->TextArrayName << std::endl;
    // input->GetPointData()->Print(std::cerr);
    // fprintf(stderr, "%s, %d\n", __FILE__,__LINE__);
    // std::cerr << "GetNumberOfArrays: " << input->GetPointData()->GetNumberOfArrays () << std::endl;
    // for (int j = 0; j < input->GetPointData()->GetNumberOfArrays (); j ++) 
    // 	{
    // 	char *name = 0;
    // 	if (input->GetPointData()->GetArray(j))
    // 	    {
    // 	    name = input->GetPointData()->GetArray(j)->GetName();
    // 	    std::cerr << name << std::endl;
    // 	    input->GetPointData()->GetArray(j)->Print(std::cerr);
    // 	    }
    // 	else
    // 	    std::cerr << "Array #: " << j << std::endl;
    // 	}
    // std::cerr << input->GetPointData()->GetArrayName(7) << std::endl;
    // //vtkDataArray* dataArray= input->GetPointData()->GetArray(this->TextArrayName.c_str());
    //vtkDataArray* dataArray= input->GetPointData()->GetArray("hkl-label");
    // vtkAbstractArray* dataArray= input->GetPointData()->GetAbstractArray(this->TextArrayName);
    // fprintf(stderr, "%s, %d\n", __FILE__,__LINE__);
    // dataArray->Print(std::cerr);
    // vtkStringArray* textArray= vtkStringArray::SafeDownCast(dataArray);
    //vtkStringArray* textArray= vtkStringArray::SafeDownCast(input->GetPointData()->GetArray("hkl-label"));

    vtkStringArray* textArray= vtkStringArray::SafeDownCast(input->GetPointData()->GetAbstractArray(this->TextArrayName));

    if(!textArray){
	std::cerr << "Specified array could not be casted to vtkStringArray! Aborting." << std::endl;
	return EXIT_FAILURE;
	}


    vtkSmartPointer<vtkVectorText> text3d= vtkSmartPointer<vtkVectorText>::New();
	
    // vtkSmartPointer<vtkTransform> tf= vtkSmartPointer<vtkTransform>::New();
    // tf->Scale(this->Scale, this->Scale, this->Scale);
    // tf->PostMultiply();	//scale first, then translate

    vtkSmartPointer<vtkTransformPolyDataFilter> tff= vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    // tff->SetTransform(tf);
    tff->SetInputConnection(text3d->GetOutputPort());

    vtkSmartPointer<vtkAppendPolyData> append= vtkSmartPointer<vtkAppendPolyData>::New();

    for(vtkIdType i= 0; i < input->GetNumberOfPoints(); i++){
	//std::cerr << textArray->GetValue(i) << std::endl;
	text3d->SetText(textArray->GetValue(i));
	vtkSmartPointer<vtkTransform> tf= vtkSmartPointer<vtkTransform>::New();
	// double p[3];
	// input->GetPoint(i, p);
	// fprintf(stderr, "%f, %f, %f\n", p[0], p[1], p[2]);
	// tf->Translate(p);
	tf->Translate(input->GetPoint(i));
	tf->Scale(this->Scale, this->Scale, this->Scale);
	//tf->PostMultiply();	//scale first, then translate
	tff->SetTransform(tf);
	tff->Update();

	vtkSmartPointer<vtkPolyData> outputCopy = vtkSmartPointer<vtkPolyData>::New();
	outputCopy->ShallowCopy(tff->GetOutput());
	append->AddInputData(outputCopy);
	}


// textMapper = vtk.vtkPolyDataMapper()
// textMapper.SetInputConnection(atext.GetOutputPort())
// textActor = vtk.vtkFollower()
// textActor.SetMapper(textMapper)
// textActor.SetScale(0.2, 0.2, 0.2)
// textActor.AddPosition(1, 0, 0)


    // // Copy original points and point data
    // output->CopyStructure( input );
    // output->GetPointData()->PassData(input->GetPointData());
    // output->GetCellData()->PassData(input->GetCellData());

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

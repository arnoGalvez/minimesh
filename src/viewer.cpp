#include "viewer.hpp"

#include "import.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

Viewer::Viewer() {}

void Viewer::ViewDataSet( vtkDataSet *dataSet )
{
    auto colors = vtkSmartPointer<vtkNamedColors>::New();

    auto renderer = vtkSmartPointer<vtkRenderer>::New();

    auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize( 640, 480 );
    renderWindow->AddRenderer( renderer );

    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow( renderWindow );

    renderer->SetBackground( colors->GetColor3d( "Wheat" ).GetData() );
    renderer->UseHiddenLineRemovalOn();

    // Visualize
    auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData( dataSet );
    mapper->ScalarVisibilityOff();

    auto backProp = vtkSmartPointer<vtkProperty>::New();
    backProp->SetDiffuseColor( colors->GetColor3d( "Banana" ).GetData() );
    backProp->SetSpecular( .6 );
    backProp->SetSpecularPower( 30 );

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper( mapper );
    actor->SetBackfaceProperty( backProp );
    actor->GetProperty()->SetDiffuseColor( colors->GetColor3d( "Tomato" ).GetData() );
    actor->GetProperty()->SetSpecular( .3 );
    actor->GetProperty()->SetSpecularPower( 30 );
    actor->GetProperty()->EdgeVisibilityOn();

    renderer->AddActor( actor );
    renderer->GetActiveCamera()->Azimuth( 45 );
    renderer->GetActiveCamera()->Elevation( 45 );
    renderer->ResetCamera();
    interactor->Initialize();
    renderWindow->Render();
    interactor->Start();
}

/* This code is almost a 1:1 copy from https://lorensen.github.io/VTKExamples/site/Cxx/IO/ReadAllUnstructuredGridTypes/
 */

Viewer &Viewer::Instance()
{
    static Viewer instance;
    return instance;
}

void Viewer::View( std::string const &fileName )
{
    std::cout << "Loading: " << fileName << std::endl;
    auto unstructuredGrid = ReadUnstructuredGrid( fileName );

    ViewDataSet( unstructuredGrid );
}

void Viewer::View( vtkSmartPointer<vtkPolyData> polyData )
{
    ViewDataSet( polyData );
}

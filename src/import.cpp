#include "import.hpp"

#include <vtkXMLPolyDataReader.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkSphereSource.h>
#include <vtkAppendFilter.h>

#include <vtkUnstructuredGrid.h>
#include <vtkSphereSource.h>
#include <vtkAppendFilter.h>



vtkSmartPointer<vtkPolyData> ReadPolyData( const std::string &file )
{
    auto polyData = vtkSmartPointer<vtkPolyData>::New();

    vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName( file.c_str() );
    reader->Update();
    polyData->ShallowCopy( reader->GetOutput() );

    return polyData;
}

vtkSmartPointer<vtkUnstructuredGrid> ReadUnstructuredGrid( std::string const &fileName )
{
    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid;
    std::string                          extension = "";
    if ( fileName.find_last_of( "." ) != std::string::npos )
    { extension = fileName.substr( fileName.find_last_of( "." ) ); }

    // Drop the case of the extension
    std::transform( extension.begin(), extension.end(), extension.begin(), ::tolower );

    if ( extension == ".vtu" )
    {
        auto reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
        reader->SetFileName( fileName.c_str() );
        reader->Update();
        unstructuredGrid = reader->GetOutput();
    }
    else if ( extension == ".vtk" )
    {
        auto reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
        reader->SetFileName( fileName.c_str() );
        reader->Update();
        unstructuredGrid = reader->GetOutput();
    }
    else
    {
        auto source = vtkSmartPointer<vtkSphereSource>::New();
        source->Update();
        auto appendFilter = vtkSmartPointer<vtkAppendFilter>::New();
        appendFilter->AddInputData( source->GetOutput() );
        appendFilter->Update();
        unstructuredGrid = appendFilter->GetOutput();
    }
    return unstructuredGrid;
}

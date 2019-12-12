#include "concatenate.hpp"

#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>

/* implementation taken from https://lorensen.github.io/VTKExamples/site/Cxx/Filtering/CombinePolyData/ */

vtkSmartPointer<vtkPolyData> Concatenate( vtkSmartPointer<vtkPolyData> lhs,
                                     vtkSmartPointer<vtkPolyData> rhs,
                                     bool                         mergeDuplicates /*= true*/ )
{
    auto appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
    appendFilter->AddInputData( lhs );
    appendFilter->AddInputData( rhs );
    appendFilter->Update();

    if ( mergeDuplicates )
    {
        auto cleanFilter = vtkSmartPointer<vtkCleanPolyData>::New();
        cleanFilter->SetInputConnection( appendFilter->GetOutputPort() );
        cleanFilter->Update();

        vtkSmartPointer<vtkPolyData> ret( cleanFilter->GetOutput() );
        return ret;
    }

    vtkSmartPointer<vtkPolyData> ret( appendFilter->GetOutput() );
    return ret;
}

vtkSmartPointer<vtkPolyData> Concatenate( std::vector<vtkSmartPointer<vtkPolyData>> data,
                                          bool                                      mergeDuplicates /*= true */ )
{
    auto appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
    for (auto &d : data)
    {
        appendFilter->AddInputData(d);
    }

    appendFilter->Update();

    if ( mergeDuplicates )
    {
        auto cleanFilter = vtkSmartPointer<vtkCleanPolyData>::New();
        cleanFilter->SetInputConnection( appendFilter->GetOutputPort() );
        cleanFilter->Update();

        vtkSmartPointer<vtkPolyData> ret( cleanFilter->GetOutput() );
        return ret;
    }

    vtkSmartPointer<vtkPolyData> ret( appendFilter->GetOutput() );
    return ret;

}

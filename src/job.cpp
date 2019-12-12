#include "job.hpp"

#include "concatenate.hpp"
#include "import.hpp"
#include "viewer.hpp"

#include <memory>
#include <vtkGeometryFilter.h>

MergeJob::MergeJob( const std::vector<std::string> &meshes, const std::string &outputFile, bool mergeNodes )
    : meshes( meshes )
    , outputFile( outputFile )
    , mergeNodes( mergeNodes )
{
}

void MergeJob::Execute()
{
    if ( meshes.size() > 0 )
    {
        std::vector<vtkSmartPointer<vtkPolyData>> v_polyData( meshes.size() );

        for ( auto &mesh : meshes )
        {
            auto unstructuredGrid = ReadUnstructuredGrid( mesh );
            auto geometryFilter   = vtkSmartPointer<vtkGeometryFilter>::New();
            geometryFilter->SetInputData( unstructuredGrid );
            geometryFilter->Update();
            auto tmpPolyData = vtkSmartPointer<vtkPolyData>( geometryFilter->GetOutput() );
            v_polyData.emplace_back( tmpPolyData ); // polyData = Concatenate( polyData, polyData2, merge_nodes );
        }

        auto polyData = Concatenate( v_polyData );

        auto &viewer = Viewer::Instance();
        viewer.View( polyData );
    }

}

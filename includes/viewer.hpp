#pragma once

#include <string>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

class Viewer
{
  public:
    static Viewer &Instance();

    void View( std::string const &fileName );
    void View( vtkSmartPointer<vtkPolyData> polyData );

  private:
    Viewer();
    ~Viewer() {}

    void ViewDataSet(vtkDataSet* dataSet);

    // TODO
};

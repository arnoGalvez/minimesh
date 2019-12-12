#pragma once

#include <string>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

class Viewer
{
  public:
    static Viewer &Instance();
    void           View( std::string const &fileName );

  private:
    Viewer();
    ~Viewer() {}
    vtkSmartPointer<vtkUnstructuredGrid> ReadUnstructuredGrid( std::string const &fileName );

    // TODO
};

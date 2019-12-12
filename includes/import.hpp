#include <string>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridReader.h>

vtkSmartPointer<vtkPolyData>         ReadPolyData( const std::string &file );
vtkSmartPointer<vtkUnstructuredGrid> ReadUnstructuredGrid( std::string const &fileName );

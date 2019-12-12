#pragma once

#include <string>
#include <vector>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

vtkSmartPointer<vtkPolyData> Concatenate( vtkSmartPointer<vtkPolyData> lhs,
                                          vtkSmartPointer<vtkPolyData> rhs,
                                          bool                         mergeDuplicates = true );

vtkSmartPointer<vtkPolyData> Concatenate( std::vector<vtkSmartPointer<vtkPolyData>> data, bool mergeDuplicates = true );

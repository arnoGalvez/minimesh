#pragma once

#include <string>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>

vtkSmartPointer<vtkPolyData> Concatenate( vtkSmartPointer<vtkPolyData> lhs,
                                     vtkSmartPointer<vtkPolyData> rhs,
                                     bool                         mergeDuplicates = true );

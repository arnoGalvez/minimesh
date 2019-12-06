#include <vtkUnstructuredGridReader.h>

#include <memory>
#include <string>

namespace import {
    std::shared_ptr<vtkUnstructuredGrid> GridReader(std::string const &file);
}

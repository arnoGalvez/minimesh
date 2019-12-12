#pragma once

#include "cpptoml.h"
#include "job.hpp"

#include <memory>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

class OptionsParser
{
  public:
    OptionsParser( const std::string & );
    ~OptionsParser( void ) {}

    // TODO: modifier le type de retour en cohérence
    // avec la structure de données renvoyée.
    std::shared_ptr<Job> parse( void );

  private:
    std::string                     m_file_name;
    std::shared_ptr<cpptoml::table> m_data;
};

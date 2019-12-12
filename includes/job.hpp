#pragma once

#include <string>
#include <vector>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

class Job
{
  public:
    virtual void Execute() {}
};

class MergeJob : public Job
{
  public:
    virtual void Execute();
    MergeJob( const std::vector<std::string> &meshes, const std::string &outputFile, bool mergeNodes );

  private:
    std::vector<std::string> meshes;
    std::string              outputFile;
    bool                     mergeNodes;
};

class TranslateJob : public Job
{
};
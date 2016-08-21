// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
*
* \author  Felix Mauch <mauch@fzi.de>
* \date    2015-05-04
*
*/
//----------------------------------------------------------------------
#include <cstdlib>
#include <signal.h>

#include <gpu_voxels/GpuVoxels.h>
#include <gpu_voxels/helpers/GeometryGeneration.h>
#include <gpu_voxels/logging/logging_gpu_voxels.h>

using namespace gpu_voxels;
using namespace voxelmap;
using namespace geometry_generation;

GpuVoxels* gvl;

void ctrlchandler(int)
{
  delete gvl;
  exit(EXIT_SUCCESS);
}
void killhandler(int)
{
  delete gvl;
  exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
  signal(SIGINT, ctrlchandler);
  signal(SIGTERM, killhandler);

  icl_core::logging::initialize(argc, argv);

  Vector3ui dim(89, 123, 74);
  float side_length = 1.f;
  ProbVoxelMap map_1(dim.x, dim.y, dim.z, side_length, MT_PROBAB_VOXELMAP);
  ProbVoxelMap map_2(dim.x, dim.y, dim.z, side_length, MT_PROBAB_VOXELMAP);

  std::vector<Vector3f> this_testpoints1;
  std::vector<Vector3f> this_testpoints2;

  this_testpoints1 = createBoxOfPoints( Vector3f(2.1, 2.1, 2.1), Vector3f(4.1, 4.1, 4.1), 0.5);
  this_testpoints2 = createBoxOfPoints( Vector3f(3.1, 3.1, 3.1), Vector3f(5.1, 5.1, 5.1), 0.5);

  map_1.insertPointCloud(this_testpoints1, eBVM_OCCUPIED);
  map_2.insertPointCloud(this_testpoints2, eBVM_OCCUPIED);

  std::cout << "Blub" << std::endl;
  std::cout << "Collisions w offset: " << map_1.collideWith(&map_2, 0.1, Vector3i(-1,-0,-1)) << std::endl;
  std::cout << "Collisions wo offset: " << map_1.collideWith(&map_2, 0.1) << std::endl;





  return 0;
}

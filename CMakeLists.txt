cmake_minimum_required(VERSION 3.3...3.12 FATAL_ERROR)


PROJECT (TempIsoSurface)

find_package(VTK COMPONENTS
  vtkFiltersGeometry
  vtkFiltersModeling
  vtkIOImage
  vtkIOLegacy
  vtkIOXML
  vtkImagingStatistics
  vtkInteractionStyle
  vtkRenderingVolumeOpenGL2
  vtkTestingRendering
  vtksys
)
include(${VTK_USE_FILE})

add_executable(TempIsoSurface MACOSX_BUNDLE TempIsoSurface.cxx)
target_link_libraries(TempIsoSurface ${VTK_LIBRARIES})


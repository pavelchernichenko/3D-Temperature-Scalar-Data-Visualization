cmake_minimum_required(VERSION 3.3...3.12 FATAL_ERROR)


PROJECT (MedicalComplete)

find_package(VTK COMPONENTS
  vtkFiltersGeometry
  vtkFiltersModeling
  
  vtkCommonCore
  vtkCommonDataModel
  vtkFiltersSources

  vtkIOImage
  vtkIOXML
  vtkIOLegacy

  vtkImagingStatistics
  vtkInteractionStyle

  vtkRenderingAnnotation
  vtkRenderingLabel
  vtkRenderingCore
  vtkRenderingFreeType


  vtkRenderingVolumeOpenGL2
  vtkTestingRendering
  vtksys
)
include(${VTK_USE_FILE})

add_executable(MedicalComplete MACOSX_BUNDLE MedicalComplete.cxx)
target_link_libraries(MedicalComplete ${VTK_LIBRARIES})


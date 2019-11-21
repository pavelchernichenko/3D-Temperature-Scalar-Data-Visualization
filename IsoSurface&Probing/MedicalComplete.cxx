/*=========================================================================

  Program:   Visualization Toolkit
  Module:    Medical1.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This example reads a volume dataset, extracts an isosurface that
// represents the skin and displays it.
//


#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredPointsReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
#include <vtkContourFilter.h>
#include <vtkSmartPointer.h>
#include <vtkVolume16Reader.h>
#include <vtkLookupTable.h>
#include <vtkPolyData.h>
#include <vtkImageMapToColors.h>
#include <vtkImageActor.h>
#include <vtkSmartPointer.h>
#include <vtkImageMapper3D.h>

int main (int argc, char *argv[])
{

  // Create the renderer, the render window, and the interactor. The renderer
  // draws into the render window, the interactor enables mouse- and
  // keyboard-based interaction with the data within the render window.
  //
  vtkSmartPointer<vtkRenderer> aRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(aRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
  lut->SetHueRange(0.6667, 0.0);
  lut->SetSaturationRange(1.0, 1.0);
  lut->SetValueRange(1.0, 1.0);
  lut->SetAlphaRange(1.0, 1.0);
  lut->Build();


  // The following reader is used to read a series of 2D slices (images)
  // that compose the volume. The slice dimensions are set, and the
  // pixel spacing. The data Endianness must also be specified. The reader
  // uses the FilePrefix in combination with the slice number to construct
  // filenames using the format FilePrefix.%d. (In this case the FilePrefix
  // is the root name of the file: quarter.)

  vtkSmartPointer<vtkStructuredPointsReader> v16 = vtkSmartPointer<vtkStructuredPointsReader>::New();
  v16->SetFileName("temperature.dat");
  v16->Update();

 
  // An isosurface, or contour value of 500 is known to correspond to the
  // skin of the patient. Once generated, a vtkPolyDataNormals filter is
  // is used to create normals for smooth surface shading during rendering.

  vtkSmartPointer<vtkContourFilter> skinExtractor1 =
	  vtkSmartPointer<vtkContourFilter>::New();
  skinExtractor1->SetInputConnection(v16->GetOutputPort());
  skinExtractor1->SetValue(0, 0.5);

  vtkSmartPointer<vtkPolyDataNormals> skinNormals1 =
	  vtkSmartPointer<vtkPolyDataNormals>::New();
  skinNormals1->SetInputConnection(skinExtractor1->GetOutputPort());
  skinNormals1->SetFeatureAngle(60.0);

  vtkSmartPointer<vtkPolyDataMapper> skinMapper1 =
	  vtkSmartPointer<vtkPolyDataMapper>::New();
  skinMapper1->SetInputConnection(skinNormals1->GetOutputPort());
  //skinMapper->ScalarVisibilityOn();
  skinMapper1->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> skin1 =
	  vtkSmartPointer<vtkActor>::New();
  skin1->SetMapper(skinMapper1);

  vtkSmartPointer<vtkContourFilter> skinExtractor2 =
	  vtkSmartPointer<vtkContourFilter>::New();
  skinExtractor2->SetInputConnection(v16->GetOutputPort());
  skinExtractor2->SetValue(0, 0.1);

  vtkSmartPointer<vtkPolyDataNormals> skinNormals2 =
	  vtkSmartPointer<vtkPolyDataNormals>::New();
  skinNormals2->SetInputConnection(skinExtractor2->GetOutputPort());
  skinNormals2->SetFeatureAngle(60.0);

  vtkSmartPointer<vtkPolyDataMapper> skinMapper2 =
	  vtkSmartPointer<vtkPolyDataMapper>::New();
  skinMapper2->SetInputConnection(skinNormals2->GetOutputPort());
  //skinMapper->ScalarVisibilityOn();
  skinMapper2->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> skin2 =
	  vtkSmartPointer<vtkActor>::New();
  skin2->SetMapper(skinMapper2);

  vtkSmartPointer<vtkContourFilter> skinExtractor3 =
	  vtkSmartPointer<vtkContourFilter>::New();
  skinExtractor3->SetInputConnection(v16->GetOutputPort());
  skinExtractor3->SetValue(0, 0.9);

  vtkSmartPointer<vtkPolyDataNormals> skinNormals3 =
	  vtkSmartPointer<vtkPolyDataNormals>::New();
  skinNormals3->SetInputConnection(skinExtractor3->GetOutputPort());
  skinNormals3->SetFeatureAngle(60.0);

  vtkSmartPointer<vtkPolyDataMapper> skinMapper3 =
	  vtkSmartPointer<vtkPolyDataMapper>::New();
  skinMapper3->SetInputConnection(skinNormals3->GetOutputPort());
  //skinMapper->ScalarVisibilityOn();
  skinMapper3->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> skin3 =
	  vtkSmartPointer<vtkActor>::New();
  skin3->SetMapper(skinMapper3);



  /*************************************/
    
  // An outline provides context around the data.
  //
  vtkSmartPointer<vtkOutlineFilter> outlineData = vtkSmartPointer<vtkOutlineFilter>::New();
                                    outlineData->SetInputConnection(v16->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> mapOutline = vtkSmartPointer<vtkPolyDataMapper>::New();
                                     mapOutline->SetInputConnection(outlineData->GetOutputPort());

  vtkSmartPointer<vtkActor> outline = vtkSmartPointer<vtkActor>::New();
                            outline->SetMapper(mapOutline);
                            outline->GetProperty()->SetColor(0,0,0);

 
  // It is convenient to create an initial view of the data. The FocalPoint
  // and Position form a vector direction. Later on (ResetCamera() method)
  // this vector is used to position the camera to look at the data in
  // this direction.

  vtkSmartPointer<vtkCamera> aCamera = vtkSmartPointer<vtkCamera>::New();
  aCamera->SetViewUp(0, 1, 0);
  aCamera->SetPosition(0, 0, 1);
  aCamera->SetFocalPoint(0, 0, 0);
  aCamera->ComputeViewPlaneNormal();
  aCamera->Azimuth(0.0);
  aCamera->Elevation(0.0);
  
  // Setup the text and add it to the renderer

  aRenderer->AddActor(outline);

  aRenderer->AddActor(skin1);
  aRenderer->AddActor(skin2);
  aRenderer->AddActor(skin3);



  aRenderer->SetActiveCamera(aCamera);
  aRenderer->ResetCamera ();
  
  // Set a background color for the renderer and set the size of the
  // render window (expressed in pixels).
  aRenderer->SetBackground(.2, .3, .4);
  renWin->SetSize(800, 800);

  // Note that when camera movement occurs (as it does in the Dolly()
  // method), the clipping planes often need adjusting. Clipping planes
  // consist of two planes: near and far along the view direction. The
  // near plane clips out objects in front of the plane; the far plane
  // clips out objects behind the plane. This way only what is drawn
  // between the planes is actually rendered.

  aRenderer->ResetCameraClippingRange ();

  // Initialize the event loop and then start it.
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

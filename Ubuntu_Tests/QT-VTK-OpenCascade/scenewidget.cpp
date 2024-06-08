#include "scenewidget.h"

#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <vtkAutoInit.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>
#include <IGESControl_Reader.hxx> 
#include <STEPCAFControl_Reader.hxx>
//Lesson 17
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <vtkCubeSource.h>
#include <vtkEllipseArcSource.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkBoundingBox.h>



SceneWidget::SceneWidget(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent)
{
    vtkNew<vtkGenericOpenGLRenderWindow> window;
    setRenderWindow(window.Get());

    // Camera
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(0, 0, 10);
    camera->SetFocalPoint(0, 0, 0);

    // Renderer
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_renderer->SetActiveCamera(camera);
    m_renderer->SetBackground(0.5, 0.5, 0.5);
    renderWindow()->AddRenderer(m_renderer);
}

void SceneWidget::addDataSet(vtkSmartPointer<vtkDataSet> dataSet)
{
	//TopoDS_ShapeSphere
	gp_Ax2 sphere_origin(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	BRepPrimAPI_MakeCone mkCone(sphere_origin, 1.0,0.01,1);
	const TopoDS_Shape& TopoDS_ShapemkConeTMP = mkCone.Shape();
	TopoDS_Shape TopoDS_ShapeCONE = static_cast<TopoDS_Shape>(TopoDS_ShapemkConeTMP);
	gp_Trsf TSPHERE;
	TSPHERE.SetScaleFactor(0.9);
	TSPHERE.SetTranslationPart(gp_Vec(0, 0, 0));
	BRepBuilderAPI_Transform stepBRepTransformationTOPBOX(TopoDS_ShapeCONE, TSPHERE, Standard_True);
	TopoDS_ShapeCONE = stepBRepTransformationTOPBOX.Shape();

	//VTKpointOnMeshes
	vtkNew<vtkPoints> VTKpointsOnMeshes;
	vtkNew<vtkCellArray> verticesForVTKpointsOnMeshes;
	vtkIdType pid[1];

	//vtkPolyData creation
	vtkNew<vtkPolyData> PolyDataVTKPointsOnMeshes;

	//vtkPolyData initialization
	PolyDataVTKPointsOnMeshes->SetPoints(VTKpointsOnMeshes);
	PolyDataVTKPointsOnMeshes->SetVerts(verticesForVTKpointsOnMeshes);
	
	//VTKpoint IGES, STEP TopoDS_ShapeBOX CALC   
	Bnd_Box aabb;
	//AABB ALGO Per TopoDS_Shape mesh  , Please choose the source you like to run and put it in next line
	BRepBndLib::Add(TopoDS_ShapeCONE, aabb, true); //TopoDS_ShapeIGES  //TopoDS_ShapeSTEP //TopoDS_ShapeCONE
	//VTKpointIGES CALC per TopoDS_Shape mesh
	int density = 20;
	gp_XYZ Pmin = aabb.CornerMin().XYZ();
	gp_XYZ Pmax = aabb.CornerMax().XYZ();
	gp_XYZ D = Pmax - Pmin;
	double dim[3] = { D.X(),D.Y(),D.Z() };
	double mind = Min(dim[0], Min(dim[1], dim[2]));
	const double d = mind / density;
	int nslice[3] = {
		int(Round(dim[0] / d)) + 1 ,
		int(Round(dim[1] / d)) + 1 ,
		int(Round(dim[2] / d)) + 1 };
	for (int i = 0; i < nslice[0]; ++i)
		for (int j = 0; j < nslice[1]; ++j)
			for (int k = 0; k < nslice[2]; ++k)
			{
				gp_XYZ p = Pmin
					+ gp_XYZ(d * i, 0, 0)
					+ gp_XYZ(0, d * j, 0)
					+ gp_XYZ(0, 0, d * k);
				pid[0] = VTKpointsOnMeshes->InsertNextPoint(p.X(), p.Y(), p.Z());
				verticesForVTKpointsOnMeshes->InsertNextCell(1, pid);
			};
	
	//Append the meshes
	vtkNew<vtkAppendPolyData> appendFilter;
	appendFilter->AddInputData(PolyDataVTKPointsOnMeshes);

	//Remove any duplicate points.
	vtkNew<vtkCleanPolyData> cleanFilterForMapperVTKShapes;
	cleanFilterForMapperVTKShapes->SetInputConnection(appendFilter->GetOutputPort());
	cleanFilterForMapperVTKShapes->Update();

	//Create mappers
	vtkNew<vtkPolyDataMapper> mapperVTKShapes;
	vtkNew<vtkPolyDataMapper> mapperTOPOCONE;

	vtkNew<IVtkTools_ShapeDataSource> TOPOCONESource;
	TOPOCONESource->SetShape(new IVtkOCC_Shape(TopoDS_ShapeCONE));

	//Mappers Intialize
	mapperVTKShapes->SetInputConnection(cleanFilterForMapperVTKShapes->GetOutputPort());
    mapperTOPOCONE->SetInputConnection(TOPOCONESource->GetOutputPort());

	//Create Actors
	vtkNew<vtkActor> actorVTKShapes;
	vtkNew<vtkActor> actorTOPOCONE;

	//Actors Intialize
	actorVTKShapes->SetMapper(mapperVTKShapes);
	actorTOPOCONE->SetMapper(mapperTOPOCONE);

    m_renderer->AddActor(actorVTKShapes);
    m_renderer->AddActor(actorTOPOCONE);

    renderWindow()->Render();
}

void SceneWidget::removeDataSet()
{
    vtkActor* actor = m_renderer->GetActors()->GetLastActor();
    if (actor != nullptr) {
        m_renderer->RemoveActor(actor);
    }

    renderWindow()->Render();
}

void SceneWidget::zoomToExtent()
{
    // Zoom to extent of last added actor
    vtkSmartPointer<vtkActor> actor = m_renderer->GetActors()->GetLastActor();
    if (actor != nullptr) {
        m_renderer->ResetCamera(actor->GetBounds());
    }

    renderWindow()->Render();
}

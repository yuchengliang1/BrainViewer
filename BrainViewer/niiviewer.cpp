#include "niiviewer.h"
#include "ui_niiviewer.h"
#include <QApplication>

NiiViewer::NiiViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NiiViewer)
{
    ui->setupUi(this);
    saggitalWidget = ui->sagittalViewPanel;
    coronalWidget = ui->coronalViewPanel;
    transverseWidget = ui->transverseViewPanel;
    view3DWidget = ui->View3DPanel;

	imageReader = FileReader::New();

	connector = ConnectorType::New();

	m_vtkImage_data = NULL;

	for (int i = 0; i < 4; i++)
	{
		actor[i] = vtkSmartPointer<vtkImageActor>::New();
		renderer[i] = vtkSmartPointer<vtkRenderer>::New();
		renderWindowInteractor[i] = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		style[i] = vtkSmartPointer<wheelCancelInteractorStyle>::New();
		viewer[i] = vtkSmartPointer<myVtkViewer>::New();
	}
}

NiiViewer::~NiiViewer()
{
    delete ui;
}

void NiiViewer::initialize(QString fileName) {
    imageReader->SetFileName(fileName.toStdString());
    imageReader->Update();

	connector->SetInput(imageReader->GetOutput());
	connector->Update();

	m_vtkImage_data = connector->GetOutput();

	vtkSmartPointer<vtkImageHistogramStatistics> stats = vtkSmartPointer<vtkImageHistogramStatistics>::New();
	stats->SetAutoRangePercentiles(0.1, 99.9);
	stats->SetAutoRangeExpansionFactors(0.0, 0.0);
	stats->SetInputData(connector->GetOutput());
	stats->Update();
	double* intensityRange0 = stats->GetAutoRange();
	double window = intensityRange0[1] - intensityRange0[0];
	double level = 0.5 * (intensityRange0[0] + intensityRange0[1]);

	//auto reslice = vtkSmartPointer<vtkImageReslice>::New();
	//reslice->SetInputData(connector->GetOutput());
	//int* extent = connector->GetOutput()->GetExtent();
	//// int zSlice = extent[4] + (extent[5] - extent[4]) / 2; // 中间切片
	//reslice->SetResliceAxesDirectionCosines(0, 1, 0, 1, 0, 0, 0, 0, 1); // 轴向
	//reslice->SetOutputExtent(extent[0], extent[1], extent[2], extent[3], 0, 0);
	//reslice->Update();
	//viewer[0]->SetInputData(connector->GetOutput());
	//viewer[0]->SetColorLevel(level);
	//viewer[0]->SetColorWindow(window);
	//viewer[0]->SetSliceOrientationToYZ();
	//viewer[0]->SetSlice(0);
	//viewer[0]->SetRenderer(renderer[0]);
	//viewer[0]->SetRenderWindow(transverseWidget->GetRenderWindow());
	//viewer[0]->Render();
	//vtkSmartPointer<vtkImageInteractionCallback> callback = vtkSmartPointer<vtkImageInteractionCallback>::New();
	//callback->SetImageViewer(viewer[0]);
	//renderWindowInteractor[0]->AddObserver(vtkCommand::MouseWheelForwardEvent, callback);
	//renderWindowInteractor[0]->AddObserver(vtkCommand::MouseWheelBackwardEvent, callback);
	//renderWindowInteractor[0]->SetInteractorStyle(style[0]);
	//viewer[0]->SetupInteractor(renderWindowInteractor[0]);

	viewer[1]->SetInputData(connector->GetOutput());
	viewer[1]->SetColorLevel(level);
	viewer[1]->SetColorWindow(window);
	viewer[1]->SetRenderer(renderer[1]);
	viewer[1]->SetSliceOrientationToYZ();
	viewer[1]->SetRenderWindow(saggitalWidget->GetRenderWindow());
	viewer[1]->SetSlice(20);
	vtkSmartPointer<vtkImageInteractionCallback> callback1 = vtkSmartPointer<vtkImageInteractionCallback>::New();
	callback1->SetImageViewer(viewer[1]);
	renderWindowInteractor[1]->AddObserver(vtkCommand::MouseWheelForwardEvent, callback1);
	renderWindowInteractor[1]->AddObserver(vtkCommand::MouseWheelBackwardEvent, callback1);
	renderWindowInteractor[1]->SetInteractorStyle(style[1]);
	viewer[1]->SetupInteractor(renderWindowInteractor[1]);


	//viewer[2]->SetInputData(connector->GetOutput());
	//viewer[2]->SetColorLevel(level);
	//viewer[2]->SetColorWindow(window);
	//viewer[2]->SetSliceOrientationToYZ();
	//viewer[2]->SetSlice(0);
	//viewer[2]->SetRenderer(renderer[2]);
	//viewer[2]->SetRenderWindow(coronalWidget->GetRenderWindow());
	//viewer[2]->Render();
	//vtkSmartPointer<vtkImageInteractionCallback> callback2 = vtkSmartPointer<vtkImageInteractionCallback>::New();
	//callback2->SetImageViewer(viewer[2]);
	//renderWindowInteractor[2]->AddObserver(vtkCommand::MouseWheelForwardEvent, callback2);
	//renderWindowInteractor[2]->AddObserver(vtkCommand::MouseWheelBackwardEvent, callback2);
	//renderWindowInteractor[2]->SetInteractorStyle(style[2]);
	//viewer[2]->SetupInteractor(renderWindowInteractor[2]);


	//renderWindowInteractor[0]->Start();
	renderWindowInteractor[1]->Start();
	// renderWindowInteractor[2]->Start();
}

void NiiViewer::ComputeOptimalZoom(int sliceOrientation = 0) {
	int* mImageSize = m_vtkImage_data->GetDimensions();
	double* mImageSpacing = m_vtkImage_data->GetSpacing();

	double worldSize[2];
	switch (sliceOrientation) {
		case 0:
			worldSize[0] = mImageSize[0] * mImageSpacing[0];
			worldSize[1] = mImageSize[1] * mImageSpacing[1];
			break;
		case 1:
			worldSize[0] = mImageSize[0] * mImageSpacing[0];
			worldSize[1] = mImageSize[2] * mImageSpacing[2];
			break;
		case 2:
			worldSize[0] = mImageSize[1] * mImageSpacing[1];
			worldSize[1] = mImageSize[2] * mImageSpacing[2];
			break;
	}

	double widgetPixel[2];
	widgetPixel[0] = saggitalWidget->width() * saggitalWidget->devicePixelRatio();
	widgetPixel[1] = saggitalWidget->height() * saggitalWidget->devicePixelRatio();

	vtkVector2d ratios(widgetPixel[0]/ worldSize[0], widgetPixel[1] / worldSize[1]);
	double minValue = std::min(ratios.GetX(), ratios.GetY());
	m_optimal_zoom = minValue;
}
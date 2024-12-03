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
	imageReader2 = FileReader::New();
	connector = ConnectorType::New();
	connector2 = ConnectorType::New();

	for (int i = 0; i < 4; i++)
	{
		actor[i] = vtkSmartPointer<vtkImageActor>::New();
		renderer[i] = vtkSmartPointer<vtkRenderer>::New();
		renderWindowInteractor[i] = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		viewer[i] = vtkSmartPointer<myVtkViewer>::New();
		m_vtkImage_data[i] = vtkSmartPointer<vtkImageData>::New();
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
	vtkImageData* img = connector->GetOutput();

	//for (int i = 0; i < 4; i++) {
	//	m_vtkImage_data[i]->DeepCopy(img);
	//}
	m_vtkImage_data[0]->DeepCopy(img);
	m_vtkImage_data[1]->DeepCopy(img);

	vtkSmartPointer<vtkImageHistogramStatistics> stats = vtkSmartPointer<vtkImageHistogramStatistics>::New();
	stats->SetAutoRangePercentiles(0.1, 99.9);
	stats->SetAutoRangeExpansionFactors(0.0, 0.0);
	stats->SetInputData(connector->GetOutput());
	stats->Update();

	double* intensityRange0 = stats->GetAutoRange();
	double window = intensityRange0[1] - intensityRange0[0];
	double level = 0.5 * (intensityRange0[0] + intensityRange0[1]);

	viewer[0]->SetInputData(m_vtkImage_data[0]);
	viewer[0]->setCameraScale(ComputeOptimalZoom(NiiViewer::SLICE_ORIENTATION_XY) * 75);
	viewer[0]->SetSliceOrientationToXY();
	viewer[0]->SetColorLevel(level);
	viewer[0]->SetColorWindow(window);
	viewer[0]->SetRenderer(renderer[0]);
	viewer[0]->SetRenderWindow(transverseWidget->GetRenderWindow());
	viewer[0]->Render();
	viewer[0]->SetAutoSlice();
	viewer[0]->SetupInteractor(renderWindowInteractor[0]);
	renderWindowInteractor[0]->Start();
	
	viewer[1]->SetInputData(m_vtkImage_data[1]);
	viewer[1]->setCameraScale(ComputeOptimalZoom(NiiViewer::SLICE_ORIENTATION_YZ) * 75);
	viewer[1]->SetSliceOrientationToYZ();
	viewer[1]->SetColorLevel(level);
	viewer[1]->SetColorWindow(window);
	viewer[1]->SetRenderer(renderer[1]);
	viewer[1]->SetRenderWindow(saggitalWidget->GetRenderWindow());
	viewer[1]->Render();
	viewer[1]->SetAutoSlice();
	viewer[1]->SetupInteractor(renderWindowInteractor[1]);

	//viewer[2]->SetInputData(connector->GetOutput());
	//viewer[2]->setCameraScale(ComputeOptimalZoom(NiiViewer::SLICE_ORIENTATION_XZ) * 75);
	//viewer[2]->SetSliceOrientationToXZ();
	//viewer[2]->SetColorLevel(level);
	//viewer[2]->SetColorWindow(window);
	//viewer[2]->SetRenderer(renderer[2]);
	//viewer[2]->SetRenderWindow(coronalWidget->GetRenderWindow());
	//viewer[2]->Render();
	//viewer[2]->SetAutoSlice();
	//vtkSmartPointer<vtkImageInteractionCallback> callback2 = vtkSmartPointer<vtkImageInteractionCallback>::New();
	//callback2->SetImageViewer(viewer[2]);
	//renderWindowInteractor[2]->AddObserver(vtkCommand::MouseWheelForwardEvent, callback2);
	//renderWindowInteractor[2]->AddObserver(vtkCommand::MouseWheelBackwardEvent, callback2);
	//renderWindowInteractor[2]->SetInteractorStyle(style[2]);
	//viewer[2]->SetupInteractor(renderWindowInteractor[2]);

	
	renderWindowInteractor[1]->Start();
	//renderWindowInteractor[2]->Start();

}

double NiiViewer::ComputeOptimalZoom(int sliceOrientation = 0) {
	int* mImageSize = m_vtkImage_data[0]->GetDimensions();
	double* mImageSpacing = m_vtkImage_data[0]->GetSpacing();

	double worldSize[2];
	switch (sliceOrientation) {
		case NiiViewer::SLICE_ORIENTATION_XY:
			worldSize[0] = mImageSize[0] * mImageSpacing[0];
			worldSize[1] = mImageSize[1] * mImageSpacing[1];
			break;
		case NiiViewer::SLICE_ORIENTATION_XZ:
			worldSize[0] = mImageSize[0] * mImageSpacing[0];
			worldSize[1] = mImageSize[2] * mImageSpacing[2];
			break;
		case NiiViewer::SLICE_ORIENTATION_YZ:
			worldSize[0] = mImageSize[1] * mImageSpacing[1];
			worldSize[1] = mImageSize[2] * mImageSpacing[2];
			break;
	}

	double widgetPixel[2];
	widgetPixel[0] = saggitalWidget->width() * saggitalWidget->devicePixelRatio();
	widgetPixel[1] = saggitalWidget->height() * saggitalWidget->devicePixelRatio();

	vtkVector2d ratios(widgetPixel[0]/ worldSize[0], widgetPixel[1] / worldSize[1]);
	double minValue = std::min(ratios.GetX(), ratios.GetY());
	return minValue;
}
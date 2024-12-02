#ifndef NIIVIEWER_H
#define NIIVIEWER_H

#include <QWidget>
#include <itkImage.h>
#include <itkImageToVTKImageFilter.h>
#include <itkImageFileReader.h>
#include "myVtkViewer.h"
#include "vtkImageHistogramStatistics.h"
#include <QVTKWidget.h>
#include <vtkImageReslice.h>
#include <vtkVector.h>

namespace Ui {
class NiiViewer;
}

class NiiViewer : public QWidget
{
	Q_OBJECT
    typedef float PixelType;
    typedef itk::Image<PixelType, 3> ImageType;
    typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
    typedef itk::ImageFileReader<ImageType> FileReader;
public:
    explicit NiiViewer(QWidget *parent = nullptr);
    ~NiiViewer();
    void initialize(QString fileName);
    void ComputeOptimalZoom(int);

private:
    Ui::NiiViewer *ui;
    FileReader::Pointer imageReader;
    QVTKWidget* saggitalWidget;
    QVTKWidget* coronalWidget;
    QVTKWidget* transverseWidget;
    QVTKWidget* view3DWidget;
    vtkSmartPointer<vtkImageActor> actor[4];
    vtkSmartPointer<vtkRenderer> renderer[4];
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor[4];
    vtkSmartPointer<wheelCancelInteractorStyle> style[4];
    ConnectorType::Pointer connector;
    vtkSmartPointer<myVtkViewer> viewer[4];
    vtkImageData* m_vtkImage_data;
    double m_optimal_zoom;
};

#endif // NIIVIEWER_H

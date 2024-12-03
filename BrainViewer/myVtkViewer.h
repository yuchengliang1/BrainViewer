#pragma once

#include "vtkInteractionImageModule.h" // For export macro
#include "vtkObject.h"


#include <vtkAlgorithm.h>
#include <vtkImageActor.h>
#include <vtkActor.h>
#include <vtkTextMapper.h>
#include <vtkImageViewer2.h>
#include <sstream>
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>

#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>

#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <qdebug.h>

class wheelCancelInteractorStyle : public vtkInteractorStyleImage
{
public:
    static wheelCancelInteractorStyle* New();
    vtkTypeMacro(wheelCancelInteractorStyle, vtkInteractorStyleImage);
protected:
    virtual void OnMouseWheelForward()override;
    virtual void OnMouseWheelBackward()override;
};

class myVtkViewer : public vtkObject
{
public:
    static myVtkViewer* New();
    vtkTypeMacro(myVtkViewer, vtkObject);
    virtual void Render();
    virtual void SetInputData(vtkImageData* in);
    enum
    {
        SLICE_ORIENTATION_YZ = 0,
        SLICE_ORIENTATION_XZ = 1,
        SLICE_ORIENTATION_XY = 2
    };
    vtkGetMacro(SliceOrientation, int);
    virtual void SetSliceOrientation(int orientation);
    virtual void SetSliceOrientationToXY()
    {
        this->SetSliceOrientation(myVtkViewer::SLICE_ORIENTATION_XY);
    }
    virtual void SetSliceOrientationToYZ()
    {
        this->SetSliceOrientation(myVtkViewer::SLICE_ORIENTATION_YZ);
    }
    virtual void SetSliceOrientationToXZ()
    {
        this->SetSliceOrientation(myVtkViewer::SLICE_ORIENTATION_XZ);
    }
    virtual int* GetSize();
    virtual int GetSlice();
    virtual void SetSlice(int s);
    virtual void SetPosition(int x, int y);
    virtual int* GetPosition();
    virtual void SetDisplayId(void* a);
    virtual void SetWindowId(void* a);
    virtual void SetParentId(void* a);
    virtual vtkImageData* GetInput();
    virtual void UpdateDisplayExtent();
    virtual int GetSliceMin();
    virtual int GetSliceMax();
    virtual void GetSliceRange(int range[2]) { this->GetSliceRange(range[0], range[1]); }
    virtual void GetSliceRange(int& min, int& max);
    virtual int* GetSliceRange();
    virtual double GetColorWindow();
    virtual double GetColorLevel();
    virtual void SetColorWindow(double s);
    virtual void SetColorLevel(double s);
    virtual void SetSize(int width, int height);
    virtual void SetSize(int a[2]) { this->SetSize(a[0], a[1]); }
    vtkGetObjectMacro(RenderWindow, vtkRenderWindow);
    vtkGetObjectMacro(Renderer, vtkRenderer);
    vtkGetObjectMacro(ImageActor, vtkImageActor);
    vtkGetObjectMacro(WindowLevel, vtkImageMapToWindowLevelColors);
    vtkGetObjectMacro(InteractorStyle, vtkInteractorStyleImage);

    virtual void SetRenderWindow(vtkRenderWindow* arg);
    virtual void SetRenderer(vtkRenderer* arg);
    virtual void SetupInteractor(vtkRenderWindowInteractor*);
    virtual void setCameraScale(double scale);
    virtual void SetAutoSlice();
protected:
    myVtkViewer();
    ~myVtkViewer() override;

    virtual void InstallPipeline();
    virtual void UnInstallPipeline();

    vtkImageMapToWindowLevelColors* WindowLevel;
    vtkRenderWindow* RenderWindow;
    vtkRenderer* Renderer;
    vtkImageActor* ImageActor;
    vtkRenderWindowInteractor* Interactor;
    vtkInteractorStyleImage* InteractorStyle;

    int SliceOrientation;
    int FirstRender;
    int Slice;

    virtual void UpdateOrientation();

    vtkAlgorithm* GetInputAlgorithm();
    vtkInformation* GetInputInformation();

    friend class myVtkViewerCallback;

private:
    myVtkViewer(const myVtkViewer&) = delete;
    void operator=(const myVtkViewer&) = delete;
    double m_scale = 1;
};


class vtkImageInteractionCallback : public vtkCommand
{
public:
    static vtkImageInteractionCallback* New() { return new vtkImageInteractionCallback; }

    void Execute(vtkObject* caller, unsigned long event, void* vtkNotUsed(callData)) override
    {
        if (this->Viewer->GetInput() == nullptr)
        {
            return;
        }

        if (event == vtkCommand::MouseWheelForwardEvent)
        {
            auto sliceIndex = this->Viewer->GetSlice();
            this->Viewer->SetSlice(sliceIndex + 1);
            this->Viewer->Render();
            return;
        }

        if (event == vtkCommand::MouseWheelBackwardEvent)
        {
            auto sliceIndex = this->Viewer->GetSlice();
            this->Viewer->SetSlice(sliceIndex - 1);
            this->Viewer->Render();
            return;
        }
        this->Viewer->Render();
    }
    myVtkViewer* Viewer;
};

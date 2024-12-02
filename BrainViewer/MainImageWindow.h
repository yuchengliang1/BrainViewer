#ifndef MAINIMAGEWINDOW_H
#define MAINIMAGEWINDOW_H

#include <QMainWindow>

class GenericSliceView;
class SliceViewPanel;
class GlobalUIModel;
class QDockWidget;
class SnakeWizardPanel;
class EventBucket;
class QModelIndex;
class QProgressDialog;
class AboutDialog;
class QStackedWidget;

class LabelEditorDialog;
class LayerInspectorDialog;
class QtProgressReporterDelegate;
class ReorientImageDialog;
class RegistrationDialog;
class DropActionDialog;
class MainControlPanel;
class StatisticsDialog;
class QActionGroup;
class PreferencesDialog;
class InterpolateLabelsDialog;
class SmoothLabelsDialog;
class ImageIOWizard;
class ImageIOWizardModel;
class DistributedSegmentationDialog;

class QTimer;

class SplashPanel;

#include <QDebug>

namespace Ui {
class MainImageWindow;
}

class MainImageWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainImageWindow(QWidget *parent = 0);
  ~MainImageWindow();

  SliceViewPanel *GetSlicePanel(unsigned int i);

  // Initialize with a model
  void Initialize(GlobalUIModel *model);

public slots:

  void LoadMainImage(const QString &file);


private slots:

  void on_actionZoomToFitInAllViews_triggered();

  void on_actionSSSeriesAxial_triggered();

  void on_actionSSSeriesCoronal_triggered();

  void on_actionSSSeriesSagittal_triggered();

  void on_actionZoom_to_100_triggered();

  void on_actionZoom_to_200_triggered();

  void on_actionZoom_to_400_triggered();

  void on_actionClose_Window_triggered();


  void on_actionToggle_Volume_Rendering_triggered();

  void on_actionToggle_4D_Replay_triggered();

  void on_actionSwitch_Foreground_Background_Labels_triggered();


  void on_actionFree_Rotation_Mode_triggered();

protected:

  // bool eventFilter(QObject *obj, QEvent *event);

  // Change event (for tracking active / non-active window)
  virtual void changeEvent(QEvent *);

private:
  // For convenience, an array of the four panels (3 slice/1 3D)
  QWidget *m_ViewPanels[4];

  Ui::MainImageWindow *ui;

  GlobalUIModel *m_Model;

  SplashPanel *m_SplashPanel;
};



#endif // MAINIMAGEWINDOW_H

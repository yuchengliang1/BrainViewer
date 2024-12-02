#include "MeshOptions.h"

#include "MainImageWindow.h"
#include "ui_MainImageWindow.h"

#include "MainControlPanel.h"
#include "ImageIOWizard.h"
#include "ImageIOWizardModel.h"
#include "GlobalUIModel.h"
#include "ImageIODelegates.h"
#include "LayerInspectorDialog.h"
#include "IntensityCurveModel.h"
#include "DisplayLayoutModel.h"
#include "ColorMapModel.h"
#include "ViewPanel3D.h"
#include "SnakeWizardPanel.h"
#include "LatentITKEventNotifier.h"
#include <QProgressDialog>
#include "QtReporterDelegates.h"
#include "SliceWindowCoordinator.h"
#include "HistoryQListModel.h"
#include "GenericView3D.h"
#include "GenericSliceView.h"
#include "SplashPanel.h"
#include "QtWidgetCoupling.h"
#include "SimpleFileDialogWithHistory.h"
#include "StatisticsDialog.h"
#include "MeshExportWizard.h"
#include "MeshImportWizard.h"
#include "MeshImportModel.h"
#include "ImageWrapperBase.h"
#include "IRISImageData.h"
#include "AboutDialog.h"
#include "HistoryManager.h"
#include "DefaultBehaviorSettings.h"
#include "SynchronizationModel.h"
#include "LayoutReminderDialog.h"
#include "AllPurposeProgressAccumulator.h"
#include "LabelEditorModel.h"
#include "RegistrationModel.h"

#include "QtCursorOverride.h"
#include "QtWarningDialog.h"
#include <QtWidgetCoupling.h>
#include <QtWidgetActivator.h>
#include <QtActionGroupCoupling.h>

#include <LabelEditorDialog.h>
#include <ReorientImageDialog.h>
#include <DropActionDialog.h>
#include <PreferencesDialog.h>
#include "SaveModifiedLayersDialog.h"
#include <InterpolateLabelsDialog.h>
#include <SmoothLabelsDialog.h>
#include "RegistrationDialog.h"
#include "DistributedSegmentationDialog.h"

#include <QAbstractListModel>
#include <QItemDelegate>
#include <QPainter>
#include <QDockWidget>
#include <QMessageBox>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QUrl>
#include <QFileDialog>
#include <QDesktopServices>
#include <SNAPQtCommon.h>
#include <QMimeData>
#include <QShortcut>
#include <QScreen>
#include <QTextStream>

MainImageWindow::MainImageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainImageWindow),
    m_Model(NULL)
{
  ui->setupUi(this);

  // Make sure we initialize on the intro page
  ui->stackMain->setCurrentWidget(ui->pageSplash);

  // Create the view panels array
  m_ViewPanels[0] = ui->panel0;
  m_ViewPanels[1] = ui->panel1;
  m_ViewPanels[2] = ui->panel2;
  m_ViewPanels[3] = ui->panel3D;
  m_SplashPanel = new SplashPanel(this);
}


MainImageWindow::~MainImageWindow()
{
  delete ui;
}

void MainImageWindow::Initialize(GlobalUIModel *model)
{
  m_Model = model;

  // Initialize all the child panels
  ui->panel0->Initialize(model,0);
  ui->panel1->Initialize(model,1);
  ui->panel2->Initialize(model,2);
  ui->panel3D->Initialize(model);
}


void MainImageWindow::UpdateMainLayout()
{
    // Update the layout depending on whether this is a 2D or 3D image
    auto *main = m_Model->GetDriver()->GetIRISImageData()->GetMain();

    // If the image is 2D, update the display layout to only show the 2D view
    auto *dlm = m_Model->GetDisplayLayoutModel();
    if(main->GetSize()[2] == 1)
    {
        for (int i = 0; i < 3; i++)
        {
            auto *slice_model = m_Model->GetSliceModel(i);
            if (slice_model->GetSliceDirectionInImageSpace() == 2)
            {
                auto layout = dlm->GetViewPanelExpandButtonActionModel(i)->GetValue();
                dlm->GetViewPanelLayoutModel()->SetValue(layout);
                break;
            }
        }
    }
    else
    {
        dlm->GetViewPanelLayoutModel()->SetValue(DisplayLayoutModel::VIEW_ALL);
    }

    // Update the image dimensions
    this->UpdateCanvasDimensions();

    // Choose what page to show depending on if an image has been loaded
    if(m_Model->GetDriver()->IsMainImageLoaded())
    {
        ui->stackMain->setCurrentWidget(ui->pageMain);
        m_DockLeft->setWidget(m_ControlPanel);
    }
    else
    {
        // Go to the splash page
        ui->stackMain->setCurrentWidget(ui->pageSplash);
        m_DockLeft->setWidget(m_SplashPanel);

        // Choose the appropriate page depending on whether there are recent images
        // available
        if(m_Model->IsHistoryEmpty("MainImage"))
            ui->tabSplash->setCurrentWidget(ui->tabGettingStarted);

        else if(ui->tabSplash->currentWidget() == ui->tabGettingStarted)
            ui->tabSplash->setCurrentWidget(ui->tabRecent);
    }
}


void MainImageWindow::UpdateCanvasDimensions()
{
  // We should not do this in fullscreen mode
  Qt::WindowStates ws = this->windowState();
  if(ws.testFlag(Qt::WindowFullScreen))
    {
    return;
    }

  // The desired window aspect ratio
  double windowAR = 1.0;

  // Get the current aspect ratio
  if(m_Model->GetDriver()->IsMainImageLoaded())
    {
    if(m_Model->GetDisplayLayoutModel()->GetSliceViewLayerLayoutModel()->GetValue() == LAYOUT_TILED)
      {
      Vector2ui tiling =
          m_Model->GetDisplayLayoutModel()->GetSliceViewLayerTilingModel()->GetValue();

      // Compute the tiling aspect ratio
      double tilingAR = tiling(1) * 1.0 / tiling(0);

      // The tiling aspect ratio should not be mapped directly to the screen aspect ratio -
      // this creates configurations that are too wide. Instead, we will use a scaling factor
      windowAR = (tilingAR - 1.0) * 0.6 + 1.0;
      }
    else if(m_Model->GetDisplayLayoutModel()->GetNumberOfGroundLevelLayers() > 1)
      {
      windowAR = 1.0 / 0.88;
      }
    }

  // Adjust the width of the screen to achieve desired aspect ratio
  int cw_width = static_cast<int>(windowAR * ui->centralwidget->height());
  int mw_width = this->width() + (cw_width - ui->centralwidget->width());

  // Adjust the width to be within the desktop dimensions
  auto desktop = this->screen()->availableGeometry();
  mw_width = std::min(desktop.width(), mw_width);

  // Store the old width
  int old_width = this->width();
  this->resize(QSize(mw_width, this->height()));

  // Deterimine the left point
  int left = std::max(0, this->pos().x() + (old_width - this->width()) / 2);

  // Adjust the left point if necessary
  if(left + this->width() > desktop.right())
    left = std::max(0, desktop.right() - this->width());

  // Now we want to position the window nicely.
  this->move(left, this->pos().y());
}


void MainImageWindow::UpdateLayerLayoutActions()
{
  DisplayLayoutModel *dlm = m_Model->GetDisplayLayoutModel();
  LayerLayout ll = dlm->GetSliceViewLayerLayoutModel()->GetValue();
  if(ll == LAYOUT_TILED)
    {
    ui->actionToggleLayerLayout->setIcon(QIcon(":/root/layout_thumb_16.png"));
    ui->actionToggleLayerLayout->setText("Enter Thumbnail Layout");
    }
  else if(ll == LAYOUT_STACKED)
    {
    ui->actionToggleLayerLayout->setIcon(QIcon(":/root/layout_tile_16.png"));
    ui->actionToggleLayerLayout->setText("Enter Tiled Layout");
    }
}

void MainImageWindow::UpdateSelectedLayerActions()
{
  // Find the selected layer
  ImageWrapperBase *layer =
      m_Model->GetDriver()->GetCurrentImageData()->FindLayer(
        m_Model->GetGlobalState()->GetSelectedLayerId(), false);

  if(layer)
    {
    ui->actionUnload_Last_Overlay->setVisible(true);
    ui->actionUnload_Last_Overlay->setEnabled(true);
    ui->actionUnload_Last_Overlay->setText(
          QString("Close image \"%1\"").arg(from_utf8(layer->GetNickname())));
    }
  else
    {
    ui->actionUnload_Last_Overlay->setVisible(false);
    ui->actionUnload_Last_Overlay->setEnabled(false);
    ui->actionUnload_Last_Overlay->setText("Close selected image");
    }
}

Q_DECLARE_METATYPE(IRISApplication::DicomSeriesDescriptor)

void MainImageWindow::UpdateDICOMContentsMenu()
{
  // Clear the menu
  ui->menuAddAnotherDicomImage->clear();

  // Any actions added?
  bool have_actions = false;

  // Get the list of dicom series grouped by filename
  IRISApplication::DicomSeriesTree dicoms =
      m_Model->GetDriver()->ListAvailableSiblingDicomSeries();

  // Iterate over all of these
  for(IRISApplication::DicomSeriesTree::const_iterator it_map = dicoms.begin();
      it_map != dicoms.end(); ++it_map)
    {
    // Create a submenu or point to the menu itself
    QMenu *target_menu = ui->menuAddAnotherDicomImage;
    if(dicoms.size() > 1)
      {
      target_menu = new QMenu(from_utf8(it_map->first), ui->menuAddAnotherDicomImage);
      ui->menuAddAnotherDicomImage->addMenu(target_menu);
      }

    // Add all the series_ids as actions
    for(IRISApplication::DicomSeriesListing::const_iterator it_list =
        it_map->second.begin(); it_list != it_map->second.end(); it_list++)
      {
      // Create a new action
      QAction *action = new QAction(this);
      QVariant user_data; user_data.setValue(*it_list);
      action->setData(user_data);
      action->setText(QString("%1 [%2]")
                      .arg(from_utf8(it_list->series_desc))
                      .arg(from_utf8(it_list->dimensions)));

      // Connect this action to its slot
      connect(action, SIGNAL(triggered()),
              this, SLOT(LoadAnotherDicomActionTriggered()));

      // Add the action to the menu
      target_menu->addAction(action);

      // We have some actions!
      have_actions = true;
      }
    }

  // Hide or show the menu based on availability of actions
  ui->menuAddAnotherDicomImage->menuAction()->setVisible(have_actions);
}

void MainImageWindow::CreateRecentMenu(
    QMenu *submenu,
    const char *history_category,
    bool use_global_history,
    int max_items,
    const char *slot,
    bool use_shortcut, int shortcut_modifier)
{
  // Delete all the menu items in the parent menu
  submenu->clear();

  // Get the recent history for this category
  std::vector<std::string> recent =
      m_Model->GetRecentHistoryItems(history_category, max_items, use_global_history);

  // Create an action for each recent item
  for(int i = 0; i < recent.size(); i++)
    {
    // Create an action for this file
    QAction *action = submenu->addAction(from_utf8(recent[i]));
    if(use_shortcut && i < 10)
      action->setShortcut(QKeySequence(shortcut_modifier + Qt::Key_1 + i));
    connect(action, SIGNAL(triggered(bool)), this, slot);
    }

  // Toggle the visibility of the submenu
  submenu->menuAction()->setVisible(recent.size() > 0);
}

void MainImageWindow::UpdateRecentMenu()
{
  // Create recent menus for various history categories
  this->CreateRecentMenu(ui->menuRecent_Images, "MainImage", true, 5,
                         SLOT(LoadRecentActionTriggered()), true, Qt::CTRL);

  this->CreateRecentMenu(ui->menuRecent_Overlays, "AnatomicImage", false, 5,
                         SLOT(LoadRecentOverlayActionTriggered()), true, Qt::CTRL | Qt::SHIFT);

  this->CreateRecentMenu(ui->menuRecent_Segmentations, "LabelImage", false, 5,
                         SLOT(LoadRecentSegmentationActionTriggered()));

  this->CreateRecentMenu(ui->menuAddSegmentation_Recent, "LabelImage", false, 5,
                         SLOT(LoadAnotherRecentSegmentationActionTriggered()));

  this->CreateRecentMenu(ui->menuRecentLabelDefs, "LabelDescriptions", true, 5,
                         SLOT(LoadRecentLabelDefinitionsTriggered()));
}

void MainImageWindow::UpdateRecentProjectsMenu()
{
  this->CreateRecentMenu(ui->menuRecentWorkspaces, "Project", true, 5,
                         SLOT(LoadRecentProjectActionTriggered()));
}



void MainImageWindow::UpdateWindowTitle()
{
  GenericImageData *gid = m_Model->GetDriver()->GetIRISImageData();
  bool is4D = m_Model->GetDriver()->GetNumberOfTimePoints() > 1;
  QString mainfile, segfile, projfile;
  if(gid && gid->IsMainLoaded())
    {
    mainfile = QFileInfo(from_utf8(gid->GetMain()->GetFileName())).fileName();
    if(m_Model->GetDriver()->GetSelectedSegmentationLayer())
      segfile = QFileInfo(from_utf8(m_Model->GetDriver()->GetSelectedSegmentationLayer()->GetFileName())).fileName();
    }

  // If a project is loaded, we display the project title
  if(m_Model->GetGlobalState()->GetProjectFilename().length())
    projfile = QFileInfo(from_utf8(m_Model->GetGlobalState()->GetProjectFilename())).fileName();

  // Set up the window title
  if(projfile.length())
    {
    // If a project has multiple layers, we should indicate which segmentation image is being viewed
    this->setWindowTitle(QString("%1 - ITK-SNAP").arg(projfile));
    }
  else if(mainfile.length() && segfile.length())
    {
    this->setWindowTitle(QString("%1 - %2 - ITK-SNAP").arg(mainfile).arg(segfile));
    }
  else if(mainfile.length())
    {
    this->setWindowTitle(QString("%1 - New Segmentation - ITK-SNAP").arg(mainfile));
    }
  else
    {
    this->setWindowTitle("ITK-SNAP");
    }

  // Set up the save segmentation menu items
  if(segfile.length())
    {
    ui->actionSaveSegmentation->setText(QString("Save \"%1\"").arg(segfile));
    ui->actionSaveSegmentationAs->setText(QString("Save \"%1\" as...").arg(segfile));
    ui->actionSaveSegmentationAs->setVisible(true);
    ui->actionReloadSegmentation->setText(QString("Reload \"%1\" from File").arg(segfile));
    ui->actionReloadSegmentation->setVisible(true);
    }
  else if(mainfile.length())
    {
    QString infix4D(is4D ? "4D " : "");
    ui->actionSaveSegmentation->setText(QString("Save %1Segmentation Image ...").arg(infix4D));
    ui->actionSaveSegmentationAs->setVisible(false);
    ui->actionReloadSegmentation->setVisible(false);
    }
  else
    {
    ui->actionSaveSegmentation->setText(QString("Save"));
    ui->actionSaveSegmentationAs->setText(QString("Save as..."));
    ui->actionReloadSegmentation->setVisible(false);
    }

  // Set up the segmentation items
  if(gid->GetNumberOfLayers(LABEL_ROLE) > 1)
    {
    ui->actionClear->setText(QString("Unload All Segmentations"));
    ui->actionClearActive->setVisible(true);
    if(segfile.length())
      ui->actionClearActive->setText(QString("Unload \"%1\"").arg(segfile));
    else
      ui->actionClearActive->setText(QString("Unload Active Segmentation"));
    }
  else
    {
    ui->actionClear->setText(QString("Unload Segmentation"));
    ui->actionClearActive->setVisible(false);
    }
}



SliceViewPanel * MainImageWindow::GetSlicePanel(unsigned int i)
{
  if(i == 0)
    return ui->panel0;
  else if (i == 1)
    return ui->panel1;
  else if (i == 2)
    return ui->panel2;
  else
    return NULL;
}

void MainImageWindow::closeEvent(QCloseEvent *event)
{
  // Prompt for unsaved changes
  if(!SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model))
    {
    event->ignore();
    return;
    }

  // Close all the windows that are open
  QApplication::closeAllWindows();

  // Unload all images (this causes the associations to be saved)
  m_Model->GetDriver()->Quit();

  // Exit the application
  QCoreApplication::exit();
}

void MainImageWindow::on_actionQuit_triggered()
{ 
  // Close the main window
  this->close();
}

void MainImageWindow::on_actionLoad_from_Image_triggered()
{
  // Prompt for unsaved changes
  // -- only prompt for 3d
  if(m_Model->GetDriver()->GetNumberOfTimePoints() == 1 &&
     !SaveModifiedLayersDialog::PromptForUnsavedSegmentationChanges(m_Model))
    return;

  // Create a model for IO
  SmartPtr<LoadSegmentationImageDelegate> delegate = LoadSegmentationImageDelegate::New();
  delegate->Initialize(m_Model->GetDriver());

  SmartPtr<ImageIOWizardModel> model = ImageIOWizardModel::New();
  model->InitializeForLoad(m_Model, delegate);

  // Execute the IO wizard
  ImageIOWizard wiz(this);
  wiz.SetModel(model);
  wiz.exec();
}


void MainImageWindow::on_actionImage_Contrast_triggered()
{
  // Go to the contrast page in the dialog
  m_LayerInspector->SetPageToContrastAdjustment();

  // Show the dialog
  RaiseDialog(m_LayerInspector);
}

void MainImageWindow::on_actionColor_Map_Editor_triggered()
{
  // Go to the contrast page in the dialog
  m_LayerInspector->SetPageToColorMap();

  // Show the dialog
  RaiseDialog(m_LayerInspector);
}

void MainImageWindow::on_actionImage_Information_triggered()
{
  // Go to the contrast page in the dialog
  m_LayerInspector->SetPageToImageInfo();

  // Show the dialog
  RaiseDialog(m_LayerInspector);
}

void MainImageWindow::on_actionLabel_Editor_triggered()
{
  // Execute the label editor
  RaiseDialog(m_LabelEditor);
}

void MainImageWindow::OpenSnakeWizard()
{
  // Initialize the snake wizard
  this->m_SnakeWizard->Initialize();

  // Remember the size of the window before the right dock was shown
  m_SizeWithoutRightDock = this->size();

  // Make the dock containing the wizard visible
  m_DockRight->setWindowTitle("Segment 3D");
  m_RightDockStack->setCurrentWidget(m_SnakeWizard);
  m_DockRight->setVisible(true);
}

void MainImageWindow::AdjustMarginsForDocks()
{
  // Get the current margins
  QMargins margin = ui->centralwidget->layout()->contentsMargins();
  QMargins mld = m_DockLeft->widget()->layout()->contentsMargins();
  QMargins mrd = m_DockRight->widget()->layout()->contentsMargins();

  // Whether each of the docks is attached
  bool leftDockAtLeft =
      (dockWidgetArea(m_DockLeft) == Qt::LeftDockWidgetArea &&
       !m_DockLeft->isWindow() &&
       m_DockLeft->isVisible());

  bool rightDockAtRight =
      (dockWidgetArea(m_DockRight) == Qt::RightDockWidgetArea &&
       !m_DockRight->isWindow() &&
       m_DockRight->isVisible());

  margin.setLeft(leftDockAtLeft ? 0 : 4);
  margin.setRight(rightDockAtRight ? 0 : 4);
  ui->centralwidget->layout()->setContentsMargins(margin);

  mld.setRight(leftDockAtLeft ? 0 : 5);
  m_DockLeft->widget()->layout()->setContentsMargins(mld);

  mrd.setLeft(rightDockAtRight ? 0 : 5);
  m_DockRight->widget()->layout()->setContentsMargins(mrd);

}

void MainImageWindow::dragEnterEvent(QDragEnterEvent *event)
{
  const QMimeData *md = event->mimeData();
  if(md->hasUrls() && md->urls().size() == 1)
    {
    QUrl url = md->urls().first();
    if(url.isLocalFile())
      {
      event->setDropAction(Qt::CopyAction);
      event->accept();
      }
    }
}

void MainImageWindow::LoadDroppedFile(QString file)
{
  try
    {
    std::string filename = to_utf8(file);
    // Check if the dropped file is a project
    if(m_Model->GetDriver()->IsProjectFile(filename.c_str()))
      {
      // For the time being, the feature of opening the workspace in a new
      // window is not implemented. Instead, we just prompt the user for
      // unsaved changes.
      if(!SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model))
        return;

      // Load the project
      LoadProject(file);
      }

    else
      {
      if(m_Model->GetDriver()->IsMainImageLoaded())
        {
        // check if it's a label description file
        if (m_Model->GetDriver()->GetColorLabelTable()->ValidateFile(filename.c_str()))
          {
          m_Model->GetDriver()->LoadLabelDescriptions(filename.c_str());
          return;
          }

        // If an image is already loaded, we show the dialog
        m_DropDialog->SetDroppedFilename(file);
        m_DropDialog->setModal(true);

        RaiseDialog(m_DropDialog);
        }
      else
        {
        // Otherwise, load the main image directly
        m_DropDialog->InitialLoad(file);
        }
      }
    }
  catch (exception &exc) // for minor exceptions, no need to crash the entire program
    {
    ReportNonLethalException(this, exc, "File Dropping Error",
                             QString("Failed to load file %1").arg(file));
    }

}

#ifdef __APPLE__
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFURL.h>
#endif

void MainImageWindow::dropEvent(QDropEvent *event)
{
  QUrl url = event->mimeData()->urls().first();

#if defined(__APPLE__) && QT_VERSION >= 0x050000
  // TODO: this is a Yosemite bug fix - bug https://bugreports.qt.io/browse/QTBUG-40449
  // Check if this is still necessary in future Qt versions (discovered in Qt 5.4)
  if (url.toString().startsWith("file:///.file/id="))
    {
    CFURLRef cfurl = url.toCFURL();
    CFErrorRef error = 0;
    CFURLRef absurl = CFURLCreateFilePathURL(kCFAllocatorDefault, cfurl, &error);
    url = QUrl::fromCFURL(absurl);
    CFRelease(cfurl);
    CFRelease(absurl);
    }

#elif defined(__APPLE__) && QT_VERSION < 0x050000

  QString localFileQString = url.toLocalFile();
  // [pzion 20150805] Work around
  // https://bugreports.qt.io/browse/QTBUG-40449
  if ( localFileQString.startsWith("/.file/id=") )
    {
    CFStringRef relCFStringRef =
        CFStringCreateWithCString(
          kCFAllocatorDefault,
          localFileQString.toUtf8().constData(),
          kCFStringEncodingUTF8
          );
    CFURLRef relCFURL =
        CFURLCreateWithFileSystemPath(
          kCFAllocatorDefault,
          relCFStringRef,
          kCFURLPOSIXPathStyle,
          false // isDirectory
          );
    CFErrorRef error = 0;
    CFURLRef absCFURL =
        CFURLCreateFilePathURL(
          kCFAllocatorDefault,
          relCFURL,
          &error
          );
    if ( !error )
      {
      static const CFIndex maxAbsPathCStrBufLen = 4096;
      char absPathCStr[maxAbsPathCStrBufLen];
      if ( CFURLGetFileSystemRepresentation(
             absCFURL,
             true, // resolveAgainstBase
             reinterpret_cast<UInt8 *>( &absPathCStr[0] ),
             maxAbsPathCStrBufLen
             ) )
        {
        localFileQString = QString( absPathCStr );
        }
      }
    CFRelease( absCFURL );
    CFRelease( relCFURL );
    CFRelease( relCFStringRef );

    url = QUrl::fromLocalFile(localFileQString);
    }

#endif

  QString file = url.toLocalFile();
  event->acceptProposedAction();
  LoadDroppedFile(file);
}

QActionGroup *MainImageWindow::GetMainToolActionGroup()
{
  return ui->actionCrosshair->actionGroup();
}

QActionGroup *MainImageWindow::Get3DToolActionGroup()
{
  return ui->action3DCrosshair->actionGroup();
}

LayerInspectorDialog *MainImageWindow::GetLayerInspector()
{
  return m_LayerInspector;
}

void MainImageWindow::LoadMainImage(const QString &file)
{
	// Show a progress dialog
	using namespace imageiowiz;
	ImageIOProgressDialog::ScopedPointer progress(new ImageIOProgressDialog(this));
	progress->display();

	SmartPtr<ImageReadingProgressAccumulator> irProgAccum =
			ImageReadingProgressAccumulator::New();
  irProgAccum->AddProgressReporterCommand(progress->createCommand());

  // Prompt for unsaved changes
  if(!SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model))
    return;

  // Try loading the image
  try
    {
    // Change cursor for this operation
    QtCursorOverride c(Qt::WaitCursor);
    IRISWarningList warnings;
    SmartPtr<LoadMainImageDelegate> del = LoadMainImageDelegate::New();
    del->Initialize(m_Model->GetDriver());
		m_Model->GetDriver()->OpenImageViaDelegate(file.toUtf8().constData(), del, warnings,
																							 NULL, irProgAccum.GetPointer());
    }
  catch(exception &exc)
    {
    progress->close();
    ReportNonLethalException(this, exc, "Image IO Error",
                             QString("Failed to load image %1").arg(file));

    }
}

void MainImageWindow::LoadRecentActionTriggered()
{
  // Get the filename that wants to be loaded
  QAction *action = qobject_cast<QAction *>(sender());
  QString file = action->text();
  LoadMainImage(file);
}

void MainImageWindow::LoadRecentOverlayActionTriggered()
{
  // Get the filename that wants to be loaded
  QAction *action = qobject_cast<QAction *>(sender());
  QString file = action->text();

	// Show a progress dialog
	using namespace imageiowiz;
	ImageIOProgressDialog::ScopedPointer progress(new ImageIOProgressDialog(this));
	progress->display();

	SmartPtr<ImageReadingProgressAccumulator> irProgAccum =
			ImageReadingProgressAccumulator::New();
	irProgAccum->AddObserver(itk::ProgressEvent(), progress->createCommand());

  // Try loading the image
  try
    {
    // Change cursor for this operation
    QtCursorOverride c(Qt::WaitCursor);
    IRISWarningList warnings;
    SmartPtr<LoadOverlayImageDelegate> del = LoadOverlayImageDelegate::New();
    del->Initialize(m_Model->GetDriver());
		m_Model->GetDriver()->OpenImageViaDelegate(file.toUtf8().constData(), del, warnings,
																							 NULL, irProgAccum);
    }
  catch(exception &exc)
    {
    progress->close();
    ReportNonLethalException(this, exc, "Image IO Error",
                             QString("Failed to load overlay image %1").arg(file));
    }
}

void MainImageWindow::LoadRecentSegmentation(QString file, bool additive)
{
  // Prompt for unsaved changes
  if(!SaveModifiedLayersDialog::PromptForUnsavedSegmentationChanges(m_Model))
    return;

	// Show a progress dialog
	using namespace imageiowiz;
	ImageIOProgressDialog::ScopedPointer progress(new ImageIOProgressDialog(this));
	progress->display();

	SmartPtr<ImageReadingProgressAccumulator> irProgAccum =
			ImageReadingProgressAccumulator::New();
	irProgAccum->AddObserver(itk::ProgressEvent(), progress->createCommand());

  // Try loading the image
  try
    {
    // Change cursor for this operation
    QtCursorOverride c(Qt::WaitCursor);
    IRISWarningList warnings;
    SmartPtr<LoadSegmentationImageDelegate> del = LoadSegmentationImageDelegate::New();
    del->Initialize(m_Model->GetDriver());
    del->SetAdditiveMode(additive);
		m_Model->GetDriver()->OpenImageViaDelegate(file.toUtf8().constData(), del, warnings,
																							 NULL, irProgAccum);
    }
  catch(exception &exc)
    {
    progress->close();
    ReportNonLethalException(this, exc, "Image IO Error",
                             QString("Failed to load segmentation image %1").arg(file));
    }
}


void MainImageWindow::LoadRecentSegmentationActionTriggered()
{
  // Get the filename that wants to be loaded
  QAction *action = qobject_cast<QAction *>(sender());
  QString file = action->text();
  LoadRecentSegmentation(file, false);
}

void MainImageWindow::LoadAnotherRecentSegmentationActionTriggered()
{
  // Get the filename that wants to be loaded
  QAction *action = qobject_cast<QAction *>(sender());
  QString file = action->text();
  LoadRecentSegmentation(file, true);
}

void MainImageWindow::LoadLabelDefinitions(QString file)
{
  try
    {
    std::string utf = to_utf8(file);
    m_Model->GetDriver()->LoadLabelDescriptions(utf.c_str());
    }
  catch(std::exception &exc)
    {
    ReportNonLethalException(this, exc, "Label Definitions IO Error",
                             QString("Failed to load label definitions from file"));
    }
}

void MainImageWindow::LoadRecentLabelDefinitionsTriggered()
{
  // Get the filename that wants to be loaded
  QAction *action = qobject_cast<QAction *>(sender());
  QString file = action->text();
  LoadLabelDefinitions(file);
}

void MainImageWindow::LoadAnotherDicomActionTriggered()
{
  // Request to load another DICOM from the main image's folder
  QAction *action = qobject_cast<QAction *>(sender());

  // Get the dicom descriptor
  IRISApplication::DicomSeriesDescriptor desc =
      action->data().value<IRISApplication::DicomSeriesDescriptor>();

  // Try to load a DICOM with this series ID
  try
    {
    // Change cursor for this operation
    QtCursorOverride c(Qt::WaitCursor);
    IRISWarningList warnings;
    SmartPtr<LoadOverlayImageDelegate> del = LoadOverlayImageDelegate::New();
    del->Initialize(m_Model->GetDriver());
    m_Model->GetDriver()->LoadAnotherDicomSeriesViaDelegate(
          desc.layer_uid, desc.series_id.c_str(), del, warnings);
    }
  catch(exception &exc)
    {
    ReportNonLethalException(this, exc, "Image IO Error",
                             QString("Failed to load overlay image %1").arg(action->text()));
    }

}



void MainImageWindow::LoadProject(const QString &file)
{
  // Try loading the image
  try
    {
    // Change cursor for this operation
    QtCursorOverride c(Qt::WaitCursor);
    IRISWarningList warnings;

    // Load the project
    m_Model->GetDriver()->OpenProject(to_utf8(file), warnings);
    }
  catch(exception &exc)
    {
    ReportNonLethalException(this, exc, "Error Opening Project",
                             QString("Failed to open project %1").arg(file));
  }
}

void MainImageWindow::LoadProjectInNewInstance(const QString &file)
{
  std::list<std::string> args;
  args.push_back("-w");
  args.push_back(to_utf8(file));
  try
  {
  m_Model->GetSystemInterface()->LaunchChildSNAPSimple(args);
  }
  catch(IRISException &exc)
  {
    ReportNonLethalException(this, exc, "Failed to open workspace in new ITK-SNAP window");
  }
}

void MainImageWindow::onAnimationTimeout()
{
  if(m_Model)
    m_Model->AnimateLayerComponents();
}

void MainImageWindow::on4DReplayTimeout()
{
  if(m_Model && m_Model->GetDriver()->GetNumberOfTimePoints() > 1)
    {
    int crntTP = m_Model->GetDriver()->GetCursorTimePoint();
    int nextTP = (crntTP + 1) % (m_Model->GetDriver()->GetNumberOfTimePoints());
    m_Model->GetDriver()->SetCursorTimePoint(nextTP);
    }
}

void MainImageWindow::LoadRecentProjectActionTriggered()
{
  // Check for unsaved changes before loading new data
  if(!SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model))
    return;

  // Get the filename that wants to be loaded
  QAction *action = qobject_cast<QAction *>(sender());
  QString file = action->text();
  LoadProject(file);
}


void MainImageWindow::onRightDockDialogFinished()
{
  // Make the dock containing the wizard visible
  m_DockRight->setVisible(false);

  // Auto-adjust the canvas size
  QTimer::singleShot(0, this, SLOT(UpdateCanvasDimensions()));
  // this->UpdateCanvasDimensions();
}

void MainImageWindow::on_actionUnload_All_triggered()
{
  // Prompt for unsaved changes
  if(!SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model))
    return;

  // Unload the main image
  m_Model->GetDriver()->UnloadMainImage();
}

void MainImageWindow::on_actionReorient_Image_triggered()
{
  // Show the reorientation dialog
  RaiseDialog(m_ReorientImageDialog);
}

void MainImageWindow::on_actionZoomToFitInAllViews_triggered()
{
  // Reset the common zoom factor
  m_Model->GetSliceCoordinator()->ResetViewToFitInAllWindows();
}

void MainImageWindow::on_actionCenter_on_Cursor_triggered()
{
  m_Model->GetSliceCoordinator()->CenterViewOnCursorInAllWindows();
}

void MainImageWindow::on_actionZoom_to_100_triggered()
{
  m_Model->GetSliceCoordinator()->SetZoomPercentageInAllWindows(1);
}

void MainImageWindow::on_actionZoom_to_200_triggered()
{
  m_Model->GetSliceCoordinator()->SetZoomPercentageInAllWindows(2);
}

void MainImageWindow::on_actionZoom_to_400_triggered()
{
  m_Model->GetSliceCoordinator()->SetZoomPercentageInAllWindows(4);
}


void MainImageWindow::on_actionUndo_triggered()
{
  m_Model->GetDriver()->Undo();
}

void MainImageWindow::on_actionRedo_triggered()
{
  m_Model->GetDriver()->Redo();
}

#include <QKeyEvent>
bool MainImageWindow::event(QEvent *event)
{
    /*
  if(dynamic_cast<QKeyEvent *>(event))
    {
    QKeyEvent *kevent = dynamic_cast<QKeyEvent *>(event);
    std::cout << "KEY event: " << kevent->text().toStdString() << std::endl;
    std::cout << "  "
    std::cout << "MODIFIERS: " << (int) kevent->modifiers() << std::endl;
    }
    */
  return QWidget::event(event);
}

void MainImageWindow::on_actionOpenMain_triggered()
{
  // Prompt for unsaved changes
  if(!SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model))
    return;

  // Create a model for IO
  SmartPtr<LoadMainImageDelegate> delegate = LoadMainImageDelegate::New();
  delegate->Initialize(m_Model->GetDriver());
  SmartPtr<ImageIOWizardModel> model = ImageIOWizardModel::New();
  model->InitializeForLoad(m_Model, delegate);

  // Execute the IO wizard
  ImageIOWizard wiz(this);
  wiz.SetModel(model);
  wiz.exec();
}

void MainImageWindow::on_actionAdd_Overlay_triggered()
{
  SmartPtr<LoadOverlayImageDelegate> delegate = LoadOverlayImageDelegate::New();
  delegate->Initialize(m_Model->GetDriver());
  SmartPtr<ImageIOWizardModel> model = ImageIOWizardModel::New();
  model->InitializeForLoad(m_Model, delegate);

  // Execute the IO wizard
  ImageIOWizard wiz(this);
  wiz.SetModel(model);
  wiz.exec();
}

void MainImageWindow::on_actionAddMesh_triggered()
{
  // Get and Configure the model
  auto model = m_Model->GetMeshImportModel();
  model->SetMode(MeshImportModel::Mode::SINGLE);

  // Show the Wizard Dialog
  MeshImportWizard wiz(this);
  wiz.SetModel(model);
  wiz.exec();
}

void MainImageWindow::on_actionAddMeshSeries_triggered()
{
  auto model = m_Model->GetMeshImportModel();
  model->SetMode(MeshImportModel::Mode::SERIES);

  // Show the Wizard Dialog
  MeshImportWizard wiz(this);
  wiz.SetModel(model);
  wiz.exec();
}


void MainImageWindow::ExportScreenshot(int panelIndex)
{
  // Generate a filename for the screenshot
  std::string finput = m_Model->GenerateScreenshotFilename();

  // Open a file browser and have the user select something
  QString fuser = ShowSimpleSaveDialogWithHistory(
        this, m_Model, "Snapshots",
        "Save Snapshot - ITK-SNAP",
        "Snapshot File:",
        "PNG Image (*.png);;TIFF Image (*.tiff *.tif);;JPEG Image (*.jpg *.jpeg)",
        true,
        from_utf8(finput));

  // If nothing selected, exit
  if(fuser.length() == 0)
    return;

  // What panel is this?
  if(panelIndex == 3)
    {
    auto *target = ui->panel3D->Get3DView();
    target->SaveScreenshot(to_utf8(fuser));
    }
  else
    {
    SliceViewPanel *svp = reinterpret_cast<SliceViewPanel *>(m_ViewPanels[panelIndex]);
    svp->GetSliceView()->SaveScreenshot(to_utf8(fuser));
    }

  // Store the last filename
  m_Model->SetLastScreenshotFileName(to_utf8(fuser));
}

void MainImageWindow::on_actionSSAxial_triggered()
{
  ExportScreenshot(
        m_Model->GetDriver()->GetDisplayWindowForAnatomicalDirection(ANATOMY_AXIAL));
}

void MainImageWindow::on_actionSSCoronal_triggered()
{
  ExportScreenshot(
        m_Model->GetDriver()->GetDisplayWindowForAnatomicalDirection(ANATOMY_CORONAL));
}

void MainImageWindow::on_actionSSSagittal_triggered()
{
  ExportScreenshot(
        m_Model->GetDriver()->GetDisplayWindowForAnatomicalDirection(ANATOMY_SAGITTAL));
}


#include "SynchronizationModel.h"

void MainImageWindow::ExportScreenshotSeries(AnatomicalDirection direction)
{
  // Get the corresponding window
  unsigned int iWindow =
      m_Model->GetDriver()->GetDisplayWindowForAnatomicalDirection(direction);

  // Get the corresponding image direction
  unsigned int iImageDir =
      m_Model->GetDriver()->GetImageDirectionForAnatomicalDirection(direction);

  // Browse for the output directory
  QString duser = QFileDialog::getExistingDirectory(
        this,
        "Directory where to save the screenshot series");

  if(!duser.length())
    return;

  // Generate the output filename
  const char *names[] = { "axial0001.png", "sagittal0001.png", "coronal0001.png" };
  std::string filename = to_utf8(QDir(duser).filePath(names[direction]));

  // back up cursor location
  Vector3ui xCrossImageOld = m_Model->GetDriver()->GetCursorPosition();
  Vector3ui xCrossImage = xCrossImageOld;
  Vector3ui xSize = m_Model->GetDriver()->GetCurrentImageData()->GetVolumeExtents();
  xCrossImage[iImageDir] = 0;

  // Get the panel that's saving
  SliceViewPanel *svp = reinterpret_cast<SliceViewPanel *>(m_ViewPanels[iWindow]);
  QtVTKRenderWindowBox *target = svp->GetSliceView();

  // turn sync off temporarily
  bool sync_state = m_Model->GetSynchronizationModel()->GetSyncEnabled();
  m_Model->GetSynchronizationModel()->SetSyncEnabled(false);

  for (size_t i = 0; i < xSize[iImageDir]; ++i)
  {
    // Set the cursor position
    m_Model->GetDriver()->SetCursorPosition(xCrossImage);

    // Repaint the GL window and save screenshot
    target->SaveScreenshot(filename);
    target->update();

    // Needed for this to actually save individual screenshots
    QCoreApplication::processEvents();

    // Go to the next slice
    xCrossImage[iImageDir]++;

    // Generate the next filename
    m_Model->SetLastScreenshotFileName(filename);
    filename = m_Model->GenerateScreenshotFilename();
  }

  // recover the original cursor position
  m_Model->GetDriver()->SetCursorPosition(xCrossImageOld);

  // turn sync back on
  m_Model->GetSynchronizationModel()->SetSyncEnabled(sync_state);
}



void MainImageWindow::on_actionSegmentationIncreaseOpacity_triggered()
{
  int opacity = m_Model->GetSegmentationOpacity();
  m_Model->SetSegmentationOpacity(std::min(opacity+5, 100));
}

void MainImageWindow::on_actionSegmentationDecreaseOpacity_triggered()
{
  int opacity = m_Model->GetSegmentationOpacity();
  m_Model->SetSegmentationOpacity(std::max(opacity-5, 0));
}

void MainImageWindow::on_actionSegmentationToggle_triggered()
{
  bool value = m_Model->GetSegmentationVisibility();
  m_Model->SetSegmentationVisibility(!value);
}


void MainImageWindow::on_actionLoadLabels_triggered()
{
  // Ask for a filename
  QString selection = ShowSimpleOpenDialogWithHistory(
        this, m_Model, "LabelDescriptions",
        "Open Label Descriptions - ITK-SNAP",
        "Label Description File",
        "Text Files (*.txt);; Label Files (*.label)");

  // Open the labels from the selection
  if(selection.length())
    LoadLabelDefinitions(selection);
}

void MainImageWindow::on_actionSaveLabels_triggered()
{
  // Ask for a filename
  QString selection = ShowSimpleSaveDialogWithHistory(
        this, m_Model, "LabelDescriptions",
        "Save Label Descriptions - ITK-SNAP",
        "Label Description File",
        "Text Files (*.txt);; Label Files (*.label)",
        true);

  // Open the labels from the selection
  if(selection.length())
    {
    try
      {
      std::string utf = to_utf8(selection);
      m_Model->GetDriver()->SaveLabelDescriptions(utf.c_str());
      }
    catch(std::exception &exc)
      {
      ReportNonLethalException(this, exc, "Label Description IO Error",
                               QString("Failed to save label descriptions"));
      }
    }
}

void MainImageWindow::on_actionVolumesAndStatistics_triggered()
{
  m_StatisticsDialog->Activate();
}

bool MainImageWindow::SaveSegmentation(bool interactive, bool currentTPOnly)
{
  return SaveImageLayer(
        m_Model, m_Model->GetDriver()->GetSelectedSegmentationLayer(),
        LABEL_ROLE, interactive, this, currentTPOnly);
}

void MainImageWindow::RaiseDialog(QDialog *dialog)
{
  // propagate the attributes.
  dialog->setAttribute(Qt::WA_PaintOnScreen, this->testAttribute(Qt::WA_PaintOnScreen));

  dialog->show();
  dialog->activateWindow();
  dialog->raise();
}

void MainImageWindow::on_actionSaveSegmentation_triggered()
{
  SaveSegmentation(false);
}

void MainImageWindow::on_actionSaveSegmentationAs_triggered()
{
  SaveSegmentation(true);
}

void MainImageWindow::on_actionSaveTimePointSegmentation_triggered()
{
  SaveSegmentation(true, true);
}


void MainImageWindow::on_actionOverlayVisibilityToggleAll_triggered()
{
  m_Model->ToggleOverlayVisibility();
}

void MainImageWindow::on_actionOverlayVisibilityIncreaseAll_triggered()
{
  m_Model->AdjustOverlayOpacity(5);
}

void MainImageWindow::on_actionOverlayVisibilityDecreaseAll_triggered()
{
  m_Model->AdjustOverlayOpacity(-5);
}

void MainImageWindow::on_actionLayerInspector_triggered()
{
  // Show the dialog
  if(m_LayerInspector->isVisible() && m_LayerInspector->isActiveWindow())
    m_LayerInspector->advanceTab();
  else
    RaiseDialog(m_LayerInspector);
}

void MainImageWindow::on_actionAbout_triggered()
{
  // Show the about window
  RaiseDialog(m_AboutDialog);
}





void MainImageWindow::on_actionClear_triggered()
{
  IRISApplication *app = m_Model->GetDriver();

  // In snake mode, it is possible to clear the segmentation, but we don't
  // need to prompt for save
  if(app->IsSnakeModeActive())
    {
    app->ResetSNAPSegmentationImage();
    }
  else
    {
    // Prompt for unsaved changes
    if(!SaveModifiedLayersDialog::PromptForUnsavedSegmentationChanges(m_Model))
      return;

    app->ResetIRISSegmentationImage();
    }
}

void MainImageWindow::on_actionSave_as_Mesh_triggered()
{
  MeshExportWizard wizard(this);
  wizard.SetModel(m_Model->GetMeshExportModel());
  wizard.exec();
}

void MainImageWindow::on_actionSaveMain_triggered()
{
  // This should only happen in SNAP mode
  assert(!m_Model->GetDriver()->IsSnakeModeActive());

  // Handle this through the layer manager
  ImageWrapperBase *wrapper =
      m_Model->GetDriver()->GetIRISImageData()->GetMain();
  QAction *save_action = m_LayerInspector->GetLayerSaveAction(wrapper);
  if(save_action)
    save_action->trigger();
}

#include "SNAPImageData.h"
void MainImageWindow::on_actionSaveSpeed_triggered()
{
  // This should only happen in SNAP mode
  assert(m_Model->GetDriver()->IsSnakeModeActive());

  // Handle this through the layer manager
  ImageWrapperBase *wrapper =
      m_Model->GetDriver()->GetSNAPImageData()->GetSpeed();
  QAction *save_action = m_LayerInspector->GetLayerSaveAction(wrapper);
  if(save_action)
    save_action->trigger();
}

void MainImageWindow::on_actionSaveLevelSet_triggered()
{
  // This should only happen in SNAP mode
  assert(m_Model->GetDriver()->IsSnakeModeLevelSetActive());

  // Handle this through the layer manager
  ImageWrapperBase *wrapper =
      m_Model->GetDriver()->GetSNAPImageData()->GetSnake();
  QAction *save_action = m_LayerInspector->GetLayerSaveAction(wrapper);
  if(save_action)
    save_action->trigger();
}

void MainImageWindow::on_actionSaveMainROI_triggered()
{
  // This should only happen in SNAP mode
  assert(m_Model->GetDriver()->IsSnakeModeActive());

  // Handle this through the layer manager
  ImageWrapperBase *wrapper =
      m_Model->GetDriver()->GetSNAPImageData()->GetMain();
  QAction *save_action = m_LayerInspector->GetLayerSaveAction(wrapper);
  if(save_action)
    save_action->trigger();
}

QSize MainImageWindow::sizeHint() const
{
  return QSize(900,700);
}

void MainImageWindow::on_actionPreferences_triggered()
{
  m_PreferencesDialog->ShowDialog();
}


void MainImageWindow::on_actionOpenWorkspace_triggered()
{
  // Check for unsaved changes before loading new data
  if(!SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model))
    return;

  // Use the dialog with history - to be consistent with other parts of SNAP
  QString file = ShowSimpleOpenDialogWithHistory(
        this, m_Model, "Project", "Open Workspace",
        "Workspace File", "ITK-SNAP Workspace Files (*.itksnap)");

  // If user hits cancel, move on
  if(file.isNull())
    return;

  // Make sure to get an absolute path, because the project needs that info
  QString file_abs = QFileInfo(file).absoluteFilePath();

  // Try loading the image
  try
    {
    // Change cursor for this operation
    QtCursorOverride c(Qt::WaitCursor);
    IRISWarningList warnings;

    // Load the project
    m_Model->GetDriver()->OpenProject(to_utf8(file_abs), warnings);
    }
  catch(exception &exc)
    {
    ReportNonLethalException(this, exc, "Error Opening Project",
                             QString("Failed to open project %1").arg(file_abs));
    }
}

bool MainImageWindow::SaveWorkspace(bool interactive)
{
  // Make sure that there are no unsaved changes. This is necessary before
  // a workspace can be saved. We disable the discard feature here because
  // the subsequent action does not close anything. The real purpose of this
  // dialog is to make sure each layer is assigned a name before saving the
  // workspace
  if(!SaveModifiedLayersDialog::PromptForUnsavedChanges(
       m_Model, ALL_ROLES,
       SaveModifiedLayersDialog::DiscardDisabled
       | SaveModifiedLayersDialog::ProjectsDisabled))
    return false;

  // Use the global method
  return ::SaveWorkspace(this, m_Model, interactive, this);
}

void MainImageWindow::on_actionSaveWorkspace_triggered()
{
  SaveWorkspace(false);
}

void MainImageWindow::on_actionSaveWorkspaceAs_triggered()
{
  SaveWorkspace(true);
}


void MainImageWindow::ExportSlice(AnatomicalDirection direction)
{
  // Generate a default filename for this slice
  static const char *defpref[3] = {"axial", "sagittal", "coronal"};
  char deffn[40];

  // Figure out what slice it is
  size_t iSliceImg =
    m_Model->GetDriver()->GetImageDirectionForAnatomicalDirection(direction);

  snprintf(deffn, 40, "%s_slice_%04d.png", defpref[direction],
    m_Model->GetDriver()->GetCursorPosition()[iSliceImg] + 1);

  // Open a file browser and have the user select something
  std::string fuser = to_utf8(ShowSimpleSaveDialogWithHistory(
        this, m_Model, "Slices",
        "Save Slice - ITK-SNAP",
        "Slice Image File",
        "PNG Image (*.png);;TIFF Image (*.tiff *.tif);;JPEG Image (*.jpg *.jpeg)",true));

  if(fuser.length())
    m_Model->GetDriver()->ExportSlice(direction, fuser.c_str());
}

void MainImageWindow::on_actionExportAxial_triggered()
{
  this->ExportSlice(ANATOMY_AXIAL);
}

void MainImageWindow::on_actionExportCoronal_triggered()
{
  this->ExportSlice(ANATOMY_CORONAL);
}

void MainImageWindow::on_actionExportSagittal_triggered()
{
  this->ExportSlice(ANATOMY_SAGITTAL);
}

void MainImageWindow::on_actionSSSeriesAxial_triggered()
{
  this->ExportScreenshotSeries(ANATOMY_AXIAL);
}

void MainImageWindow::on_actionSSSeriesCoronal_triggered()
{
  this->ExportScreenshotSeries(ANATOMY_CORONAL);
}

void MainImageWindow::on_actionSSSeriesSagittal_triggered()
{
  this->ExportScreenshotSeries(ANATOMY_SAGITTAL);
}

void MainImageWindow::on_actionForegroundLabelPrev_triggered()
{
  // Decrement the active label
  m_Model->IncrementDrawingColorLabel(-1);
}

void MainImageWindow::on_actionForegroundLabelNext_triggered()
{
  // Increment the active label
  m_Model->IncrementDrawingColorLabel(1);
}

void MainImageWindow::on_actionBackgroundLabelPrev_triggered()
{
  m_Model->IncrementDrawOverColorLabel(-1);
}

void MainImageWindow::on_actionBackgroundLabelNext_triggered()
{
  m_Model->IncrementDrawOverColorLabel(1);
}

void MainImageWindow::on_actionToggle_All_Annotations_triggered()
{
  // Toggle the overall visibility
  m_Model->GetAppearanceSettings()->SetOverallVisibility(
        !m_Model->GetAppearanceSettings()->GetOverallVisibility());
}

void MainImageWindow::on_actionToggle_Crosshair_triggered()
{
  // Toggle the crosshair visibility
  OpenGLAppearanceElement *elt = m_Model->GetAppearanceSettings()->GetUIElement(
        SNAPAppearanceSettings::CROSSHAIRS);
  elt->SetVisibilityFlag(!elt->GetVisibilityFlag());
}

void MainImageWindow::on_actionAnnotation_Preferences_triggered()
{
  // Show the preferences dialog
  m_PreferencesDialog->ShowDialog();
  m_PreferencesDialog->GoToPage(PreferencesDialog::Appearance);
}

void MainImageWindow::on_actionAutoContrastGlobal_triggered()
{
  // This triggers the autocontrast option for all layers.
  m_Model->AutoContrastAllLayers();
}

void MainImageWindow::on_actionResetContrastGlobal_triggered()
{
  // This triggers the autocontrast option for all layers.
  m_Model->ResetContrastAllLayers();
}

void MainImageWindow::DoUpdateCheck(bool quiet)
{
  std::string nver;

  // Check for the update
  SystemInterface::UpdateStatus  us =
      m_Model->GetSystemInterface()->CheckUpdate(nver, 1, 0, !quiet);

  // Communicate with the user
  if(us == SystemInterface::US_OUT_OF_DATE)
    {
    QMessageBox mbox(this);
    QPushButton *downloadButton = mbox.addButton("Open Download Page", QMessageBox::ActionRole);
    mbox.addButton("Not Now", QMessageBox::RejectRole);
    mbox.setIcon(QMessageBox::Question);
    mbox.setText(QString("A newer ITK-SNAP version (%1) is available.").arg(nver.c_str()));
    mbox.setInformativeText("Do you want to download the latest version?");
    mbox.setWindowTitle("ITK-SNAP Update Check");
    mbox.exec();

    if (mbox.clickedButton() == downloadButton)
      {
      QDesktopServices::openUrl(QUrl("http://www.itksnap.org/pmwiki/pmwiki.php?n=Downloads.SNAP3"));
      }
    }
  else if(us == SystemInterface::US_UP_TO_DATE && !quiet)
    {
    QMessageBox::information(this, "ITK-SNAP Update Check",
                             "Your version of ITK-SNAP is up to date!",
                             QMessageBox::Ok);
    }
  else if(us == SystemInterface::US_CONNECTION_FAILED && !quiet)
    {
    QMessageBox::warning(this,
                         "ITK-SNAP Update Check Failed",
                         "Could not connect to server. Go to itksnap.org to check if a new"
                         " version is available.");
    }
}

void MainImageWindow::UpdateAutoCheck()
{
  // Get the update state
  DefaultBehaviorSettings::UpdateCheckingPermission permission =
      m_Model->GetGlobalState()->GetDefaultBehaviorSettings()->GetCheckForUpdates();

  // If permission is unknown, prompt and change the setting
  if(permission == DefaultBehaviorSettings::UPDATE_UNKNOWN)
    {
    if(QMessageBox::Yes == QMessageBox::question(
         this, "Allow Automatic Update Checks?",
         "ITK-SNAP can check for software updates automatically.\n"
         "Do you want to enable this feature?",
         QMessageBox::Yes, QMessageBox::No))
      {
      permission = DefaultBehaviorSettings::UPDATE_YES;
      }
    else
      {
      permission = DefaultBehaviorSettings::UPDATE_NO;
      }
    m_Model->GetGlobalState()->GetDefaultBehaviorSettings()->SetCheckForUpdates(permission);
    }

  // Execute the update check
  if(permission == DefaultBehaviorSettings::UPDATE_YES)
    {
    DoUpdateCheck(true);
    }
}

void MainImageWindow::Update4DReplay()
{
  bool isReplayOn = GetModel()->GetGlobalState()->Get4DReplay();
  int interval = GetModel()->GetGlobalState()->Get4DReplayInterval();

  if (interval != m_Crnt4DReplayInteval)
    {
    m_Crnt4DReplayInteval = interval;
    m_4DReplayTimer->setInterval(interval);
    }

  if (isReplayOn)
    this->m_4DReplayTimer->start();
  else
    this->m_4DReplayTimer->stop();
}

void MainImageWindow::RemindLayoutPreference()
{
  LayoutReminderDialog *layoutReminder = new LayoutReminderDialog(this);

  layoutReminder->Initialize(this->m_Model);
  layoutReminder->ConditionalExec();
}

void MainImageWindow::on_actionCheck_for_Updates_triggered()
{
  DoUpdateCheck(false);
}

void MainImageWindow::on_actionDocumentation_Home_triggered()
{
  QDesktopServices::openUrl(QUrl("http://www.itksnap.org/pmwiki/pmwiki.php?n=Documentation.SNAP3"));
}

void MainImageWindow::on_actionNew_ITK_SNAP_Window_triggered()
{
  // Launch a new SNAP in the relevant directory
  std::list<std::string> args;
  args.push_back("--cwd");
  args.push_back(to_utf8(GetFileDialogPath(m_Model, "MainImage")));
  m_Model->GetSystemInterface()->LaunchChildSNAPSimple(args);
}

void MainImageWindow::on_actionUnload_All_Overlays_triggered()
{
  // Prompt for changes to the overlays
  if(SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model, OVERLAY_ROLE))
    {
    m_Model->GetDriver()->UnloadAllOverlays();
    }
}

void MainImageWindow::changeEvent(QEvent *)
{
  if(m_Model)
    m_Model->GetSynchronizationModel()->SetCanBroadcast(this->isActiveWindow());
}

void MainImageWindow::on_actionClose_Window_triggered()
{
  // If main window is not the active window, close the active window instead of closing
  // any images. This is because Ctrl-W shortcut should be reserved for closign windows
  if(QApplication::activeWindow() != this)
    {
    QApplication::activeWindow()->close();
    return;
    }
}

void MainImageWindow::onRightDockCurrentChanged(int)
{
  // Adjust the width of the stack to match the current widget
  m_RightDockStack->setMaximumWidth(
        m_RightDockStack->currentWidget()->maximumWidth());
}


void MainImageWindow::on_actionUnload_Last_Overlay_triggered()
{
  // Get the selected ID
  unsigned long id_selected = m_Model->GetDriver()->GetGlobalState()->GetSelectedLayerId();

  // Find the actual layer
  ImageWrapperBase *layer = m_Model->GetDriver()->GetCurrentImageData()->FindLayer(id_selected, false);

  // Is this layer an overlay or a main image
  if(layer && layer == m_Model->GetDriver()->GetCurrentImageData()->GetMain())
    {
    // Prompt for unsaved changes
    if(SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model))
      {
      // Unload the main image
      m_Model->GetDriver()->UnloadMainImage();
      }
    }
  else
    {
    if(SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model, OVERLAY_ROLE))
      {
      m_Model->GetDriver()->UnloadOverlay(layer);
      }
    }
}


void MainImageWindow::on_actionToggleLayerLayout_triggered()
{
  m_Model->GetDisplayLayoutModel()->ToggleSliceViewLayerLayout();
}

void MainImageWindow::on_actionActivateNextLayer_triggered()
{
  m_Model->GetDisplayLayoutModel()->ActivateNextLayerInTiledMode();
}

void MainImageWindow::on_actionActivatePreviousLayer_triggered()
{
  m_Model->GetDisplayLayoutModel()->ActivatePrevLayerInTiledMode();
}

void MainImageWindow::on_actionInterpolate_Labels_triggered()
{
  RaiseDialog(m_InterpolateLabelsDialog);
}

// issue #24: Add label smoothing feature
void MainImageWindow::on_actionSmooth_Labels_triggered() {
  RaiseDialog(m_SmoothLabelsDialog);
}

void MainImageWindow::on_actionRegistration_triggered()
{
  // Remember the size of the window before the right dock was shown
  m_SizeWithoutRightDock = this->size();
  m_DockRight->setWindowTitle("Registration");
  m_Model->GetRegistrationModel()->SetFreeRotationMode(false);
  m_RightDockStack->setCurrentWidget(m_RegistrationDialog);
  m_DockRight->setVisible(true);
}


void MainImageWindow::on_actionFree_Rotation_Mode_triggered()
{
  // Remember the size of the window before the right dock was shown
  m_SizeWithoutRightDock = this->size();
  m_DockRight->setWindowTitle("Free Rotation");
  m_Model->GetRegistrationModel()->SetFreeRotationMode(true);
  m_RightDockStack->setCurrentWidget(m_RegistrationDialog);
  m_DockRight->setVisible(true);
}

void MainImageWindow::on_actionMainControlPanel_triggered()
{
  if(ui->actionMainControlPanel->isChecked())
    m_DockLeft->show();
  else
    m_DockLeft->hide();
}

void MainImageWindow::on_actionActivateNextSegmentationLayer_triggered()
{
  // Get the list of all the segmentation images
  m_Model->CycleSelectedSegmentationLayer(1);
}

void MainImageWindow::on_actionActivatePreviousSegmentationLayer_triggered()
{
  m_Model->CycleSelectedSegmentationLayer(-1);
}

void MainImageWindow::on_actionAddSegmentation_New_triggered()
{
  // Create an empty new segmentation
  m_Model->GetDriver()->AddBlankSegmentation();
}

void MainImageWindow::on_actionAddSegmentation_Open_triggered()
{
  // This is the same as opening segmentation, but with the "add" feature
  // Create a model for IO
  SmartPtr<LoadSegmentationImageDelegate> delegate = LoadSegmentationImageDelegate::New();
  delegate->Initialize(m_Model->GetDriver());
  delegate->SetAdditiveMode(true);

  SmartPtr<ImageIOWizardModel> model = ImageIOWizardModel::New();
  model->InitializeForLoad(m_Model, delegate);

  // Execute the IO wizard
  ImageIOWizard wiz(this);
  wiz.SetModel(model);
  wiz.exec();
}

void MainImageWindow::on_actionClearActive_triggered()
{
  // This is the layer that needs to be closed
  LabelImageWrapper *liw = m_Model->GetDriver()->GetSelectedSegmentationLayer();

  // Prompt for unsaved changes
  if(!SaveModifiedLayersDialog::PromptForUnsavedChanges(m_Model, liw))
    return;

  // Unload the wrapper
  m_Model->GetDriver()->UnloadSegmentation(liw);
}

void MainImageWindow::on_actionInstallCLI_triggered()
{
#ifdef __APPLE__
  QFileInfo fi(QCoreApplication::applicationDirPath(), "../bin/install_cmdl.sh");
  if(fi.exists() && fi.isExecutable())
    {
    QString html = QString(
        "<p>ITK-SNAP is packaged with several useful command-line programs. "
        "Visit <a href='http://itksnap.org/cmdl'>http://itksnap.org/cmdl</a> "
        "for a listing of these tools. </p>"
        "<p>To create links to these programs in <b>/usr/local/bin</b>, "
        "execute the following command in the Terminal App:</p>"
        "<code> sudo %1 </code>"
        "<p>To create links in another directory 'my_directory', execute </p>"
        "<code> sudo %1 my_directory </code>"
        "<p>To enable the tools for a single session, enter this command into the "
        "Terminal window:</p>"
        "<code> export PATH=%2:$PATH </code>").
        arg(fi.absoluteFilePath(), fi.absoluteDir().absolutePath());

    QMessageBox msg;
    msg.setText("How to Install ITK-SNAP Command Line Tools");
    msg.setInformativeText(html);
    msg.setWindowTitle("Install Command Line Tools -- ITK-SNAP");
    msg.setStyleSheet("QLabel{min-width: 700px;}");
    msg.exec();
    }
#endif
}

void MainImageWindow::on_actionDSS_triggered()
{
  RaiseDialog(m_DSSDialog);
}

void MainImageWindow::on_actionNext_Display_Layout_triggered()
{
  DisplayLayoutModel::ViewPanelLayout lo = m_Model->GetDisplayLayoutModel()->GetViewPanelLayout();
  lo = (DisplayLayoutModel::ViewPanelLayout)((lo + 1) % 5);
  m_Model->GetDisplayLayoutModel()->SetViewPanelLayout(lo);
}

#include <LayerTableRowModel.h>
void MainImageWindow::on_actionToggle_Volume_Rendering_triggered()
{
  // Iterate over the layers for each class of displayed layers
  LayerIterator it = m_Model->GetDriver()->GetCurrentImageData()->GetLayers(
        MAIN_ROLE | OVERLAY_ROLE | SNAP_ROLE | LABEL_ROLE);

  for(; !it.IsAtEnd(); ++it)
    {
    // Check if a model exists for this layer
		SmartPtr<ImageLayerTableRowModel> model =
				dynamic_cast<ImageLayerTableRowModel *>(
          it.GetLayer()->GetUserData("LayerTableRowModel"));

    // If not, create it and stick as 'user data' into the layer
    if(model)
      {
      if(model->GetLayer()->GetUniqueId() == m_Model->GetGlobalState()->GetSelectedLayerId())
        model->SetVolumeRenderingEnabled(!model->GetVolumeRenderingEnabled());
      else
        model->SetVolumeRenderingEnabled(false);
      }
    }
}

void MainImageWindow::on_actionToggle_4D_Replay_triggered()
{
  if (!m_Model->CheckState(UIF_IS_4D))
    return;

  GetModel()->GetGlobalState()->Toggle4DReplay();
  Update4DReplay();
}

void MainImageWindow::on_actionSwitch_Foreground_Background_Labels_triggered()
{
  GetModel()->SwitchForegroundBackgroundLabels();
}

void MainImageWindow::on_actionContinuous_Update_triggered()
{
  bool currentValue = GetModel()->GetModel3D()->GetContinuousUpdate();
  GetModel()->GetModel3D()->SetContinuousUpdate(!currentValue);
}


void MainImageWindow::on_actionResetLabels_triggered()
{
  this->GetModel()->GetLabelEditorModel()->ResetLabels();
}


void MainImageWindow::on_actionReloadSegmentation_triggered()
{
  auto *seg_wrapper = m_Model->GetDriver()->GetSelectedSegmentationLayer();
  if(seg_wrapper)
    {
    auto *model = dynamic_cast<AbstractLayerTableRowModel *>(seg_wrapper->GetUserData("LayerTableRowModel"));
    IRISWarningList wl;
    try
      {
      model->ReloadWrapperFromFile(wl);
      }
    catch (IRISException &ex)
      {
      ReportNonLethalException(this, ex, "Error reloading image from file");
      }
    }
}

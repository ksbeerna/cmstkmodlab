#ifndef ASSEMBLYMAINWINDOW_H
#define ASSEMBLYMAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QDir>
#include <QTimer>
#include <QToolBar>
#include <QScrollArea>

#include "AssemblyVUEyeCamera.h"

#ifdef USE_UEYE
#include "AssemblyUEyeModel.h"
typedef AssemblyUEyeModel AssemblyUEyeModel_t;
#else
#include "AssemblyUEyeFakeModel.h"
typedef AssemblyUEyeFakeModel AssemblyUEyeModel_t;
#endif

#include "AssemblyUEyeCameraThread.h"
#include "AssemblyUEyeWidget.h"
#include "AssemblyUEyeView.h"
#include "AssemblyUEyeSnapShooter.h"
#include "AssemblyModuleAssembler.h"


#include "AssemblyMarkerFinderThread.h"
#include "AssemblySensorMarkerFinder.h"
#include "AssemblySensorMarkerFinderWidget.h"

class AssemblyMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit AssemblyMainWindow(QWidget *parent = 0);

public slots:

  void quit();

  void testTimer();

  void onOpenCamera();
  void onCloseCamera();
  void onSnapShot();

  void cameraOpened();
  void cameraClosed();

signals:

  void openCamera();
  void closeCamera();
  void acquireImage();

protected slots:

void liveUpdate();

protected:

  QDir currentDir_;

  QToolBar* toolBar_;

  QTabWidget* tabWidget_;

  AssemblyUEyeSnapShooter* finderView_;
  AssemblyUEyeSnapShooter* edgeView_;
  AssemblyUEyeSnapShooter* rawView_;
  AssemblyModuleAssembler* assembleView_;
    

  AssemblyUEyeModel_t* uEyeModel_;
  AssemblyUEyeCameraThread* cameraThread_;
  AssemblyUEyeWidget* uEyeWidget_;

  AssemblyVUEyeCamera * camera_;

  AssemblyMarkerFinderThread* finderThread_;
  AssemblySensorMarkerFinder* finder_;
  AssemblySensorMarkerFinderWidget* finderWidget_;

  double testTimerCount_;

  QTimer *liveTimer_;
};

#endif // ASSEMBLYMAINWINDOW_H

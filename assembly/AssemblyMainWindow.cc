#include <stdlib.h>

#include <string>
#include <iostream>

#include <QGroupBox>
#include <QFileDialog>
#include <QApplication>

#include <nqlogger.h>
#include <ApplicationConfig.h>

#include "AssemblyMainWindow.h"

AssemblyMainWindow::AssemblyMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ApplicationConfig* config = ApplicationConfig::instance();

    tabWidget_ = new QTabWidget(this);
    tabWidget_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    uEyeModel_ = new AssemblyUEyeModel_t(10);
    cameraThread_ = new AssemblyUEyeCameraThread(uEyeModel_, this);
    uEyeWidget_ = new AssemblyUEyeWidget(uEyeModel_, this);

    tabWidget_->addTab(uEyeWidget_, "uEye");

    connect(QApplication::instance(), SIGNAL(aboutToQuit()),
            this, SLOT(quit()));

    setCentralWidget(tabWidget_);
    updateGeometry();

    NQLog("AssemblyMainWindow") << "main window constructed";

    uEyeModel_->updateInformation();
    cameraThread_->start();
}

void AssemblyMainWindow::quit()
{
    NQLog("AssemblyMainWindow") << "quit";

    if (cameraThread_) {
        cameraThread_->quit();
        cameraThread_->wait();
    }
}
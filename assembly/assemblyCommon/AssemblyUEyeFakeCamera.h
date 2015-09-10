#ifndef ASSEMBLYUEYEFAKECAMERA_H
#define ASSEMBLYUEYEFAKECAMERA_H

#include <vector>

#include <opencv2/opencv.hpp>

#include "AssemblyVUEyeCamera.h"

class AssemblyUEyeFakeCamera : public AssemblyVUEyeCamera
{
    Q_OBJECT
public:
    explicit AssemblyUEyeFakeCamera(QObject *parent);
    ~AssemblyUEyeFakeCamera();

    void updateInformation();
    void updatePixelClock();
    void updateExposureTime();

    bool isAvailable() const { return true; }

public slots:

    void open();
    void close();

    void acquireImage();

    void setPixelClock(unsigned int pc);
    void setExposureTime(double et);

protected slots:

protected:

    std::vector<cv::Mat> images_;
    size_t imageIndex_;

signals:

private:
};

#endif // ASSEMBLYUEYEFAKECAMERA_H
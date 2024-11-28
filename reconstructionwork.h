#ifndef RECONSTRUCTIONWORK_H
#define RECONSTRUCTIONWORK_H

#endif // RECONSTRUCTIONWORK_H

#include "mainwindows.h"
#include "PyThreadStateLock.h"

#include <QThread>
#include <QObject>
#include <QDebug>  // 添加调试信息
#include <string>
#include <numpy/arrayobject.h>

#undef slots
#include "Python.h"
#define slots Q_SLOTS

class Reconstructionwork : public QThread {
    Q_OBJECT
public:
    Reconstructionwork(const std::string& img_path_, const std::string& device_, const std::string& model_, const std::string& save_path_, const std::string& svg_name_, QObject *parent = nullptr)
        : QThread(parent), img_path(img_path_), device(device_), model(model_), save_path(save_path_), svg_name(svg_name_) {
        // 调试输出
        qDebug() << "Initialized with:" << QString::fromStdString(img_path) << QString::fromStdString(device) << QString::fromStdString(model) << QString::fromStdString(save_path) << QString::fromStdString(svg_name);
    }

signals:
    void progressUpdated(int progress);    // 进度更新信号
    void processingFinished(bool success); // 处理完成信号

protected:
    void run() override {

        class PyThreadStateLock PyThreadLock; // 获取全局锁

        // 加载模块
        qDebug() << "Loading module 'safmn'...";
        PyObject *pModule = PyImport_ImportModule("safmn");
        if (!pModule) {
            qDebug() << "Failed to load module 'safmn'.";
            PyErr_Print();  // 打印错误信息
            emit processingFinished(false);
            return;
        }

        // 获取函数
        qDebug() << "Getting function 'safmn'...";
        PyObject *pFunc = PyObject_GetAttrString(pModule, "safmn");
        if (!pFunc || !PyCallable_Check(pFunc)) {
            qDebug() << "Function 'safmn' not callable or not found.";
            PyErr_Print();  // 打印错误信息
            Py_XDECREF(pModule);
            emit processingFinished(false);
            return;
        }

        // 创建参数元组
        qDebug() << "Creating argument tuple...";
        PyObject *pArgs = PyTuple_New(5);

        if (!pArgs) {
            qDebug() << "Failed to create argument tuple.";
            PyErr_Print();
            Py_XDECREF(pFunc);
            Py_XDECREF(pModule);
            emit processingFinished(false);
            return;
        }

        // 设置参数
        PyObject *imgPathObj = PyUnicode_FromString(img_path.c_str());
        PyObject *deviceObj = PyUnicode_FromString(device.c_str());
        PyObject *modelObj = PyUnicode_FromString(model.c_str());
        PyObject *savePathObj = PyUnicode_FromString(save_path.c_str());
        PyObject *svgNameObj = PyUnicode_FromString(svg_name.c_str());

        PyTuple_SetItem(pArgs, 0, imgPathObj); // pArgs的引用计数归于pArgs
        PyTuple_SetItem(pArgs, 1, deviceObj);
        PyTuple_SetItem(pArgs, 2, modelObj);
        PyTuple_SetItem(pArgs, 3, savePathObj);
        PyTuple_SetItem(pArgs, 4, svgNameObj);

        // 调用Python函数
        qDebug() << "Calling Python function 'safmn'...";
        PyObject *pResult = PyObject_CallObject(pFunc, pArgs);

        bool success = (pResult != nullptr);
        if (!success) {
            qDebug() << "Function call failed.";
            PyErr_Print();
        } else {
            qDebug() << "Function call succeeded.";
        }

        // 清理
        Py_XDECREF(pResult);
        Py_DECREF(pArgs);
        Py_DECREF(pFunc);
        Py_DECREF(pModule);

        emit processingFinished(success);
    }

private:
    std::string img_path;
    std::string device;
    std::string model;
    std::string save_path;
    std::string svg_name;
};



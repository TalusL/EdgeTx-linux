#include <QApplication>
#include <QPushButton>
#include <QLibrary>
#include "simulatorinterface.h"
#include "lcdwidget.h"

typedef SimulatorFactory * (*RegisterSimulator)();
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LcdWidget lcdWidget;
    SimulatorInterface * si = NULL;
#if(_WIN32)
    auto * lib = new QLibrary(  "../libedgetx-tx16s-simulator.dll");
#else
    auto * lib = new QLibrary(  "../libedgetx-tx16s-simulator.so");
#endif
    SimulatorFactory * factory;
    auto registerFunc = (RegisterSimulator)lib->resolve("registerSimu");
    if (registerFunc && (factory = registerFunc()) && (si = factory->create())) {
        quint8 instance = lib->property("instances_used").toUInt();
        lib->setProperty("instances_used", ++instance);
        qDebug() << "Loaded" << factory->name() << "simulator instance" << instance;
        delete factory;
    }
    else {
        qWarning() << "Library error" << lib->fileName() << lib->errorString();
        exit(0);
    }
    QObject::connect(si, &SimulatorInterface::lcdChange, [&](bool backlightEnable){
        lcdWidget.onLcdChanged(backlightEnable);
    });
    lcdWidget.setData(si->getLcd(),480,272,16);
    lcdWidget.show();
    QObject::connect(&lcdWidget, &LcdWidget::touchEvent, si, &SimulatorInterface::touchEvent);
    si->setSdPath("/home/wind/CLionProjects/edgetx-linux/cmake-build-debug/sd");
    si->init();
    si->setVolumeGain(50);
    si->start();
    return QApplication::exec();
}

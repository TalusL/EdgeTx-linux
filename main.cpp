#include <QApplication>
#include <QPushButton>
#include <QLibrary>
#include <iostream>
#include "simulatorinterface.h"
#include "lcdwidget.h"
#include "joystick.h"

typedef SimulatorFactory * (*RegisterSimulator)();
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LcdWidget lcdWidget;
    SimulatorInterface * si = NULL;
    SDL_Init(SDL_INIT_JOYSTICK);
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
    lcdWidget.setFixedSize(800,480);
    lcdWidget.show();
    Joystick joystick;
    QObject::connect(&joystick,&Joystick::axisValueChanged,[](int axis, int value){
        qDebug() << "axis:" << axis << " value" << value;
    });
    QObject::connect(&joystick,&Joystick::buttonValueChanged,[](int button, int value){
        qDebug() << "button:" << button << " value" << value;
    });
    if(!joystick.joystickNames.empty()){
        joystick.open(0);
    }
    QObject::connect(&lcdWidget, &LcdWidget::touchEvent, si, &SimulatorInterface::touchEvent);
    si->setSdPath("D:\\EGSD");
    si->init();
    si->setVolumeGain(50);
    si->start();
    return QApplication::exec();
}

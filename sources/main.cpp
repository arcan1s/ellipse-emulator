/******************************************************************************
* The MIT License (MIT)                                                       *
*                                                                             *
* Copyright (c) 2016 Evgeniy Alekseev                                         *
*******************************************************************************/


#include <QApplication>
#include <QCommandLineParser>

#include "ellipseemulator.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Ellipse emulator");
    app.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("A fractal-like ellipse");
    parser.addHelpOption();
    parser.addVersionOption();

    // args
    parser.process(app);

    EllipseEmulator ellipseEmulator;
    ellipseEmulator.show();

    return app.exec();
}


#ifdef _WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif /* _WIN32 */

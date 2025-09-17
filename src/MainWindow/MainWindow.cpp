#include "MainWindow.hpp"
#include <QLabel>
#include <QStatusBar>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("InstallHub — Demo");
    resize(800, 500);

    auto* label = new QLabel("InstallHub demo window", this);
    label->setAlignment(Qt::AlignCenter);
    setCentralWidget(label);

    statusBar()->showMessage("Ready");
}

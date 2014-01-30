/********************************************************************************
** Form generated from reading UI file 'frag_window.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAG_WINDOW_H
#define UI_FRAG_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frag_window
{
public:
    QAction *action_file_exit;
    QAction *action_help_about;
    QAction *action_file_open_image;
    QAction *action_file_save_image;
    QAction *action_filter_original;
    QAction *action_filter_inverse;
    QAction *action_file_read_supported_format;
    QAction *action_file_write_supported_format;
    QAction *action_filter_median_3X3;
    QAction *action_filter_mosaic;
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuFilter;

    void setupUi(QMainWindow *frag_window)
    {
        if (frag_window->objectName().isEmpty())
            frag_window->setObjectName(QStringLiteral("frag_window"));
        frag_window->resize(559, 253);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Moon.png"), QSize(), QIcon::Normal, QIcon::Off);
        frag_window->setWindowIcon(icon);
        frag_window->setLocale(QLocale(QLocale::English, QLocale::Canada));
        action_file_exit = new QAction(frag_window);
        action_file_exit->setObjectName(QStringLiteral("action_file_exit"));
        action_help_about = new QAction(frag_window);
        action_help_about->setObjectName(QStringLiteral("action_help_about"));
        action_file_open_image = new QAction(frag_window);
        action_file_open_image->setObjectName(QStringLiteral("action_file_open_image"));
        action_file_save_image = new QAction(frag_window);
        action_file_save_image->setObjectName(QStringLiteral("action_file_save_image"));
        action_filter_original = new QAction(frag_window);
        action_filter_original->setObjectName(QStringLiteral("action_filter_original"));
        action_filter_inverse = new QAction(frag_window);
        action_filter_inverse->setObjectName(QStringLiteral("action_filter_inverse"));
        action_file_read_supported_format = new QAction(frag_window);
        action_file_read_supported_format->setObjectName(QStringLiteral("action_file_read_supported_format"));
        action_file_write_supported_format = new QAction(frag_window);
        action_file_write_supported_format->setObjectName(QStringLiteral("action_file_write_supported_format"));
        action_filter_median_3X3 = new QAction(frag_window);
        action_filter_median_3X3->setObjectName(QStringLiteral("action_filter_median_3X3"));
        action_filter_mosaic = new QAction(frag_window);
        action_filter_mosaic->setObjectName(QStringLiteral("action_filter_mosaic"));
        centralwidget = new QWidget(frag_window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        frag_window->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(frag_window);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        frag_window->setStatusBar(statusbar);
        menubar = new QMenuBar(frag_window);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 559, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFilter = new QMenu(menubar);
        menuFilter->setObjectName(QStringLiteral("menuFilter"));
        frag_window->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuFilter->menuAction());
        menuFile->addAction(action_file_open_image);
        menuFile->addAction(action_file_save_image);
        menuFile->addSeparator();
        menuFile->addAction(action_file_read_supported_format);
        menuFile->addAction(action_file_write_supported_format);
        menuFile->addAction(action_file_exit);
        menuFilter->addAction(action_filter_original);
        menuFilter->addAction(action_filter_inverse);
        menuFilter->addAction(action_filter_mosaic);
        menuFilter->addAction(action_filter_median_3X3);

        retranslateUi(frag_window);

        QMetaObject::connectSlotsByName(frag_window);
    } // setupUi

    void retranslateUi(QMainWindow *frag_window)
    {
        frag_window->setWindowTitle(QApplication::translate("frag_window", "GLSL Image Processing Example", 0));
        action_file_exit->setText(QApplication::translate("frag_window", "Exit", 0));
        action_help_about->setText(QApplication::translate("frag_window", "About", 0));
        action_file_open_image->setText(QApplication::translate("frag_window", "Open Image", 0));
        action_file_save_image->setText(QApplication::translate("frag_window", "Save Image", 0));
        action_filter_original->setText(QApplication::translate("frag_window", "Original", 0));
        action_filter_inverse->setText(QApplication::translate("frag_window", "Inverse", 0));
        action_file_read_supported_format->setText(QApplication::translate("frag_window", "List Supported Image Format to Read", 0));
        action_file_write_supported_format->setText(QApplication::translate("frag_window", "List Supported Image Format to Write", 0));
        action_filter_median_3X3->setText(QApplication::translate("frag_window", "Median Filter 3X3", 0));
        action_filter_mosaic->setText(QApplication::translate("frag_window", "Mosaic", 0));
        menuFile->setTitle(QApplication::translate("frag_window", "File", 0));
        menuFilter->setTitle(QApplication::translate("frag_window", "Filter", 0));
    } // retranslateUi

};

namespace Ui {
    class frag_window: public Ui_frag_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAG_WINDOW_H

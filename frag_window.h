#pragma once

#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QMainWindow>

namespace Ui {
   class frag_window;
}

class frag_pane;

class frag_window : public QMainWindow
//class frag_window : public QMainWindow, protected QOpenGLFunctions
{
   Q_OBJECT

public:
   // Menu Action Stratus Mode
   // This is encedded to QAction Items
   enum {
      // always enabled
      MouseActionItemEnabled = 0, 
      // enabled only when double sequences ares loaded
      MouseActionItemLoaded = 1, 
      // always disnabled
      MouseActionItemDisabled = 4, 
   } MouseActionSelectionMode;
   
private:
    Ui::frag_window *ui;

private:              
   frag_pane *_frag_pane;    
   
public:
    explicit frag_window(QWidget *parent = 0);
    ~frag_window();
    
private:      
   bool saveSingleImage( void );
   bool selectSingleImage( void );
   void listSupportedFormats( bool bReader );

   frag_pane *getPane( void ) const { return _frag_pane; }
   
   void restoreWindowPosition( void );
   void storeWindowPosition( void );

protected:
   void closeEvent( QCloseEvent *event );

private slots:
   // *** file menu ***
   void on_action_file_open_image_triggered();
   void on_action_file_save_image_triggered();
   void on_action_file_read_supported_format_triggered();
   void on_action_file_write_supported_format_triggered();
   void on_action_file_exit_triggered();
   
   // *** Filter menu ***
   void on_action_filter_original_triggered();
   void on_action_filter_inverse_triggered();
   void on_action_filter_mosaic_triggered();
   void on_action_filter_median_3X3_triggered();
};

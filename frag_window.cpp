#include "frag_pane.h"
#include "frag_window.h"
#include "ui_frag_window.h"

frag_window::frag_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frag_window)
{
   QIcon icon;

   ui->setupUi(this);

   _frag_pane = new frag_pane;  
   _frag_pane->setParent( this );  

   setCentralWidget( _frag_pane );
   
   restoreWindowPosition( );

   icon = QIcon( ":/images/Moon.png" );
   setWindowIcon( icon );

   return;
}

frag_window::~frag_window()
{
   delete ui;
}

void frag_window::closeEvent( QCloseEvent * /*eve*/ )
{
   storeWindowPosition( );

   return;
}

// *** file ***

void frag_window::on_action_file_open_image_triggered()
{
   if( !selectSingleImage( ) ) {
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

void frag_window::on_action_file_save_image_triggered()
{
   frag_pane *pPane = getPane( );  

   if( !pPane->validImageProc( ) ) {
      goto PIX_EXIT;
   }
   
   if( !saveSingleImage( ) ) {
      goto PIX_EXIT;
   }

PIX_EXIT:
   return;
}

void frag_window::on_action_file_read_supported_format_triggered()
{
    listSupportedFormats( true );

    return;
}

void frag_window::on_action_file_write_supported_format_triggered()
{
    listSupportedFormats( false );

    return;
}

void frag_window::on_action_file_exit_triggered()
{
    close( );
}

// *** filter ***

void frag_window::on_action_filter_original_triggered()
{
   frag_pane *pPane = getPane( );  

   if( !pPane->validImageProc( ) ) {
      goto PIX_EXIT;
   }
   
   pPane->setImageProc( frag_pane::ImageProcOriginal );
   
   if( !pPane->setTexture( ) ) {
      pPane->resetImageProc( );
      pPane->refreshImage( );
      goto PIX_EXIT;
   }
   
   pPane->refreshImage( );

PIX_EXIT:
   return;
}

void frag_window::on_action_filter_inverse_triggered()
{
   frag_pane *pPane = getPane( );

   if( !pPane->validImageProc( ) ) {
       goto PIX_EXIT;
    }

   pPane->setImageProc( frag_pane::ImageProcInverse );
       
   if( !pPane->setTexture( ) ) {
      pPane->resetImageProc( );
      pPane->refreshImage( );
      goto PIX_EXIT;
   }
   
   pPane->refreshImage( );

 PIX_EXIT:
    return;
}

void frag_window::on_action_filter_mosaic_triggered()
{
    frag_pane *pPane = getPane( );

    if( !pPane->validImageProc( ) ) {
        goto PIX_EXIT;
     }

    pPane->setImageProc( frag_pane::ImageProcMosaic );

    if( !pPane->setTexture( ) ) {
       pPane->resetImageProc( );
       pPane->refreshImage( );
       goto PIX_EXIT;
    }

    pPane->refreshImage( );

  PIX_EXIT:
    return;
}

void frag_window::on_action_filter_median_3X3_triggered()
{
   frag_pane *pPane = getPane( );

   if( !pPane->validImageProc( ) ) {
       goto PIX_EXIT;
    }

   pPane->setImageProc( frag_pane::ImageProcMedian3X3 );
       
   if( !pPane->setTexture( ) ) {
      pPane->resetImageProc( );
      pPane->refreshImage( );
      goto PIX_EXIT;
   }
   
   pPane->refreshImage( );

 PIX_EXIT:
   return;
}

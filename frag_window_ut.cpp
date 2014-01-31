#include "frag_pane.h"
#include "frag_window.h"

//
// make filter string to be used in QFileDialog 
// to get a list of supported image formats.
//
static void ImageFileFilter( QStringList &strFilters,	// [o] list of supported image formats
                            bool bRead ) // [i] to read or wrote the image
{
   int k;
   QString strAllExt, strFormat, strLowFormat, strUpFormat, strBuffer;
   
   // make a list image formats which are supported by Qt Image I/O function

   QList<QByteArray> formats;
   
   if( bRead ) {
      formats = QImageReader::supportedImageFormats( );
   } else {
      formats = QImageWriter::supportedImageFormats( );
   }

   int nFormats = (int)formats.size( );
    
   strFilters.clear( );
   strAllExt.clear( );
   for( k = 0 ; k < nFormats ; k++ ) {
      strFormat = formats.at( k );
      strUpFormat = strFormat.toUpper( );
      strLowFormat = strFormat.toLower( );
      strBuffer = strUpFormat + "(*." + strLowFormat + ")";
      strAllExt = strAllExt + "*." + strLowFormat + " ";
      strFilters.append( strBuffer );
   }
   
   // all files

   strBuffer = "All Files(*.*)";
   strFilters.insert( 0, strBuffer );

   // all format 

   strBuffer = "All Formats (" + strAllExt + ")";
   strFilters.insert( 0, strBuffer );
   
   return;
}

static void ImageFileFilter( QString &strFilter, // [o] list of supported image formats
                            bool bRead ) // [i] to read or wrote the image
{
   int i, nBufferSize, nFormats;
   QString strFormat;
   QStringList strFilters;

   strFilters.clear( );

   ImageFileFilter( strFilters, bRead );
   
   nFormats = (int)strFilters.size( );
   nBufferSize = 0;
   for( i = 0 ; i < nFormats ; i++ ) {
      strFormat = strFilters.at( i );  
      if( 0 < i ) {
         nBufferSize = nBufferSize + 2;
      }
      nBufferSize = nBufferSize + (int)strFormat.size( );
   } 
      
   strFilter.clear( );
   strFilter.reserve( nBufferSize + 10 );
   for( i = 0 ; i < nFormats ; i++ ) {
      strFormat = strFilters.at( i );  
      if( 0 < i ) {
         strFilter.push_back( ";;" );
      }
      strFilter.push_back( strFormat );
   }
   
   return;
}

//
// select single image file from dialog
// show the image on widget
// 
bool frag_window::selectSingleImage( void )
{
   bool bRetCode = false;
   frag_pane *pPane = getPane( );  
   QFileInfo finfo;
   QString strPath, strMessage, strLastDir, strLabel, strFile;
   QStringList fileNames;
   QString strFilters, strSelectedFilter;
   
   QString strKeyDir = "Last Image Path";
   QString strOrganisation = qApp->organizationName( );
   QString strApplication = qApp->applicationName( );
   QSettings settings( strOrganisation, strApplication );

QApplication::setOverrideCursor( Qt::BusyCursor );

   QFileDialog::Options options;
   
   // get the last directory image was selected
   
   strLastDir = QDir::currentPath( );
   strLastDir = settings.value( strKeyDir, strLastDir ).toString( );
    
   // create filter strings used in QFileDialog
   // to choose from supported image files

   ImageFileFilter( strFilters, true );
  
   //
   // select a image
   //
  
   options = QFileDialog::ReadOnly;
   strLabel = tr("Select Image");
   
   strFile = QFileDialog::getOpenFileName( this, 
      strLabel,
      strLastDir, 
      strFilters, 
      &strSelectedFilter,
      options );

   if( strFile.isEmpty( ) ) {
      // cancelled
      goto PIX_EXIT;
   }

   // *** Load the image from file to texture ***

   if( !pPane->loadImage( strFile ) ) {
      pPane->resetImageProc( );
      pPane->refreshImage( );
      goto PIX_EXIT;
   }

   pPane->setImageProc( frag_pane::ImageProcOriginal );
   
   // *** set the image on FBO! ***
   
   if( !pPane->setTexture( ) ) {
      pPane->resetImageProc( );
      pPane->refreshImage( );
      goto PIX_EXIT;
   }
   
   pPane->refreshImage( );

   // *** remember the directory for the next time ***

   finfo.setFile( strFile );
   strPath = finfo.path( );
   settings.setValue( strKeyDir, strPath );

   // --- Done --- 
   bRetCode = true;
PIX_EXIT:
QApplication::restoreOverrideCursor( );
   return bRetCode;
}

bool frag_window::saveSingleImage( void )
{
   bool bRetCode = false;
   frag_pane *pPane = getPane( );  
   QFileInfo finfo;
   QString strPath, strMessage, strLastDir, strLabel, strFile;
   QStringList fileNames;
   QString strFilters, strSelectedFilter;
   
QApplication::setOverrideCursor( Qt::BusyCursor );

   QFileDialog::Options options;

   QString strKeyDir = "Last Saved Path";
   QString strOrganisation = qApp->organizationName( );
   QString strApplication = qApp->applicationName( );
   QSettings settings( strOrganisation, strApplication );
   
   if( !pPane->validImageProc( ) ) {
      goto PIX_EXIT;
   }
   
   // get the last directory image was selected
   
   strLastDir = QDir::currentPath( );
   strLastDir = settings.value( strKeyDir, strLastDir ).toString( );
   
   // create filter strings used in QFileDialog
   // to choose from supported image files

   ImageFileFilter( strFilters, false );
  
   // select image name
  
   options = QFileDialog::DontConfirmOverwrite;
   strLabel = "Select Image";
   
   strFile = QFileDialog::getSaveFileName( this, 
      strLabel,
      strLastDir, 
      strFilters, 
      &strSelectedFilter,
      options );

   if( strFile.isEmpty( ) ) {
      // cancelled
      goto PIX_EXIT;
   }

   // *** set the file! ***

   if( !pPane->saveImage( strFile ) ) {
      goto PIX_EXIT;
   }
   
   // *** remember the directory for the next time ***

   finfo.setFile( strFile );
   strPath = finfo.path( );
   settings.setValue( strKeyDir, strPath );

   // --- Done --- 
   bRetCode = true;
PIX_EXIT:
QApplication::restoreOverrideCursor( );
   return bRetCode;
}

//
// list all image formats supported by QtImageReader/Writer
//
void frag_window::listSupportedFormats( bool bReader )
{
   int k, nFormats;
   QList<QByteArray> formats;
   QString strTitle, strFormats, strFormat;
   QMessageBox box;

   if( bReader ) {
      // read
      formats = QImageReader::supportedImageFormats( );
      strTitle = "Supported Image Formats[Reader]:";
   } else {
      // Writer
      formats = QImageWriter::supportedImageFormats( );
      strTitle = "Supported Image Formats[Writer]:";
   }

   qDebug() << strTitle;

   nFormats = (int)formats.size( );
   strFormats.clear( );   
   for( k = 0 ; k < nFormats ; k++ ) {
      strFormat = formats.at( k );
      qDebug() << "[" << k+1 << "/" <<nFormats << "] " << strFormat;

      if( 0 < k ) {
         strFormats = strFormats + "\n";
      }
      strFormats = strFormats + strFormat;
   }
   
   box.setText( strFormats );
   box.setWindowTitle( strTitle );
   box.setStandardButtons( QMessageBox::Ok );
   box.exec( );

   return;
}

//
// store window position in the setting
//
void frag_window::storeWindowPosition()
{
   QByteArray geo;
   
   QString strOrganisation = qApp->organizationName( );
   QString strApplication = qApp->applicationName( );
   QSettings settings( strOrganisation, strApplication );

   //

   geo = saveGeometry( );
   settings.setValue( "geometry", geo );

   return;
}

//
// restore the last window geometry
//
void frag_window::restoreWindowPosition()
{
   QByteArray geo;
   
   QString strOrganisation = qApp->organizationName( );
   QString strApplication = qApp->applicationName( );
   QSettings settings( strOrganisation, strApplication );

   geo = settings.value("geometry").toByteArray( );
   if( 0 >= geo.count( ) ) {
      // first time
      QSize sz( 600, 600 );
      QPoint ps( 30, 30 );
      move( ps );
      resize( sz );
   } else {
      restoreGeometry( geo );
   }

   return;
}

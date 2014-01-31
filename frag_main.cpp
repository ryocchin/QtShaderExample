#include <QtCore>
#include <QtGui>
#include <QApplication> 
#include <QMainWindow>

#include "frag_window.h"
#include "frag_pane.h"

int main(int argc, char **argv)
{
   Q_INIT_RESOURCE( frag_sampler );

   QApplication app(argc, argv);

   app.setApplicationName("Qt GLSL Image Processing Example");
   app.setOrganizationName( "PixTOPO" );
   app.setOrganizationDomain( "www.pixtopo.com" );
   app.setApplicationVersion("1.0");
   
   if( !QGLFramebufferObject::hasOpenGLFramebufferObjects()) {
      QMessageBox::information( 0, 
         app.applicationName( ),
         "This system does not support OpenGL/framebuffer objects.");
      return -1;
   }

   frag_window window;
   
   window.show( );

   return app.exec();
}

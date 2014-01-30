#pragma once

#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QtOpenGL>
#include <QGLFunctions>
#include <QGLWidget>
#include <QMainWindow>
#include <QGLShaderProgram>

class frag_window;

class frag_pane : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
       
public:
   // image processing
   enum {
      // Image is not Selected
      ImageProcInvalid = 0, 
      // original
      ImageProcOriginal = 1, 
      // GLSL Shader
      ImageProcInverse = 101,
      // Chapter 2 : Basic Filter and Transformation
      ImageProcMosaic = 201,
      // Chapter 4 : Smoothing Processing
      ImageProcMedian3X3 = 403,
   } ImageProcessingMethod;

private:            
   // pointer to the main window
   frag_window *_pParent;
   
   // one of ImageProcessingMethod
   short _sImageProc;
      
private:
   // shader programs
      
   int _image_attr;
   int _width_attr;
   int _height_attr;
    
   QGLShaderProgram _copy_program;
   QGLShaderProgram _inverse_program;
   QGLShaderProgram _mosaic_program;
   QGLShaderProgram _median3_program;
   
   // FBO that contains the texture(image) read from the file
   QGLFramebufferObject *_in_fbo;
   
   // FBO that carries the texture to be shown on the pane
   QGLFramebufferObject *_out_fbo; 
   
public:
   explicit frag_pane(QWidget *parent = 0);
   ~frag_pane();  
   
   void clear( void );
   bool setTexture( void );
   bool loadImage( const QString strFile );
   bool saveImage( const QString strFile );

   void setParent( frag_window *pMain ) { _pParent = pMain; }
   frag_window *getParent( void ) { return _pParent; }
   
   void refreshImage( void );
   void bindShader( void );
   void releaseShader( void );
   
   bool validImageProc( void ) const;
   
   void resetImageProc( void ) { _sImageProc = ImageProcInvalid; }
   void setImageProc( short sImageProc ) { _sImageProc = sImageProc; }
   short getImageProc( void ) const { return _sImageProc; }

protected:
   void initializeGL( void );
   void paintGL( void );
   void resizeGL(int w, int h);
   
private:
   bool createShaders( void );
   bool createInverseShader( void );
      
   bool createSingleShader( QGLShaderProgram *pShader,
      const QString strVertexFile, 
      const QString strFragmentFile );
};


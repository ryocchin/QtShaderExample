//
// Fragment Shader for Image processing
//
// Mosaic Filter by Average
//

//
// Fragment shader for mosaic image
//
uniform sampler2D image;
uniform int imgWidth;
uniform int imgHeight;
uniform int nPixels; // block size
varying vec2 pos;

void main(void)
{
   vec2 texCoord;
   int i, j;
   int iCol = int( floor(pos.x / float(nPixels)) );
   int iRow = int( floor(pos.y / float(nPixels)) );
   int iRowStart = iRow*nPixels;
   int iColStart = iCol*nPixels;

   vec4 sum = vec4(0.0);
   int cnt = 0;    
   for( j = iRowStart ; j < iRowStart + nPixels ; j++) {
      for( i = iColStart; i < iColStart + nPixels; i++) {
         texCoord = vec2(float(i) / float(imgWidth),
            float(j) / float(imgHeight));
         sum += texture2D(image, texCoord);
         cnt ++;
      }
   }

   gl_FragColor.rgb = sum.rgb / (float(cnt));  
}

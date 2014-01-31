//
// Fragment Shader for Image processing
//
// Mosaic Filter
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
   int iCol = floor(pos.x / float(nPixels));
   int iRow = floor(pos.y / float(nPixels));
        
   // Mosaic by Average
   int i, j;
   vec4 sum = vec4(0.0);
   int cnt = 0;    
   for(int j = iRow*nPixels ; j < iRow*nPixels + nPixels ; j++) {
      for(int i = iCol*nPixels; i < iCol*nPixels + nPixels; i++) {
         texCoord = vec2(float(i) / float(imgWidth),
            float(j) / float(imgHeight));
         sum += texture2D(image, texCoord);
         cnt ++;
      }
   }

   gl_FragColor.rgb = sum.rgb / (float(cnt));
  
}

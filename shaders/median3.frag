//
// Fragment Shader for Image processing
//
// 3X3 Median Filter for smoothing
//

//
// Macro for sorting
// makes a always smaller than b
//
#define small2(a,b) tmp=a; a=min(a,b); b=max(tmp,b);

// Bring the smallest number to the left
#define small3(a,b,c) small2(a,b); small2(a,c);
#define small4(a,b,c,d) small3(a,b,c); small2(a,d);
#define small5(a,b,c,d,e) small4(a,b,c,d); small2(a,e);
#define small6(a,b,c,d,e,f) small5(a,b,c,d,e); small2(a,f);
#define small7(a,b,c,d,e,f,g) small6(a,b,c,d,e,f); small2(a,g);
#define small8(a,b,c,d,e,f,g,h) small7(a,b,c,d,e,f,g); small2(a,h);
#define small9(a,b,c,d,e,f,g,h,i) small8(a,b,c,d,e,f,g,h); small2(a,i);

uniform sampler2D image;
uniform int imgWidth;
uniform int imgHeight;
varying vec2 pos;

void main(void)
{
   int i, j, k;
   int kernelRadius = 1;
   int diameter = kernelRadius + 1 + kernelRadius;
   int center = 2 * kernelRadius * ( 1 + kernelRadius );
   int size = diameter * diameter;
   vec2 offset;
   vec3 c[25];
   vec3 tmp;

   vec2 texCoord = vec2( pos.x / float( imgWidth ), pos.y / float( imgHeight ) );
	
   k = 0;
   for( i = -kernelRadius ; i <= kernelRadius ; i++ ) {
      for( j = -kernelRadius ; j <= kernelRadius ; j++ ) {
         offset = vec2( i / float( imgWidth ), j / float( imgHeight ) );
         c[k++] = texture2D( image, texCoord+offset ).rgb;
      }
   }

   // 3X3 kernel
   small9( c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8] );
   small8( c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8] );
   small7( c[2], c[3], c[4], c[5], c[6], c[7], c[8] );
   small6( c[3], c[4], c[5], c[6], c[7], c[8] );
   small5( c[4], c[5], c[6], c[7], c[8] );

   gl_FragColor = vec4( c[center], 1.0 );
   
   return;
}

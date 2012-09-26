/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define to 1 if you have `alloca', as a function or macro. */
/* #undef HAVE_ALLOCA */

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
/* #undef HAVE_ALLOCA_H */

/* V4L capturing support */
/* #undef HAVE_CAMV4L */

/* V4L2 capturing support */
/* #undef HAVE_CAMV4L2 */

/* V4L/V4L2 capturing support via libv4l */
/* #undef HAVE_LIBV4L */

/* Carbon windowing environment */
/* #undef HAVE_CARBON */

/* IEEE1394 capturing support */
/* #undef HAVE_DC1394 */

/* libdc1394 0.9.4 or 0.9.5 */
/* #undef HAVE_DC1394_095 */

/* IEEE1394 capturing support - libdc1394 v2.x */
/* #undef HAVE_DC1394_2 */

/* ffmpeg in Gentoo */
/* #undef HAVE_GENTOO_FFMPEG */

/* FFMpeg video library */
/* #undef HAVE_FFMPEG */

/* FFMpeg version flag */
/* #undef NEW_FFMPEG */

/* ffmpeg's libswscale */
/* #undef HAVE_FFMPEG_SWSCALE */

/* GStreamer multimedia framework */
/* #undef HAVE_GSTREAMER */

/* GTK+ 2.0 Thread support */
/* #undef HAVE_GTHREAD */

/* GTK+ 2.x toolkit */
/* #undef HAVE_GTK */

/* OpenEXR codec */
/* #undef HAVE_ILMIMF */

/* Apple ImageIO Framework */
/* #undef HAVE_IMAGEIO */

/* Define to 1 if you have the <inttypes.h> header file. */
/* #undef HAVE_INTTYPES_H */

/* JPEG-2000 codec */
/* #undef HAVE_JASPER */

/* IJG JPEG codec */
/* #undef HAVE_JPEG */

/* Define to 1 if you have the `dl' library (-ldl). */
/* #undef HAVE_LIBDL */

/* Define to 1 if you have the `gomp' library (-lgomp). */
/* #undef HAVE_LIBGOMP */

/* Define to 1 if you have the `m' library (-lm). */
/* #undef HAVE_LIBM */

/* libpng/png.h needs to be included */
/* #undef HAVE_LIBPNG_PNG_H */

/* Define to 1 if you have the `pthread' library (-lpthread). */
/* #undef HAVE_LIBPTHREAD */

/* Define to 1 if you have the `lrint' function. */
/* #undef HAVE_LRINT */

/* PNG codec */
/* #undef HAVE_PNG */

/* Define to 1 if you have the `png_get_valid' function. */
/* #undef HAVE_PNG_GET_VALID */

/* png.h needs to be included */
/* #undef HAVE_PNG_H */

/* Define to 1 if you have the `png_set_tRNS_to_alpha' function. */
/* #undef HAVE_PNG_SET_TRNS_TO_ALPHA */

/* QuickTime video libraries */
/* #undef HAVE_QUICKTIME */

/* AVFoundation video libraries */
/* #undef HAVE_AVFOUNDATION */

/* TIFF codec */
/* #undef HAVE_TIFF */

/* Unicap video capture library */
/* #undef HAVE_UNICAP */

/* Define to 1 if you have the <unistd.h> header file. */
/* #undef HAVE_UNISTD_H */

/* Xine video library */
/* #undef HAVE_XINE */

/* OpenNI library */
/* #undef HAVE_OPENNI */

/* LZ77 compression/decompression library (used for PNG) */
/* #undef HAVE_ZLIB */

/* Intel Integrated Performance Primitives */
/* #undef HAVE_IPP */

/* OpenCV compiled as static or dynamic libs */
/* #undef BUILD_SHARED_LIBS */

/* Name of package */
#define  PACKAGE "opencv"

/* Define to the address where bug reports for this package should be sent. */
#define  PACKAGE_BUGREPORT "opencvlibrary-devel@lists.sourceforge.net"

/* Define to the full name of this package. */
#define  PACKAGE_NAME "opencv"

/* Define to the full name and version of this package. */
#define  PACKAGE_STRING "opencv 2.4.0"

/* Define to the one symbol short name of this package. */
#define  PACKAGE_TARNAME "opencv"

/* Define to the version of this package. */
#define  PACKAGE_VERSION "2.4.0"

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Version number of package */
#define  VERSION "2.4.0"

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
/* #undef WORDS_BIGENDIAN */

/* Intel Threading Building Blocks */
/* #undef HAVE_TBB */

/* Eigen Matrix & Linear Algebra Library */
/* #undef HAVE_EIGEN */

/* NVidia Cuda Runtime API*/
/* #undef HAVE_CUDA */

/* NVidia Cuda Fast Fourier Transform (FFT) API*/
/* #undef HAVE_CUFFT */

/* NVidia Cuda Basic Linear Algebra Subprograms (BLAS) API*/
/* #undef HAVE_CUBLAS */

/* Compile for 'real' NVIDIA GPU architectures */
#define CUDA_ARCH_BIN ""

/* Compile for 'virtual' NVIDIA PTX architectures */
#define CUDA_ARCH_PTX ""

/* NVIDIA GPU features are used */
#define CUDA_ARCH_FEATURES ""

/* Create PTX or BIN for 1.0 compute capability */
/* #undef CUDA_ARCH_BIN_OR_PTX_10 */

/* VideoInput library */
/* #undef HAVE_VIDEOINPUT */

/* XIMEA camera support */
/* #undef HAVE_XIMEA */

/* OpenGL support*/
/* #undef HAVE_OPENGL */

/* Clp support */
/* #undef HAVE_CLP */

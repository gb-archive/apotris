#include "../build/sprite_pal_bin.h"
#include "../build/sprite1tiles_bin.h"
#include "../build/sprite2tiles_bin.h"
#include "../build/sprite3tiles_bin.h"
#include "../build/sprite4tiles_bin.h"
#include "../build/sprite5tiles_bin.h"
#include "../build/sprite6tiles_bin.h"
#include "../build/sprite7tiles_bin.h"
#include "../build/sprite8tiles_bin.h"
#include "../build/sprite9tiles_bin.h"
#include "../build/sprite10tiles_bin.h"
#include "../build/sprite11tiles_bin.h"
#include "../build/sprite12tiles_bin.h"
#include "../build/sprite13tiles_bin.h"
#include "../build/sprite14tiles_bin.h"
#include "../build/sprite15tiles_bin.h"
#include "../build/sprite16tiles_bin.h"
#include "../build/sprite17tiles_bin.h"
#include "../build/sprite18tiles_bin.h"
#include "../build/sprite19tiles_bin.h"
#include "../build/sprite20tiles_bin.h"
#include "../build/sprite21tiles_bin.h"
#include "../build/sprite22tiles_bin.h"
#include "../build/sprite23tiles_bin.h"
#include "../build/sprite24tiles_bin.h"

#include "../build/title1tiles_bin.h"
#include "../build/title2tiles_bin.h"
#include "../build/title_pal_bin.h"

#define paletteLen 512
/* const unsigned short palette[256] __attribute__((aligned(4)))= */
/* { */
/* 	0x0000,0x45c3,0x6ea5,0x7f26,0x7FFF,0x0c63,0x0421,0x7fff, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//0 */

/* 	0x0000,0x48a4,0x5ce5,0x7506,0x7FFF,0x1ce7,0x0421,0x0421, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//1 */

/* 	0x0000,0x0174,0x01fa,0x025f,0x7FFF,0x318c,0x0421,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//2 */

/* 	0x0000,0x0276,0x02fa,0x035f,0x7FFF,0x5294,0x0421,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//3 */

/* 	0x0000,0x0287,0x02e8,0x0368,0x7FFF,0x6739,0x0421,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//4 */

/* 	0x0000,0x588f,0x6cb2,0x7cd5,0x7FFF,0x5294,0x0421,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//5 */

/* 	0x0000,0x0015,0x0018,0x001a,0x7FFF,0x318c,0x0421,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//6 */

/* 	0x0000,0x1ce7,0x318c,0x5294,0x7FFF,0x1ce7,0x0421,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//7 */

/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//8 */

/* 	0x0000,0x318c,0x5294,0x7fff,0x0000,0x0000,0x0000,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//9 */

/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//10 */

/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//11 */

/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//12 */

/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//13 */

/* 	0x0000,0x4A52,0x318c,0x0421,0x0000,0x0000,0x0000,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//14 */

/* 	0x0000,0x4A52,0x7FFF,0x294a,0x0000,0x0000,0x0000,0x0000, */
/* 	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//15 */

/* }; */

const unsigned short palette[256] __attribute__((aligned(4)))=
{
	0x0000,0x45c3,0x6ea5,0x7f26,0x7FFF,0x0c63,0x0421,0x7fff,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//0

	0x0000,0x48a4,0x5982,0x7e66,0x7FFF,0x1ce7,0x0421,0x0421,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//1

	0x0000,0x0174,0x123e,0x2ebf,0x7FFF,0x318c,0x0421,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//2

	0x0000,0x0276,0x1f5e,0x3fff,0x7FFF,0x5294,0x0421,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//3

	0x0000,0x0287,0x26ea,0x43f0,0x7FFF,0x6739,0x0421,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//4

	0x0000,0x588f,0x50d3,0x757b,0x7FFF,0x5294,0x0421,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//5

	0x0000,0x0015,0x313d,0x3dff,0x7FFF,0x318c,0x0421,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//6

	0x0000,0x1ce7,0x318c,0x5294,0x7FFF,0x1ce7,0x0421,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//7

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//8

	0x0000,0x318c,0x5294,0x7fff,0x739c,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//9

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//10

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//11

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//12

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//13

	0x0000,0x4A52,0x318c,0x0421,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//14

	0x0000,0x4A52,0x7FFF,0x294a,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//15

};


extern const uint8_t * mini[2][7];

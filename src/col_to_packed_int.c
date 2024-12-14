
#define R_NO_REMAP

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "hash-color.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// color names as returned by "colors()"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern char *col_name[];

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Actual color values
//
// Mostly created with the following code:
//
//  mat <- t(col2rgb(colors(), alpha = TRUE))
//  apply(mat, 1, \(x) paste0("{", paste(x, collapse = ", "), "},")) |>
//  cat(sep = "\n")
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static uint32_t packed_int[659] = {
  0x00FFFFFF, // NA
  0x00FFFFFF, // transparent
  0xFFFFFFFF, // white
  0xFFFFF8F0, // aliceblue
  0xFFD7EBFA, // antiquewhite
  0xFFDBEFFF, // antiquewhite1
  0xFFCCDFEE, // antiquewhite2
  0xFFB0C0CD, // antiquewhite3
  0xFF78838B, // antiquewhite4
  0xFFD4FF7F, // aquamarine
  0xFFD4FF7F, // aquamarine1
  0xFFC6EE76, // aquamarine2
  0xFFAACD66, // aquamarine3
  0xFF748B45, // aquamarine4
  0xFFFFFFF0, // azure
  0xFFFFFFF0, // azure1
  0xFFEEEEE0, // azure2
  0xFFCDCDC1, // azure3
  0xFF8B8B83, // azure4
  0xFFDCF5F5, // beige
  0xFFC4E4FF, // bisque
  0xFFC4E4FF, // bisque1
  0xFFB7D5EE, // bisque2
  0xFF9EB7CD, // bisque3
  0xFF6B7D8B, // bisque4
  0xFF000000, // black
  0xFFCDEBFF, // blanchedalmond
  0xFFFF0000, // blue
  0xFFFF0000, // blue1
  0xFFEE0000, // blue2
  0xFFCD0000, // blue3
  0xFF8B0000, // blue4
  0xFFE22B8A, // blueviolet
  0xFF2A2AA5, // brown
  0xFF4040FF, // brown1
  0xFF3B3BEE, // brown2
  0xFF3333CD, // brown3
  0xFF23238B, // brown4
  0xFF87B8DE, // burlywood
  0xFF9BD3FF, // burlywood1
  0xFF91C5EE, // burlywood2
  0xFF7DAACD, // burlywood3
  0xFF55738B, // burlywood4
  0xFFA09E5F, // cadetblue
  0xFFFFF598, // cadetblue1
  0xFFEEE58E, // cadetblue2
  0xFFCDC57A, // cadetblue3
  0xFF8B8653, // cadetblue4
  0xFF00FF7F, // chartreuse
  0xFF00FF7F, // chartreuse1
  0xFF00EE76, // chartreuse2
  0xFF00CD66, // chartreuse3
  0xFF008B45, // chartreuse4
  0xFF1E69D2, // chocolate
  0xFF247FFF, // chocolate1
  0xFF2176EE, // chocolate2
  0xFF1D66CD, // chocolate3
  0xFF13458B, // chocolate4
  0xFF507FFF, // coral
  0xFF5672FF, // coral1
  0xFF506AEE, // coral2
  0xFF455BCD, // coral3
  0xFF2F3E8B, // coral4
  0xFFED9564, // cornflowerblue
  0xFFDCF8FF, // cornsilk
  0xFFDCF8FF, // cornsilk1
  0xFFCDE8EE, // cornsilk2
  0xFFB1C8CD, // cornsilk3
  0xFF78888B, // cornsilk4
  0xFFFFFF00, // cyan
  0xFFFFFF00, // cyan1
  0xFFEEEE00, // cyan2
  0xFFCDCD00, // cyan3
  0xFF8B8B00, // cyan4
  0xFF8B0000, // darkblue
  0xFF8B8B00, // darkcyan
  0xFF0B86B8, // darkgoldenrod
  0xFF0FB9FF, // darkgoldenrod1
  0xFF0EADEE, // darkgoldenrod2
  0xFF0C95CD, // darkgoldenrod3
  0xFF08658B, // darkgoldenrod4
  0xFFA9A9A9, // darkgray
  0xFF006400, // darkgreen
  0xFFA9A9A9, // darkgrey
  0xFF6BB7BD, // darkkhaki
  0xFF8B008B, // darkmagenta
  0xFF2F6B55, // darkolivegreen
  0xFF70FFCA, // darkolivegreen1
  0xFF68EEBC, // darkolivegreen2
  0xFF5ACDA2, // darkolivegreen3
  0xFF3D8B6E, // darkolivegreen4
  0xFF008CFF, // darkorange
  0xFF007FFF, // darkorange1
  0xFF0076EE, // darkorange2
  0xFF0066CD, // darkorange3
  0xFF00458B, // darkorange4
  0xFFCC3299, // darkorchid
  0xFFFF3EBF, // darkorchid1
  0xFFEE3AB2, // darkorchid2
  0xFFCD329A, // darkorchid3
  0xFF8B2268, // darkorchid4
  0xFF00008B, // darkred
  0xFF7A96E9, // darksalmon
  0xFF8FBC8F, // darkseagreen
  0xFFC1FFC1, // darkseagreen1
  0xFFB4EEB4, // darkseagreen2
  0xFF9BCD9B, // darkseagreen3
  0xFF698B69, // darkseagreen4
  0xFF8B3D48, // darkslateblue
  0xFF4F4F2F, // darkslategray
  0xFFFFFF97, // darkslategray1
  0xFFEEEE8D, // darkslategray2
  0xFFCDCD79, // darkslategray3
  0xFF8B8B52, // darkslategray4
  0xFF4F4F2F, // darkslategrey
  0xFFD1CE00, // darkturquoise
  0xFFD30094, // darkviolet
  0xFF9314FF, // deeppink
  0xFF9314FF, // deeppink1
  0xFF8912EE, // deeppink2
  0xFF7610CD, // deeppink3
  0xFF500A8B, // deeppink4
  0xFFFFBF00, // deepskyblue
  0xFFFFBF00, // deepskyblue1
  0xFFEEB200, // deepskyblue2
  0xFFCD9A00, // deepskyblue3
  0xFF8B6800, // deepskyblue4
  0xFF696969, // dimgray
  0xFF696969, // dimgrey
  0xFFFF901E, // dodgerblue
  0xFFFF901E, // dodgerblue1
  0xFFEE861C, // dodgerblue2
  0xFFCD7418, // dodgerblue3
  0xFF8B4E10, // dodgerblue4
  0xFF2222B2, // firebrick
  0xFF3030FF, // firebrick1
  0xFF2C2CEE, // firebrick2
  0xFF2626CD, // firebrick3
  0xFF1A1A8B, // firebrick4
  0xFFF0FAFF, // floralwhite
  0xFF228B22, // forestgreen
  0xFFDCDCDC, // gainsboro
  0xFFFFF8F8, // ghostwhite
  0xFF00D7FF, // gold
  0xFF00D7FF, // gold1
  0xFF00C9EE, // gold2
  0xFF00ADCD, // gold3
  0xFF00758B, // gold4
  0xFF20A5DA, // goldenrod
  0xFF25C1FF, // goldenrod1
  0xFF22B4EE, // goldenrod2
  0xFF1D9BCD, // goldenrod3
  0xFF14698B, // goldenrod4
  0xFFBEBEBE, // gray
  0xFF000000, // gray0
  0xFF030303, // gray1
  0xFF050505, // gray2
  0xFF080808, // gray3
  0xFF0A0A0A, // gray4
  0xFF0D0D0D, // gray5
  0xFF0F0F0F, // gray6
  0xFF121212, // gray7
  0xFF141414, // gray8
  0xFF171717, // gray9
  0xFF1A1A1A, // gray10
  0xFF1C1C1C, // gray11
  0xFF1F1F1F, // gray12
  0xFF212121, // gray13
  0xFF242424, // gray14
  0xFF262626, // gray15
  0xFF292929, // gray16
  0xFF2B2B2B, // gray17
  0xFF2E2E2E, // gray18
  0xFF303030, // gray19
  0xFF333333, // gray20
  0xFF363636, // gray21
  0xFF383838, // gray22
  0xFF3B3B3B, // gray23
  0xFF3D3D3D, // gray24
  0xFF404040, // gray25
  0xFF424242, // gray26
  0xFF454545, // gray27
  0xFF474747, // gray28
  0xFF4A4A4A, // gray29
  0xFF4D4D4D, // gray30
  0xFF4F4F4F, // gray31
  0xFF525252, // gray32
  0xFF545454, // gray33
  0xFF575757, // gray34
  0xFF595959, // gray35
  0xFF5C5C5C, // gray36
  0xFF5E5E5E, // gray37
  0xFF616161, // gray38
  0xFF636363, // gray39
  0xFF666666, // gray40
  0xFF696969, // gray41
  0xFF6B6B6B, // gray42
  0xFF6E6E6E, // gray43
  0xFF707070, // gray44
  0xFF737373, // gray45
  0xFF757575, // gray46
  0xFF787878, // gray47
  0xFF7A7A7A, // gray48
  0xFF7D7D7D, // gray49
  0xFF7F7F7F, // gray50
  0xFF828282, // gray51
  0xFF858585, // gray52
  0xFF878787, // gray53
  0xFF8A8A8A, // gray54
  0xFF8C8C8C, // gray55
  0xFF8F8F8F, // gray56
  0xFF919191, // gray57
  0xFF949494, // gray58
  0xFF969696, // gray59
  0xFF999999, // gray60
  0xFF9C9C9C, // gray61
  0xFF9E9E9E, // gray62
  0xFFA1A1A1, // gray63
  0xFFA3A3A3, // gray64
  0xFFA6A6A6, // gray65
  0xFFA8A8A8, // gray66
  0xFFABABAB, // gray67
  0xFFADADAD, // gray68
  0xFFB0B0B0, // gray69
  0xFFB3B3B3, // gray70
  0xFFB5B5B5, // gray71
  0xFFB8B8B8, // gray72
  0xFFBABABA, // gray73
  0xFFBDBDBD, // gray74
  0xFFBFBFBF, // gray75
  0xFFC2C2C2, // gray76
  0xFFC4C4C4, // gray77
  0xFFC7C7C7, // gray78
  0xFFC9C9C9, // gray79
  0xFFCCCCCC, // gray80
  0xFFCFCFCF, // gray81
  0xFFD1D1D1, // gray82
  0xFFD4D4D4, // gray83
  0xFFD6D6D6, // gray84
  0xFFD9D9D9, // gray85
  0xFFDBDBDB, // gray86
  0xFFDEDEDE, // gray87
  0xFFE0E0E0, // gray88
  0xFFE3E3E3, // gray89
  0xFFE5E5E5, // gray90
  0xFFE8E8E8, // gray91
  0xFFEBEBEB, // gray92
  0xFFEDEDED, // gray93
  0xFFF0F0F0, // gray94
  0xFFF2F2F2, // gray95
  0xFFF5F5F5, // gray96
  0xFFF7F7F7, // gray97
  0xFFFAFAFA, // gray98
  0xFFFCFCFC, // gray99
  0xFFFFFFFF, // gray100
  0xFF00FF00, // green
  0xFF00FF00, // green1
  0xFF00EE00, // green2
  0xFF00CD00, // green3
  0xFF008B00, // green4
  0xFF2FFFAD, // greenyellow
  0xFFBEBEBE, // grey
  0xFF000000, // grey0
  0xFF030303, // grey1
  0xFF050505, // grey2
  0xFF080808, // grey3
  0xFF0A0A0A, // grey4
  0xFF0D0D0D, // grey5
  0xFF0F0F0F, // grey6
  0xFF121212, // grey7
  0xFF141414, // grey8
  0xFF171717, // grey9
  0xFF1A1A1A, // grey10
  0xFF1C1C1C, // grey11
  0xFF1F1F1F, // grey12
  0xFF212121, // grey13
  0xFF242424, // grey14
  0xFF262626, // grey15
  0xFF292929, // grey16
  0xFF2B2B2B, // grey17
  0xFF2E2E2E, // grey18
  0xFF303030, // grey19
  0xFF333333, // grey20
  0xFF363636, // grey21
  0xFF383838, // grey22
  0xFF3B3B3B, // grey23
  0xFF3D3D3D, // grey24
  0xFF404040, // grey25
  0xFF424242, // grey26
  0xFF454545, // grey27
  0xFF474747, // grey28
  0xFF4A4A4A, // grey29
  0xFF4D4D4D, // grey30
  0xFF4F4F4F, // grey31
  0xFF525252, // grey32
  0xFF545454, // grey33
  0xFF575757, // grey34
  0xFF595959, // grey35
  0xFF5C5C5C, // grey36
  0xFF5E5E5E, // grey37
  0xFF616161, // grey38
  0xFF636363, // grey39
  0xFF666666, // grey40
  0xFF696969, // grey41
  0xFF6B6B6B, // grey42
  0xFF6E6E6E, // grey43
  0xFF707070, // grey44
  0xFF737373, // grey45
  0xFF757575, // grey46
  0xFF787878, // grey47
  0xFF7A7A7A, // grey48
  0xFF7D7D7D, // grey49
  0xFF7F7F7F, // grey50
  0xFF828282, // grey51
  0xFF858585, // grey52
  0xFF878787, // grey53
  0xFF8A8A8A, // grey54
  0xFF8C8C8C, // grey55
  0xFF8F8F8F, // grey56
  0xFF919191, // grey57
  0xFF949494, // grey58
  0xFF969696, // grey59
  0xFF999999, // grey60
  0xFF9C9C9C, // grey61
  0xFF9E9E9E, // grey62
  0xFFA1A1A1, // grey63
  0xFFA3A3A3, // grey64
  0xFFA6A6A6, // grey65
  0xFFA8A8A8, // grey66
  0xFFABABAB, // grey67
  0xFFADADAD, // grey68
  0xFFB0B0B0, // grey69
  0xFFB3B3B3, // grey70
  0xFFB5B5B5, // grey71
  0xFFB8B8B8, // grey72
  0xFFBABABA, // grey73
  0xFFBDBDBD, // grey74
  0xFFBFBFBF, // grey75
  0xFFC2C2C2, // grey76
  0xFFC4C4C4, // grey77
  0xFFC7C7C7, // grey78
  0xFFC9C9C9, // grey79
  0xFFCCCCCC, // grey80
  0xFFCFCFCF, // grey81
  0xFFD1D1D1, // grey82
  0xFFD4D4D4, // grey83
  0xFFD6D6D6, // grey84
  0xFFD9D9D9, // grey85
  0xFFDBDBDB, // grey86
  0xFFDEDEDE, // grey87
  0xFFE0E0E0, // grey88
  0xFFE3E3E3, // grey89
  0xFFE5E5E5, // grey90
  0xFFE8E8E8, // grey91
  0xFFEBEBEB, // grey92
  0xFFEDEDED, // grey93
  0xFFF0F0F0, // grey94
  0xFFF2F2F2, // grey95
  0xFFF5F5F5, // grey96
  0xFFF7F7F7, // grey97
  0xFFFAFAFA, // grey98
  0xFFFCFCFC, // grey99
  0xFFFFFFFF, // grey100
  0xFFF0FFF0, // honeydew
  0xFFF0FFF0, // honeydew1
  0xFFE0EEE0, // honeydew2
  0xFFC1CDC1, // honeydew3
  0xFF838B83, // honeydew4
  0xFFB469FF, // hotpink
  0xFFB46EFF, // hotpink1
  0xFFA76AEE, // hotpink2
  0xFF9060CD, // hotpink3
  0xFF623A8B, // hotpink4
  0xFF5C5CCD, // indianred
  0xFF6A6AFF, // indianred1
  0xFF6363EE, // indianred2
  0xFF5555CD, // indianred3
  0xFF3A3A8B, // indianred4
  0xFFF0FFFF, // ivory
  0xFFF0FFFF, // ivory1
  0xFFE0EEEE, // ivory2
  0xFFC1CDCD, // ivory3
  0xFF838B8B, // ivory4
  0xFF8CE6F0, // khaki
  0xFF8FF6FF, // khaki1
  0xFF85E6EE, // khaki2
  0xFF73C6CD, // khaki3
  0xFF4E868B, // khaki4
  0xFFFAE6E6, // lavender
  0xFFF5F0FF, // lavenderblush
  0xFFF5F0FF, // lavenderblush1
  0xFFE5E0EE, // lavenderblush2
  0xFFC5C1CD, // lavenderblush3
  0xFF86838B, // lavenderblush4
  0xFF00FC7C, // lawngreen
  0xFFCDFAFF, // lemonchiffon
  0xFFCDFAFF, // lemonchiffon1
  0xFFBFE9EE, // lemonchiffon2
  0xFFA5C9CD, // lemonchiffon3
  0xFF70898B, // lemonchiffon4
  0xFFE6D8AD, // lightblue
  0xFFFFEFBF, // lightblue1
  0xFFEEDFB2, // lightblue2
  0xFFCDC09A, // lightblue3
  0xFF8B8368, // lightblue4
  0xFF8080F0, // lightcoral
  0xFFFFFFE0, // lightcyan
  0xFFFFFFE0, // lightcyan1
  0xFFEEEED1, // lightcyan2
  0xFFCDCDB4, // lightcyan3
  0xFF8B8B7A, // lightcyan4
  0xFF82DDEE, // lightgoldenrod
  0xFF8BECFF, // lightgoldenrod1
  0xFF82DCEE, // lightgoldenrod2
  0xFF70BECD, // lightgoldenrod3
  0xFF4C818B, // lightgoldenrod4
  0xFFD2FAFA, // lightgoldenrodyellow
  0xFFD3D3D3, // lightgray
  0xFF90EE90, // lightgreen
  0xFFD3D3D3, // lightgrey
  0xFFC1B6FF, // lightpink
  0xFFB9AEFF, // lightpink1
  0xFFADA2EE, // lightpink2
  0xFF958CCD, // lightpink3
  0xFF655F8B, // lightpink4
  0xFF7AA0FF, // lightsalmon
  0xFF7AA0FF, // lightsalmon1
  0xFF7295EE, // lightsalmon2
  0xFF6281CD, // lightsalmon3
  0xFF42578B, // lightsalmon4
  0xFFAAB220, // lightseagreen
  0xFFFACE87, // lightskyblue
  0xFFFFE2B0, // lightskyblue1
  0xFFEED3A4, // lightskyblue2
  0xFFCDB68D, // lightskyblue3
  0xFF8B7B60, // lightskyblue4
  0xFFFF7084, // lightslateblue
  0xFF998877, // lightslategray
  0xFF998877, // lightslategrey
  0xFFDEC4B0, // lightsteelblue
  0xFFFFE1CA, // lightsteelblue1
  0xFFEED2BC, // lightsteelblue2
  0xFFCDB5A2, // lightsteelblue3
  0xFF8B7B6E, // lightsteelblue4
  0xFFE0FFFF, // lightyellow
  0xFFE0FFFF, // lightyellow1
  0xFFD1EEEE, // lightyellow2
  0xFFB4CDCD, // lightyellow3
  0xFF7A8B8B, // lightyellow4
  0xFF32CD32, // limegreen
  0xFFE6F0FA, // linen
  0xFFFF00FF, // magenta
  0xFFFF00FF, // magenta1
  0xFFEE00EE, // magenta2
  0xFFCD00CD, // magenta3
  0xFF8B008B, // magenta4
  0xFF6030B0, // maroon
  0xFFB334FF, // maroon1
  0xFFA730EE, // maroon2
  0xFF9029CD, // maroon3
  0xFF621C8B, // maroon4
  0xFFAACD66, // mediumaquamarine
  0xFFCD0000, // mediumblue
  0xFFD355BA, // mediumorchid
  0xFFFF66E0, // mediumorchid1
  0xFFEE5FD1, // mediumorchid2
  0xFFCD52B4, // mediumorchid3
  0xFF8B377A, // mediumorchid4
  0xFFDB7093, // mediumpurple
  0xFFFF82AB, // mediumpurple1
  0xFFEE799F, // mediumpurple2
  0xFFCD6889, // mediumpurple3
  0xFF8B475D, // mediumpurple4
  0xFF71B33C, // mediumseagreen
  0xFFEE687B, // mediumslateblue
  0xFF9AFA00, // mediumspringgreen
  0xFFCCD148, // mediumturquoise
  0xFF8515C7, // mediumvioletred
  0xFF701919, // midnightblue
  0xFFFAFFF5, // mintcream
  0xFFE1E4FF, // mistyrose
  0xFFE1E4FF, // mistyrose1
  0xFFD2D5EE, // mistyrose2
  0xFFB5B7CD, // mistyrose3
  0xFF7B7D8B, // mistyrose4
  0xFFB5E4FF, // moccasin
  0xFFADDEFF, // navajowhite
  0xFFADDEFF, // navajowhite1
  0xFFA1CFEE, // navajowhite2
  0xFF8BB3CD, // navajowhite3
  0xFF5E798B, // navajowhite4
  0xFF800000, // navy
  0xFF800000, // navyblue
  0xFFE6F5FD, // oldlace
  0xFF238E6B, // olivedrab
  0xFF3EFFC0, // olivedrab1
  0xFF3AEEB3, // olivedrab2
  0xFF32CD9A, // olivedrab3
  0xFF228B69, // olivedrab4
  0xFF00A5FF, // orange
  0xFF00A5FF, // orange1
  0xFF009AEE, // orange2
  0xFF0085CD, // orange3
  0xFF005A8B, // orange4
  0xFF0045FF, // orangered
  0xFF0045FF, // orangered1
  0xFF0040EE, // orangered2
  0xFF0037CD, // orangered3
  0xFF00258B, // orangered4
  0xFFD670DA, // orchid
  0xFFFA83FF, // orchid1
  0xFFE97AEE, // orchid2
  0xFFC969CD, // orchid3
  0xFF89478B, // orchid4
  0xFFAAE8EE, // palegoldenrod
  0xFF98FB98, // palegreen
  0xFF9AFF9A, // palegreen1
  0xFF90EE90, // palegreen2
  0xFF7CCD7C, // palegreen3
  0xFF548B54, // palegreen4
  0xFFEEEEAF, // paleturquoise
  0xFFFFFFBB, // paleturquoise1
  0xFFEEEEAE, // paleturquoise2
  0xFFCDCD96, // paleturquoise3
  0xFF8B8B66, // paleturquoise4
  0xFF9370DB, // palevioletred
  0xFFAB82FF, // palevioletred1
  0xFF9F79EE, // palevioletred2
  0xFF8968CD, // palevioletred3
  0xFF5D478B, // palevioletred4
  0xFFD5EFFF, // papayawhip
  0xFFB9DAFF, // peachpuff
  0xFFB9DAFF, // peachpuff1
  0xFFADCBEE, // peachpuff2
  0xFF95AFCD, // peachpuff3
  0xFF65778B, // peachpuff4
  0xFF3F85CD, // peru
  0xFFCBC0FF, // pink
  0xFFC5B5FF, // pink1
  0xFFB8A9EE, // pink2
  0xFF9E91CD, // pink3
  0xFF6C638B, // pink4
  0xFFDDA0DD, // plum
  0xFFFFBBFF, // plum1
  0xFFEEAEEE, // plum2
  0xFFCD96CD, // plum3
  0xFF8B668B, // plum4
  0xFFE6E0B0, // powderblue
  0xFFF020A0, // purple
  0xFFFF309B, // purple1
  0xFFEE2C91, // purple2
  0xFFCD267D, // purple3
  0xFF8B1A55, // purple4
  0xFF0000FF, // red
  0xFF0000FF, // red1
  0xFF0000EE, // red2
  0xFF0000CD, // red3
  0xFF00008B, // red4
  0xFF8F8FBC, // rosybrown
  0xFFC1C1FF, // rosybrown1
  0xFFB4B4EE, // rosybrown2
  0xFF9B9BCD, // rosybrown3
  0xFF69698B, // rosybrown4
  0xFFE16941, // royalblue
  0xFFFF7648, // royalblue1
  0xFFEE6E43, // royalblue2
  0xFFCD5F3A, // royalblue3
  0xFF8B4027, // royalblue4
  0xFF13458B, // saddlebrown
  0xFF7280FA, // salmon
  0xFF698CFF, // salmon1
  0xFF6282EE, // salmon2
  0xFF5470CD, // salmon3
  0xFF394C8B, // salmon4
  0xFF60A4F4, // sandybrown
  0xFF578B2E, // seagreen
  0xFF9FFF54, // seagreen1
  0xFF94EE4E, // seagreen2
  0xFF80CD43, // seagreen3
  0xFF578B2E, // seagreen4
  0xFFEEF5FF, // seashell
  0xFFEEF5FF, // seashell1
  0xFFDEE5EE, // seashell2
  0xFFBFC5CD, // seashell3
  0xFF82868B, // seashell4
  0xFF2D52A0, // sienna
  0xFF4782FF, // sienna1
  0xFF4279EE, // sienna2
  0xFF3968CD, // sienna3
  0xFF26478B, // sienna4
  0xFFEBCE87, // skyblue
  0xFFFFCE87, // skyblue1
  0xFFEEC07E, // skyblue2
  0xFFCDA66C, // skyblue3
  0xFF8B704A, // skyblue4
  0xFFCD5A6A, // slateblue
  0xFFFF6F83, // slateblue1
  0xFFEE677A, // slateblue2
  0xFFCD5969, // slateblue3
  0xFF8B3C47, // slateblue4
  0xFF908070, // slategray
  0xFFFFE2C6, // slategray1
  0xFFEED3B9, // slategray2
  0xFFCDB69F, // slategray3
  0xFF8B7B6C, // slategray4
  0xFF908070, // slategrey
  0xFFFAFAFF, // snow
  0xFFFAFAFF, // snow1
  0xFFE9E9EE, // snow2
  0xFFC9C9CD, // snow3
  0xFF89898B, // snow4
  0xFF7FFF00, // springgreen
  0xFF7FFF00, // springgreen1
  0xFF76EE00, // springgreen2
  0xFF66CD00, // springgreen3
  0xFF458B00, // springgreen4
  0xFFB48246, // steelblue
  0xFFFFB863, // steelblue1
  0xFFEEAC5C, // steelblue2
  0xFFCD944F, // steelblue3
  0xFF8B6436, // steelblue4
  0xFF8CB4D2, // tan
  0xFF4FA5FF, // tan1
  0xFF499AEE, // tan2
  0xFF3F85CD, // tan3
  0xFF2B5A8B, // tan4
  0xFFD8BFD8, // thistle
  0xFFFFE1FF, // thistle1
  0xFFEED2EE, // thistle2
  0xFFCDB5CD, // thistle3
  0xFF8B7B8B, // thistle4
  0xFF4763FF, // tomato
  0xFF4763FF, // tomato1
  0xFF425CEE, // tomato2
  0xFF394FCD, // tomato3
  0xFF26368B, // tomato4
  0xFFD0E040, // turquoise
  0xFFFFF500, // turquoise1
  0xFFEEE500, // turquoise2
  0xFFCDC500, // turquoise3
  0xFF8B8600, // turquoise4
  0xFFEE82EE, // violet
  0xFF9020D0, // violetred
  0xFF963EFF, // violetred1
  0xFF8C3AEE, // violetred2
  0xFF7832CD, // violetred3
  0xFF52228B, // violetred4
  0xFFB3DEF5, // wheat
  0xFFBAE7FF, // wheat1
  0xFFAED8EE, // wheat2
  0xFF96BACD, // wheat3
  0xFF667E8B, // wheat4
  0xFFF5F5F5, // whitesmoke
  0xFF00FFFF, // yellow
  0xFF00FFFF, // yellow1
  0xFF00EEEE, // yellow2
  0xFF00CDCD, // yellow3
  0xFF008B8B, // yellow4
  0xFF32CD9A  // yellowgreen
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prior hex-to-nibble methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// uint8_t hexlut[128] = {
//   0,
//   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
//   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
//   0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 
//   0, 0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
//   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 
//   14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
//   0, 0, 0, 0, 0, 0, 0
// };
// #define hex2nibble(x) ( 9 * ((x) >> 6) + ((x) & 017) )
// #define hex2nibble(x) (hexlut[(uint8_t)(x)])
// #define hex2nibble(s) ((s) <= '9') ? (s) - '0' : ((s) & 0x7) + 9;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Convert a hex digit to a nibble. 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define hex2nibble(x) ( (((x) & 0xf) + ((x) >> 6) + ((x >> 6) << 3)) & 0xf )


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Convert a character vector of R colors to 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP col_to_int_(SEXP cols_) {
  
  int n = LENGTH(cols_);
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Output is an integer vector
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  SEXP res_ = PROTECT(Rf_allocVector(INTSXP, n));

  uint32_t *ptr = (uint32_t *)INTEGER(res_);
  
  for(int i = 0; i < n; i++) {
    const char *col = CHAR(STRING_ELT(cols_, i));
    
    if (col[0] == '#') {
      switch (strlen(col)) {
      case 4:  // #123 == #112233
        ptr[i] =
          0xFF000000u + 
          (uint32_t)(hex2nibble(col[3]) << 20) +
          (uint32_t)(hex2nibble(col[3]) << 16) +
          (uint32_t)(hex2nibble(col[2]) << 12) +
          (uint32_t)(hex2nibble(col[2]) <<  8) +
          (uint32_t)(hex2nibble(col[1]) <<  4) +
          (uint32_t)(hex2nibble(col[1]) <<  0);
        break;
      case 5: // #1234 = #11223344
        ptr[i] =
          ((uint32_t)(hex2nibble(col[4])) << 28) +
          (uint32_t)(hex2nibble(col[4]) << 24) +
          (uint32_t)(hex2nibble(col[3]) << 20) +
          (uint32_t)(hex2nibble(col[3]) << 16) +
          (uint32_t)(hex2nibble(col[2]) << 12) +
          (uint32_t)(hex2nibble(col[2]) <<  8) +
          (uint32_t)(hex2nibble(col[1]) <<  4) +
          (uint32_t)(hex2nibble(col[1]) <<  0);
        break;
      case 7: // #rrggbb
        ptr[i] =
          0xFF000000u + 
          (uint32_t)(hex2nibble(col[5]) << 20) +
          (uint32_t)(hex2nibble(col[6]) << 16) +
          (uint32_t)(hex2nibble(col[3]) << 12) +
          (uint32_t)(hex2nibble(col[4]) <<  8) +
          (uint32_t)(hex2nibble(col[1]) <<  4) +
          (uint32_t)(hex2nibble(col[2]) <<  0);
        break;
      case 9: // #rrggbbaa
        ptr[i] =
          ((uint32_t)(hex2nibble(col[7])) << 28) +
          (uint32_t)(hex2nibble(col[8]) << 24) +
          (uint32_t)(hex2nibble(col[5]) << 20) +
          (uint32_t)(hex2nibble(col[6]) << 16) +
          (uint32_t)(hex2nibble(col[3]) << 12) +
          (uint32_t)(hex2nibble(col[4]) <<  8) +
          (uint32_t)(hex2nibble(col[1]) <<  4) +
          (uint32_t)(hex2nibble(col[2]) <<  0);
        break;
      default:
        Rf_error("col_to_int_(): Hex notation error: %s", col);
      }
    } else {
      
      int idx = hash_color((const unsigned char *)col);
      // don't need to do a full string comparison, as the probability of
      // an incorrect color name (e.g. 'bluexx') hashing to a color
      // that starts with 'blu' seems incredibly remote.  
      // Probably worth testing though to figure out what is needed to 
      // actually cause a collision here. (and how much of the strings should
      // be compared to detect it)
      if (idx < 0 || idx > 658 || memcmp(col, col_name[idx], 2) != 0) {
        Rf_error("col_to_int_(): Not a valid color name: %s", col);
      }
      ptr[i] = packed_int[idx];
    }
  }
  
  
  UNPROTECT(1);
  return res_;
}



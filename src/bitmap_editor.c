/**
 * Control Software for the Inland (FURI KEYSHINE) USB LED Badge
 * Copyright (C) 2009 Tim Hentenaar. http://hentenaar.com
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your option) any later version. This program is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this 
 * program. If not, see http://www.gnu.org/licenses/. 
 */

#include <stdlib.h>
#include <string.h>
#include <glib/gi18n.h>

#include "bitmap_editor.h"

extern GtkWidget *window;

/* Colors */
static const GdkColor bg_color   = { 0x0000, 0x0000, 0x0000, 0x0000 };
static const GdkColor fg_color   = { 0x0000, 0xFFFF, 0x0000, 0x0000 };
static const GdkColor grid_color = { 0x0000, 0xFFFF, 0xFFFF, 0xFFFF };

/* Grid points (assuming every two points is one line) */
static const GdkSegment grid_segments[707] = {
	/* X Axis */
	{ 16, 0, 16, 112 }, { 32, 0, 32, 112 }, { 48, 0, 48, 112 }, { 64, 0, 64, 112 }, { 80, 0, 80, 112 }, 
	{ 96, 0, 96, 112 }, { 112, 0, 112, 112 }, { 128, 0, 128, 112 }, { 144, 0, 144, 112 }, { 160, 0, 160, 112 }, 
	{ 176, 0, 176, 112 }, { 192, 0, 192, 112 }, { 208, 0, 208, 112 }, { 224, 0, 224, 112 }, { 240, 0, 240, 112 }, 
	{ 256, 0, 256, 112 }, { 272, 0, 272, 112 }, { 288, 0, 288, 112 }, { 304, 0, 304, 112 }, { 320, 0, 320, 112 }, 
	{ 336, 0, 336, 112 }, { 352, 0, 352, 112 }, { 368, 0, 368, 112 }, { 384, 0, 384, 112 }, { 400, 0, 400, 112 }, 
	{ 416, 0, 416, 112 }, { 432, 0, 432, 112 }, { 448, 0, 448, 112 }, { 464, 0, 464, 112 }, { 480, 0, 480, 112 }, 
	{ 496, 0, 496, 112 }, { 512, 0, 512, 112 }, { 528, 0, 528, 112 }, { 544, 0, 544, 112 }, { 560, 0, 560, 112 }, 
	{ 576, 0, 576, 112 }, { 592, 0, 592, 112 }, { 608, 0, 608, 112 }, { 624, 0, 624, 112 }, { 640, 0, 640, 112 }, 
	{ 656, 0, 656, 112 }, { 672, 0, 672, 112 }, { 688, 0, 688, 112 }, { 704, 0, 704, 112 }, { 720, 0, 720, 112 }, 
	{ 736, 0, 736, 112 }, { 752, 0, 752, 112 }, { 768, 0, 768, 112 }, { 784, 0, 784, 112 }, { 800, 0, 800, 112 }, 
	{ 816, 0, 816, 112 }, { 832, 0, 832, 112 }, { 848, 0, 848, 112 }, { 864, 0, 864, 112 }, { 880, 0, 880, 112 }, 
	{ 896, 0, 896, 112 }, { 912, 0, 912, 112 }, { 928, 0, 928, 112 }, { 944, 0, 944, 112 }, { 960, 0, 960, 112 }, 
	{ 976, 0, 976, 112 }, { 992, 0, 992, 112 }, { 1008, 0, 1008, 112 }, { 1024, 0, 1024, 112 }, { 1040, 0, 1040, 112 }, 
	{ 1056, 0, 1056, 112 }, { 1072, 0, 1072, 112 }, { 1088, 0, 1088, 112 }, { 1104, 0, 1104, 112 }, { 1120, 0, 1120, 112 }, 
	{ 1136, 0, 1136, 112 }, { 1152, 0, 1152, 112 }, { 1168, 0, 1168, 112 }, { 1184, 0, 1184, 112 }, { 1200, 0, 1200, 112 }, 
	{ 1216, 0, 1216, 112 }, { 1232, 0, 1232, 112 }, { 1248, 0, 1248, 112 }, { 1264, 0, 1264, 112 }, { 1280, 0, 1280, 112 }, 
	{ 1296, 0, 1296, 112 }, { 1312, 0, 1312, 112 }, { 1328, 0, 1328, 112 }, { 1344, 0, 1344, 112 }, { 1360, 0, 1360, 112 }, 
	{ 1376, 0, 1376, 112 }, { 1392, 0, 1392, 112 }, { 1408, 0, 1408, 112 }, { 1424, 0, 1424, 112 }, { 1440, 0, 1440, 112 }, 
	{ 1456, 0, 1456, 112 }, { 1472, 0, 1472, 112 }, { 1488, 0, 1488, 112 }, { 1504, 0, 1504, 112 }, { 1520, 0, 1520, 112 }, 
	{ 1536, 0, 1536, 112 }, { 1552, 0, 1552, 112 }, { 1568, 0, 1568, 112 }, { 1584, 0, 1584, 112 }, { 1600, 0, 1600, 112 }, 
	{ 1616, 0, 1616, 112 }, { 1632, 0, 1632, 112 }, { 1648, 0, 1648, 112 }, { 1664, 0, 1664, 112 }, { 1680, 0, 1680, 112 }, 
	{ 1696, 0, 1696, 112 }, { 1712, 0, 1712, 112 }, { 1728, 0, 1728, 112 }, { 1744, 0, 1744, 112 }, { 1760, 0, 1760, 112 }, 
	{ 1776, 0, 1776, 112 }, { 1792, 0, 1792, 112 }, { 1808, 0, 1808, 112 }, { 1824, 0, 1824, 112 }, { 1840, 0, 1840, 112 }, 
	{ 1856, 0, 1856, 112 }, { 1872, 0, 1872, 112 }, { 1888, 0, 1888, 112 }, { 1904, 0, 1904, 112 }, { 1920, 0, 1920, 112 }, 
	{ 1936, 0, 1936, 112 }, { 1952, 0, 1952, 112 }, { 1968, 0, 1968, 112 }, { 1984, 0, 1984, 112 }, { 2000, 0, 2000, 112 }, 
	{ 2016, 0, 2016, 112 }, { 2032, 0, 2032, 112 }, { 2048, 0, 2048, 112 }, { 2064, 0, 2064, 112 }, { 2080, 0, 2080, 112 }, 
	{ 2096, 0, 2096, 112 }, { 2112, 0, 2112, 112 }, { 2128, 0, 2128, 112 }, { 2144, 0, 2144, 112 }, { 2160, 0, 2160, 112 }, 
	{ 2176, 0, 2176, 112 }, { 2192, 0, 2192, 112 }, { 2208, 0, 2208, 112 }, { 2224, 0, 2224, 112 }, { 2240, 0, 2240, 112 }, 
	{ 2256, 0, 2256, 112 }, { 2272, 0, 2272, 112 }, { 2288, 0, 2288, 112 }, { 2304, 0, 2304, 112 }, { 2320, 0, 2320, 112 }, 
	{ 2336, 0, 2336, 112 }, { 2352, 0, 2352, 112 }, { 2368, 0, 2368, 112 }, { 2384, 0, 2384, 112 }, { 2400, 0, 2400, 112 }, 
	{ 2416, 0, 2416, 112 }, { 2432, 0, 2432, 112 }, { 2448, 0, 2448, 112 }, { 2464, 0, 2464, 112 }, { 2480, 0, 2480, 112 }, 
	{ 2496, 0, 2496, 112 }, { 2512, 0, 2512, 112 }, { 2528, 0, 2528, 112 }, { 2544, 0, 2544, 112 }, { 2560, 0, 2560, 112 }, 
	{ 2576, 0, 2576, 112 }, { 2592, 0, 2592, 112 }, { 2608, 0, 2608, 112 }, { 2624, 0, 2624, 112 }, { 2640, 0, 2640, 112 }, 
	{ 2656, 0, 2656, 112 }, { 2672, 0, 2672, 112 }, { 2688, 0, 2688, 112 }, { 2704, 0, 2704, 112 }, { 2720, 0, 2720, 112 }, 
	{ 2736, 0, 2736, 112 }, { 2752, 0, 2752, 112 }, { 2768, 0, 2768, 112 }, { 2784, 0, 2784, 112 }, { 2800, 0, 2800, 112 }, 
	{ 2816, 0, 2816, 112 }, { 2832, 0, 2832, 112 }, { 2848, 0, 2848, 112 }, { 2864, 0, 2864, 112 }, { 2880, 0, 2880, 112 }, 
	{ 2896, 0, 2896, 112 }, { 2912, 0, 2912, 112 }, { 2928, 0, 2928, 112 }, { 2944, 0, 2944, 112 }, { 2960, 0, 2960, 112 }, 
	{ 2976, 0, 2976, 112 }, { 2992, 0, 2992, 112 }, { 3008, 0, 3008, 112 }, { 3024, 0, 3024, 112 }, { 3040, 0, 3040, 112 }, 
	{ 3056, 0, 3056, 112 }, { 3072, 0, 3072, 112 }, { 3088, 0, 3088, 112 }, { 3104, 0, 3104, 112 }, { 3120, 0, 3120, 112 }, 
	{ 3136, 0, 3136, 112 }, { 3152, 0, 3152, 112 }, { 3168, 0, 3168, 112 }, { 3184, 0, 3184, 112 }, { 3200, 0, 3200, 112 }, 
	{ 3216, 0, 3216, 112 }, { 3232, 0, 3232, 112 }, { 3248, 0, 3248, 112 }, { 3264, 0, 3264, 112 }, { 3280, 0, 3280, 112 }, 
	{ 3296, 0, 3296, 112 }, { 3312, 0, 3312, 112 }, { 3328, 0, 3328, 112 }, { 3344, 0, 3344, 112 }, { 3360, 0, 3360, 112 }, 
	{ 3376, 0, 3376, 112 }, { 3392, 0, 3392, 112 }, { 3408, 0, 3408, 112 }, { 3424, 0, 3424, 112 }, { 3440, 0, 3440, 112 }, 
	{ 3456, 0, 3456, 112 }, { 3472, 0, 3472, 112 }, { 3488, 0, 3488, 112 }, { 3504, 0, 3504, 112 }, { 3520, 0, 3520, 112 }, 
	{ 3536, 0, 3536, 112 }, { 3552, 0, 3552, 112 }, { 3568, 0, 3568, 112 }, { 3584, 0, 3584, 112 }, { 3600, 0, 3600, 112 }, 
	{ 3616, 0, 3616, 112 }, { 3632, 0, 3632, 112 }, { 3648, 0, 3648, 112 }, { 3664, 0, 3664, 112 }, { 3680, 0, 3680, 112 }, 
	{ 3696, 0, 3696, 112 }, { 3712, 0, 3712, 112 }, { 3728, 0, 3728, 112 }, { 3744, 0, 3744, 112 }, { 3760, 0, 3760, 112 }, 
	{ 3776, 0, 3776, 112 }, { 3792, 0, 3792, 112 }, { 3808, 0, 3808, 112 }, { 3824, 0, 3824, 112 }, { 3840, 0, 3840, 112 }, 
	{ 3856, 0, 3856, 112 }, { 3872, 0, 3872, 112 }, { 3888, 0, 3888, 112 }, { 3904, 0, 3904, 112 }, { 3920, 0, 3920, 112 }, 
	{ 3936, 0, 3936, 112 }, { 3952, 0, 3952, 112 }, { 3968, 0, 3968, 112 }, { 3984, 0, 3984, 112 }, { 4000, 0, 4000, 112 }, 
	{ 4016, 0, 4016, 112 }, { 4032, 0, 4032, 112 }, { 4048, 0, 4048, 112 }, { 4064, 0, 4064, 112 }, { 4080, 0, 4080, 112 }, 
	{ 4096, 0, 4096, 112 }, { 4112, 0, 4112, 112 }, { 4128, 0, 4128, 112 }, { 4144, 0, 4144, 112 }, { 4160, 0, 4160, 112 }, 
	{ 4176, 0, 4176, 112 }, { 4192, 0, 4192, 112 }, { 4208, 0, 4208, 112 }, { 4224, 0, 4224, 112 }, { 4240, 0, 4240, 112 }, 
	{ 4256, 0, 4256, 112 }, { 4272, 0, 4272, 112 }, { 4288, 0, 4288, 112 }, { 4304, 0, 4304, 112 }, { 4320, 0, 4320, 112 }, 
	{ 4336, 0, 4336, 112 }, { 4352, 0, 4352, 112 }, { 4368, 0, 4368, 112 }, { 4384, 0, 4384, 112 }, { 4400, 0, 4400, 112 }, 
	{ 4416, 0, 4416, 112 }, { 4432, 0, 4432, 112 }, { 4448, 0, 4448, 112 }, { 4464, 0, 4464, 112 }, { 4480, 0, 4480, 112 }, 
	{ 4496, 0, 4496, 112 }, { 4512, 0, 4512, 112 }, { 4528, 0, 4528, 112 }, { 4544, 0, 4544, 112 }, { 4560, 0, 4560, 112 }, 
	{ 4576, 0, 4576, 112 }, { 4592, 0, 4592, 112 }, { 4608, 0, 4608, 112 }, { 4624, 0, 4624, 112 }, { 4640, 0, 4640, 112 }, 
	{ 4656, 0, 4656, 112 }, { 4672, 0, 4672, 112 }, { 4688, 0, 4688, 112 }, { 4704, 0, 4704, 112 }, { 4720, 0, 4720, 112 }, 
	{ 4736, 0, 4736, 112 }, { 4752, 0, 4752, 112 }, { 4768, 0, 4768, 112 }, { 4784, 0, 4784, 112 }, { 4800, 0, 4800, 112 }, 
	{ 4816, 0, 4816, 112 }, { 4832, 0, 4832, 112 }, { 4848, 0, 4848, 112 }, { 4864, 0, 4864, 112 }, { 4880, 0, 4880, 112 }, 
	{ 4896, 0, 4896, 112 }, { 4912, 0, 4912, 112 }, { 4928, 0, 4928, 112 }, { 4944, 0, 4944, 112 }, { 4960, 0, 4960, 112 }, 
	{ 4976, 0, 4976, 112 }, { 4992, 0, 4992, 112 }, { 5008, 0, 5008, 112 }, { 5024, 0, 5024, 112 }, { 5040, 0, 5040, 112 }, 
	{ 5056, 0, 5056, 112 }, { 5072, 0, 5072, 112 }, { 5088, 0, 5088, 112 }, { 5104, 0, 5104, 112 }, { 5120, 0, 5120, 112 }, 
	{ 5136, 0, 5136, 112 }, { 5152, 0, 5152, 112 }, { 5168, 0, 5168, 112 }, { 5184, 0, 5184, 112 }, { 5200, 0, 5200, 112 }, 
	{ 5216, 0, 5216, 112 }, { 5232, 0, 5232, 112 }, { 5248, 0, 5248, 112 }, { 5264, 0, 5264, 112 }, { 5280, 0, 5280, 112 }, 
	{ 5296, 0, 5296, 112 }, { 5312, 0, 5312, 112 }, { 5328, 0, 5328, 112 }, { 5344, 0, 5344, 112 }, { 5360, 0, 5360, 112 }, 
	{ 5376, 0, 5376, 112 }, { 5392, 0, 5392, 112 }, { 5408, 0, 5408, 112 }, { 5424, 0, 5424, 112 }, { 5440, 0, 5440, 112 }, 
	{ 5456, 0, 5456, 112 }, { 5472, 0, 5472, 112 }, { 5488, 0, 5488, 112 }, { 5504, 0, 5504, 112 }, { 5520, 0, 5520, 112 }, 
	{ 5536, 0, 5536, 112 }, { 5552, 0, 5552, 112 }, { 5568, 0, 5568, 112 }, { 5584, 0, 5584, 112 }, { 5600, 0, 5600, 112 }, 
	{ 5616, 0, 5616, 112 }, { 5632, 0, 5632, 112 }, { 5648, 0, 5648, 112 }, { 5664, 0, 5664, 112 }, { 5680, 0, 5680, 112 }, 
	{ 5696, 0, 5696, 112 }, { 5712, 0, 5712, 112 }, { 5728, 0, 5728, 112 }, { 5744, 0, 5744, 112 }, { 5760, 0, 5760, 112 }, 
	{ 5776, 0, 5776, 112 }, { 5792, 0, 5792, 112 }, { 5808, 0, 5808, 112 }, { 5824, 0, 5824, 112 }, { 5840, 0, 5840, 112 }, 
	{ 5856, 0, 5856, 112 }, { 5872, 0, 5872, 112 }, { 5888, 0, 5888, 112 }, { 5904, 0, 5904, 112 }, { 5920, 0, 5920, 112 }, 
	{ 5936, 0, 5936, 112 }, { 5952, 0, 5952, 112 }, { 5968, 0, 5968, 112 }, { 5984, 0, 5984, 112 }, { 6000, 0, 6000, 112 }, 
	{ 6016, 0, 6016, 112 }, { 6032, 0, 6032, 112 }, { 6048, 0, 6048, 112 }, { 6064, 0, 6064, 112 }, { 6080, 0, 6080, 112 }, 
	{ 6096, 0, 6096, 112 }, { 6112, 0, 6112, 112 }, { 6128, 0, 6128, 112 }, { 6144, 0, 6144, 112 }, { 6160, 0, 6160, 112 }, 
	{ 6176, 0, 6176, 112 }, { 6192, 0, 6192, 112 }, { 6208, 0, 6208, 112 }, { 6224, 0, 6224, 112 }, { 6240, 0, 6240, 112 }, 
	{ 6256, 0, 6256, 112 }, { 6272, 0, 6272, 112 }, { 6288, 0, 6288, 112 }, { 6304, 0, 6304, 112 }, { 6320, 0, 6320, 112 }, 
	{ 6336, 0, 6336, 112 }, { 6352, 0, 6352, 112 }, { 6368, 0, 6368, 112 }, { 6384, 0, 6384, 112 }, { 6400, 0, 6400, 112 }, 
	{ 6416, 0, 6416, 112 }, { 6432, 0, 6432, 112 }, { 6448, 0, 6448, 112 }, { 6464, 0, 6464, 112 }, { 6480, 0, 6480, 112 }, 
	{ 6496, 0, 6496, 112 }, { 6512, 0, 6512, 112 }, { 6528, 0, 6528, 112 }, { 6544, 0, 6544, 112 }, { 6560, 0, 6560, 112 }, 
	{ 6576, 0, 6576, 112 }, { 6592, 0, 6592, 112 }, { 6608, 0, 6608, 112 }, { 6624, 0, 6624, 112 }, { 6640, 0, 6640, 112 }, 
	{ 6656, 0, 6656, 112 }, { 6672, 0, 6672, 112 }, { 6688, 0, 6688, 112 }, { 6704, 0, 6704, 112 }, { 6720, 0, 6720, 112 }, 
	{ 6736, 0, 6736, 112 }, { 6752, 0, 6752, 112 }, { 6768, 0, 6768, 112 }, { 6784, 0, 6784, 112 }, { 6800, 0, 6800, 112 }, 
	{ 6816, 0, 6816, 112 }, { 6832, 0, 6832, 112 }, { 6848, 0, 6848, 112 }, { 6864, 0, 6864, 112 }, { 6880, 0, 6880, 112 }, 
	{ 6896, 0, 6896, 112 }, { 6912, 0, 6912, 112 }, { 6928, 0, 6928, 112 }, { 6944, 0, 6944, 112 }, { 6960, 0, 6960, 112 }, 
	{ 6976, 0, 6976, 112 }, { 6992, 0, 6992, 112 }, { 7008, 0, 7008, 112 }, { 7024, 0, 7024, 112 }, { 7040, 0, 7040, 112 }, 
	{ 7056, 0, 7056, 112 }, { 7072, 0, 7072, 112 }, { 7088, 0, 7088, 112 }, { 7104, 0, 7104, 112 }, { 7120, 0, 7120, 112 }, 
	{ 7136, 0, 7136, 112 }, { 7152, 0, 7152, 112 }, { 7168, 0, 7168, 112 }, { 7184, 0, 7184, 112 }, { 7200, 0, 7200, 112 }, 
	{ 7216, 0, 7216, 112 }, { 7232, 0, 7232, 112 }, { 7248, 0, 7248, 112 }, { 7264, 0, 7264, 112 }, { 7280, 0, 7280, 112 }, 
	{ 7296, 0, 7296, 112 }, { 7312, 0, 7312, 112 }, { 7328, 0, 7328, 112 }, { 7344, 0, 7344, 112 }, { 7360, 0, 7360, 112 }, 
	{ 7376, 0, 7376, 112 }, { 7392, 0, 7392, 112 }, { 7408, 0, 7408, 112 }, { 7424, 0, 7424, 112 }, { 7440, 0, 7440, 112 }, 
	{ 7456, 0, 7456, 112 }, { 7472, 0, 7472, 112 }, { 7488, 0, 7488, 112 }, { 7504, 0, 7504, 112 }, { 7520, 0, 7520, 112 }, 
	{ 7536, 0, 7536, 112 }, { 7552, 0, 7552, 112 }, { 7568, 0, 7568, 112 }, { 7584, 0, 7584, 112 }, { 7600, 0, 7600, 112 }, 
	{ 7616, 0, 7616, 112 }, { 7632, 0, 7632, 112 }, { 7648, 0, 7648, 112 }, { 7664, 0, 7664, 112 }, { 7680, 0, 7680, 112 }, 
	{ 7696, 0, 7696, 112 }, { 7712, 0, 7712, 112 }, { 7728, 0, 7728, 112 }, { 7744, 0, 7744, 112 }, { 7760, 0, 7760, 112 }, 
	{ 7776, 0, 7776, 112 }, { 7792, 0, 7792, 112 }, { 7808, 0, 7808, 112 }, { 7824, 0, 7824, 112 }, { 7840, 0, 7840, 112 }, 
	{ 7856, 0, 7856, 112 }, { 7872, 0, 7872, 112 }, { 7888, 0, 7888, 112 }, { 7904, 0, 7904, 112 }, { 7920, 0, 7920, 112 }, 
	{ 7936, 0, 7936, 112 }, { 7952, 0, 7952, 112 }, { 7968, 0, 7968, 112 }, { 7984, 0, 7984, 112 }, { 8000, 0, 8000, 112 }, 
	{ 8016, 0, 8016, 112 }, { 8032, 0, 8032, 112 }, { 8048, 0, 8048, 112 }, { 8064, 0, 8064, 112 }, { 8080, 0, 8080, 112 }, 
	{ 8096, 0, 8096, 112 }, { 8112, 0, 8112, 112 }, { 8128, 0, 8128, 112 }, { 8144, 0, 8144, 112 }, { 8160, 0, 8160, 112 }, 
	{ 8176, 0, 8176, 112 }, { 8192, 0, 8192, 112 }, { 8208, 0, 8208, 112 }, { 8224, 0, 8224, 112 }, { 8240, 0, 8240, 112 }, 
	{ 8256, 0, 8256, 112 }, { 8272, 0, 8272, 112 }, { 8288, 0, 8288, 112 }, { 8304, 0, 8304, 112 }, { 8320, 0, 8320, 112 }, 
	{ 8336, 0, 8336, 112 }, { 8352, 0, 8352, 112 }, { 8368, 0, 8368, 112 }, { 8384, 0, 8384, 112 }, { 8400, 0, 8400, 112 }, 
	{ 8416, 0, 8416, 112 }, { 8432, 0, 8432, 112 }, { 8448, 0, 8448, 112 }, { 8464, 0, 8464, 112 }, { 8480, 0, 8480, 112 }, 
	{ 8496, 0, 8496, 112 }, { 8512, 0, 8512, 112 }, { 8528, 0, 8528, 112 }, { 8544, 0, 8544, 112 }, { 8560, 0, 8560, 112 }, 
	{ 8576, 0, 8576, 112 }, { 8592, 0, 8592, 112 }, { 8608, 0, 8608, 112 }, { 8624, 0, 8624, 112 }, { 8640, 0, 8640, 112 }, 
	{ 8656, 0, 8656, 112 }, { 8672, 0, 8672, 112 }, { 8688, 0, 8688, 112 }, { 8704, 0, 8704, 112 }, { 8720, 0, 8720, 112 }, 
	{ 8736, 0, 8736, 112 }, { 8752, 0, 8752, 112 }, { 8768, 0, 8768, 112 }, { 8784, 0, 8784, 112 }, { 8800, 0, 8800, 112 }, 
	{ 8816, 0, 8816, 112 }, { 8832, 0, 8832, 112 }, { 8848, 0, 8848, 112 }, { 8864, 0, 8864, 112 }, { 8880, 0, 8880, 112 }, 
	{ 8896, 0, 8896, 112 }, { 8912, 0, 8912, 112 }, { 8928, 0, 8928, 112 }, { 8944, 0, 8944, 112 }, { 8960, 0, 8960, 112 }, 
	{ 8976, 0, 8976, 112 }, { 8992, 0, 8992, 112 }, { 9008, 0, 9008, 112 }, { 9024, 0, 9024, 112 }, { 9040, 0, 9040, 112 }, 
	{ 9056, 0, 9056, 112 }, { 9072, 0, 9072, 112 }, { 9088, 0, 9088, 112 }, { 9104, 0, 9104, 112 }, { 9120, 0, 9120, 112 }, 
	{ 9136, 0, 9136, 112 }, { 9152, 0, 9152, 112 }, { 9168, 0, 9168, 112 }, { 9184, 0, 9184, 112 }, { 9200, 0, 9200, 112 }, 
	{ 9216, 0, 9216, 112 }, { 9232, 0, 9232, 112 }, { 9248, 0, 9248, 112 }, { 9264, 0, 9264, 112 }, { 9280, 0, 9280, 112 }, 
	{ 9296, 0, 9296, 112 }, { 9312, 0, 9312, 112 }, { 9328, 0, 9328, 112 }, { 9344, 0, 9344, 112 }, { 9360, 0, 9360, 112 }, 
	{ 9376, 0, 9376, 112 }, { 9392, 0, 9392, 112 }, { 9408, 0, 9408, 112 }, { 9424, 0, 9424, 112 }, { 9440, 0, 9440, 112 }, 
	{ 9456, 0, 9456, 112 }, { 9472, 0, 9472, 112 }, { 9488, 0, 9488, 112 }, { 9504, 0, 9504, 112 }, { 9520, 0, 9520, 112 }, 
	{ 9536, 0, 9536, 112 }, { 9552, 0, 9552, 112 }, { 9568, 0, 9568, 112 }, { 9584, 0, 9584, 112 }, { 9600, 0, 9600, 112 }, 
	{ 9616, 0, 9616, 112 }, { 9632, 0, 9632, 112 }, { 9648, 0, 9648, 112 }, { 9664, 0, 9664, 112 }, { 9680, 0, 9680, 112 }, 
	{ 9696, 0, 9696, 112 }, { 9712, 0, 9712, 112 }, { 9728, 0, 9728, 112 }, { 9744, 0, 9744, 112 }, { 9760, 0, 9760, 112 }, 
	{ 9776, 0, 9776, 112 }, { 9792, 0, 9792, 112 }, { 9808, 0, 9808, 112 }, { 9824, 0, 9824, 112 }, { 9840, 0, 9840, 112 }, 
	{ 9856, 0, 9856, 112 }, { 9872, 0, 9872, 112 }, { 9888, 0, 9888, 112 }, { 9904, 0, 9904, 112 }, { 9920, 0, 9920, 112 }, 
	{ 9936, 0, 9936, 112 }, { 9952, 0, 9952, 112 }, { 9968, 0, 9968, 112 }, { 9984, 0, 9984, 112 }, { 10000, 0, 10000, 112 }, 
	{ 10016, 0, 10016, 112 }, { 10032, 0, 10032, 112 }, { 10048, 0, 10048, 112 }, { 10064, 0, 10064, 112 }, { 10080, 0, 10080, 112 }, 
	{ 10096, 0, 10096, 112 }, { 10112, 0, 10112, 112 }, { 10128, 0, 10128, 112 }, { 10144, 0, 10144, 112 }, { 10160, 0, 10160, 112 }, 
	{ 10176, 0, 10176, 112 }, { 10192, 0, 10192, 112 }, { 10208, 0, 10208, 112 }, { 10224, 0, 10224, 112 }, { 10240, 0, 10240, 112 }, 
	{ 10256, 0, 10256, 112 }, { 10272, 0, 10272, 112 }, { 10288, 0, 10288, 112 }, { 10304, 0, 10304, 112 }, { 10320, 0, 10320, 112 }, 
	{ 10336, 0, 10336, 112 }, { 10352, 0, 10352, 112 }, { 10368, 0, 10368, 112 }, { 10384, 0, 10384, 112 }, { 10400, 0, 10400, 112 }, 
	{ 10416, 0, 10416, 112 }, { 10432, 0, 10432, 112 }, { 10448, 0, 10448, 112 }, { 10464, 0, 10464, 112 }, { 10480, 0, 10480, 112 }, 
	{ 10496, 0, 10496, 112 }, { 10512, 0, 10512, 112 }, { 10528, 0, 10528, 112 }, { 10544, 0, 10544, 112 }, { 10560, 0, 10560, 112 }, 
	{ 10576, 0, 10576, 112 }, { 10592, 0, 10592, 112 }, { 10608, 0, 10608, 112 }, { 10624, 0, 10624, 112 }, { 10640, 0, 10640, 112 }, 
	{ 10656, 0, 10656, 112 }, { 10672, 0, 10672, 112 }, { 10688, 0, 10688, 112 }, { 10704, 0, 10704, 112 }, { 10720, 0, 10720, 112 }, 
	{ 10736, 0, 10736, 112 }, { 10752, 0, 10752, 112 }, { 10768, 0, 10768, 112 }, { 10784, 0, 10784, 112 }, { 10800, 0, 10800, 112 }, 
	{ 10816, 0, 10816, 112 }, { 10832, 0, 10832, 112 }, { 10848, 0, 10848, 112 }, { 10864, 0, 10864, 112 }, { 10880, 0, 10880, 112 }, 
	{ 10896, 0, 10896, 112 }, { 10912, 0, 10912, 112 }, { 10928, 0, 10928, 112 }, { 10944, 0, 10944, 112 }, { 10960, 0, 10960, 112 }, 
	{ 10976, 0, 10976, 112 }, { 10992, 0, 10992, 112 }, { 11008, 0, 11008, 112 }, { 11024, 0, 11024, 112 }, { 11040, 0, 11040, 112 }, 
	{ 11056, 0, 11056, 112 }, { 11072, 0, 11072, 112 }, { 11088, 0, 11088, 112 }, { 11104, 0, 11104, 112 }, { 11120, 0, 11120, 112 }, 
	{ 11136, 0, 11136, 112 }, { 11152, 0, 11152, 112 }, { 11168, 0, 11168, 112 }, { 11184, 0, 11184, 112 }, { 0, 0, 0, 112 },
	
	/* Y Axis */
	{ 0, 0, 11200, 0 }, { 0, 16, 11200, 16 }, { 0, 32, 11200, 32 }, { 0, 48, 11200, 48 }, { 0, 64, 11200, 64 }, { 0, 80, 11200, 80 }, 
	{ 0, 96, 11200, 96 }
};
#define N_GRID_SEGMENTS 707

/*
 * This could be a macro, but it's always better to err on the side of caution...
 */
static gboolean bitmap_is_pixel_set(bitmap_editor_t *ed, unsigned int x, unsigned int y) {
	if (!ed || !ed->bitmap || !*ed->bitmap || x > 699 || y > 6 || x > ed->length) return FALSE;
	return (*(*ed->bitmap+x) & (0x40 >> y)) ? TRUE : FALSE;
}

/**
 * This sets a pixel in the bitmap, and small image. 
 */
static void bitmap_set_pixel(bitmap_editor_t *ed, unsigned int x, unsigned int y) {
	if (!ed || !ed->bitmap || !*ed->bitmap || x > 699 || y > 6) return;

	/* Expand as needed */
	if (x > ed->length) {
		*ed->bitmap = realloc(*ed->bitmap,x+1);
		memset(*ed->bitmap+ed->length+1,0,x-ed->length+1);
		ed->length = x+1;
	} 

	/* Set the pixel in the bitmap */
	*(*ed->bitmap+x) = (*(*ed->bitmap+x) & ~(0x40 >> y)) | (0x40 >> y);

	/* Now, update the pixmap ... */
	gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap),ed->gc,TRUE,(x*16),(y*16),16,16);
	if (x < 68) gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap_small),ed->gc_small,TRUE,(x*3),(y*3),3,3);

	/* Draw the grid */
	gdk_gc_set_rgb_fg_color(ed->gc,&grid_color);
	gdk_draw_segments(GDK_DRAWABLE(ed->pixmap),ed->gc,(GdkSegment *)grid_segments,N_GRID_SEGMENTS);
	gdk_gc_set_rgb_fg_color(ed->gc,&fg_color);

	/* ... and redraw the GtkImage. */
	gtk_widget_queue_draw(ed->image);
	gtk_widget_queue_draw(ed->image_small);
}

/**
 * This un-sets a pixel in the bitmap, and small image. 
 */
static void bitmap_unset_pixel(bitmap_editor_t *ed, unsigned int x, unsigned int y) {
	if (!ed || !ed->bitmap || !*ed->bitmap || x > 699 || y > 6) return;
	if (x > ed->length) return;

	/* Un-set the pixel in the bitmap */
	*(*ed->bitmap+x) = (*(*ed->bitmap+x) & ~(0x40 >> y));

	/* If the column is clear, see if we can contract the bitmap */
	if (*(*ed->bitmap+x) == 0) {
		if (x == ed->length && x > 1) {
			*ed->bitmap = realloc(*ed->bitmap,x);
			ed->length--;
		} 
	} 

	/* Now, update the pixmap ... */
	gdk_gc_set_rgb_fg_color(ed->gc,&bg_color); gdk_gc_set_rgb_fg_color(ed->gc_small,&bg_color);
	gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap),ed->gc,TRUE,(x*16),(y*16),16,16);
	if (x < 68) gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap_small),ed->gc_small,TRUE,(x*3),(y*3),3,3);
	gdk_gc_set_rgb_fg_color(ed->gc,&fg_color); gdk_gc_set_rgb_fg_color(ed->gc_small,&fg_color);

	/* Draw the grid */
	gdk_gc_set_rgb_fg_color(ed->gc,&grid_color);
	gdk_draw_segments(GDK_DRAWABLE(ed->pixmap),ed->gc,(GdkSegment *)grid_segments,N_GRID_SEGMENTS);
	gdk_gc_set_rgb_fg_color(ed->gc,&fg_color);

	/* ... and redraw the GtkImage. */
	gtk_widget_queue_draw(ed->image);
	gtk_widget_queue_draw(ed->image_small);
}

/**
 * This handles a click inside the event box (on the image.) 
 */
static gboolean image_clicked(GtkWidget *evbox, GdkEventButton *event, gpointer data) {
	bitmap_editor_t *ed = (bitmap_editor_t *)data;

	if (event->button == 1) { /* left */
		if (!bitmap_is_pixel_set(ed,event->x/16,event->y/16)) bitmap_set_pixel(ed,event->x/16,event->y/16);
		else bitmap_unset_pixel(ed,event->x/16,event->y/16);
	} else { /* right, middle, etc. */
		/* Popup menu with an option to clear the bitmap. */ 
		gtk_widget_show_all(ed->popup);
		gtk_menu_popup(GTK_MENU(ed->popup),NULL,NULL,NULL,NULL,event->button,event->time);
	}

	return TRUE; /* stop propogating the event */
}

/**
 * This handles a click inside the event box (on the small image.) 
 */
static gboolean small_image_clicked(GtkWidget *evbox, GdkEventButton *event, gpointer data) {
	gint resp;
	bitmap_editor_t *ed = (bitmap_editor_t *)data;

	if (event->button == 1) {
		gtk_widget_show_all(ed->dialog);
		resp = gtk_dialog_run(GTK_DIALOG(ed->dialog));
		gtk_widget_hide(ed->dialog);
	}

	return TRUE; /* stop propogating the event */
}

/**
 * This handles a click on the popup menu item. 
 */
static gboolean clear_clicked(GtkMenuItem *item, gpointer data) {
	bitmap_editor_t *ed = (bitmap_editor_t *)data;

	/* Reallocate the bitmap memory area */
	*ed->bitmap = realloc(*ed->bitmap,1);
	ed->length  = 0;

	/* Clear the images */
	gdk_gc_set_rgb_fg_color(ed->gc,&bg_color); gdk_gc_set_rgb_fg_color(ed->gc_small,&bg_color); 
	gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap),ed->gc,TRUE,0,0,700*16,7*16);
	gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap_small),ed->gc_small,TRUE,0,0,68*3,7*3);

	/* Draw the grid */
	gdk_gc_set_rgb_fg_color(ed->gc,&grid_color);
	gdk_draw_segments(GDK_DRAWABLE(ed->pixmap),ed->gc,(GdkSegment *)grid_segments,N_GRID_SEGMENTS);
	gdk_gc_set_rgb_fg_color(ed->gc,&fg_color);

	/* ... and redraw the GtkImage. */
	gtk_widget_queue_draw(ed->image);
	gtk_widget_queue_draw(ed->image_small);
	return TRUE;
}

bitmap_editor_t *bitmap_editor_new(unsigned char **bmp, unsigned short ncols) {
	bitmap_editor_t *ed; GdkGC *gc; GtkWidget *wid, *item; unsigned short x; int y;

	if (!(ed = g_new0(bitmap_editor_t,1))) return NULL;
	if (bmp) {
		ed->length = ncols;
		ed->bitmap = bmp;
	}

	/* Create the GtkEventBoxes */
	ed->evbox       = gtk_event_box_new();
	ed->evbox_small = gtk_event_box_new();

	/* Create the GdkPixmaps */
	ed->pixmap       = gdk_pixmap_new(GDK_DRAWABLE(gtk_widget_get_root_window(window)),700*16,7*16,
	                                  gdk_drawable_get_depth(GDK_DRAWABLE(gtk_widget_get_root_window(window))));
	ed->pixmap_small = gdk_pixmap_new(GDK_DRAWABLE(gtk_widget_get_root_window(window)),68*3,7*3,
	                                  gdk_drawable_get_depth(GDK_DRAWABLE(gtk_widget_get_root_window(window))));

	/* Create the GtkImages */
	ed->image       = gtk_image_new_from_pixmap(ed->pixmap,NULL);
	ed->image_small = gtk_image_new_from_pixmap(ed->pixmap_small,NULL);
	gtk_container_add(GTK_CONTAINER(ed->evbox_small),ed->image_small);
	
	/* Setup events for the event boxes */
	g_signal_connect(G_OBJECT(ed->evbox),"button_press_event",G_CALLBACK(image_clicked),ed);
	g_signal_connect(G_OBJECT(ed->evbox_small),"button_press_event",G_CALLBACK(small_image_clicked),ed);

	/* Create the Bitmap Editor dialog (gtk_dialog_get_content_area() requires Gtk+ >= 2.14) */
	ed->dialog = gtk_dialog_new_with_buttons(_("Bitmap Editor"),GTK_WINDOW(window),GTK_DIALOG_NO_SEPARATOR,
	                                         GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,NULL);
	wid        = gtk_dialog_get_content_area(GTK_DIALOG(ed->dialog));
	ed->scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_misc_set_alignment(GTK_MISC(ed->image),0,0);
	gtk_misc_set_padding(GTK_MISC(ed->image),0,0);
	gtk_container_add(GTK_CONTAINER(ed->evbox),ed->image);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(ed->scroll),ed->evbox);
	gtk_container_add(GTK_CONTAINER(wid),ed->scroll);
	gtk_widget_set_size_request(ed->image_small,68*3,7*3);
	gtk_widget_set_size_request(ed->evbox_small,68*3,7*3);
	gtk_widget_set_size_request(ed->image,700*16,7*16);
	gtk_widget_set_size_request(ed->evbox,700*16,7*16);
	gtk_widget_set_size_request(wid,597,180);

	/* Set up the popup menu */
	ed->popup  = gtk_menu_new();
	item       = gtk_menu_item_new_with_label(_("Clear Bitmap"));
	gtk_menu_shell_append(GTK_MENU_SHELL(ed->popup),item);
	g_signal_connect(G_OBJECT(item),"activate",G_CALLBACK(clear_clicked),ed);
	
	/* Allocate the pixmaps */
	ed->gc       = gdk_gc_new(GDK_DRAWABLE(ed->pixmap));
	ed->gc_small = gdk_gc_new(GDK_DRAWABLE(ed->pixmap_small));

	/* Fill with the background color */
	gdk_gc_set_rgb_fg_color(ed->gc,&bg_color); gdk_gc_set_rgb_fg_color(ed->gc_small,&bg_color); 
	gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap),ed->gc,TRUE,0,0,700*16,7*16);
	gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap_small),ed->gc_small,TRUE,0,0,68*3,7*3);

	/* Establish the foreground and background colors */
	gdk_gc_set_rgb_bg_color(ed->gc,&bg_color);       gdk_gc_set_rgb_fg_color(ed->gc,&fg_color);
	gdk_gc_set_rgb_bg_color(ed->gc_small,&bg_color); gdk_gc_set_rgb_fg_color(ed->gc_small,&fg_color);

	/* Draw the visible pixels */
	for (y=0;y<7;y++) {
		for (x=0;x<ncols;x++) {
			if (*(*ed->bitmap+x) & (0x40 >> y)) {
				gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap),ed->gc,TRUE,(x*16),(y*16),16,16);
				if (x < 68) gdk_draw_rectangle(GDK_DRAWABLE(ed->pixmap_small),ed->gc_small,TRUE,(x*3),(y*3),3,3);
			}
		}
	}

	/* Draw the grid */
	gdk_gc_set_rgb_fg_color(ed->gc,&grid_color);
	gdk_draw_segments(GDK_DRAWABLE(ed->pixmap),ed->gc,(GdkSegment *)grid_segments,N_GRID_SEGMENTS);
	gdk_gc_set_rgb_fg_color(ed->gc,&fg_color);
	return ed;
}

void bitmap_editor_free(bitmap_editor_t *ed) {
	if (!ed) return
	gtk_widget_destroy(ed->dialog);
	g_free(ed);
}

/* vim: set ts=4: */

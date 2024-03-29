//	Copyright (C) 2010-2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Fractals with Shaders.
 *
 *	Fractals with Shaders is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Fractals with Shaders is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Fractals with Shaders.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "color tables.h"

#include <cmath>
#include <Color/wavelength to RGB.h>

#define e 2.71828f

#define LAB 0
#define SPECTRUM 1
#define REVERSE_SPECTRUM 2
#define YELLOW_ON_BLUE 3
#define LOGARITHMIC_SPECTRUM 4
#define REVERSE_LOGARITHMIC_SPECTRUM 5


void populate_color_tables()
{
	for(int i = 0 ; i < TABLE_ENTRIES-1 ; ++i)
	{
		float factor = (float)i / TABLE_ENTRIES;
		color_table[YELLOW_ON_BLUE][i].r = factor;
		color_table[YELLOW_ON_BLUE][i].g = factor;
		color_table[YELLOW_ON_BLUE][i].b = 0.5;

		float temp = (640-380)*(factor) + 380;	// wavelength
		color_table[REVERSE_SPECTRUM][TABLE_ENTRIES-2-i].r = color_table[SPECTRUM][i].r = spectrumRed(temp);
		color_table[REVERSE_SPECTRUM][TABLE_ENTRIES-2-i].g = color_table[SPECTRUM][i].g = spectrumGreen(temp);
		color_table[REVERSE_SPECTRUM][TABLE_ENTRIES-2-i].b = color_table[SPECTRUM][i].b = spectrumBlue(temp);

		temp = (640-380)*log((e-1)*factor+1) + 380;	// wavelength
		color_table[LOGARITHMIC_SPECTRUM][i].r = spectrumRed(temp);
		color_table[LOGARITHMIC_SPECTRUM][i].g = spectrumGreen(temp);
		color_table[LOGARITHMIC_SPECTRUM][i].b = spectrumBlue(temp);

		temp = (380-640)*log((e-1)*factor+1) + 640;	// wavelength
		color_table[REVERSE_LOGARITHMIC_SPECTRUM][i].r = spectrumRed(temp);
		color_table[REVERSE_LOGARITHMIC_SPECTRUM][i].g = spectrumGreen(temp);
		color_table[REVERSE_LOGARITHMIC_SPECTRUM][i].b = spectrumBlue(temp);
	} // end for

	color_table[YELLOW_ON_BLUE][TABLE_ENTRIES-1].r = 0.0;
	color_table[YELLOW_ON_BLUE][TABLE_ENTRIES-1].g = 0.0;
	color_table[YELLOW_ON_BLUE][TABLE_ENTRIES-1].b = 0.0;

	color_table[SPECTRUM][TABLE_ENTRIES-1].r = 0.0;
	color_table[SPECTRUM][TABLE_ENTRIES-1].g = 0.0;
	color_table[SPECTRUM][TABLE_ENTRIES-1].b = 0.0;

	color_table[REVERSE_SPECTRUM][TABLE_ENTRIES-1].r = 0.0;
	color_table[REVERSE_SPECTRUM][TABLE_ENTRIES-1].g = 0.0;
	color_table[REVERSE_SPECTRUM][TABLE_ENTRIES-1].b = 0.0;

	color_table[LOGARITHMIC_SPECTRUM][TABLE_ENTRIES-1].r = 0.0;
	color_table[LOGARITHMIC_SPECTRUM][TABLE_ENTRIES-1].g = 0.0;
	color_table[LOGARITHMIC_SPECTRUM][TABLE_ENTRIES-1].b = 0.0;

	color_table[REVERSE_LOGARITHMIC_SPECTRUM][TABLE_ENTRIES-1].r = 0.0;
	color_table[REVERSE_LOGARITHMIC_SPECTRUM][TABLE_ENTRIES-1].g = 0.0;
	color_table[REVERSE_LOGARITHMIC_SPECTRUM][TABLE_ENTRIES-1].b = 0.0;
} // end function populate_color_tables


RGBColor color_table[COLOR_TABLES][TABLE_ENTRIES] = {{
	{0.000f,0.000f,0.734f},
	{0.000f,0.300f,0.734f},
	{0.000f,0.734f,0.000f},
	{0.734f,0.734f,0.000f},
	{0.734f,0.000f,0.000f},
	{0.734f,0.000f,0.734f},
	{0.000f,0.734f,0.734f},
	{0.750f,0.750f,0.750f},
	{0.750f,0.859f,0.750f},
	{0.641f,0.781f,0.938f},
	{0.500f,0.000f,0.000f},
	{0.000f,0.500f,0.000f},
	{0.500f,0.500f,0.000f},
	{0.000f,0.000f,0.500f},
	{0.500f,0.000f,0.500f},
	{0.000f,0.500f,0.500f},
	{0.234f,0.359f,0.234f},
	{0.359f,0.359f,0.234f},
	{0.484f,0.359f,0.234f},
	{0.609f,0.359f,0.234f},
	{0.734f,0.359f,0.234f},
	{0.859f,0.359f,0.234f},
	{0.984f,0.359f,0.234f},
	{0.234f,0.484f,0.234f},
	{0.359f,0.484f,0.234f},
	{0.484f,0.484f,0.234f},
	{0.609f,0.484f,0.234f},
	{0.734f,0.484f,0.234f},
	{0.859f,0.484f,0.234f},
	{0.984f,0.484f,0.234f},
	{0.234f,0.609f,0.234f},
	{0.359f,0.609f,0.234f},
	{0.484f,0.609f,0.234f},
	{0.609f,0.609f,0.234f},
	{0.734f,0.609f,0.234f},
	{0.859f,0.609f,0.234f},
	{0.984f,0.609f,0.234f},
	{0.234f,0.734f,0.234f},
	{0.359f,0.734f,0.234f},
	{0.484f,0.734f,0.234f},
	{0.609f,0.734f,0.234f},
	{0.734f,0.734f,0.234f},
	{0.859f,0.734f,0.234f},
	{0.984f,0.734f,0.234f},
	{0.234f,0.859f,0.234f},
	{0.359f,0.859f,0.234f},
	{0.484f,0.859f,0.234f},
	{0.609f,0.859f,0.234f},
	{0.734f,0.859f,0.234f},
	{0.859f,0.859f,0.234f},
	{0.984f,0.859f,0.234f},
	{0.234f,0.984f,0.234f},
	{0.359f,0.984f,0.234f},
	{0.484f,0.984f,0.234f},
	{0.609f,0.984f,0.234f},
	{0.734f,0.984f,0.234f},
	{0.859f,0.984f,0.234f},
	{0.984f,0.984f,0.234f},
	{0.234f,0.234f,0.359f},
	{0.359f,0.234f,0.359f},
	{0.484f,0.234f,0.359f},
	{0.609f,0.234f,0.359f},
	{0.734f,0.234f,0.359f},
	{0.859f,0.234f,0.359f},
	{0.984f,0.234f,0.359f},
	{0.234f,0.359f,0.359f},
	{0.359f,0.359f,0.359f},
	{0.484f,0.359f,0.359f},
	{0.609f,0.359f,0.359f},
	{0.734f,0.359f,0.359f},
	{0.859f,0.359f,0.359f},
	{0.984f,0.359f,0.359f},
	{0.234f,0.484f,0.359f},
	{0.359f,0.484f,0.359f},
	{0.484f,0.484f,0.359f},
	{0.609f,0.484f,0.359f},
	{0.734f,0.484f,0.359f},
	{0.859f,0.484f,0.359f},
	{0.984f,0.484f,0.359f},
	{0.234f,0.609f,0.359f},
	{0.359f,0.609f,0.359f},
	{0.484f,0.609f,0.359f},
	{0.609f,0.609f,0.359f},
	{0.734f,0.609f,0.359f},
	{0.859f,0.609f,0.359f},
	{0.984f,0.609f,0.359f},
	{0.234f,0.734f,0.359f},
	{0.359f,0.734f,0.359f},
	{0.484f,0.734f,0.359f},
	{0.609f,0.734f,0.359f},
	{0.734f,0.734f,0.359f},
	{0.859f,0.734f,0.359f},
	{0.984f,0.734f,0.359f},
	{0.234f,0.859f,0.359f},
	{0.359f,0.859f,0.359f},
	{0.484f,0.859f,0.359f},
	{0.609f,0.859f,0.359f},
	{0.734f,0.859f,0.359f},
	{0.859f,0.859f,0.359f},
	{0.984f,0.859f,0.359f},
	{0.234f,0.984f,0.359f},
	{0.359f,0.984f,0.359f},
	{0.484f,0.984f,0.359f},
	{0.609f,0.984f,0.359f},
	{0.734f,0.984f,0.359f},
	{0.859f,0.984f,0.359f},
	{0.984f,0.984f,0.359f},
	{0.234f,0.234f,0.484f},
	{0.359f,0.234f,0.484f},
	{0.484f,0.234f,0.484f},
	{0.609f,0.234f,0.484f},
	{0.734f,0.234f,0.484f},
	{0.859f,0.234f,0.484f},
	{0.984f,0.234f,0.484f},
	{0.234f,0.359f,0.484f},
	{0.359f,0.359f,0.484f},
	{0.484f,0.359f,0.484f},
	{0.609f,0.359f,0.484f},
	{0.734f,0.359f,0.484f},
	{0.859f,0.359f,0.484f},
	{0.984f,0.359f,0.484f},
	{0.234f,0.484f,0.484f},
	{0.359f,0.484f,0.484f},
	{0.484f,0.484f,0.484f},
	{0.609f,0.484f,0.484f},
	{0.734f,0.484f,0.484f},
	{0.859f,0.484f,0.484f},
	{0.984f,0.484f,0.484f},
	{0.234f,0.609f,0.484f},
	{0.359f,0.609f,0.484f},
	{0.484f,0.609f,0.484f},
	{0.609f,0.609f,0.484f},
	{0.734f,0.609f,0.484f},
	{0.859f,0.609f,0.484f},
	{0.984f,0.609f,0.484f},
	{0.234f,0.734f,0.484f},
	{0.359f,0.734f,0.484f},
	{0.484f,0.734f,0.484f},
	{0.609f,0.734f,0.484f},
	{0.734f,0.734f,0.484f},
	{0.859f,0.734f,0.484f},
	{0.984f,0.734f,0.484f},
	{0.234f,0.859f,0.484f},
	{0.359f,0.859f,0.484f},
	{0.484f,0.859f,0.484f},
	{0.609f,0.859f,0.484f},
	{0.734f,0.859f,0.484f},
	{0.859f,0.859f,0.484f},
	{0.984f,0.859f,0.484f},
	{0.234f,0.984f,0.484f},
	{0.359f,0.984f,0.484f},
	{0.484f,0.984f,0.484f},
	{0.609f,0.984f,0.484f},
	{0.734f,0.984f,0.484f},
	{0.859f,0.984f,0.484f},
	{0.984f,0.984f,0.484f},
	{0.234f,0.234f,0.609f},
	{0.359f,0.234f,0.609f},
	{0.484f,0.234f,0.609f},
	{0.609f,0.234f,0.609f},
	{0.734f,0.234f,0.609f},
	{0.859f,0.234f,0.609f},
	{0.984f,0.234f,0.609f},
	{0.234f,0.359f,0.609f},
	{0.359f,0.359f,0.609f},
	{0.484f,0.359f,0.609f},
	{0.609f,0.359f,0.609f},
	{0.734f,0.359f,0.609f},
	{0.859f,0.359f,0.609f},
	{0.984f,0.359f,0.609f},
	{0.234f,0.484f,0.609f},
	{0.359f,0.484f,0.609f},
	{0.484f,0.484f,0.609f},
	{0.609f,0.484f,0.609f},
	{0.734f,0.484f,0.609f},
	{0.859f,0.484f,0.609f},
	{0.984f,0.484f,0.609f},
	{0.234f,0.609f,0.609f},
	{0.359f,0.609f,0.609f},
	{0.484f,0.609f,0.609f},
	{0.609f,0.609f,0.609f},
	{0.734f,0.609f,0.609f},
	{0.859f,0.609f,0.609f},
	{0.984f,0.609f,0.609f},
	{0.234f,0.734f,0.609f},
	{0.359f,0.734f,0.609f},
	{0.484f,0.734f,0.609f},
	{0.609f,0.734f,0.609f},
	{0.734f,0.734f,0.609f},
	{0.859f,0.734f,0.609f},
	{0.984f,0.734f,0.609f},
	{0.234f,0.859f,0.609f},
	{0.359f,0.859f,0.609f},
	{0.484f,0.859f,0.609f},
	{0.609f,0.859f,0.609f},
	{0.734f,0.859f,0.609f},
	{0.859f,0.859f,0.609f},
	{0.984f,0.859f,0.609f},
	{0.234f,0.984f,0.609f},
	{0.359f,0.984f,0.609f},
	{0.484f,0.984f,0.609f},
	{0.609f,0.984f,0.609f},
	{0.734f,0.984f,0.609f},
	{0.859f,0.984f,0.609f},
	{0.984f,0.984f,0.609f},
	{0.234f,0.234f,0.734f},
	{0.359f,0.234f,0.734f},
	{0.484f,0.234f,0.734f},
	{0.609f,0.234f,0.734f},
	{0.734f,0.234f,0.734f},
	{0.859f,0.234f,0.734f},
	{0.984f,0.234f,0.734f},
	{0.234f,0.359f,0.734f},
	{0.359f,0.359f,0.734f},
	{0.484f,0.359f,0.734f},
	{0.609f,0.359f,0.734f},
	{0.734f,0.359f,0.734f},
	{0.859f,0.359f,0.734f},
	{0.984f,0.359f,0.734f},
	{0.234f,0.484f,0.734f},
	{0.359f,0.484f,0.734f},
	{0.484f,0.484f,0.734f},
	{0.609f,0.484f,0.734f},
	{0.734f,0.484f,0.734f},
	{0.859f,0.484f,0.734f},
	{0.984f,0.484f,0.734f},
	{0.234f,0.609f,0.734f},
	{0.359f,0.609f,0.734f},
	{0.484f,0.609f,0.734f},
	{0.609f,0.609f,0.734f},
	{0.734f,0.609f,0.734f},
	{0.859f,0.609f,0.734f},
	{0.984f,0.609f,0.734f},
	{0.234f,0.734f,0.734f},
	{0.359f,0.734f,0.734f},
	{0.484f,0.734f,0.734f},
	{0.609f,0.734f,0.734f},
	{0.734f,0.734f,0.734f},
	{0.859f,0.734f,0.734f},
	{0.984f,0.734f,0.734f},
	{0.234f,0.859f,0.734f},
	{0.359f,0.859f,0.734f},
	{0.484f,0.859f,0.734f},
	{0.609f,0.859f,0.734f},
	{0.734f,0.859f,0.734f},
	{0.859f,0.859f,0.734f},
	{0.984f,0.969f,0.938f},
	{0.625f,0.625f,0.641f},
	{0.500f,0.500f,0.500f},
	{0.984f,0.000f,0.000f},
	{0.000f,0.984f,0.000f},
	{0.984f,0.984f,0.000f},
	{0.000f,0.000f,0.984f},
	{0.984f,0.000f,0.984f},
	{0.000f,0.984f,0.984f},
	{0.000f,0.000f,0.000f}
}};

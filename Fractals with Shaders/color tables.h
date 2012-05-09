//	Copyright (C) 2010-2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
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

#ifndef COLOR_TABLES_H
#define COLOR_TABLES_H

#define TABLE_ENTRIES 256
#define COLOR_TABLES 6

struct RGBColor
{
	float r;
	float g;
	float b;
}; // end struct RGBColor

extern RGBColor color_table[COLOR_TABLES][TABLE_ENTRIES];

void populate_color_tables();

#endif // COLOR_TABLES_H
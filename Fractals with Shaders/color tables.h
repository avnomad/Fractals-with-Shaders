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
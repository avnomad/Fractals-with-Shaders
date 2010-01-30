#ifndef COLOR_TABLES_H
#define COLOR_TABLES_H

#define TABLE_ENTRIES 256

struct RGBColor
{
	float r;
	float g;
	float b;
}; // end struct RGBColor

extern RGBColor yellow_on_blue_color_table[TABLE_ENTRIES];
extern RGBColor spectrum_color_table[TABLE_ENTRIES];
extern RGBColor reverse_spectrum_color_table[TABLE_ENTRIES];
extern RGBColor lab_color_table[TABLE_ENTRIES];

void populate_color_tables();

#endif // COLOR_TABLES_H
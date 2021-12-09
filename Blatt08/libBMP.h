/**
 * Prozedurale Programmierung
 *
 * Bibliothek fuer BMP (Windows Bitmap)
 */
#ifndef __libBMP_h__
#define __libBMP_h__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Definiere einfache BMP Farben
#define COLOR_BLACK 0x00000000
#define COLOR_RED   0x00FF0000
#define COLOR_GREEN 0x0000FF00
#define COLOR_BLUE  0x000000FF
#define COLOR_WHITE 0x00FFFFFF


/**
 * Schreibt die N letzten Bytes eines 64-bit Integers in ein BMP Bild.
 * Das am wenigsten signifikante Byte (LSB) wird zuerst geschrieben.
 * (Little Endian).
 *
 * bmp  - Zeiger auf das bmp Bild
 * byte - Byte-Muster
 * N    - Anzahl der zu schreibenden Bytes (N <= 8).
 */
void bmp_write_N_byte(FILE * bmp, uint64_t byte, int N) {
  for (int i = 0; ((i < N) && (i < 8)); i++) {
    fputc(byte % 256, bmp);
    byte /= 256;
  }
}

/**
 * Erstellt einen BMP-File-Header, insgesamt 14 Byte.
 *
 * bmp    - Zeiger auf das bmp Bild
 * width  - Bildbreite (in Pixel)
 * height - Bildhoehe  (in Pixel)
 */
void bmp_file_header(FILE * bmp, int width, int height) {
  // (2 Byte, uint16_t) ASCII-Zeichenkette "BM" (Hex: 0x42 0x4D Dez: 19778).
  fputc('B', bmp);
  fputc('M', bmp);
  // (4 Byte, uint32_t) Groesse der BMP-Datei in Byte.
  // = bmp_file_header + bmp_info_header + Daten
  bmp_write_N_byte(bmp, 14 + 40 + width * height * 32, 4);
  // (4 Byte, uint32_t) Reserviert, Standard: 0
  bmp_write_N_byte(bmp, 0, 4);
  // (4 Byte, uint32_t) Offset der Bilddaten in Byte vom Beginn der Datei an,
  // bei Echtfarben fast immer 54 (manche Software ignoriert diese Angabe
  // daher fehlerhafterweise).
  bmp_write_N_byte(bmp, 54, 4);
}



/**
 * Erstellt einen BMP-Info-Header, insgesamt 40 Byte.
 *
 * bmp    - Zeiger auf das bmp Bild
 * width  - Bildbreite (in Pixel)
 * height - Bildhoehe  (in Pixel)
 */
void bmp_info_header(FILE* bmp, int width, int height) {
  // (4 Byte, uint32_t) Groesse von bmp_info_header in Byte
  bmp_write_N_byte(bmp, 40, 4);
  // (4 Byte, int32_t) Breite der Bitmap in Pixel.
  bmp_write_N_byte(bmp, width, 4);
  // (4 Byte, int32_t) Hoehe der Bitmap in Pixel. Negativ: top-bottom.
  bmp_write_N_byte(bmp, -height, 4);
  // (2 Byte, uint16_t) Anzahl der Farbebenen, nicht fuer BMP verwendet
  bmp_write_N_byte(bmp, 1, 2);
  // (2 Byte, uint16_t) Gibt die Farbtiefe der Bitmap in bpp an; muss einer
  // der folgenden Werte sein: 1, 4, 8, 16, 24 oder 32. Bei 1, 4 und 8 bpp
  // sind die Farben indiziert.
  bmp_write_N_byte(bmp, 32, 2);
  // (4 Byte, uint32_t) Keine Kompression verwendet = 0
  bmp_write_N_byte(bmp, 0, 4);
  // (4 Byte, uint32_t) Groesse der reinen Bilddaten in Byte (mit padding).
  bmp_write_N_byte(bmp, width * height * 32, 4);
  // (4 Byte, int32_t) Horizontale Aufloesung des Zielausgabegerätes in Pixel
  // pro Meter; wird aber fuer BMP-Dateien meistens auf 0 gesetzt.
  bmp_write_N_byte(bmp, 0, 4);
  // (4 Byte, int32_t) Vertikale Aufloesung des Zielausgabegerätes in Pixel
  // pro Meter; wird aber fuer BMP-Dateien meistens auf 0 gesetzt.
  bmp_write_N_byte(bmp, 0, 4);
  // (4 Byte, uint32_t) Anzahl der Eintraege der Farbtabelle; 0 bedeutet keine.
  bmp_write_N_byte(bmp, 0, 4);
  // (4 Byte, uint32_t) Anzahl wichtiger Farben; 0 bedeutet alle sind wichtig.
  bmp_write_N_byte(bmp, 0, 4);
}



/**
 * Erstellt ein BMP Bild.
 *
 * bmp_name - Name des BMP Bildes
 * data     - BMP Daten-Array
 * width    - Bildbreite (in Pixel)
 * height   - Bildhoehe  (in Pixel)
 */
void bmp_create(char* bmp_name, uint32_t* data, int width, int height) {
  FILE* bmp = fopen(bmp_name, "wb");
  if (bmp == NULL) {
    fprintf(stderr, "\nbmp Bilddatei konnte nicht geoeffnet werden!\n");
    exit(EXIT_FAILURE);
  }
  bmp_file_header(bmp, width, height);
  bmp_info_header(bmp, width, height);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      bmp_write_N_byte(bmp, data[y * width + x], 4);
    }
  }
  fclose(bmp);
}

#endif

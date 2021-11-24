/**
 * Prozedurale Programmierung: Beispiel zu Uebungsplatt 6
 *
 */

#include "libBMP.h"

// Grenzen BMP Bereich
#define H 400  // Hoehe des BMP Bildes
#define W 500  // Weite (Breite) des BMP Bildes

int main() {
    uint32_t* data;
    int X,Y;
    //eindimensionales dynamisches Array der Größe W x H
    //mit dem Datentyp uint32_t
    data = (uint32_t*) malloc (W * H * sizeof(uint32_t));

    for (X = 0; X < W; X++) {
        for (Y = 0; Y < H; Y++) {
            // Abwechselnd werden jeweils 10 Zeilen in rot bzw. gruen gezeichnet,
            // sodass sich ein Streifenmuster ergibt.
            if((Y/10)%2)
                data[Y * W + X] = COLOR_RED;
            else
                data[Y * W + X] = COLOR_GREEN;
        }
    }
    // Schreibe BMP Datei
    bmp_create("plot.bmp", data, W, H);
    free(data);
    return 0;
}

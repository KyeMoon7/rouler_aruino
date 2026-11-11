// Le code minimal

#include <Arduino.h>

#include <M5_Encoder.h>
M5_Encoder monEncodeur;

#include <MicroOscSlip.h>
MicroOscSlip<128> monOsc(&Serial);

void setup()
{
    Wire.begin();
    monEncodeur.begin();
    Serial.begin(115200);
}

void loop()
{
    monEncodeur.update(); // Mise à jour des valeurs de l’encodeur.

    // Lecture du changement depuis la dernière lecture
    int changementEncodeur = monEncodeur.getEncoderChange();
    if (changementEncodeur != 0)
    {
        monOsc.sendInt("/enc/rot", changementEncodeur);
    }

    if (monEncodeur.wasPressed())
    {
        monOsc.sendInt("/enc/but", 1);
    }

    if (monEncodeur.wasReleased())
    {
        monOsc.sendInt("/enc/but", 0);
    }
}

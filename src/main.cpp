#include <Arduino.h>
#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32_NimBLE.h>

#include "midi_console.h"

BLEMIDI_CREATE_INSTANCE("FBVtoMIDI", MIDI);

void sendControlChange(uint8_t channel, uint8_t cc, uint8_t value)
{
    MIDI.sendControlChange(cc, value, channel);
}

void sendProgramChange(uint8_t channel, uint8_t program)
{
    MIDI.sendProgramChange(program, channel);
}

midi_console::Console midiConsole(sendControlChange, sendProgramChange);

void onControlChange(byte channel, byte cc, byte value)
{
    midiConsole.onControlChange(channel, cc, value);
}

void onProgramChange(byte channel, byte program)
{
    midiConsole.onProgramChange(channel, program);
}

void onBleConnected()
{
    Serial.println("[BLE] MIDI central connected.");
    if (NimBLEDevice::getServer()->getConnectedCount() < CONFIG_BT_NIMBLE_MAX_CONNECTIONS &&
        !NimBLEDevice::startAdvertising())
    {
        Serial.println("[BLE] Failed to restart advertising.");
    }
}

void onBleDisconnected()
{
    Serial.println("[BLE] MIDI central disconnected.");
}

void setup()
{
    Serial.begin(115200);

    BLEMIDI.setHandleConnected(onBleConnected);
    BLEMIDI.setHandleDisconnected(onBleDisconnected);

    MIDI.setHandleControlChange(onControlChange);
    MIDI.setHandleProgramChange(onProgramChange);
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();

    midiConsole.begin("BLE MIDI console ready. Advertised name: FBVtoMIDI.");
}

void loop()
{
    MIDI.read();
    midiConsole.poll();
}
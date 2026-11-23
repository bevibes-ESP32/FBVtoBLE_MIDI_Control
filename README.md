# FBVtoBLE_MIDI_Control

Freenove ESP32-S3 BLE MIDI console for testing ToneXController commands. The board advertises the standard BLE MIDI service under the name `FBVtoMIDI`, so it can be paired with ToneXController or a BLE MIDI host on Windows/macOS.

## Serial console

Open the PlatformIO monitor on the CH343 COM port at 115200 baud. Commands are processed only when Enter is pressed.

```text
CC 12 15
PC 17
gain 10
treble 8.5
preset 12
preset slot 2
bank +
bank -
help params
```

`PC` values are zero-based; `preset` values are one-based and send Program Change. `preset slot 2` selects slot 2 in the currently selected bank through CC 105. `bank +`/`bank -` change banks. Parameter aliases use ToneXController units and are range-checked. The console reports received and transmitted CC/PC messages as `[Rx]` and `[Tx]`.

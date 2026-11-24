# FBVtoBLE_MIDI_Control

Freenove ESP32-S3 BLE MIDI console for testing ToneXController commands. The board advertises the standard BLE MIDI service under the name `FBVtoMIDI`, so it can be paired with ToneXController or a BLE MIDI host on Windows/macOS.

The BLE MIDI peripheral is configured for up to four simultaneous connections and resumes advertising after each connection while capacity remains. Connected clients share the MIDI stream: incoming messages from any client are received by FBVtoBLE, and outgoing messages are notified to subscribed clients.

## Serial console

Open the PlatformIO monitor on the CH343 COM port at 115200 baud. Commands are processed only when Enter is pressed.

```text
CC 12 15
PC 17
gain 10
treble 8.5
delay off
comp toggle
mod pre
BPM 90
preset 12
preset slot 2
bank +
bank -
help params
```

`PC` values are zero-based; `preset` values are one-based and send Program Change. `preset slot 2` selects slot 2 in the currently selected bank through CC 105. `bank +`/`bank -` change banks. Short effect aliases accept `on`/`off`/`toggle` (for example `delay off` or `comp toggle`); `mod pre` and `mod post` select modulation position. Other parameter aliases use ToneXController units and are range-checked. `[Tx]` and `[Rx]` are colored by direction; effect messages also use distinct ANSI colors (delay orange, gate yellow, compressor violet, EQ green, modulation cyan, reverb blue). ANSI colors are intended for the PlatformIO serial monitor.

//+----------+----------------------------------------------------+-----------------------+
//| SOFTWARE |                                                    | HARDWARE Transceiver  |
//|          |                  HARDWARE/SOFTWARE                 |         |∖            |
//|          |          CAN DRIVER ALL ARDUINO COMPATIBLE         |     TXD_| ∖___CANH    |
//|          |                                                    |         |  ∖          |
//|          |                                                    |     RXD_|  /__CANL    |
//|          |                                                    |         | /           |
//|          |                                                    |         |/            |
//|          |                                                    |  CAN LEVEL ADAPTATOR  |
//+----------+----------------------------------------------------+-----------------------+
//|          |        |               | ESP32(VDD=3.3V)           |                       |
//|          |        |               | TXD:GPIOx RXD:GPIOy       | MCP2551(VDD=5V)       |
//|          | C      |               | driver:CAN Thomas Barth   | OR                    |
//+ N        + A      +               +---------------------------+ MCP2562(VDD=5v=>3.3V) +
//| M        |        |    INTERNAL   | DUE(VDD=3.3V)             | OR                    |
//| E        | N      |               | driver:due_can            | sn65hvd23x(VDD=3.3V)  |
//| A        |        |               | TXD:A14 RXD:A15           | OR                    |
//+ 2        +        +               +---------------------------+ sn65hvd34             +
//| K        | D      |               | Teensy 3.1/3.2 or 3.5/3.6 | OR                    |
//|          | R      |               | driver:FlexCAN            | tja1050               |
//+          + I      +---------------+---------------------------+  etc...               +
//|          | V      |    EXTERNAL   | ALL arduino with MCP2515  |                       |
//+          + E      +               + SPI (VDD=5v=>.3.3V)       +                       +
//|          | R      |               | driver:NMEA2000_mcp       |                       |
//+----------+--------+---------------+---------------------------+-----------------------+

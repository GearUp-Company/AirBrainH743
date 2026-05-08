# AirBrain H743 quality

## End-of-line functional test

Every AirBrain H743 board is functionally tested before shipping. The test verifies:

- **Power rails**: VBat to 5V BEC and VBat to 10V BEC, both verified under load.
- **MCU programmability**: a Betaflight build is flashed via DFU, success of the flash is verified.
- **UART communication**: serial communication on the active UART is exercised end-to-end.
- **Motor outputs**: outputs M1 to M4 are verified for correct switching behaviour.

A board that does not pass every step on the test fixture does not ship.

## EMC

Pre-compliance EMC sweeps are run at the [Würth Elektronik eiSos](https://www.we-online.com/) lab in Belgium before each board revision. Sweeps cover radiated emissions and conducted emissions per the EN 55032 / EN 55035 reference, in the configurations relevant to the AirBrain's deployment profile.

Specific test report content is held under confidentiality with Würth and is not republished. The test ticket reference for the current revision is available on request from [info@takeyourgear.com](mailto:info@takeyourgear.com) for procurement and integration evaluators.

## ESD

Every external connector on the AirBrain H743 carries ESD protection on the signal lines. The board survives realistic ESC / VTX / RX coexistence, not just bench-perfect conditions.

## Bill of materials

The component bill of materials is sourced exclusively from authorised distributors in EU / US / JP / TW countries. The supply origin is **NDAA-compliant**.

## Conformal coating

Conformal coating is **not applied by default** on standard production AirBrain H743 boards.

Conformal coating is **available as a paid extra** for orders that meet a minimum order quantity. The coating type, masked areas, and MOQ are agreed per order. Contact [info@takeyourgear.com](mailto:info@takeyourgear.com) with the application context (humidity profile, salt fog, dielectric requirement) for a quote.

## Warranty

The standard warranty period is **24 months from date of shipment** for defects in materials and workmanship under normal operating conditions. Warranty is fulfilled by replacement of the defective board.

For B2B and OEM orders, warranty terms are contractually defined per order; the 24-month period is the default unless otherwise agreed.

Out of scope: physical damage from crash, water ingress (the AirBrain is IP67 only as a connector with proper gasket installation, not as a board), reverse polarity, over-voltage beyond the specified 3S to 10S input range, and modifications.

## Origin

The AirBrain H743 is **designed in Belgium and assembled in Belgium**. Final functional test is performed at our facility before shipment.

## Contact

Quality questions, conformal-coating quotes, EMC test ticket reference, or warranty claims:

- [info@takeyourgear.com](mailto:info@takeyourgear.com)
- For quality issues on a unit, include the order reference and a description of the failure mode.

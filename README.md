[![GitHub Issues](https://img.shields.io/github/issues/jasonmce/lighthouse)](https://github.com/jasonmce/lighthouse/issues)
[![GitHub Stars](https://img.shields.io/github/stars/jasonmce/lighthouse)](https://github.com/jasonmce/lighthouse/stargazers)

# 🗼 Cape Hatteras Lighthouse Light

This project recreates the iconic Cape Hatteras Lighthouse light as a 3D-printed model, complete with an Arduino-driven animation that mimics the real-world light signature of the actual lighthouse. At dusk a string of NeoPixels illuminate the lighthouse with a rotating beam effect to help my sister park &#128515;.

It is an example of a solar-powered Lighthouse Light, with a weatherproof enclosure, a switch to turn it on and off, and a solar charge controller to keep the battery charged.  It is meant to be easy to extend for creating your own lighthouse light model and custom signature.


## 📚 Background
My sister asked for a Cape Hatteras lighthouse garden decoration for her birthday.  Making the body was a fun project, but illuminating it was the part that interested me.  It was a great experience in what could go wrong with distantly deployed deliverables.

Evolutions in this project:
- Larger battery to survive multiple days of darkness - 10K mAh
- Stronger housing.  I originally used [Thingiverse myst lighthouse](https://www.thingiverse.com/thing:3164021) as the light fixture but it proved brittle when:
    - branches hit it
    - wind toppled the structure
- Custom light model to better match the Cape Hatteras light
- External power switch makes it easier to:
    - Reset the circuit if low voltage causes arduino issues
    - Ensure a solid charge after prolonged darkness
---

## 🔧 Features

- Fully 3D printable model, designed in modular STL components.
- Arduino-compatible `.ino` sketch to drive a NeoPixel LED strip.
- Solar powered - no charging or replacing of batteries required.
- Detects when it is dark and animates the light.
- Mimics the actual flash pattern of Cape Hatteras Lighthouse (light every 7.5 seconds).
- Designed to house internal wiring and switch access.
  
---

## 🖨️ 3D Printed Parts

All STL files can be found in the `models/` directory:

- `roof.stl` – Top cap for the lighthouse.
- `lens.stl` – Translucent lens for the light animation.
- `base.stl` – Base of the lighthouse.
- `base_ring_for_switch.stl` – Fits below base to allow switch access.
- `core.stl` – Internal lighthouse column that holds electronics.

---

## 🧠 Arduino Code

The `code/lighthouse.ino` sketch uses the Adafruit NeoPixel library to animate a light strip. It creates a rotating beam with fade transitions that align with the lighthouse's characteristic 7.5-second interval signature.

Requirements:
- Arduino Uno or compatible board - I used a Seeeduino XIAO because it was handy.
- Adafruit NeoPixel library
- 21 NeoPixel strip - can be customized to any length
- Light sensor
- Solar panel
- Weather proof switch
- Solar charge controller
- LiPo battery - Mine is a whopping 10k mAh to outlast a few dark or rainy days

---

## 🖼️ Photos

<figure>
    <img
        src="assets/images/Cape%20Hatteras%20Light%20head.jpg"
        alt="Assembled lighthouse with solar panel"
        height="auto" width="400" style="max-width: 100%;">
    <figcaption><strong>Model Head</strong></figcaption>
</figure>
<figure>
    <img
        src="assets/images/Cape%20Hatteras%20Light%20undressed.jpg"
        alt="Lighthouse with electronics exposed"
        height="auto" width="400" style="max-width: 100%;">
    <figcaption><strong>Undressed View</strong></figcaption>
</figure>
<figure>
    <img
        src="assets/images/Cape%20Hatteras%20Light%20core%20topdown.jpg"
        alt="Top down view of the core electronics"
        height="auto" width="400" style="max-width: 100%;">
    <figcaption><strong>Core Top-down View</strong></figcaption>
</figure>

---


## ⚙️ Assembly Notes

- Print the lens using clear or translucent filament for best light diffusion.
- Attach the NeoPixel strip onto the core, aligned with the center of the lens.
- Connect the NeoPixel strip to 5V, GND, and a digital pin (e.g., D10) on your Arduino.
- Connect the light sensor to an analog pin (e.g., A9) on your Arduino.
- Use the `base_ring_for_switch.stl` if you want external access to the power or mode switch
    It will control the connection between the solar controller output and the arduino.

---

## 📜 License

MIT License. Use and remix freely, and credit is appreciated.

---

## 🗺️ About the Real Lighthouse

Cape Hatteras Lighthouse is located in North Carolina and is known for its distinct black-and-white spiral pattern and strong maritime heritage. The animation in this project replicates its 7.5-second rotating flash pattern.

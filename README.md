# ApolOS

A 32-bit x86 operating system designed for NASA mission monitoring.
### [DEMO YOUTUBE LINK](https://youtu.be/a9k2mqdElSw)

## Interface

![ApolOS Terminal Interface](/web/public/demo.png)

## Technical Specifications

- **Boot Origin**: 0x7c00
- **Kernel Entry**: 0x1000
- **Stack (32-bit)**: 0x90000
- **Video Buffer**: 0xb8000 (VGA Text Mode)
- **I/O Ports**: Keyboard (0x60), CMOS (0x70/0x71), PIC (0x20/0x21)

## Execution

To test ApolOS, ensure QEMU and `apolos.bin` are installed. Execute the following command in your terminal (debian command):

```bash
sudo apt update && sudo apt install -y qemu-system-x86 && qemu-system-i386 -drive format=raw,file=apolos.bin
```

## CLI Reference

The ApolOS shell provides a set of low-level commands for system management and NASA mission database interaction.

### System Commands

- **`help`**
  Displays a list of all available commands and basic usage instructions.

- **`clear`**
  Clears the VGA text buffer (at `0xb8000`) and resets the cursor position to the top-left corner.

- **`info`**
  Outputs the current operating system version string: `ApolOS v0.1`.

- **`whoami`**
  Displays the current user privilege level, which defaults to `root`.

- **`echo [text]`**
  Prints the user-provided text string directly to the terminal.

- **`color [hex_code]`**
  Changes the global text and background colors by updating the `currentColor` variable.
  - **Format**: `0xBG` (B = Background, G = Foreground).
  - **Example**: `color 0x0A` sets green text on a black background.

### NASA Mission Control

- **`nasa list`**
  Lists all NASA missions currently stored in the internal kernel database, including their names and current operational status.

- **`nasa info [mission_name]`**
  Retrieves detailed technical data for a specific mission.
  - **Data points**: Launch date, mission objective, operational status, and a brief technical description.
  - **Database Coverage**: Includes missions such as Apollo 11, Voyager 1, New Horizons, and the Artemis program.

## Background Processes

- **Real-Time Clock (RTC)**
  A background routine continuously reads time data from CMOS registers (`0x00`, `0x02`, `0x04`) to update the status bar clock on the bottom row of the display.

- **Keyboard Input**
  The system uses an Interrupt Descriptor Table (IDT) to catch hardware interrupts from port `0x60`, mapping scancodes to a QWERTY character set for real-time typing.

## Contributing

Contributions to ApolOS are welcome! Please fork the repository and submit a pull request with your improvements or bug fixes.

## License

ApolOS is licensed under the MIT License. See `LICENSE` for more details.

This example uses an Atmel ATXMEGA128A1U micrcontroller and an LSM6DSL accelerometer and serial plot to plot accelerometer values.

To run this example, you will need:
1. atmel studio
2. serial plot https://mil.ufl.edu/4744/software/serialplot-0.12.0-win32-setup.exe
3. an Atmel ATXMEGA128A1U microcontroller board
4. an LSM6DSL accelerometer. It needs to be connected to the atmel through one of the spi ports.

1.open the atmel studio solution file under lab 6/ lab_6 (ignore the "first submission" folder)
2.compile it, connect your microcontroller to your pc, and upload the code to the board.
3.open serial plot, for the "port" tab, find the com port your microcontroller is connected to.
3a.choose the highest clock frequency that you can (this depends on your system. i chose 115200)
  leave everything else as default. meaning 8-bit data, 1 stop bit, no flow control.
3b.make sure your progam is running before you click "open" on serial plot.
3c.for the data format tab, choose simple binary, three channels, int16 number type, and little endian.
3d.for the plot tab, choose 1000 for the buffer size and plot width, make sure all channels are open.
  tick "index as x axis" and "auto scale y axis" and choose "signed 16 bits" for the range preset

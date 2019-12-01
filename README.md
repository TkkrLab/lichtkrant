# lichtkrant

Data is sent to the FDS132 panel via a TORX111 and TOTX111 optical sensor. When scoping the transmitted data we can see a pulsetrain consisting of a start segment, a data segment and a end segment. 


Each of the FDS132 panels contain 3 rows of led matrix modules (5x7 pixels). Each row has 18 modules.

In each data segment 270 bits are transferred, this corresponds to the pixel data of an entire line for each of the 3 rows. 
So writing all 270 bits high, you will see the first line of pixels of all 3 rows light up.

A single data bit in this data segment has a length of 3μs. 
High: 2.2μs high and 0.8μs low
Low: 0.4μs High and 2.6μs low


The start and end segment should contain all the info regarding the row and panel selection. 

World Generation
================

Requirements
------------

+ Continents of varying size and quantity
+ Oceans between continents (obviously)
+ Oceans to edge of map
+ Mountain ranges that make sense
+ Rivers that make sense
+ Lakes that make sense
+ Biome generation that makes sense

Details
-------
(Faerun is apparently 2,500 x 3,500 miles, which is 4,023 x 5,632 kilometres)

+ Overview map
    + One cell = 10km x 10km
    + Faerun size map would therefore be ~400 x 560 cells, or 224,000 cells. This allows us to store 8 bytes per cell in ~1.8MB of memory.
    + Each cell contains a terrain type, and average altitude
+ Detail map
    + Each cell on the overview map is split into a 1000x1000 grid. Each cell on this detail map is therefore 10m x 10m in size

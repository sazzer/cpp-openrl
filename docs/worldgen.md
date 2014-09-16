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
+ Comparisons
    + Faerun is apparently 2,500 x 3,500 miles, which is 4,023 x 5,632 kilometres
    + England is apparently 575 x 588 Kilometres
    + USA is apparently 4,174 x 2,589 Kilometres


+ Overview map
    + One cell = 1km x 1km
    + Faerun size map would therefore be ~4000 x 5600 cells, or 22,400,000 cells. This allows us to store 2 bytes per cell in ~44,800,000 bytes of memory, which is ~40MB.
    + Each cell contains a terrain type, and average altitude
    + Can store each of those as a 1 byte value. Gives us altitude variance of 256km, and 256 different terrain types.
+ Detail map
    + Each cell on the overview map is split into a 1000x1000 grid. Each cell on this detail map is therefore 1m x 1m in size
    + Each cell will have more detail, but there are less of them. Sparse data structures can help a lot here too.

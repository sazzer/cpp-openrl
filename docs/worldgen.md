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

Continent Generation
--------------------
The way that we are going to generate the continent layout and height map is as follows:
+ Generate a number of seeds based on the size of the map
+ Calculate an average radius of the seeds based on the desired coverage of the map
    + coverage * w * h = numberOfSeeds * 3.14 * (averageRadius ^ 2)
    + Therefore, averageRadius = sqrt((coverage * w * h) / (numberOfSeeds * 3.14))
+ Render each seed onto the map in turn
    + When rendering a seed, do so using the Diamond Square algorithm. Calculate the starting values by:
        + Quarter the seed
        + Any starting points that are already rendered from a previous seed are left as-is
        + The center point of the seed will be at height 150
        + The edge points will all be at height 75
    + Doing this means that overlapping seeds will be continuous correctly, and the coastline will be decent

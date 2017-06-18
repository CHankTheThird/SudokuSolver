##Sudoku Solver##

Written and Designed by Charles Hankins

#Usage Instructions#
Compile and run the code and when prompted enter the level of difficulty of puzzle you would like to see solved.
Text input is case-sensitive at this time. The starting board will print, followed by the step by step number
placements, and finally the solved board. You will be prompted to type exit to close the program.

#Design Notes#
The main methodology for the solver was to track what I referred to as "potential" on each tile in the grid. Each of the 81 Tile objects that make up the puzzle contains a bitset of size 9 (in addition to other information such as row, column, square, etc). This bitset represents the numbers 1-9 that the particular tile has the potential to be with a 1 representing potential and a 0 representing that a particular number has been ruled out for various reasons. For example, say the tile in row 1, column 1 was empty, and that the numbers 1, 4, 7, 8, and 9 were represented in either the row or column it resided in. The bitset for this tile would look like: 011011000. So naturally, as the program updates the potential in a tile, it checks to see if that tile's potential bitset contains only one 1 bit (done easily with the STL bitset count() function). If a tile only has one 1 bit, that indicates that only one value can possible go in that tile so we can queue it to have its value set. The majority of the remaining work was coding the logic in to either update potential accordingly or to check it in the necessary ways. An example of the former would be a scenario in which a number is known to only occupy a certain column within a square but perhaps not the particular row. That column then should remove the potential of that number for the squares above it. An example of the latter would be checking the cumulative potential of every tile in a particular row or col. If only one tile in a row or col has the potential to be a specific number, then it must be that number even if its potential hasn't yet eliminated other possibilities.

The code also utilizes a queue for actually placing the tiles. By queueing the tiles that have had their values determined, we can ensure that tiles have their potential updated accurately as we place others. Since we are never guessing when it comes to tile placement, we can safely queue a tile for a long time before placing it, because we know that no new information could cause it to become any other number than the one we chose for it. To protect the data within the Tile while it is queued, in addition to preventing a Tile from being queued multiple times, each tile also has a bool "wasQueued". This bool is initialized to false and is only flipped once the Tile has been added to the queue. It is never reset to false, and is checked anytime operations are to be made on a tile or a tile is to be added to the queue.


#Miscellaneous Notes#
There are certainly many improvements and optimizations that can be made to this program. I am sure there may be inefficiences in data types or data structures that use more space than they need to or are slower than other alternatives. I am also leery of the logic itself, as I may have many redundant operations or even logical scenarios that are not accounted for. This is principally because I did not want to look up the "optimal logic" for sudoku if such a thing exists. I was inspired to write this program partially because I am an avid sudoku player myself, and I wanted to challenge myself to come up with the logic on my own. I will most likely update this code from time to time to further optimize it or make it more user-friendly.
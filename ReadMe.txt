To use this program: 
	MagicMatrix size [output-file]
If output-file is not specified, the resulting matrix will be written to Magic.Txt.

To fufill the requirements of this progject, I researched how to find Magic squares of all kinds.  From my research, I discovered that there are
3 types of magic square, each with its own method of generation: Odd, Singly Even and Doubly Even.

Odd Magic Squares were the easiest and cleanest to generate.  I found an extemely elegant formula that's a function of the indices and the rank.  I used this formula in the algorithm for generating
the odd magic square.  

Doubly Even Magic Squares can be generated through a few approaches.  I watched some videos and skimmed some research articles, until I found a relatively elegant solution as well.  This solution 
relied on using bitshifting to determine the zones and assign numbers from both ends of the range.  The key to this formula was the mask which controlled the patterns of the
zones.

Singly Even Magic Squares are the least elegant to generate.  Here, I used a method that decomposed the square into odd magic squares, and then used a series of transformations to ensure the 
composite square was magic.  This had the added benefit of re-using the odd magic square code. A key insight here is if n is even and not divisible by 4, then n/2 is odd, thus ensuring we can 
always find the odd magic sub-square. A key to the transformations was dividing the square into quadrants, which controlled the operations to be performed.

To test this, I wrote an ad-hoc testing function.  I considered adding a unit testing project to this, but decided to keep it simple and not introduce additional dependencies.  The ad hoc
testing project was a property based/generative testing function that simply used the definition of a magic square to ensure that any given matrix was magic -- rows and column sum to the magic constant,
etc... I have included the testing code in testing.txt to show what was used to test without requiring any further installations in the project.  Note that as this was ad hoc
testing, I didn't worry much about efficiency or elegance, as this was a temporary solution just to ensure that the results were good.  Magic Squares from 3x3 to 100x100 were tested. 1x1 Magic
Squares are trivial and 2x2 don't exist.


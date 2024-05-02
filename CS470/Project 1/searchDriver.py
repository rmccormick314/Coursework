__author__ = "rlm443"

from projectOne import *
import time, math
from itertools import chain

def flatten(container):
    for i in container:
        if isinstance(i, (list,tuple)):
            for j in flatten(i):
                yield j
        else:
            yield i


fileobj=open( "twl06.txt" )         # Open dictionary
lines=[]                            # Convert words in dict to list
for line in fileobj:                # Iterate over lines in dict...
    lines.append( line.strip() )    # Strip whitespace and add to word list

lines = '\t'.join(lines).split()

def solveHelper( board, startNode, seq ):
    results = []
    hist = seq.copy()
    hist.append( startNode )

    test = examineState( startNode, board, hist )
    currentWord = test[0].lower()
    print( currentWord, end="\r" )

    if [value for value in lines if value[0:len(currentWord)] == currentWord.lower()]:
        moves = legalMoves( startNode, board, hist )

        if test[1] == "yes":
            print( end='\x1b[2K' )
            #print( "\r" + str(test[0]) )
            results.append( test[0] )

        for move in moves:
            pog = []
            pog.append( solveHelper( board, move, hist ) )
            if pog != []:
                results.append( pog )

    return results

def solveBoard( boardFile ):
    myBoard = loadBoard( boardFile )
    words = []

    for y in range( len( myBoard ) ):
        for x in range( len( myBoard ) ):
            print("called help init: (" + str(x) + "," + str(y) + ")")
            words.append( solveHelper( myBoard, ( x, y ), [] ) )

    words = flatten(words)
    words = set( [i for i in words if i != []] )
    print( words )

from translator import *
import dinobrain
import time
import sys

argc = len(sys.argv)
argv = sys.argv

print( f"Starting Dinoai with [{argc}] arguments: {str(argv)}" )

if(argc != 3 ):
    print("Provide the number of instances followed by the first display indentifier.\n")
    exit(1)

N = int( argv[1] )
firstDisplay = int( argv[2] )

print( f"\n\n==================== Starting DinoAI ====================\n" )
print( f"Batch size = {N}\n\n" )



pyhandlerInit( N, firstDisplay )

time.sleep(5)

print( pyhandlerGetObservation(1) ) 

# jump forever
while 1:
    for i in range(N):
        pyhandlerSetAction(i, 1) # up
        pyhandlerSetAction(i, 0) # none

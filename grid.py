import random
import tkinter
from tkinter import *

#Draw a grid using tkinter USED FOR TESTING
def DrawGrid(Board,EmptyBoard,GridSize,Objectives,Enemies):
    for x in range(GridSize):
        for y in range(GridSize):
            Canvas(height = 50, width= 50,  bg = 'blue').grid(row = x,column = y)
            #shows where the objectives and enemies are for testing 
            if Board[x][y] == 'E':
                Canvas(height = 50, width= 50,  bg = 'red').grid(row = x,column = y)
            if Board[x][y] == 'O':
                Canvas(height = 50, width= 50,  bg = 'green').grid(row = x,column = y)
            if Board[x][y] == 'X':
                Canvas(height = 50, width= 50,  bg = 'pink').grid(row = x,column = y)

#function to draw the grid used for playing
def DrawGrid2(Board,EmptyBoard,GridSize,Objectives,Enemies):
    for x in range(GridSize):
        for y in range(GridSize):
            Canvas(height = 50, width= 50,  bg = 'blue').grid(row = x,column = y)
    for x in range(GridSize):
        for y in range(GridSize):
            if EmptyBoard[x][y] == 'X':
                Canvas(height = 50, width= 50,  bg = 'pink').grid(row = x,column = y)

    Button(height = 2, width= 5,  bg = 'red' ,command = lambda :MovePlayerRight(EmptyBoard,GridSize)).grid(row = x+1,column = y-GridSize+1)
    Button(height = 2, width= 5,  bg = 'red' ,command = lambda :MovePlayerLeft(EmptyBoard,GridSize)).grid(row = x+1,column = y-GridSize+2)
    Button(height = 2, width= 5,  bg = 'red' ,command = lambda :MovePlayerDown(EmptyBoard,GridSize)).grid(row = x+1,column = y-GridSize+3)
    Button(height = 2, width= 5,  bg = 'red' ,command = lambda :MovePlayerUp(EmptyBoard,GridSize)).grid(row = x+1,column = y-GridSize+4)
    


def MovePlayerLeft(Board,GridSize):
    print('')
    x=99
    y=99
    size=len(Board)-1
    for i in range(size):
        for e in range(size):
            if Board[i][e]=='X':
                x=i
                y=e
    if y+1 > size:
        print('Error')
        print(x,y)
    else:
        print(x,y+1)
        Board[x][y+1]='X'
        Board[x][y]=' '
    DrawGrid2(Board,EmptyBoard,GridSize,Objectives,Enemies)

def MovePlayerDown(Board,GridSize):
    print('')
    x=99
    y=99
    size=len(Board)-1
    for i in range(size):
        for e in range(size):
            if Board[i][e]=='X':
                x=i
                y=e
    if x+1 > size or x+1 < 0:
        print('Error')
        print(x,y)
    else:
        print(x+1,y)
        Board[x+1][y]='X'
        Board[x][y]=' '
    DrawGrid2(Board,EmptyBoard,GridSize,Objectives,Enemies)

def MovePlayerUp(Board,GridSize):
    print('')
    x=99
    y=99
    size=len(Board)-1
    for i in range(size):
        for e in range(size):
            if Board[i][e]=='X':
                x=i
                y=e
    if x-1 > size or x-1 < 0:
        print('Error')
        print(x,y)
    else:
        print(x,y)
        Board[x-1][y]='X'
        Board[x][y]=' '
    DrawGrid2(Board,EmptyBoard,GridSize,Objectives,Enemies)

def MovePlayerRight(Board,GridSize):
    print('')
    x=99
    y=99
    size=len(Board)-1
    for i in range(size):
        for e in range(size):
            if Board[i][e]=='X':
                x=i
                y=e
    if y-1 > size or y-1 < 0:
        print('Error')
        print(x,y)
    else:
        Board[x][y-1]='X'
        Board[x][y]=' '
        print(x,y)
    DrawGrid2(Board,EmptyBoard,GridSize,Objectives,Enemies)

#Function to create two nested list to a set size like a grid
def CreateBoard(Board,EmptyBoard,GridSize,Objectives,Enemies):
    Board.clear()
    for i in range(GridSize):
        Board.append([' '] * GridSize )
        Board[0][0] = 'X'
    EmptyBoard.clear()
    for i in range(GridSize):
        EmptyBoard.append([' '] * GridSize )
        EmptyBoard[0][0] = 'X'


#Function to draw out the nested list line by line like a grid with saved values
#used for testing
def DrawBoard(Board,EmptyBoard,GridSize,Objectives,Enemies):
        for a in range(GridSize):
            for b in range(GridSize):
                print(' |', Board[a][b], end='' )
            print(' |','\n')
        print('Enemies:',Enemies)
        print('Objectives:',Objectives)
        print('Grid Size:',GridSize)
        #Menu(Board,EmptyBoard,GridSize,Objectives,Enemies)


#function to draw out an empty grid without any values in the squares
#used for playing the game with out seeing the values
def DrawEmptyBoard(Board,EmptyBoard,GridSize,Objectives,Enemies):
        for a in range(GridSize):
            for b in range(GridSize):
                print(' |', EmptyBoard[a][b], end='' )
            print(' |','\n')


#adds the enemies to the board
def AddEnemies(Board,EmptyBoard,GridSize,Objectives,Enemies):
        Count = 0
        while Count < Enemies:
            x = random.randint(0,GridSize-1)
            y = random.randint(0,GridSize-1)
            if Board[x][y] == 'E' or Board[x][y] == 'O' or Board[x][y] == 'X':
                Board[x][y] == ' '
            else:
                Board[x][y]='E'
                Count += 1


#Adds the objectives to the grid
def AddObjectives(Board,EmptyBoard,GridSize,Objectives,Enemies):
        Count = 0
        while Count < Objectives:
            x = random.randint(0,GridSize-1)
            y = random.randint(0,GridSize-1)
            if Board[x][y] == 'O' or Board[x][y] == 'E' or Board[x][y] == 'X':
                Board[x][y] == ' '
            else:
                Board[x][y]='O'
                Count += 1


#Menu used to run the functions For testing
def Menu(Board,EmptyBoard,GridSize,Objectives,Enemies):
    print('')
    choice = str(input('Please Choose An Option:'))
    if choice == '1':
        print('')
        CreateBoard(Board,EmptyBoard,GridSize,Objectives,Enemies)
    elif choice == '2':
        print('')
        DrawBoard(Board,EmptyBoard,GridSize,Objectives,Enemies)
    elif choice == '3':
        print('')
        DrawEmptyBoard(Board,EmptyBoard,GridSize,Objectives,Enemies)
    elif choice == '4':
        print('')
        AddEnemies(Board,EmptyBoard,GridSize,Objectives,Enemies)
    elif choice == '5':
        print('')
        AddObjectives(Board,EmptyBoard,GridSize,Objectives,Enemies)
    elif choice == '6':
        print('')
        DrawGrid(Board,EmptyBoard,GridSize,Objectives,Enemies)
    elif choice == 'q' or choice == 'Q':
        print('')
        ()
    else:
        print('')
        print('Please Choose A Valid Option \n')


#Constant values
GridSize = 7
Objectives = 10
Enemies = 5

#Creates the initial list before nesting
Board = []
EmptyBoard = []

Window = tkinter.Tk()
Window.title('Play Grid')
#Runs the initial function
#Menu(Board,EmptyBoard,GridSize,Objectives,Enemies)


#***********Function Names and Parameters************
#Menu(Board,EmptyBoard,GridSize,Objectives,Enemies)
#DrawGrid(Board,EmptyBoard,GridSize,Objectives,Enemies)
#AddObjectives(Board,EmptyBoard,GridSize,Objectives,Enemies)
#AddEnemies(Board,EmptyBoard,GridSize,Objectives,Enemies)
#CreateBoard(Board,EmptyBoard,GridSize,Objectives,Enemies)
#DrawEmptyBoard(Board,EmptyBoard,GridSize,Objectives,Enemies)
#DrawBoard(Board,EmptyBoard,GridSize,Objectives,Enemies)
#DrawGrid2(Board,EmptyBoard,GridSize,Objectives,Enemies)
#MovePlayer(Board,EmptyBoard,GridSize,Objectives,Enemies)


#The start up sequence
CreateBoard(Board,EmptyBoard,GridSize,Objectives,Enemies)
AddEnemies(Board,EmptyBoard,GridSize,Objectives,Enemies)
AddObjectives(Board,EmptyBoard,GridSize,Objectives,Enemies)
DrawBoard(Board,EmptyBoard,GridSize,Objectives,Enemies)
DrawEmptyBoard(Board,EmptyBoard,GridSize,Objectives,Enemies)
DrawGrid2(Board,EmptyBoard,GridSize,Objectives,Enemies)
DrawGrid(Board,EmptyBoard,GridSize,Objectives,Enemies)


Window.mainloop()



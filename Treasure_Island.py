from tkinter import *
import random



def key(event):
    global row
    global col
    global GridSize
    global Board
    global Taken
    global SaveSquare
    global Health
    global Key
    global Player
    global Score
    NewCol = col
    NewRow = row

    #detects the movements
    if event.char == event.keysym:
        if event.char == 'w':
            if row > 0:
                NewRow = row -1

        if event.char == 'a':
            if col > 0:
                NewCol = col -1

        if event.char == 's':
            if row < GridSize-1:
                NewRow = row +1

        if event.char == 'd':
            if col < GridSize-1:
                NewCol = col +1
                
    #checks if the player lands on a damage square
    if Board[NewRow][NewCol] == 2:
        Health -= 1
        Label(image=SpikesImg ,borderwidth=0,highlightthickness=0).grid(row=NewRow,column=NewCol)
        Player.destroy()
        Player = Canvas(height = SquareSize, width= SquareSize, highlightthickness=0)
        Player.create_image(0, 0, image=pimg, anchor=NW)
        Player.grid(column = col, row = row)
        PopUpWindow('You Stepped on a SPIKE and lost some Health')

    #checks if the player has landed on a key   
    if Board[NewRow][NewCol] == 1:
        if  Key == False:
            Key = True
            Board[NewRow][NewCol] = ' '
            PopUpWindow('You found a KEY and put it in your BAG')
            Label(image=BlankImg,borderwidth=0,highlightthickness=0).grid(row=NewRow,column=NewCol)
        else:
            PopUpWindow('You found a KEY but you can only hold one KEY at a time')
            Img = random.choice(KeyImg)
            Label(image=Img ,borderwidth=0,highlightthickness=0).grid(row=NewRow,column=NewCol)
        Player.destroy()
        Player = Canvas(height = SquareSize, width= SquareSize, highlightthickness=0)
        Player.create_image(0, 0, image=pimg, anchor=NW)
        Player.grid(column = col, row = row)

    #checks if the player has landed on a chest
    if Board[NewRow][NewCol] == 0:
        Label(image=ChestImg ,borderwidth=0,highlightthickness=0).grid(row=NewRow,column=NewCol)
        if Key == True:
            PopUpWindow('You found the TREASURE CHEST and try the KEY in the lock')
            unlock = random.randint(0,1)
            if unlock == 0:
                Label(image=Chest_OImg ,borderwidth=0,highlightthickness=0).grid(row=NewRow,column=NewCol)
                Board[NewRow][NewCol] = ' '
                PopUpWindow('The KEY worked and you found the TREASURE inside')
                Score +=1
            else:
                PopUpWindow('Oh No, the KEY failed, try find the correct one')
                Key = False
        else:
            PopUpWindow('You found the TREASURE CHEST try find its KEY!')
        Player.destroy()
        Player = Canvas(height = SquareSize, width= SquareSize, highlightthickness=0)
        Player.create_image(0, 0, image=pimg, anchor=NW)
        Player.grid(column = col, row = row)
        
    #checks if the player has landed on a Health Power up
    if Board[NewRow][NewCol] == 3:
        Board[NewRow][NewCol] = ' '
        Health +=1
        Label(image=BlankImg ,borderwidth=0,highlightthickness=0).grid(row=NewRow,column=NewCol)
        PopUpWindow('You found A HEALTH PACK and it increased your HEALTH')
        Player.destroy()
        Player = Canvas(height = SquareSize, width= SquareSize, highlightthickness=0)
        Player.create_image(0, 0, image=pimg, anchor=NW)
        Player.grid(column = col, row = row)        
        

    #saves the placeholder in the square when the plater overwrites it
    if Taken == True:
        Board[row][col] = SaveSquare
    else:
        Board[row][col] = ' '
    if Board[NewRow][NewCol] != ' ':
        Taken = True
        SaveSquare = Board[NewRow][NewCol]
    else:
        Taken = False
        SaveSquare = ' '

    #prints the square statis for testing
    #print(Taken, SaveSquare)
    Board[NewRow][NewCol] = 'X'
    col = NewCol
    row = NewRow

    #displays the grid and other infomation for testing
    #for a in range(GridSize):
        #for b in range(GridSize):
            #print(' |', Board[a][b], end='' )
        #print(' |','\n')
    #print('Key:',Key)
    #print('Health:',Health)
    #print('#####'*GridSize)
    Player.grid(column = col, row = row)
    Player.update()

    #checks the win conditionss
    if Health <= 0:
        PopUpWindow('You sustained too many injuries and DIED, GAME OVER!')
        Window.destroy()
    if Score >= 3:
        PopUpWindow('CONGRATS YOU FOUND ALL 3 TREASURES AND WON!')
        Window.destroy()

def PopUpWindow(InfoText):
    global Health
    global Key
    global Open
    global Window1
    if Open == True:
        Window1.destroy()
        Open = False
    Window1 = Tk()
    Window1.title('Alert')
    Label(Window1, text=InfoText).grid(row=1,column=1, columnspan=3)
    Label(Window1, text='Health:').grid(row=2,column=1, columnspan=2)
    Label(Window1, text=Health).grid(row=2,column=3)
    Label(Window1, text='Key:').grid(row=3,column=1, columnspan=2)
    Label(Window1, text=Key).grid(row=3,column=3)
    Button(Window1, text='Ok!',command = lambda:CloseWindow(Window1)).grid(row=4,column=1, columnspan=3)
    Open = True
    
def CloseWindow(Window1):
    global Open
    Open = False
    Window1.destroy()
        
#defines initial variables
Board=[]
GridSize = 16 #min8 max16
SquareSize = 40
row = random.randint(0,GridSize-1)
col = random.randint(0,GridSize-1)
Drops = GridSize*5
Taken = False
Health = 5
Key = False
Score = 0
Open = False

#creates the Tk window
Window = Tk()
Window.title('Treasure Island')

#sets all the images
SquaresImg = [PhotoImage(file='SmallBush.png'),PhotoImage(file='Flowers.png'),PhotoImage(file='Rock.png'),PhotoImage(file='Mushroom.png'),
PhotoImage(file='Blank.png'),PhotoImage(file='Blank.png'),PhotoImage(file='Blank.png'),PhotoImage(file='Blank.png'),PhotoImage(file='Blank.png')]
BushImg = PhotoImage(file='Bush.png')
KeyImg =  [PhotoImage(file='Key.png'),PhotoImage(file='Key1.png'),PhotoImage(file='Key2.png')]
BlankImg = PhotoImage(file='Blank.png')
GrassImg = PhotoImage(file='Grass.png')
ChestImg = PhotoImage(file='Chest.png')
Chest_OImg = PhotoImage(file='Chest_Open.png')
SpikesImg = PhotoImage(file='Spikes.png')

#creates the main canvas to size the window
Area = Canvas(Window)
Area.config(width=GridSize*SquareSize, height=GridSize*SquareSize, highlightthickness=0)  
Area.create_image(0, 0, image=GrassImg, anchor=NW)
Area.grid(column = 0, row = 0,rowspan=GridSize,columnspan=GridSize)
           
#creates a nested list
Board = []
for i in range(GridSize):
    Board.append([' '] * GridSize )
Board[row][col] = 'X'

#adds the drops to the board
count = 0
while count <= Drops:
    Temprow = random.randint(0,GridSize-1)
    Tempcol = random.randint(0,GridSize-1)
    if Board[Temprow][Tempcol] == ' ':
        drop = random.randint(1,6)
        Board[Temprow][Tempcol] = drop
        count+=1

#adds the objective to the board
Objective = 0
while Objective < 3:
    Temprow = random.randint(0,GridSize-1)
    Tempcol = random.randint(0,GridSize-1)
    if Board[Temprow][Tempcol] == ' ':
        Board[Temprow][Tempcol] = 0
        Objective += 1

#reads the board and creats widgets depending on the contents of each square
for x in range(0,GridSize):
    for y in range(0,GridSize):
        if Board[x][y] != ' ' and Board[x][y] != 'X':
            Label(image=BushImg,borderwidth=0,highlightthickness=0).grid(row=x,column=y)
        else:
            Img = random.choice(SquaresImg)
            Label(image=Img,borderwidth=0,highlightthickness=0).grid(row=x,column=y)
                 
#adds the player to the tk grid
global Player
pimg = PhotoImage(file='Player.png')
Player = Canvas(height = SquareSize, width= SquareSize, highlightthickness=0)
Player.create_image(0, 0, image=pimg, anchor=NW)
Player.grid(column = col, row = row)
              
Window.bind_all('<Key>', key)
Window.mainloop()

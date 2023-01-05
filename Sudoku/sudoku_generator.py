import math
import random

class SudokuGenerator:
    #initializes many variables, and creates a 2d (nested) list which is meant to represent a grid
    def __init__(self, row_length, removed_cells):
        self.row_length = row_length
        self.removed_cells = removed_cells
        self.box_length = int(math.sqrt(self.row_length))
        self.board = []
        for length in range(self.row_length * self.row_length):
            self.board.append(0)
        board = []
        for i in range(self.row_length):
            board.insert(i, self.board[(i * self.row_length):(self.row_length + i * self.row_length)])
        self.board = board

    #returns a nested list of values which represents the grid
    def get_board(self):
        return self.board

    #prints the board to the console
    @staticmethod
    def print_board(x):
        list = x
        for row in list:
            line = " ".join([str(item) for item in row])
            print(line)

    #returns true if the num inputed is not repeated within the row
    def valid_in_row(self, row, num):
        for col in range(self.row_length):
            if num == self.board[row][col]:
                return False
        return True

    #returns true if the num inputed is not repeated within the column
    def valid_in_col(self, col, num):
        # print("")
        # SudokuGenerator.print_board(self.board)
        for row in range(self.row_length):
            if num == self.board[row][col]:
                return False
        return True

    #returns true if the num inputed is not repeated within the column
    def valid_in_box(self, row_start, col_start, num):
        for row in range(row_start, row_start + 3):
            for col in range(col_start, col_start + 3):
                if num == self.board[row][col]:
                    return False
        return True

    #returns true if the num inputed is not repeated within the row, column, or box
    def is_valid(self, row, col, num):
        check_row = self.valid_in_row(row, num)
        check_col = self.valid_in_col(col, num)
        check_box = self.valid_in_box(((row // 3) * 3), ((col // 3) * 3), num)
        if check_row == True and check_col == True and check_box == True:
            return True
        return False

    #randomly fills in values in the 3x3 box from
    def fill_box(self, row_start, col_start):
        #makes a list of 9 random ints b/w 1-9
        list = []
        list.append(random.randint(1,9))
        while len(list) < 9:
            placeholder = random.randint(1,9)
            if placeholder not in list:
                list.append(placeholder)

        #replaces 3x3 section w/ unique numbers
        for row in range(row_start, row_start + 3):
            for col in range(col_start, col_start + 3):
                self.board[row][col] = list.pop()

    #fills the three boxes along the main diagonal of the board
    def fill_diagonal(self):
      self.fill_box(0, 0)
      self.fill_box(3, 3)
      self.fill_box(6, 6)

    #this will return a completely filled board
    def fill_remaining(self, row, col):
        if (col >= self.row_length and row < self.row_length - 1):
            row += 1
            col = 0
        if row >= self.row_length and col >= self.row_length:
            return True
        if row < self.box_length:
            if col < self.box_length:
                col = self.box_length
        elif row < self.row_length - self.box_length:
            if col == int(row // self.box_length * self.box_length):
                col += self.box_length
        else:
            if col == self.row_length - self.box_length:
                row += 1
                col = 0
                if row >= self.row_length:
                    return True

        for num in range(1, self.row_length + 1):
            if self.is_valid(row, col, num):
                self.board[row][int(col)] = num
                if self.fill_remaining(row, col + 1):
                    return True
                self.board[row][int(col)] = 0
        return False

    #it constructs a solution by calling fill_diagonal and fill_remaining.
    def fill_values(self):
        self.fill_diagonal()
        self.fill_remaining(0, int(self.box_length))
        return self.board

    #This method removes the appropriate number of cells from the board
    def remove_cells(self):
        i = 0
        while i < self.removed_cells:
            col_number = random.randint(0, 8)
            row_number = random.randint(0, 8)
            if self.board[col_number][row_number] != 0:
                self.board[col_number][row_number] = 0
                i = i + 1
            else:
                continue
        return self.board

#This function should just call the constructor and appropriate methods from the SudokuGenerator class
def generate_sudoku(size, removed):
    sudoku = SudokuGenerator(size, removed)
    sudoku.fill_values()
    answer1 = tuple(sudoku.get_board())
    answer = []
    for item in answer1:
        answer.append(tuple(item))
    sudoku.remove_cells()
    board = sudoku.get_board()
    reset1= tuple(sudoku.get_board())
    reset = []
    for item in reset1:
        reset.append(tuple(item))
    original_board = sudoku.get_board()
    return board, answer, reset


# print(bird)
# cow, pig = generate_sudoku(9, 30)
#
# SudokuGenerator.print_board(cow)
# print("")
# SudokuGenerator.print_board(pig)
# print("")
# pig = [list(l) for l in pig]
# SudokuGenerator.print_board(pig)



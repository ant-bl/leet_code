from pprint import pprint
from typing import List


class Board:

    def __init__(self, board):
        self.board = board
        # if number - 1 is available at self.cols[x]
        self.cols = [[True for _ in range(9)] for _ in range(9)]
        # if number - 1 is available at self.rows[x]
        self.rows = [[True for _ in range(9)] for _ in range(9)]
        # if number - 1 is available at self.squares[row_id][col_id]
        self.squares = [[[True for _ in range(9)] for _ in range(3)] for _ in range(3)]

        for row_idx, row in enumerate(self.board):
            for col_idx, cell in enumerate(row):
                if cell == ".":
                    continue

                ncell = int(cell) - 1

                self.cols[col_idx][ncell] = False
                self.rows[row_idx][ncell] = False

                square_row_idx = int(row_idx / 3)
                square_col_idx = int(col_idx / 3)
                self.squares[square_row_idx][square_col_idx][ncell] = False

    def __str__(self):
        s = ""
        for row_idx, row in enumerate(self.board):
            for col_idx, cell in enumerate(row):
                s += cell + " "
            s += "\n"
        return s

    def is_valid(self):

        cols = [{} for _ in range(9)]
        rows = [{} for _ in range(9)]
        squares = [[{} for _ in range(3)] for _ in range(3)]

        for row_idx, row in enumerate(self.board):
            for col_idx, cell in enumerate(row):
                if cell in rows[row_idx]:
                    return False
                rows[row_idx][cell] = True

                if cell in cols[col_idx]:
                    return False
                cols[col_idx][cell] = True

                square_row_idx = int(row_idx / 3)
                square_col_idx = int(col_idx / 3)
                if cell in squares[square_row_idx][square_col_idx]:
                    return False
                squares[square_row_idx][square_col_idx][cell] = True

        return True

    def progress(self):

        num_fill = 0

        for row_idx, row in enumerate(self.board):
            for col_idx, cell in enumerate(row):
                if cell != ".":
                    num_fill += 1

        return num_fill / (9 * 9) * 100

    def available_chars(self, row_idx, col_idx):
        for c in range(0, 9):
            if not self.cols[col_idx][c]:
                continue
            if not self.rows[row_idx][c]:
                continue

            square_row_idx = int(row_idx / 3)
            square_col_idx = int(col_idx / 3)

            if not self.squares[square_row_idx][square_col_idx][c]:
                continue

            yield str(c + 1)

    def fix_char(self, row_idx, col_idx, cell):
        ncell = int(cell) - 1
        assert self.board[row_idx][col_idx] == "."
        assert cell in self.available_chars(row_idx, col_idx)

        square_row_idx = int(row_idx / 3)
        square_col_idx = int(col_idx / 3)

        self.board[row_idx][col_idx] = str(ncell + 1)
        self.cols[col_idx][ncell] = False
        self.rows[row_idx][ncell] = False
        self.squares[square_row_idx][square_col_idx][ncell] = False

    def unfix_char(self, row_idx, col_idx):
        assert self.board[row_idx][col_idx] != "."
        ncell = int(self.board[row_idx][col_idx]) - 1

        square_row_idx = int(row_idx / 3)
        square_col_idx = int(col_idx / 3)

        self.board[row_idx][col_idx] = "."
        self.cols[col_idx][ncell] = True
        self.rows[row_idx][ncell] = True
        self.squares[square_row_idx][square_col_idx][ncell] = True

    def empty_cell(self):
        for row_idx, row in enumerate(self.board):
            for col_idx, col in enumerate(row):
                if self.board[row_idx][col_idx] == ".":
                    return row_idx, col_idx
        return None, None

    def solve(self):

        # print(f"{self.progress()}")

        row_idx, col_idx = self.empty_cell()

        if row_idx is None:
            return True

        possible_chars = list(self.available_chars(row_idx, col_idx))
        if len(possible_chars) == 0:
            return None

        for c in possible_chars:
            self.fix_char(row_idx, col_idx, c)

            assert self.board[row_idx][col_idx] == c
            assert c not in list(self.available_chars(row_idx, col_idx))

            if self.solve():
                return True
            else:
                self.unfix_char(row_idx, col_idx)

        return None


class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        bo = Board(board)

        assert bo.solve()

        for row_idx, row in enumerate(bo.board):
            for col_idx, col in enumerate(row):
                board[row_idx][col_idx] = bo.board[row_idx][col_idx]


def test_1():
    resolve_board = [
        ["5", "3", ".", ".", "7", ".", ".", ".", "."],
        ["6", ".", ".", "1", "9", "5", ".", ".", "."],
        [".", "9", "8", ".", ".", ".", ".", "6", "."],
        ["8", ".", ".", ".", "6", ".", ".", ".", "3"],
        ["4", ".", ".", "8", ".", "3", ".", ".", "1"],
        ["7", ".", ".", ".", "2", ".", ".", ".", "6"],
        [".", "6", ".", ".", ".", ".", "2", "8", "."],
        [".", ".", ".", "4", "1", "9", ".", ".", "5"],
        [".", ".", ".", ".", "8", ".", ".", "7", "9"]
    ]

    bb = Board(resolve_board)
    print(bb)
    bb.solve()
    assert bb.is_valid()


def test_2():
    resolve_board = [
        [".", ".", ".", ".", ".", "7", ".", ".", "9"],
        [".", "4", ".", ".", "8", "1", "2", ".", "."],
        [".", ".", ".", "9", ".", ".", ".", "1", "."],
        [".", ".", "5", "3", ".", ".", ".", "7", "2"],
        ["2", "9", "3", ".", ".", ".", ".", "5", "."],
        [".", ".", ".", ".", ".", "5", "3", ".", "."],
        ["8", ".", ".", ".", "2", "3", ".", ".", "."],
        ["7", ".", ".", ".", "5", ".", ".", "4", "."],
        ["5", "3", "1", ".", "7", ".", ".", ".", "."]
    ]

    bb = Board(resolve_board)
    print(bb)
    bb.solve()
    assert bb.is_valid()


if __name__ == "__main__":
    test_1()
    test_2()

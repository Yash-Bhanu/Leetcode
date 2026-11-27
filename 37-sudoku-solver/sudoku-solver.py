class Solution:
    def solveSudoku(self, board: list[list[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """


        # Build data for investigation

        # declare all the necessary hashmaps and lists
        BITPOS = {1 << i: i + 1 for i in range(9)}
        boxcal = [[] for _ in range(9)]
        rows = [511 for _ in range(9)]
        cols = [511 for _ in range(9)]
        boxes = [511 for _ in range(9)]
        bcells = [[-1] * 9 for _ in range(9)]
        btrack = set()

        # Function to turn a bitmask to a set of numbers
        def masktolist(mask: int):
            rs = []
            while mask > 0:
                rs.append(mask & (-mask))
                mask &= (mask - 1)
            return rs

        for row in range(9):
            for col in range(9):
                val = board[row][col]
                box = (row // 3) * 3 + (col // 3)
                boxcal[row].append(box)
                # add blank cells to corresponding list
                if board[row][col] == ".":
                    btrack.add((row, col))
                    continue

                val = 1 << (int(val) - 1)
                # remove the digits already existed from current row, col, box
                rows[row] &= ~val
                cols[col] &= ~val
                boxes[box] &= ~val
        
        # note the possible digits for each of the blank cells
        mindigit, frow, fcol = 10, -1, -1

        for row, col in btrack:
            possible = rows[row] & cols[col] & boxes[boxcal[row][col]]
            bcells[row][col] = possible
            # find the cell with least possible choice(s)
            nbit1 = possible.bit_count()
            if mindigit > nbit1:
                mindigit = nbit1
                frow, fcol = row, col
        
        # Fill in the empty cells:
        result = []
        finished = False

        def fill_in_cells(row, col):
            nonlocal finished
            if not btrack:
                finished = True
                print("finished")
                return
            
            print(f"check ({row},{col})")
            # fill cell (row, col) with val and remove it from the blank cell tracker btrack:
            candidates = masktolist(bcells[row][col])
            print(f"candidates are {candidates}")
            btrack.discard((row, col))
            for val in candidates:
                print(f"try {val}")
                rows[row] &= ~val
                cols[col] &= ~val
                boxes[boxcal[row][col]] &= ~val
                mindigit, frow, fcol = 10, -1, -1
                for r, c in btrack:
                    # remove the val filled from notes of all cells in the same row, col and box
                    possible = rows[r] & cols[c] & boxes[boxcal[r][c]]
                    bcells[r][c] = possible
                    # find the next cell with least possible choice(s)
                    nbit1 = possible.bit_count()
                    if mindigit > nbit1:
                        mindigit = nbit1
                        frow, fcol = r, c
                if mindigit > 0:
                    fill_in_cells(frow, fcol)
                    if finished:
                        result.append((row, col, BITPOS[val]))
                        print(f"fill ({row},{col}) with {val}")
                        return
                rows[row] |= val
                cols[col] |= val
                boxes[boxcal[row][col]] |= val
            # reset the status
            btrack.add((row, col))
            
        
        fill_in_cells(frow, fcol)

        for row, col, val in result:
            board[row][col] = str(val)
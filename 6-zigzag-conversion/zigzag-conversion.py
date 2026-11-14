class Solution(object):
    def convert(self, s, numRows):
        n = len(s)
        if numRows == 1 or numRows >= n:
            return s

        step = 2 * (numRows - 1)
        res = [s[0::step]]

        for i in range(1, numRows - 1):
            down = s[i::step]
            up = s[step - i::step]
            row = [''] * (len(down) + len(up))
            row[0::2] = down
            row[1::2] = up
            res.append(''.join(row))

        res.append(s[numRows - 1::step])
        return ''.join(res)
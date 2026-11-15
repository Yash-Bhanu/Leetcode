class Solution(object):
    def myAtoi(self, s):
        INT_MAX = 2**31 - 1
        INT_MIN = -2**31
        
        i = 0
        n = len(s)
        

        while i < n and s[i] == ' ':
            i += 1
            
        if i == n:
            return 0
            

        sign = 1
        if s[i] == '-':
            sign = -1
            i += 1
        elif s[i] == '+':
            i += 1
            

        res = 0
        while i < n and '0' <= s[i] <= '9':

            digit = ord(s[i]) - ord('0')
            if res > (INT_MAX - digit) // 10:
                return INT_MAX if sign == 1 else INT_MIN
                
            res = res * 10 + digit
            i += 1
            
        return sign * res
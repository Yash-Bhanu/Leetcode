
#include <stdbool.h>
#include <string.h>

bool dfs(char** board, int m, int n, char* word,
         int r, int c, int k, int len, bool rev) {

    if (r < 0 || c < 0 || r >= m || c >= n)
        return false;

    char ch = word[rev ? len - 1 - k : k];

    if (board[r][c] != ch)
        return false;

    if (k == len - 1)
        return true;

    char temp = board[r][c];
    board[r][c] = '#';

    bool found =
        dfs(board, m, n, word, r+1, c, k+1, len, rev) ||
        dfs(board, m, n, word, r-1, c, k+1, len, rev) ||
        dfs(board, m, n, word, r, c+1, k+1, len, rev) ||
        dfs(board, m, n, word, r, c-1, k+1, len, rev);

    board[r][c] = temp;

    return found;
}

bool exist(char** board, int boardSize,
           int* boardColSize, char* word) {

    int m = boardSize;
    int n = boardColSize[0];
    int len = strlen(word);

    if (len > m * n)
        return false;

    int freq[128] = {0};
    int need[128] = {0};

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            freq[(unsigned char)board[i][j]]++;

    for (int i = 0; i < len; i++) {
        unsigned char ch = word[i];
        need[ch]++;

        if (need[ch] > freq[ch])
            return false;
    }

    bool rev = freq[(unsigned char)word[0]] >
               freq[(unsigned char)word[len-1]];

    char start = rev ? word[len-1] : word[0];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == start &&
                dfs(board, m, n, word, i, j, 0, len, rev))
                return true;
        }
    }

    return false;
}

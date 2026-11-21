
import java.util.*;

class Solution {
    public List<String> letterCombinations(String digits) {
        List<String> result = new ArrayList<>();

        if (digits.length() == 0) {
            return result;
        }

        String[] map = {
            "", "", "abc", "def", "ghi",
            "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        solve(digits, 0, "", map, result);
        return result;
    }

    void solve(String digits, int index, String str,
               String[] map, List<String> result) {

        if (index == digits.length()) {
            result.add(str);
            return;
        }

        int num = digits.charAt(index) - '0';

        for (char ch : map[num].toCharArray()) {
            solve(digits, index + 1, str + ch, map, result);
        }
    }
}

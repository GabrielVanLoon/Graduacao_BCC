// Link: https://www.hackerrank.com/challenges/balanced-brackets/problem

string isBalanced(string s) {
    stack<char> st;
    
    for(int i = 0; i < s.size(); i++){
        char c = s.at(i);
        
        if(c == '(' || c == '[' || c == '{'){
            st.push(c);
        } else if( !st.empty() && ((c == ')' && st.top() == '(') 
                    || (c == '}' && st.top() == '{') 
                    || (c == ']' && st.top() == '['))) { 
            st.pop();
        } else {
            return "NO";
        }
    }
    return st.empty() ? "YES" : "NO";
}
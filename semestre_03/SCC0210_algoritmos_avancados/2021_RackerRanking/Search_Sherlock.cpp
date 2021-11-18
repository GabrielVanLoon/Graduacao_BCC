// https://www.hackerrank.com/challenges/sherlock-and-array/problem

string balancedSums(vector<int> arr) {
    vector<int> lSum;
    int total_sum = 0;
    
    for(int i = 0; i < arr.size(); i++){
        lSum.push_back(total_sum);
        total_sum += arr[i];    
    }
    lSum.push_back(total_sum);
    
    
    for(int i = 0; i < arr.size(); i++){
        if(lSum[i] == (total_sum-lSum[i+1]))
            return "YES";
    }
    
    return "NO";
}
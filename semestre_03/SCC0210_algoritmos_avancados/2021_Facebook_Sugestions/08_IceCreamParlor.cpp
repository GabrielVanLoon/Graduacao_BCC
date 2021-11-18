// Link: https://www.hackerrank.com/challenges/icecream-parlor/problem

vector<int> icecreamParlor(int m, vector<int> arr) {
    map<int, int> past;
    vector<int> flavors;
    
    for(int i = 0; i < arr.size(); i++){
        int cost = arr[i], diff = m-arr[i];
        
        if( past.count(diff) != 0) { 
            flavors.push_back(past[diff]);
            flavors.push_back(i+1);
            break;
        } else{
            past.insert(pair<int,int>(cost, i+1));
        } 
    }
    return flavors;
}
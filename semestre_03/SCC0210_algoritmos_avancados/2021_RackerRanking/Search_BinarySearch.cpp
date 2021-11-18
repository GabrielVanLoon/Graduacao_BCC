// Link: https://www.hackerrank.com/challenges/tutorial-intro/problem

int introTutorial(int V, vector<int> arr) {
    int l = 0, r = arr.size()-1, m = 0;
    
    while(l <= r){ 
        m = (l+r)/2;
        
        if(arr[m] == V) return m;
        else if(V <= arr[m]) r = m-1;
        else l = m+1;     
    }
    
    return -1;
}
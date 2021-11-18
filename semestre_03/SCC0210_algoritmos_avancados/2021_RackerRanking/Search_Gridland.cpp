// Link: 

// Obs: a logica está certa mas tem algum bug ainda nos calculos :c

int gridlandMetro(int n, int m, int k, vector<vector<int>> track) {
    
    long totalTiles = n*m, trainTiles = 0;
    int  lastMarked = 0;
     
    // if there is no track just return totalTiles
    if(k ==0)
        return totalTiles;
    
    // Lets sort the vector to garantee they are in ascending row and c1
    auto trackSort = [](const vector<int>& a, const vector<int>& b) {        
        if(a[0] < b[0]) return true;
        if(a[0] > b[0]) return false;
        if(a[1] < b[1]) return true;
        if(a[1] > b[1]) return false;
        if(a[2] < b[2]) return true;
        if(a[2] > b[2]) return false;
        return true;
    };
    
    // Do the tracking sorting using the custom function
    sort(track.begin(), track.end(), trackSort);
    
    for(int i = 0; i < track.size(); i++){
        for(int j = 0; j <= 2; j++) 
            cout << track[i][j] << ' ';
        cout << endl;
    }
    
    // Pre-compute the first track size
    trainTiles = track[0][2] - track[0][1] + 1;
    lastMarked = track[0][2];
    
    // cout << track[0][1] << ' ' << trainTiles << endl;
    for(int i = 1; i < k; i++){
        
        // if last track is in different row, just add the current
        if(track[i][0] != track[i-1][0]){
            trainTiles += track[i][2] - track[i][1] + 1;
            lastMarked =  track[i][2];
        
        // 1 case: if they are disjunct tracks
        } else if(lastMarked < track[i][1]) { 
            trainTiles += track[i][2] - track[i][1] + 1;
            lastMarked =  track[i][2];
        
        // 2 case: last track contain current track
        } else if (lastMarked >= track[i][2]){
            //do nothing
        
        // 3 case: last track intersect a prefix of the current track
        } else { 
            trainTiles += track[i][2] - (lastMarked + 1) + 1;
            lastMarked =  track[i][2];
        }
        // cout << trainTiles << endl;
    }
    
    return totalTiles - trainTiles;
}
# Link: https://www.hackerrank.com/challenges/ctci-array-left-rotation/problem

vector<int> rotLeft(vector<int> a, int d) {
    vector<int> aRot;
    aRot.resize(a.size());
    
    for(int i = 0; i < a.size(); i++){
        aRot[i] = a[(i+d)%a.size()];
    }
    return aRot;
}
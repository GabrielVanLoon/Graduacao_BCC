# Link: https://www.hackerrank.com/challenges/designer-pdf-viewer/problem


int designerPdfViewer(vector<int> h, string word) {
    int maxHeight = 1;
    int charIndex = 0;
    
    for(int i = 0; i < word.size(); i++){
        charIndex = word.at(i)-int('a');
        maxHeight = (h[charIndex] > maxHeight) ? h[charIndex] : maxHeight;
    }
    return maxHeight * word.size();
}
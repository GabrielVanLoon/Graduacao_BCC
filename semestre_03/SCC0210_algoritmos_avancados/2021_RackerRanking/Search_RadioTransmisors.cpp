// Link: https://www.hackerrank.com/challenges/hackerland-radio-transmitters/problem

int hackerlandRadioTransmitters(vector<int> x, int k) {
    int maxCoverage = -1, ans = 0, i = 0, n = x.size();
    
    sort(x.begin(), x.end());
    
    // Solucao errada - pode haver antenas apenas no telhados de casas
    // for(int i = 0; i < x.size(); i++){
    //     if(x[i] > maxCoverage){
    //         ans += 1;
    //         maxCoverage = x[i] + (2*k);
    //     }
    // }
    
    while(i < n){
        // Adiciona uma antena nova
        ans += 1;
        maxCoverage = x[i++] + k;
        // Busca a casa mais a direita possivel atek blocos de distancia
        while(i < n && x[i] <= maxCoverage) i++;
        // Essa casa vai ter o transmissor
        maxCoverage = x[--i] + k;
        // Ignora casas cobertas pela direita do transmissor
        while(i < n && x[i] <= maxCoverage) i++;
    }
 
    return ans;
}
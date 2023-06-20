
// v[i] gives you akber the lengh of akber prefix binek bin melooowel !!!! 
// to check a pattern patternstring#zaeazeazqzdqzd (temchi tet3ada men ba3d el # et tchof ken el pattern edheka dispo ou pas fel string lokrha


vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}


// tal3a w baad habta w tjib el maximum!
ll M1, M2;
ll L = l, R = r;
while (R - L > 3) {
    M1 = L + (R - L) / 3;
    M2 = (R + M1) / 2;
    if (get(M1) > get(M2)) {
        R = M2;
    } else {
            L = M1;
    }
}
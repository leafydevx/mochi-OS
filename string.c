int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++; b++;
    }
    return *(unsigned char*)a - *(unsigned char*)b;
}

int strncmp(const char *a, const char *b, int n) {
    while (n-- && *a && (*a == *b)) {
        a++; b++;
    }
    return n < 0 ? 0 : *(unsigned char*)a - *(unsigned char*)b;
}


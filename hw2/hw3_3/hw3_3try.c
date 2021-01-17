#include <stdio.h>
#include <string.h>

char *suffixArray[200000]; //放字串排列
char *sub_suffixArray[200000]; //在merge的時候幫忙記東西的陣列
int movePlace[200000]; //移動幾個字串後的suffix
int sub_movePlace[200000]; //幫忙記東西

void sort(int start, int end, int char_place);
void merge(int one[], int two[], int reOne[], int reTwo[], int start, int end);

int main()
{
    int pair;
    scanf("%d", &pair);
    while (pair != 0) {
        char sen[100001], sen1[100001];
        scanf("%s%s", sen, sen1);
        int len, len1, totalLen;
        len = strlen(sen);
        len1 = strlen(sen1);
        totalLen = len + len1;
        strcat(sen, sen1); //printf("%s\n", sen1);
        // make the two strings together

        int i;
        for (i = 0; i < totalLen; i++) {
            suffixArray[i] = &sen[i];
            movePlace[i] = i;
        } //int j; for (i = 0; i < totalLen; i++) { for (j = 0; j < totalLen - i; j++) { printf("%c", *(suffixArray[i] + j)); } printf("\n"); } for (j = 0; j < totalLen; j++) { printf("%d\n", cut[j]); }
        
        printf("%d\n", totalLen);
        sort(0, totalLen - 1, 0);
        pair--;
    }
    return 0;
}

void sort(int start, int end, int char_place) {
    //*suffixArray[] 要比較大小的字串陣列
    //start 要比較大小範圍的開始
    //end 要比較大小範圍的結束
    //char_place 要開始比較的位置
    printf("%d %d %d\n", start, end, char_place);
    int len;
    len = end - start + 1;
    int one[len], two[len], reOne[len], reTwo[len];
    int i;
    for (i = start; i <= end; i++) {
        one[i] = *(suffixArray[i] + char_place) - 'a';
        if (*(suffixArray[i] + char_place + 1) == '\0') {
            two[i] = -1; //位置的數字如果是-1代表說是空的
        }
        else {
            two[i] = *(suffixArray[i] + char_place + 1) - 'a';
        }
    }
    merge(one, two, reOne, reTwo, start, end);
    for (i = start; i <= end; ) {
        int how_many = 0;
        while (one[i] == one[i + how_many + 1] && two[i] == two[i + how_many + 1]) {
            how_many++;
            if (i + how_many + 1 > end) {
                break;
            }
        }
        if (how_many >= 1) {
            sort(i, i + how_many, char_place + 2);
            i += how_many;
        }
        else {
            i++;
        }
    }
    return;
}

void merge(int one[], int two[], int reOne[], int reTwo[], int start, int end) {
    //reOne[], reTwo[]是要拿來裝新的one[], two[]
    if (start >= end)
        return;
    int len = end - start + 1;
    int mid = (start + end)/2;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge(one, two, reOne, reTwo, start1, end1);
    merge(one, two, reOne, reTwo, start2, end2);
    int i = start;
    while (start1 <= end1 && start2 <= end2) {
        if (one[start1] < one[start2]) {
            reOne[i] = one[start1];
            reTwo[i] = two[start1]; 
            sub_suffixArray[i] = suffixArray[start1];
            sub_movePlace[i] = movePlace[start1];
            start1++;
        }
        else if (one[start1] > one[start2]) {
            reOne[i] = one[start2];
            reTwo[i] = two[start2];
            sub_suffixArray[i] = suffixArray[start2];
            sub_movePlace[i] = movePlace[start2];
            start2++;
        }
        else {
            if (two[start1] < two[start2]) {
                reOne[i] = one[start1];
                reTwo[i] = two[start1];
                sub_suffixArray[i] = suffixArray[start1];
                sub_movePlace[i] = movePlace[start1];
                start1++;
            }
            else {
                reOne[i] = one[start2];
                reTwo[i] = two[start2];
                sub_suffixArray[i] = suffixArray[start2];
                sub_movePlace[i] = movePlace[start2];
                start2++;
            }
        }
        i++;
    }
    while (start1 <= end1) {
        reOne[i] = one[start1];
        reTwo[i] = two[start1];
        sub_suffixArray[i] = suffixArray[start1];
        sub_movePlace[i] = movePlace[start1];
        i++;
        start1++;
    }
    while (start2 <= end2) {
        reOne[i] = one[start2];
        reTwo[i] = two[start2];
        sub_suffixArray[i] = suffixArray[start2];
        sub_movePlace[i] = movePlace[start2];
        i++;
        start2++;
    }
    for (i = start; i<= end; i++) {
        one[i] = reOne[i];
        two[i] = reTwo[i];
        suffixArray[i] = sub_suffixArray[i];
        movePlace[i] = sub_movePlace[i];
    }
    return;
}
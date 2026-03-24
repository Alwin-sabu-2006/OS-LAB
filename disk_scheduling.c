#include <stdio.h>
#include <stdlib.h>

int n, head, req[100];

// Sort function
void sort(int a[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = i + 1; j < size; j++) {
            if(a[i] > a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }                                                                                                                                                                                                                                                                                                           
        }
    }
}

// ----------- SSTF -----------
void SSTF() {
    int visited[100] = {0}, total = 0, pos = head;

    printf("\nSSTF Sequence: %d", pos);

    for(int i = 0; i < n; i++) {
        int min = 9999, index = -1;

        for(int j = 0; j < n; j++) {
            if(!visited[j]) {
                int dist = abs(pos - req[j]);
                if(dist < min) {
                    min = dist;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total += min;
        pos = req[index];
        printf(" -> %d", pos);
    }

    printf("\nTotal Seek Time = %d\n", total);
}

// ----------- LOOK (Right first) -----------
void LOOK() {
    int left[100], right[100], l = 0, r = 0;
    int total = 0, pos = head;

    for(int i = 0; i < n; i++) {
        if(req[i] < head) left[l++] = req[i];
        else right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\nLOOK Sequence: %d", pos);

    // Move RIGHT
    for(int i = 0; i < r; i++) {
        total += abs(pos - right[i]);
        pos = right[i];
        printf(" -> %d", pos);
    }

    // Then LEFT
    for(int i = l - 1; i >= 0; i--) {
        total += abs(pos - left[i]);
        pos = left[i];
        printf(" -> %d", pos);
    }

    printf("\nTotal Seek Time = %d\n", total);
}

// ----------- C-SCAN (Right only) -----------
void CSCAN() {
    int left[100], right[100], l = 0, r = 0;
    int total = 0, pos = head;
    int disk_size = 200;

    for(int i = 0; i < n; i++) {
        if(req[i] < head) left[l++] = req[i];
        else right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\nC-SCAN Sequence: %d", pos);

    // Move RIGHT
    for(int i = 0; i < r; i++) {
        total += abs(pos - right[i]);
        pos = right[i];
        printf(" -> %d", pos);
    }

    // Go to end and jump to 0
    total += abs(pos - (disk_size - 1));
    pos = 0;
    printf(" -> %d", pos);

    // Continue remaining
    for(int i = 0; i < l; i++) {
        total += abs(pos - left[i]);
        pos = left[i];
        printf(" -> %d", pos);
    }

    printf("\nTotal Seek Time = %d\n", total);
}

// ----------- MAIN -----------
int main() {
    int choice;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter head position: ");
    scanf("%d", &head);

    do {
        printf("\n1. SSTF\n2. LOOK\n3. C-SCAN\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1) SSTF();
        else if(choice == 2) LOOK();
        else if(choice == 3) CSCAN();

    } while(choice != 4);

    return 0;
}
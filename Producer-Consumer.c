#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdbool.h>

#define N 8

int x = 0;
int buffer[N] = {0};
int in = 0, out = 0, count = 0;

void producer() {
    x++;
    buffer[in] = x;
    if(x > N){
        printf("Buffer is Full. Cannot produce.\n");
        x = N; // Cap the value
    } else {
        printf("Produced item: %d\n", x);
    }
    in = (in + 1) % N;
    count++;
}

void consumer() {
    int item = buffer[out];
    x--;
    if(x < 0){
        printf("Buffer is Empty. Cannot consume.\n");
        x = 0;
    } else {
        printf("Consumed item: %d\n", item);
    }
    out = (out + 1) % N;
    count--;
}

int main() {
    int choice;
    while (true) {
        printf("Enter 1 to produce, 0 to consume, -1 to exit: \n");
        scanf("%d", &choice);

        if (choice == 1)
            producer();
        else if (choice == 0)
            consumer();
        else if (choice == -1)
            break;
    }
    return 0;
}
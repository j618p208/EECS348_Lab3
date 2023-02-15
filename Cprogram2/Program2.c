#include <stdio.h>
#include <stdlib.h>

void rec_score(int score, int scores[5], int **output) {
    if (score == 0) {
        for (int i=0; i<500; i++) {
            if (output[i] == NULL) {
                int *final_score = (int*)malloc(sizeof(int) * 5);
                *final_score = scores[0];
                *(final_score+1) = scores[1];
                *(final_score+2) = scores[2];
                *(final_score+3) = scores[3];
                *(final_score+4) = scores[4];
                output[i] = final_score;
                break;
            } else if (scores[0] == output[i][0] &&
                       scores[1] == output[i][1] &&
                       scores[2] == output[i][2] &&
                       scores[3] == output[i][3] &&
                       scores[4] == output[i][4]) {
                            break;
            }
        }
    }
    if (score >= 8) {   //TD+2pt
        scores[0]++;
        rec_score(score-8, scores, output);
        scores[0]--;
    }
    if (score >= 7) {   //TD+FG
        scores[1]++;
        rec_score(score-7, scores, output);
        scores[1]--;
    }
    if (score >= 6) {   //TD
        scores[2]++;
        rec_score(score-6, scores, output);
        scores[2]--;
    }
    if (score >= 3) {   //FG
        scores[3]++;
        rec_score(score-3, scores, output);
        scores[3]--;
    }
    if (score >= 2) {   //SFT
        scores[4]++;
        rec_score(score-2, scores, output);
        scores[4]--;
    }
    return;
}

void score(int score) {
    int scores[] = {0, 0, 0, 0, 0};  //{TD+2, TD+1, TD, FD, SFT}
    int *output[500];

    for(int i=0; i<500; i++) {
        output[i] = NULL;
    }

    rec_score(score, scores, output);

    printf("\n");

    for (int i=0; i<500; i++) {
        if (output[i] == NULL) {
            break;
        } else {
            printf("%d TD+2pt, %d TD+FD, %d TD, %d FG, %d SAFETY\n",
            output[i][0], output[i][1], output[i][2], output[i][3], output[i][4]);
        }
    }
    return;
}

int main() {
    printf("This program will provide all possible combinations of scoring plays in a football game that adds to the given score.\n");
    int value = 0;
    while (value < 2) {
        printf("Please input the score 1 team got: ");
        scanf("%d", &value);
    }
    score(value);
}
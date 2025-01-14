#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct TriNeuron{
        float w1;
        float w2;
        float w3;
        float w4;
        float w5;
        float w6;
        float b1;
        float b2;
        float b3;
};

//a = x1 * w1 + x2 * w2 + b1
//b = x1 * w3 + x2 * w4 + b2
//c = a  * w5 + b  * w6 + b3

#define H               0.001f
#define LEARNING_RATE   0.01f
#define TRAIN_DATA_SIZE 4
#define ITR 2000 * 2000

typedef float data_set[3];

enum parameters {
        W_1=1,
        W_2,
        W_3,
        W_4,
        W_5,
        W_6,
        B_1,
        B_2,
        B_3
};

data_set xor[] = {
        {0,0,0},
        {0,1,1},
        {1,0,1},
        {1,1,0}
};
data_set or[] = {
        {0,0,0},
        {0,1,1},
        {1,0,1},
        {1,1,1}
};
data_set and[] = {
        {0,0,0},
        {0,1,0},
        {1,0,0},
        {1,1,1}
};
data_set nand[] = {
        {0,0,1},
        {0,1,1},
        {1,0,1},
        {1,1,0}
};
data_set nor[] = {
        {0,0,1},
        {0,1,0},
        {1,0,0},
        {1,1,0}
};

data_set * data = xor;

float sigmoidf(float x){
        return 1/(1 + expf(-x));
}

float cost(struct TriNeuron w){
        float result = 0.0f;
        for(int i = 0; i < TRAIN_DATA_SIZE; i++){
                float x1 = data[i][0];
                float x2 = data[i][1];
                float a  = (x1 * w.w1) + (x2 * w.w2) + w.b1;
                a = sigmoidf(a);
                float b  = (x1 * w.w3) + (x2 * w.w4) + w.b2;
                b = sigmoidf(b);
                float y  = (a  * w.w5) + (b  * w.w6) + w.b3;
                y = sigmoidf(y);
                float error = data[i][2] - y;
                result += error * error;
        }
        result /= TRAIN_DATA_SIZE;
        return result;
}

float rand_float(){
        return (float)rand()/(float)RAND_MAX;
}

void randomize(struct TriNeuron *w){
        srand(time(0));
        w->w1 = rand_float();   
        w->w2 = rand_float();
        w->w3 = rand_float();
        w->w4 = rand_float();
        w->w5 = rand_float();
        w->w6 = rand_float();
        w->b1 = rand_float();
        w->b2 = rand_float();
        w->b3 = rand_float();

}

float step(float x){
        if(x < 0.5f){
                return 0.00f;
        }else{
                return 1.00f;
        }
}
void predict_xor(struct TriNeuron w){
        for(int i = 0; i < TRAIN_DATA_SIZE; i++){
                float x1 = data[i][0];
                float x2 = data[i][1];
                float a  = (x1 * w.w1) + (x2 * w.w2) + w.b1;
                a = sigmoidf(a);
                float b  = (x1 * w.w3) + (x2 * w.w4) + w.b2;
                b = sigmoidf(b);
                float y  = (a  * w.w5) + (b  * w.w6) + w.b3;
                y = sigmoidf(y);
                float sy = step(y);
                printf("XOR(%f,%f): %f = %f\n",x1,x2,y,sy);
        }
}

float finite_diff(struct TriNeuron w, int pos){
        switch (pos) {
                case W_1:{w.w1 += H;}       break;
                case W_2:{w.w2 += H;}       break;
                case W_3:{w.w3 += H;}       break;
                case W_4:{w.w4 += H;}       break;
                case W_5:{w.w5 += H;}       break;
                case W_6:{w.w6 += H;}       break;
                case B_1:{w.b1 += H;}       break;
                case B_2:{w.b2 += H;}       break;
                case B_3:{w.b3 += H;}       break;
        }
        return cost(w);
}

void train_model(struct TriNeuron *w){
        struct TriNeuron temp = *w;
        for(int i = 0 ; i < ITR; i++){
                //printf("w1=%f | w2=%f | w3 = %f| w4 = %f | w5 = %f | w6 = %f\n",w->w1,w->w2,w->w3,w->w4,w->w5,w->w6);
                
                float c = cost(*w);
                float dw1 = (finite_diff(*w, W_1) - c)/H;
                float dw2 = (finite_diff(*w, W_2) - c)/H;
                float dw3 = (finite_diff(*w, W_3) - c)/H;
                float dw4 = (finite_diff(*w, W_4) - c)/H;
                float dw5 = (finite_diff(*w, W_5) - c)/H;
                float dw6 = (finite_diff(*w, W_6) - c)/H;
                float db1 = (finite_diff(*w, B_1) - c)/H;
                float db2 = (finite_diff(*w, B_2) - c)/H;
                float db3 = (finite_diff(*w, B_3) - c)/H;
                
                w->w1 -= LEARNING_RATE * dw1;
                w->w2 -= LEARNING_RATE * dw2;
                w->w3 -= LEARNING_RATE * dw3;
                w->w4 -= LEARNING_RATE * dw4;
                w->w5 -= LEARNING_RATE * dw5;
                w->w6 -= LEARNING_RATE * dw6;

                w->b1 -= LEARNING_RATE * db1;
                w->b2 -= LEARNING_RATE * db2;
                w->b3 -= LEARNING_RATE * db3;
        }

}

void print_parameters(struct TriNeuron w){
        printf("w1 = %f | w2 = %f | b1 = %f\nw3 = %f | w4 = %f | b2 = %f\nw5 = %f | w6 = %f | b3 = %f\n",w.w1,
                        w.w2,w.b1,w.w3,w.w4,w.b2,w.w5,w.w6,w.b3);
}

int main(){
        struct TriNeuron xor ;
        randomize(&xor);
        train_model(&xor);
        print_parameters(xor);
        printf("Cost: %f\n",cost(xor));
        predict_xor(xor);
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//XOR Gate
float XOR_train_data[][3] = {
        {0,0,0},
        {0,1,1},
        {1,0,1},
        {1,1,0}
};

//OR Gate
float OR_train_data[][3] = {
        {0,0,0},
        {0,1,1},
        {1,0,1},
        {1,1,1}
};

//AND Gate
float AND_train_data[][3] = {
        {0,0,0},
        {0,1,0},
        {1,0,0},
        {1,1,1}
};

//NOR Gate
float NOR_train_data[][3] = {
        {0,0,1},
        {0,1,0},
        {1,0,0},
        {1,1,0}
};

//NAND Gate
float NAND_train_data[][3] = {
        {0,0,1},
        {0,1,1},
        {1,0,1},
        {1,1,0}
};

typedef float training_data[3];

training_data *gate = NOR_train_data;
//------------------------------------------------------------
#define LEARNING_RATE   0.01f
#define ITER            2000 * 1500 
#define H               0.001f

#define DOT(x1,x2,w1,w2,b) (x1*w1)+(x2*w2)+b

float activation(float y)
{
        float x = 1.0f/(1.0f + expf(-y));
        return x;      
}

float random_float(void){
        return (float)rand() / (float)RAND_MAX;
}

float p_cost(float w1,float w2, float b){
        float result = 0.0f;
        for(int i = 0; i < 4; i++){
                float x1 = gate[i][0];
                float x2 = gate[i][1];
                float y = activation((x1 * w1) + (x2 * w2) + b);
                float error = gate[i][2] - y;
                result += error * error;
        }
        result /= 4;
        return result;
}


//XOR GATE : (x | y) & (~(x&y)) 
//XOR GATE : (X OR Y) AND (X NAND Y)

void train_gate(float *w1, float *w2, float *b){        
 
        for(int i = 0; i < ITER; i++){
                //printf("w1 = %f | w2 = %f | b = %f | c = %f\n",w1,w2,b,p_cost(w1,w2,b));
                //printf("%f\n", p_cost(w1,w2,b));
                float dw1 = (p_cost(*w1 + H,*w2,*b) - p_cost(*w1,*w2,*b))/H;
                float dw2 = (p_cost(*w1,*w2 + H,*b) - p_cost(*w1,*w2,*b))/H;
                float db  = (p_cost(*w1,*w2,*b + H) - p_cost(*w1,*w2,*b))/H;
                *w1 -= LEARNING_RATE * dw1;
                *w2 -= LEARNING_RATE * dw2;
                *b  -= LEARNING_RATE * db;
        }
}

float XOR_gate(float a, float b){
        float w1 = random_float();
        float w2 = random_float();
        float w3 = random_float();
        float w4 = random_float();
        float w5 = random_float();
        float w6 = random_float();

        float b1 =  random_float();
        float b2 =  random_float();
        float b3 =  random_float();

        gate = OR_train_data;
        train_gate(&w1,&w2,&b1);
        float x1 = activation(DOT(a,b,w1,w2,b1));
        gate = NAND_train_data;
        train_gate(&w3,&w4,&b2);
        float x2 = activation(DOT(a,b,w3,w4,b2));
        gate = AND_train_data;
        train_gate(&w5,&w6,&b3);
        float y = DOT(x1,x2,w5,w6,b3);
        return y;
}

int main(int argc, char** argv){
        srand(time(0));

        printf("(0,0): %f\n", activation(XOR_gate(0,0)));
        printf("(0,1): %f\n", activation(XOR_gate(0,1)));
        printf("(1,0): %f\n", activation(XOR_gate(1,0)));
        printf("(1,1): %f\n", activation(XOR_gate(1,1)));


        //For  
/*
        printf("(0,0): %f\n", DOT(0,0,w5,w6,b3));
        printf("(0,1): %f\n", DOT(0,1,w5,w6,b3));
        printf("(1,0): %f\n", DOT(1,0,w5,w6,b3));
        printf("(1,1): %f\n", DOT(1,1,w5,w6,b3));
        printf("Cost: %f\n" , p_cost(w5,w6,b3));


        printf("(0,0): %f\n", activation(DOT(0,0,w5,w6,b3)));
        printf("(0,1): %f\n", activation(DOT(0,1,w5,w6,b3)));
        printf("(1,0): %f\n", activation(DOT(1,0,w5,w6,b3)));
        printf("(1,1): %f\n", activation(DOT(1,1,w5,w6,b3)));
        printf("Cost: %f\n" , p_cost(w5,w6,b3));
*/
}

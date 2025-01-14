#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float data[][2] = {
        {0,1},
        {1,0},
};

float cost(float w, float b){
        float result = 0.0f;
        for(int i = 0; i < 5; i++){
                float x = data[i][0];
                float y = x * w + b;
                float error = data[i][1] - y;
                result += error * error;
        }
        result /= 5;
        return result;
}

int main(int argc, char** argv){
        float w = 0.0f;
        float b = 0.0f;
        for(int i = 0; i < 5; i++){
                float x = data[i][0];
                float y = x * w;
                float error = data[i][1] - y;
                w +=  error*x;
                //b +=  error;
        }
        float a = (float)atoi(argv[1]);
        printf("Test: %f * %f + %f = %f\n",a,w,b, (a*w)+b);
        printf("Cost: %f\n", cost(w,b));
}

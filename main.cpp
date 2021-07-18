#include <iostream>
#include <time.h> // нужен для вызова функции time()
#include <stdlib.h> // нужен для вызова функций rand(), srand()

using namespace std;

class TrainingSet
{
public:
    double input[2];
    double output;
    void kek(){};
};

class Perceptron
{
public:
    Perceptron(TrainingSet ts[4])
    {
        for(int i = 0 ; i<4;i++)
            this->ts[i] = ts[i];
    }
    TrainingSet ts[4];
    double weights[2] = {0,0};
    double bias = 0;
    double totalError = 0;
    void InitWeights()
    {
        for(int i = 0; i<2;i++)
        {
            weights[i] = (-100 + rand() % ((100 + 1) + 100))/100.0;
        }
        bias = (-100 + rand() % ((100 + 1) + 100))/100.0;
    }

    double Calculation(double v1[], double v2[])
    {
        double d = 0;
        for(int x = 0; x<2; x++)
        {
            d += v1[x] * v2[x];
        }
        d += bias;

        if (d>0) return 1;
        else return 0;
    }

    void UpdateWeights(int j)
    {
        double error = ts[j].output - Calculation(weights,ts[j].input);
        totalError += float(error)*float(error);
        for (int i = 0; i < 2;i++)
        {
            weights[i] += error*ts[j].input[i];
        }
        bias += error;
    }

    double CalcOutput(double input1, double input2)
    {
        double inputs[2] = {input1,input2};
        double output = Calculation(weights,inputs);
        return output;
    }

    void Train(int epochs)
    {
        InitWeights();
        for(int e=0;e<epochs;e++)
        {
            totalError = 0;
            for(int t=0;t<4;t++)
            {
                UpdateWeights(t);
                cout << "W1: "<< weights[0]<< " W2: " <<
                        weights[1] << " B: "<< bias <<endl;
            }
            cout << "Error " << totalError << endl;
        }
    }

};

int main()
{
    float train_data[14][3] = {{0.5,1,1},
                               {0,0.8,1},
                               {0.2,1,1},
                               {0.1,0.5,1},
                               {0.3,0.5,1},
                               {0.3,0.8,1},
                               {0.5,0.9,1},
                               {0.8,1,1},
                               {0.1,0,0},
                               {0.5,0.3,0},
                               {0.6,0.3,0},
                               {0.6,0.1,0},
                               {0.7,0,0},
                               {0.9,0,0}};
    TrainingSet ts[14];
    for(int i = 0;i<14;i++)
    {
        ts[i].input[0] = train_data[i][0];
        ts[i].input[1] = train_data[i][1];
        ts[i].output = train_data[i][2];
    }

    Perceptron brain(ts);

    srand(time(NULL));

    brain.Train(5);

    cout << "Test 0.2 0.1: " << brain.CalcOutput(0.2,0.1) << endl;

    return 0;
}

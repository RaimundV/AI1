#include <iostream>
#include <random>
#include <ctime>
#include <bits/stdc++.h>
#include <cmath>
#include <Windows.h>

double Sigmoid(double x[], double w[], double w0)
{
    double pwr = 0;
    int size = *(&x + 1) - x;
    for (int i = 0; i < size; i++)
    {
        pwr += x[i] * w[i];
    }
    pwr += w0;
    return 1 / (1 + exp(-pwr));
}

int StepFunction(double x[], double w[], double w0)
{
    double pwr = 0;
    int size = *(&x + 1) - x;
    for (int i = 0; i < size; i++)
    {
        pwr += x[i] * w[i];
    }

    pwr += w0;

    if (pwr >= 0)
        return 1;

    return 0;
}

bool SigmoidFun(double x1[], double x2[], double sigmoidVal)
{
    double lower_bound = -3;
    double upper_bound = 3;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    Sleep(100);
    std::default_random_engine re(time(0)*10000);
    double w1 = unif(re);
    double w2 = unif(re);
    double w0 = unif(re);
    if (1 / (1 + exp(-(x1[0] * w1 + x2[0] * w2 + w0))) >= sigmoidVal)
        return false;
    if (1 / (1 + exp(-(x1[1] * w1 + x2[1] * w2 + w0))) >= sigmoidVal)
        return false;
    if (1 / (1 + exp(-(x1[2] * w1 + x2[2] * w2 + w0))) < sigmoidVal)
        return false;
    if (1 / (1 + exp(-(x1[3] * w1 + x2[3] * w2 + w0))) < sigmoidVal)
        return false;

    std::cout << "w1: " << w1 << " w2: " << w2 << " w0: " << w0 << std::endl;
    return true;
}

void SigmoidAnswer(double x1[], double x2[], double sigmoidVal)
{
    int limit = 100000;
    int counter = 0;
    while(true)
    {
        if (SigmoidFun(x1, x2, sigmoidVal))
            break;

        counter++;
        if (counter == limit)
        {
            std::cout << "limit of iteration reached" << std::endl;
            break;
        }
    }
}

void Step(double x1[], double x2[])
{
    static double  step_size   = 0.25;
    double  roof        = 3;
    double  bottom      = -3;

    for (double w1 = bottom; w1 <= roof; w1+=step_size)
    {
        for (double w2 = bottom; w2 <= roof; w2+=step_size)
        {
            for (double w0 = bottom; w0 <= roof; w0+=step_size)
            {
                if (x1[0] * w1 + x2[0] * w2 + w0 >= 0)
                    continue;
                if (x1[1] * w1 + x2[1] * w2 + w0 >= 0)
                    continue;
                if (x1[2] * w1 + x2[2] * w2 + w0 < 0)
                    continue;
                if (x1[3] * w1 + x2[3] * w2 + w0 < 0)
                    continue;
                std::cout << "w1: " << w1 << " w2: " << w2 << " w0: " << w0 << std::endl;
            }
        }
    }
}

int main()
{
    // Variables for 1.1 -->
    double x[] = {-0.2, 0.5};
    double w[] = {0.8, 0.2};
    double w0  = 0.6;
    // Variables for 1.1 <--
    //Variables for 1.2 1.3 and possibly later -->
    double x1[] = {-0.2,0.2,0.8,0.8};
    double x2[] = {0.5,-0.5,-0.8,0.8};
    int     t[] = {0, 0, 1, 1};
    double sigmoidVal = 0.5;
    //Variables for 1.2 1.3 and possibly later <--
    std::cout << "1.1:" << std::endl;
    std::cout << "Sigmoid function result = " << Sigmoid(x, w, w0) << std::endl;
    std::cout << "Step function result = " << StepFunction(x, w, w0) << std::endl;

    std::cout << std::endl;
    std::cout << "1.2:" << std::endl;
    std::cout << "Step funkcija" << std::endl;
    Step(x1, x2);

    std::cout << std::endl;
    std::cout << "1.3:" << std::endl;
    std::cout << "Sigmoid function" << std::endl;
    SigmoidAnswer(x1, x2, sigmoidVal);

    return 0;
}
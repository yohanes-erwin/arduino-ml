// Author: Erwin Ouyang, aiotedge.tech
// Date  : 22 Feb 2020

#include <BasicLinearAlgebra.h>

using namespace BLA;

// === Step 1: create data set =================================================
// Train set
Matrix<80,1> x_train = {16, 15, 16, 10, 16, 13,  9, 19, 10, 12, 15, 10, 16, 26, 18, 16, 20, 15,
                        10, 25, 17,  9, 21,  7,  8, 13, 18,  7, 12, 18, 19, 19, 11, 12, 19, 21,
                        21, 19, 16, 10, 13, 20,  7,  8, 15, 13, 11, 14, 16, 21, 15, 12, 17, 24,
                        17, 21, 17, 14, 24, 12, 15, 16, 17, 18, 24, 16, 15, 23, 23, 21, 13,  9,
                        13, 11,  8, 15, 16, 12, 14, 21};
Matrix<80,1> y_train = {40, 52, 48, 37, 48, 37, 37, 40, 38, 29, 42, 38, 52, 57, 47, 46, 53, 32,
                        43, 63, 44, 35, 43, 43, 37, 35, 45, 37, 40, 54, 40, 51, 39, 44, 43, 49,
                        62, 60, 45, 34, 49, 44, 35, 26, 45, 42, 43, 40, 49, 52, 42, 35, 43, 51,
                        41, 51, 52, 44, 54, 38, 48, 45, 37, 50, 62, 57, 41, 47, 49, 52, 32, 33,
                        44, 43, 31, 43, 42, 42, 47, 61};
// Test set
Matrix<20,1> x_test = {13,  5, 17, 15, 10, 23, 18, 12, 22, 14,  9, 14, 14, 20, 11, 19, 10, 13, 11, 16};
Matrix<20,1> y_test = {44, 23, 47, 38, 32, 48, 40, 45, 50, 36, 37, 48, 46, 57, 42, 50, 44, 42, 45, 46};

// Parameters
Matrix<2,1> theta;

// Define the normal equation function
Matrix<2,1> normal_equation(Matrix<80,1> X, Matrix<80,1> y)
{
  Matrix<80,1> b;
  b.Fill(1);
  Matrix<80,2> X_b = b || X;
  Matrix<2,80> X_b_transpose = ~X_b;
  Matrix<2,1> theta = (X_b_transpose * X_b).Inverse() * X_b_transpose * y;
  
  return theta;
}

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  // === Step 2: train the model using normal equation =========================
  Serial.print("Training ...\n");
  theta = normal_equation(x_train, y_train);
  Serial.print("Training completed: ");
  Serial << "theta = " << theta << '\n';

  // === Step 3: making predictions with multiple samples ======================
  Matrix<20,1> b;
  b.Fill(1);
  Matrix<20,2> x_b_test = b || x_test;
  Matrix<2,20> x_b_test_transpose = ~x_b_test;
  Matrix<1,2> theta_transpose = ~theta;
  Matrix<1,20> y_pred = theta_transpose * x_b_test_transpose;
  Serial << "Multiple samples prediction: y_pred = " << y_pred << '\n';
}

void loop()
{
  // === Step 3a: making predictions with single sample ========================
  Serial.println("Single sample prediction:");
  for (int i = 0; i < 20; i++)
  {
    Matrix<1,2> theta_transpose = ~theta;
    Matrix<2,1> x_b_test = {1, x_test(i)};
    Matrix<1,1> y_pred = theta_transpose * x_b_test;

    // Round the result to nearest integer
    int y_pred_rounded = round(y_pred(0));
    // Print the result
    printf("Temperature = %.0f°C, Predicted Bike-Sharing Users = %d\n", x_test(i), y_pred_rounded);
    delay(1000);
  }
}


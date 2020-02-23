// Author: Erwin Ouyang, aiotedge.tech
// Date  : 22 Feb 2020

// === Step 1: create data set =================================================
// Train set
int x_train[80] = {16, 15, 16, 10, 16, 13,  9, 19, 10, 12, 15, 10, 16, 26, 18, 16, 20, 15,
                   10, 25, 17,  9, 21,  7,  8, 13, 18,  7, 12, 18, 19, 19, 11, 12, 19, 21,
                   21, 19, 16, 10, 13, 20,  7,  8, 15, 13, 11, 14, 16, 21, 15, 12, 17, 24,
                   17, 21, 17, 14, 24, 12, 15, 16, 17, 18, 24, 16, 15, 23, 23, 21, 13,  9,
                   13, 11,  8, 15, 16, 12, 14, 21};
int y_train[80] = {40, 52, 48, 37, 48, 37, 37, 40, 38, 29, 42, 38, 52, 57, 47, 46, 53, 32,
                   43, 63, 44, 35, 43, 43, 37, 35, 45, 37, 40, 54, 40, 51, 39, 44, 43, 49,
                   62, 60, 45, 34, 49, 44, 35, 26, 45, 42, 43, 40, 49, 52, 42, 35, 43, 51,
                   41, 51, 52, 44, 54, 38, 48, 45, 37, 50, 62, 57, 41, 47, 49, 52, 32, 33,
                   44, 43, 31, 43, 42, 42, 47, 61};
// Test set
int x_test[20] = {13,  5, 17, 15, 10, 23, 18, 12, 22, 14,  9, 14, 14, 20, 11, 19, 10, 13, 11, 16};
int y_test[20] = {44, 23, 47, 38, 32, 48, 40, 45, 50, 36, 37, 48, 46, 57, 42, 50, 44, 42, 45, 46};

// Parameters
float theta_0 = 0.0;
float theta_1 = 0.0;

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  // === Step 2: train the model using gradient descent ========================
  Serial.print("Training ...\n");
  gradient_descent(x_train, y_train, 80, 10000, 0.005);
  Serial.printf("Training completed: theta_0 = %.3f, theta_1 = %.3f\n", theta_0, theta_1);
}

void loop()
{
  // === Step 3: making predictions ============================================
  for (int i = 0; i < 20; i++)
  {
    // Make predictions using test set
    float y_pred = hypothesis(x_test[i]);
    // Round the result to nearest integer
    int y_pred_rounded = round(y_pred);
    // Print the result
    printf("Temperature = %d°C, Predicted Bike-Sharing Users = %d\n", x_test[i], y_pred_rounded);
    delay(1000);
  }
}

// Define the hypothesis function
float hypothesis(int x)
{
  return theta_0 + theta_1*x;
}

// Define the gradient descent function
void gradient_descent(int x[], int y[], int m, int iter, float eta)
{
  float h, e, sum_e, e_mul_x, sum_e_mul_x;
  
  for (int i = 0; i < iter; i++)
  {
    // Clear variable
    h = 0.0;
    e = 0.0;
    sum_e = 0.0;
    e_mul_x = 0.0;
    sum_e_mul_x = 0.0;
    
    for (int j = 0; j < m; j++)
    {
      // Calculate hypothesis
      h = hypothesis(x[j]);
      // Calculate error
      e = h - y[j];
      // Calculate sum of error
      sum_e = sum_e + e;      
      // Calculate error*x
      e_mul_x = e * x[j];
      // Calculate sum of error*x
      sum_e_mul_x = sum_e_mul_x + e_mul_x;
    }

    // Calculate d_J/d_theta_0
    float d_J_d_theta_0 = sum_e / m;  
    // Calculate d_J/d_theta_1
    float d_J_d_theta_1 = sum_e_mul_x / m;
    
    // Update theta 0
    theta_0 = theta_0 - eta*d_J_d_theta_0;    
    // Update theta 1
    theta_1 = theta_1 - eta*d_J_d_theta_1;
  }
}


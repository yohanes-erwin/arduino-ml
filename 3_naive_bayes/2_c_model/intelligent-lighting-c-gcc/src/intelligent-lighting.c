#include <stdio.h>

#define NUM_OF_ROWS(arr) ((int)(sizeof(arr)/sizeof(arr)[0]))
#define NUM_OF_COLS(arr) ((int)(sizeof(arr)[0]/sizeof(arr)[0][0]))

uint8_t X[37][2] = {{0,0},{0,1},{0,2},{0,3},{0,4},{0,4},{0,5},{0,6},{1,7},{1,8},{0,8},{1,9},{1,9},{2,10},{2,11},{3,12},{3,12},{1,12},{3,13},{3,13},{3,14},{1,14},{2,15},{0,15},{2,16},{2,17},{0,17},{1,18},{1,18},{1,19},{0,19},{0,20},{0,20},{0,21},{0,21},{0,22},{0,23}};
uint8_t y[37] = {0,0,0,0,0,0,1,1,1,0,1,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,1,1,1,1,1,1,1};
uint8_t freq_table_lsensor[4][2] = {{0}};
uint8_t freq_table_time[24][2] = {{0}};

void create_freq_table_lsensor(void);
void create_freq_table_time(void);
float label_prior_prob(uint8_t light_state);
float likelihood(uint8_t light_sensor, uint8_t time, uint8_t light_state);
float posterior_prob(uint8_t light_sensor, uint8_t time, uint8_t light_state);
uint8_t predict(uint8_t light_sensor, uint8_t time);

int main()
{
	create_freq_table_lsensor();
	create_freq_table_time();

	uint8_t light_sensor = 2;
	uint8_t time = 12;
    printf("Light Sensor: %d, Time: %d:00\n", light_sensor, time);
	printf("P(y=Off|X)=%.6f, ", posterior_prob(light_sensor, time, 0));
	printf("P(y=On|X)=%.6f\n", posterior_prob(light_sensor, time, 1));
	printf("Prediction=%s\n", (!predict(light_sensor, time)) ? "Off" : "On");

	return 0;
}

void create_freq_table_lsensor()
{
	for (int i = 0; i < sizeof(y); i++)
		freq_table_lsensor[X[i][0]][y[i]]++;
}

void create_freq_table_time()
{
	for (int i = 0; i < sizeof(y); i++)
		freq_table_time[X[i][1]][y[i]]++;
}

float label_prior_prob(uint8_t light_state)
{
	uint8_t count = 0;
	float prob_lap = 0.0;

	for (int i = 0; i < sizeof(y); i++)
		count += (y[i] == light_state) ? 1 : 0;
	prob_lap = (float)(count+1)/(sizeof(y)+2*1);

	return prob_lap;
}

float likelihood(uint8_t light_sensor, uint8_t time, uint8_t light_state)
{
	float sum_freq_table_lsensor = 0;
	float sum_freq_table_time = 0;
	float prob_lsensor_lstate_lap = 0.0;
	float prob_time_lstate_lap = 0.0;
	float prob_lsensor_time_lstate_lap = 0.0;

	// calculate probability of light sensor=light_sensor given light state=light_state
	// and add laplace smoothing
	for (int i = 0; i < NUM_OF_ROWS(freq_table_lsensor); i++)
		sum_freq_table_lsensor += freq_table_lsensor[i][light_state];
	prob_lsensor_lstate_lap = (float)(freq_table_lsensor[light_sensor][light_state]+1) /
			(sum_freq_table_lsensor+4*1);

	// calculate probability of time=time given light state=light_state
	// and add laplace smoothing
	for (int i = 0; i < NUM_OF_ROWS(freq_table_time); i++)
		sum_freq_table_time += freq_table_time[i][light_state];
	prob_time_lstate_lap = (float)(freq_table_time[time][light_state]+1) /
			(sum_freq_table_time+24*1);

	// calculate probability of light sensor=light_sensor and time=time given
	// light state=light_state
	prob_lsensor_time_lstate_lap = prob_lsensor_lstate_lap * prob_time_lstate_lap;

	return prob_lsensor_time_lstate_lap;
}

float posterior_prob(uint8_t light_sensor, uint8_t time, uint8_t light_state)
{
	return likelihood(light_sensor, time, light_state) * label_prior_prob(light_state);
}

uint8_t predict(uint8_t light_sensor, uint8_t time)
{
	uint8_t light_state_prediction = 0;
	if (posterior_prob(light_sensor, time, 0) > posterior_prob(light_sensor, time, 1))
		light_state_prediction = 0;
	else
		light_state_prediction = 1;

	return light_state_prediction;
}

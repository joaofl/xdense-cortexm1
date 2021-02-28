/*
 * packet.h
 *
 * Created: 20/11/2014 15:05:42
 *  Author: Joao
 */ 


#ifndef PACKET_H_
#define PACKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct{
	uint8_t protocol;
	int8_t s_x;
	int8_t s_y;
	int8_t d_x;
	int8_t d_y;	
	
	uint8_t app_resource;		// 0bXXXXX--- //resource //ping, ND, sensor_light, etc
	uint8_t app_method;			// 0b-----XX- //method //get, set, observe, reset
	uint8_t app_packet_type;	// 0b-------X //message type // Request or Response
	
	//uint8_t app_data_processing;
	//uint8_t app_neighbor_lookup_type;
	//uint8_t app_neighbor_lookup_radius;
	//uint8_t status;
	uint8_t payload[9];
	uint8_t port_origin;
} xdense_packet;

#define PACKET_QUEUE_N 12
//static xd_packet pck_input[PACKET_QUEUE_N];

/////////////////////////////////
//TRANSPORT LAYER
////////////////////////////////
#define PACKET_SIZE                         16

#define PROTOCOL_UNICAST                    1
#define PROTOCOL_MULTICAST_1                2
#define PROTOCOL_BROADCAST                  3

/////////////////////////////////
//APPLICATION LAYER
////////////////////////////////

#define APP_PROTOCOL_REQUEST                0
#define APP_PROTOCOL_RESPONSE               1

#define APP_METHOD_GET                      0
#define APP_METHOD_SET                      1   
#define APP_METHOD_OBSERVE		
#define APP_METHOD_RESET                    3

#define APP_RESOURCE_PING                   0
#define APP_RESOURCE_ND                     1
#define APP_RESOURCE_CONFIG                 2
#define APP_RESOURCE_SENSOR_LIGHT           3
#define APP_RESOURCE_SENSOR_PRESSURE        4
#define APP_RESOURCE_SENSOR_ACCELERATION    5
#define APP_RESOURCE_SENSOR_TEMPERATURE     6
#define APP_RESOURCE_ACTUATOR_LED           7
#define APP_RESOURCE_POLY_REGRESSION_D2     8


/////////////////////////////////////////////////////
//REQUEST
#define APP_DATAPROCESSING_NONE					0
#define APP_DATAPROCESSING_AVG					1
#define APP_DATAPROCESSING_MAX					2
#define APP_DATAPROCESSING_MIN					3
#define APP_DATAPROCESSING_LINEAR_REGRESSION	4
#define APP_DATAPROCESSING_POWER_REGRESSION		5
#define APP_DATAPROCESSING_POLY_REGRESSION_D2	6
#define APP_DATAPROCESSING_POLY_REGRESSION_D3	7

#define APP_NEIGHBOR_LOOKUP_TYPE_SQUARE		0
#define APP_NEIGHBOR_LOOKUP_TYPE_DYAMOND	1
#define APP_NEIGHBOR_LOOKUP_TYPE_CIRCLE		2	
#define APP_NEIGHBOR_LOOKUP_TYPE_CLUSTER	3

#define APP_NEIGHBOR_LOOKUP_RADIUS_NONE		0 //single
#define APP_NEIGHBOR_LOOKUP_RADIUS_1		1
#define APP_NEIGHBOR_LOOKUP_RADIUS_2		2
#define APP_NEIGHBOR_LOOKUP_RADIUS_3		3
#define APP_NEIGHBOR_LOOKUP_RADIUS_4		4
#define APP_NEIGHBOR_LOOKUP_RADIUS_5		5		

///////////////////////////////////////////////////
//RESPONSE
#define APP_METHOD_ERROR					0
#define APP_DATAPROCESSING_ERROR			1
#define APP_NEIGHBOR_LOOKUP_TYPE_ERROR		2
#define APP_NEIGHBOR_LOOKUP_RADIUS_ERROR	3
#define APP_SENSOR_ERROR					4
#define APP_SENSOR_NOT_AVAILABLE 			5

#define APP_OK								15

//Check integrity of the packet
uint8_t packet_check(char * raw_pck);

// Router GET
uint8_t packet_get_protocol(char * raw_pck);
int8_t 	packet_get_s_x(char * raw_pck);
int8_t 	packet_get_s_y(char * raw_pck);
int8_t 	packet_get_d_x(char * raw_pck);
int8_t 	packet_get_d_y(char * raw_pck);

// Application GET
uint8_t packet_get_app_resource(char * app_resource);
uint8_t packet_get_app_method(char * app_method);
uint8_t packet_get_app_packet_type(char * app_packet_type);

//Increment address
void 	packet_increment_s_x(char * raw_pck, int value_to_increment);
void 	packet_increment_s_y(char * raw_pck, int value_to_increment);
void 	packet_increment_d_x(char * raw_pck, int value_to_increment);
void 	packet_increment_d_y(char * raw_pck, int value_to_increment);

void 	packet_serialize(xdense_packet * input_pck, char * output_char);
bool 	packet_deserialize(char * input_char, xdense_packet * output_pck);
void 	packet_print();

#ifdef __cplusplus
}
#endif

#endif /* PACKET_H_ */
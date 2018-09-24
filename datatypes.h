/* datatypes.h 
 * Prof. Russell 
 * ECE 2230 Fall 2018 
 * MP2
 *
 * Propose: The data type that is stored in the list ADT is defined here.  We
 * define a single mapping that allows the list ADT to be defined in terms of a
 * generic data_t.
 *
 * Assumptions: 
 *
 * data_t: The type of data that we want to store in the list
 *
 * Bugs:
 */

typedef struct secusr_info_tag {
    int su_id;	        // secondary user's ID number 
    int ip_address;	// mobile's IP address 
    int access_point;	// IP address of access point connected to mobile 
    int authenticated;	// true or false 
    int privacy;	// mode 0 for none, 1 for encrypted
    float band;		// 3.5 for the CBRS frequency bands (in GHz) 
    int channel;	// 1-10 
    float data_rate;	// in bits per second 
    int time_received;	// time in seconds that information last updated
} su_info_t;

/* the list ADT works on packet data of this type */
typedef su_info_t data_t;

/* commands for vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */

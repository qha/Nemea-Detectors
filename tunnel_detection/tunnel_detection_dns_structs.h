/*!
 * \file tunnel_detection_dns_structs.h
 * \brief Modul that detects DNS tunnels.
 * \author Zdenek Rosa <rosazden@fit.cvut.cz>
 * \date 2014
 */
/*
 * Copyright (C) 2014 CESNET
 *
 * LICENSE TERMS
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is'', and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#ifndef _TUNNEL_DETECTION_DNS_STRUCTS_
#define _TUNNEL_DETECTION_DNS_STRUCTS_






/*!
 * \brief Structure - statistic information about string
 * Structure used to keep statistic information about string.
 */
typedef struct character_statistic_t character_statistic_t ;
 struct character_statistic_t {
    unsigned int count_of_different_letters;    /*< Count of different letters in string  */
    unsigned int count_of_numbers_in_string;    /*< Count of stored numbers in string */
    unsigned int length;    /*< Length of string */
} ;

//********* prefix tree *********
/*!
 * \name Default values
 *  Defines macros used by prefix tree
 * \{ */
#define COUNT_OF_LETTERS_IN_DOMAIN 95 /*< Max count of letter in domain. */
#define MAX_SIZE_OF_DOMAIN 256 /*< Max length of domain */
#define MAX_SIZE_OF_DEEGRE 5 /*< Max size of stored information  */
#define ADD_TO_LIST_FROM_COUNT_OF_SEARCH 20 /*< Default number of histogram size. */
#define ADD_TO_LIST_FROM_COUNT_OF_DIFFERENT_SUBDOMAINS 10 /*< Default number of histogram size. */
#define MAX_COUNT_TO_BE_IN_JUST_ONE_SEARCHER 10 /*< Default number of histogram size. */
/* /} */


 typedef struct prefix_tree_domain_t prefix_tree_domain_t ;

/*!
 * \brief Structure - Prefix tree - inner node structure
 * Structure used to keep information about inner node of prefix tree.
 */
 typedef struct prefix_tree_inner_node_t prefix_tree_inner_node_t ;
 struct prefix_tree_inner_node_t {
	unsigned char length;  /*< length of stored string */
	char * string; /*< stored string in reverse way (end of string is on postion 0)*/
	prefix_tree_inner_node_t * parent; /*< Pointer to parent */
	prefix_tree_domain_t * parent_is_domain;   /*< Pointer to parent, if NULL parent is inner node, else parent is domain name node*/
	prefix_tree_inner_node_t ** child;     /*< Pointer to descendants*/
	prefix_tree_domain_t * domain;   /*< if this string is domain, this variable conatin poiter to domain name structure*/
} ;

/*!
 * \brief Structure - Prefix tree - domain name structure
 * Structure used to keep information about domain names. It is domain name structure, which contain information about domain name.
 */
 struct prefix_tree_domain_t {
 	unsigned char exception;  /*< 1 for exception in detection, 0 for classic domain */
    unsigned char deegree;  /*< deegree of domain */
	unsigned int count_of_insert;  /*< count of searching this domain name */
	unsigned int count_of_different_subdomains;    /*< count of descendants - subdomains */
	unsigned char count_of_different_letters;  /*< count of different letters in domain name */
	prefix_tree_inner_node_t * parent; /*< pointer to parent (last character of domain) */
	prefix_tree_domain_t * parent_domain;  /*< pointer to parent (domain name) */
	prefix_tree_inner_node_t *child;   /*< pointer to descendats */

	prefix_tree_domain_t * most_used_domain_less;  /*< position in linked list, pointer to next domain, which has lower count of seatching*/
	prefix_tree_domain_t * most_used_domain_more;  /*< position in linked list, pointer to previous domain, which has higher count of seatching*/
	prefix_tree_domain_t * most_subdomains_less;   /*< position in linked list, pointer to next domain, which has lower count of descendants*/
	prefix_tree_domain_t * most_subdomains_more;   /*< position in linked list, pointer to previous domain, which has higher count of descendants*/

} ;

/*!
 * \brief Structure - Prefix tree main structure
 * Structure used to keep information about prefix tree. It is main structure, witch contains all
 * information about prexix tree.
 */
typedef struct prefix_tree_t prefix_tree_t ;
 struct prefix_tree_t {
	prefix_tree_inner_node_t * root;   /*< Pointer to root node. */
	unsigned int count_of_domain_searched_just_ones;   /*< Count of domain, witch were searcehd just ones */
	unsigned int count_of_inserting;   /*< Count of inserting and searching (all domains) */
    unsigned int count_of_inserting_for_just_ones; /*< Count of inserting, but for percent value with variable count_of_domain_searched_just_ones*/
	unsigned int count_of_different_domains; /*< Count of unique domains*/
	prefix_tree_domain_t * list_of_most_used_domains;  /*< list of most searched domains*/
	prefix_tree_domain_t * list_of_most_used_domains_end;  /*< list of most searched domains - pointer to end of the list*/
	prefix_tree_domain_t * list_of_most_unused_domains;    /*< list of most searched domains end - most unsearched domains*/
	prefix_tree_domain_t ** list_of_most_subdomains;   /*< list of domains, which has most subdomains, it is 2D linked list. 1.D is deegre of domain name, 2. is linked list*/
	prefix_tree_domain_t ** list_of_most_subdomains_end;   /*< list of domains, which has most subdomains, it is 2D linked list.  Pointers on the end of lists*/
} ;





//********* ip address record *********

/*!
 * \name Default values
 *  Defines macros used by for histograms
 * \{ */
#define HISTOGRAM_SIZE_REQUESTS 30 /*< Default number of histogram size. */
#define HISTOGRAM_SIZE_RESPONSE 150 /*< Default number of histogram size. */
/* /} */

 /*!
 * \name Detection type states
 *  State of detection type. 
 * \{ */
#define STATE_NEW              0b00000000
#define STATE_SUSPISION        0b00000001
#define STATE_ATTACK           0b00000010
#define STATE_OK               0b10000000
/* /} */


/*!
 * \brief Structure - type detection request other anomaly
 * Structure used to keep information about type detection request other anomaly
 */
 typedef struct ip_address_suspision_request_other_t ip_address_suspision_request_other_t ;
 struct ip_address_suspision_request_other_t {
    unsigned char  state_request_size [HISTOGRAM_SIZE_REQUESTS]; /*!< state, for every size to store in prefix tree */
    prefix_tree_t * other_suspision;    /*!< pointer to prefix tree */
    unsigned int round_in_suspicion;   /*!< count of round in SUSPICTION state */
 } ;

/*!
 * \brief Structure - type detection request tunnel 
 * Structure used to keep information about type detection request tunnel 
 */
 typedef struct ip_address_suspision_request_tunnel_t ip_address_suspision_request_tunnel_t ;
 struct ip_address_suspision_request_tunnel_t {
    unsigned char  state_request_size [HISTOGRAM_SIZE_REQUESTS]; /*!< state, for every size to store in prefix tree */
    prefix_tree_t * tunnel_suspision;   /*!< pointer to prefix tree */
    unsigned int round_in_suspicion;   /*!< count of round in SUSPICTION state */
 } ;



/*!
 * \brief Structure - type detection response other anomaly
 * Structure used to keep information about type detection response other anomaly.
 */
 typedef struct ip_address_suspision_response_other_t ip_address_suspision_response_other_t ;
 struct ip_address_suspision_response_other_t {
    unsigned char  state_response_size [HISTOGRAM_SIZE_RESPONSE]; /*!< state, for every size to store in prefix tree */
    prefix_tree_t * other_suspision;    /*!< pointer to prefix tree */
    unsigned int round_in_suspicion;   /*!< count of round in SUSPICTION state */
    unsigned int without_string; /*!< count of response without request string */
    unsigned int packet_in_suspicion;  /*!< count of responses in suspicion */
 } ;

/*!
 * \name Suspicion posibilities
 *  This values are used to identify which string is contains anomaly. 
 *  It could be used in one variable all types.
 * \{ */
#define TXT_TUNNEL              0b00000001
#define CNAME_TUNNEL            0b00000010
#define MX_TUNNEL               0b00000100
#define NS_TUNNEL               0b00001000
#define REQUEST_STRING_TUNNEL   0b00010000 
/* /} */

/*!
 * \brief Structure - type detection response tunnel
 * Structure used to keep information about type detection response tunnel 
 */
typedef struct ip_address_suspision_response_tunnel_t ip_address_suspision_response_tunnel_t ;
 struct ip_address_suspision_response_tunnel_t {
    prefix_tree_t * txt_suspision;      /*!< pointer to prefix tree */
    prefix_tree_t * cname_suspision;    /*!< pointer to prefix tree */
    prefix_tree_t * mx_suspision;       /*!< pointer to prefix tree */
    prefix_tree_t * ns_suspision;       /*!< pointer to prefix tree */
    prefix_tree_t * request_suspision;  /*!< pointer to prefix tree */    
    unsigned char state_type;           /*!< records to store */
    unsigned int round_in_suspicion;   /*!< count of round in SUSPICTION state */
 } ;


/*!
 * \name Version of IP address
 *  Defines macros used in B+ tree and printing IP.
 * \{ */
#define IP_VERSION_4 4
#define IP_VERSION_6 6
/* /} */

/*!
 * \brief Structure containing calculated inforamtion about requests
 * Structure used to keep information about requests
 */
 typedef struct counter_request_t counter_request_t ;
 struct counter_request_t {
    unsigned long histogram_dns_requests [HISTOGRAM_SIZE_REQUESTS]; /*!< histogram values, requests */
    unsigned long histogram_dns_request_sum_for_cout_of_used_letter [HISTOGRAM_SIZE_REQUESTS]; /*!< histogram values, requests */
    unsigned long histogram_dns_request_ex_sum_of_used_letter [HISTOGRAM_SIZE_REQUESTS]; /*!< histogram values, ex of new letters, for size. 
                                                                                            At first it is sum, but on the end it has to be devided
                                                                                            by count of requests */    
    unsigned long dns_request_count; /*!< count of requests */
    unsigned long dns_request_string_count; /*!< count of requests string */
    unsigned long sum_Xi_request; /*!< Sum of sizes request */
    unsigned long sum_Xi2_request; /*!< Sum of sizes^2 request */
    //Could be used for improving the module                                                                                        
        //unsigned long sum_Xi3_request; /*!< Sum of sizes^3 request */
        //unsigned long sum_Xi4_request; /*!< Sum of sizes^4 request */
    unsigned int request_without_string; /*!< count of requests without string */
    unsigned char round_in_suspicion_request; /*!< number of round which Ip is in suspicion */   
};

/*!
 * \brief Structure containing calculated inforamtion about responses
 * Structure used to keep information about responses
 */
 typedef struct counter_response_t counter_response_t ;
 struct counter_response_t {
    unsigned long histogram_dns_response [HISTOGRAM_SIZE_RESPONSE]; /*!< histogram values, responses */   
    unsigned long dns_response_count; /*!< count of responses */
    unsigned long sum_Xi_response; /*!< Sum of sizes respone */
    unsigned long sum_Xi2_response; /*!< Sum of sizes^2 respone */
    //Could be used for improving the module
        //unsigned long sum_Xi3_response; /*!< Sum of sizes^3 respone */
        //unsigned long sum_Xi4_response; /*!< Sum of sizes^4 respone */
    unsigned char round_in_suspicion_response; /*!< number of round which Ip is in suspicion */    
};


/*!
 * \brief Structure containing inforamtion about each IP adress
 * Structure used to keep information about each Ip address.
 */
 typedef struct ip_address_t ip_address_t ;
 struct ip_address_t {
    unsigned char ip_version;            /*!< version of ip */
    unsigned char print;                 /*!< info about printing to results */
    counter_request_t counter_request;   /*!< counter struct for requests */
    counter_response_t counter_response; /*!< counter struct for responses */

    ip_address_suspision_request_tunnel_t * suspision_request_tunnel;   /*!< suspicion struc - finding tunnel in requests */
    ip_address_suspision_request_other_t * suspision_request_other;     /*!< state of finding other anomaly in requests */
    ip_address_suspision_response_tunnel_t * suspision_response_tunnel; /*!< state of finding tunnel in response */
    ip_address_suspision_response_other_t * suspision_response_other;     /*!< state of finding other anomaly in responses */

    unsigned char state_request_other;  /*!< state of finding other anomaly in requests */
    unsigned char state_request_tunnel; /*!< state of finding tunnel in requests */
    unsigned char state_response_other; /*!< state of finding other anomaly in response */
    unsigned char state_response_tunnel;/*!< state of finding tunnel in response */
} ;

/*!
 * \brief Structure containing calculated inforamtion about IP address
 * Structure used to keep information about IP address
 */
typedef struct calulated_result_t calulated_result_t ;
 struct calulated_result_t {
    unsigned long histogram_dns_request_ex_cout_of_used_letter [HISTOGRAM_SIZE_REQUESTS]; /*!< histogram values, ex of new letters, for size. 
                                                                                            At first it is sum, but on the end it has to be devided
                                                                                            by count of requests */
    float ex_response; /*!< middle value respone */
    float ex_request; /*!< middle value respone */
    float ex_request_count_of_different_letters; /*!< middle value of count letters */
    float var_response; /*!< diffusion respone */
    float var_request; /*!< diffusion request */
    float var_request_count_letters; /*!< middle value of count letters */
    float skewness_request; /*!< skewness request */
    float skewness_response; /*!< skewness response */
    float kurtosis_request; /*!< kurtosis request */
    float kurtosis_response; /*!< kurtosis response */
} ;

//********* packet from parser *********

#define MAX_SIZE_OF_REQUEST_DOMAIN 255
#define MAX_SIZE_OF_RESPONSE_STRING 1024
/*!
 * \brief Structure containing packet DNS
 * Structure used to keep information about DNS packet.
 */
 typedef struct packet_t packet_t ;
 struct packet_t {
    double time;
    uint64_t src_ip_v6[2];
    uint64_t dst_ip_v6[2];
    uint64_t src_ip_v4;
    uint64_t dst_ip_v4;
    unsigned char ip_version;
    unsigned int size;
    char is_response;
    char  request_string[MAX_SIZE_OF_REQUEST_DOMAIN];
    int request_length;
    char mx_response[MAX_SIZE_OF_RESPONSE_STRING];
    char ns_response[MAX_SIZE_OF_RESPONSE_STRING];
    char cname_response[MAX_SIZE_OF_RESPONSE_STRING];
    char txt_response[MAX_SIZE_OF_RESPONSE_STRING];
} ;


//********* values for searching anomaly *********

/*!
 * \brief Structure containing setting of the module
 * Structure used to keep information about setting of the module.
 */
typedef struct values_t values_t ;
struct values_t { 
    unsigned int time_of_one_session;  /*< Time of collecting packets */
    unsigned int ex_request_max;    /*< maximal value of request middle value */
    unsigned int ex_request_min;    /*< minimal value of request middle value */
    unsigned int ex_response_max;   /*< maximal value of response middle value */
    unsigned int ex_response_min;   /*< minimal value of response middle value */
    unsigned int var_request_max;   /*< maximal value of request var */
    unsigned int var_request_min;   /*< minimal value of request var*/
    unsigned int var_response_max;  /*< maximal value of response var */
    unsigned int var_response_min;  /*< minimal value of response var*/
    unsigned int kurtosis_request_min;  /*< maximal value of request var */
    unsigned int min_dns_request_count; /*< minimal value of dns count of packets */
    unsigned int min_dns_request_count_tunnel;  /*< minimal value of dns count in payload analysis for tunnel */
    unsigned int min_dns_request_count_other_anomaly;   /*< minimal value of dns count in payload analysis for other anomaly */
    unsigned int min_dns_response_count_tunnel; /*< minimal value of dns count in payload analysis for tunnel */
    unsigned int min_dns_response_count_other_anomaly;  /*< minimal value of dns count in payload analysis for other anomaly */
    unsigned int request_max_count_of_used_letters; /*< maximum number of used leeters for domain */
    unsigned int response_max_count_of_used_letters;    /*< maximum number of used leeters for domain */
    float max_percent_of_new_subdomains;    /*< maximum percent of new subdomain, more than this can be tunel */
    float min_percent_of_new_subdomains;    /*< minimum percent of new subdomain, less than this can be anomaly */
    float min_percent_of_domain_searching_just_once;    /*< minimum percent of searching unique domains, less than that can be anomaly */
    float max_percent_of_domain_searching_just_once;    /*< maximum percent of searching unique domains, more than that can be tunnel */
    float min_percent_of_unique_domains;    /*< minimum percent unique domains, less than that can be anomaly */
    float max_percent_of_unique_domains;    /*< maximum percent of searching unique domains, more than that can be tunne l*/
    float max_percent_of_numbers_in_domain_prefix_tree_filter;  /*< maximum percent of numbers in domain, more than that can be tunnel */
    float max_percent_of_mallformed_packet_request; /*< maximum percent of mallformed packet in requests */
    float max_percent_of_subdomains_in_main_domain; /*< Maximal value of request middle value */
    unsigned int max_count_of_numbers_in_domain_prefix_tree_filter; /*< maximum count of numbers in domain, more than that can be tunnel */
};



#endif /* _TUNNEL_DETECTION_DNS_STRUCTS_ */
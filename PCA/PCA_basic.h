/**
 * \file PCA_basic.h
 * \brief !!!TODO...
 * \author Pavel Krobot <xkrobo01@stud.fit.vutbr.cz>
 * \date 2013
 */
#ifndef _PCA_BASIC_H_
#define _PCA_BASIC_H_

#include <string>
#include <vector>

using namespace std;

#define DEFAULT_PATH_TO_SETTINGS "settings.txt"
#define SETTINGS_COMMENTARY_CHARACTER "#"

#define DEFAULT_UNIREC_SPECIFIER "TIMESLOT,LINK_BIT_FIELD,FLOWS,PACKETS,BYTES,ENTROPY_SRCIP,ENTROPY_DSTIP,ENTROPY_SRCPORT,ENTROPY_DSTPORT"
#define DEFAULT_UNIREC_SPECIFIER_DETECTION "TIMESLOT,LINK_BIT_FIELD"

//#define LOG_DST cout
#define LOG_DST log // name of "ofstream" variable
#define LOG_TO_FILE "PCA_basic-log"
#define ANOMALY_LOG_NAME "PCA-detector-anomaly_log.txt"

#define DEFAULT_AGREG_UNIT_CNT 7 //FLOWS,PACKETS,BYTES,E-SRCIP,E-DSTIP,E-SRCPORT,E-DSTPORT

#define RCV_OUT_OF_TIMEBIN_TOLERANCE 2 //defines "out of expected" tolerance for incoming timeslots of records

#define DEFAULT_WORKING_TIMEBIN_WINDOW_SIZE (288+21*12) // For better performance it should
//#define DEFAULT_WORKING_TIMEBIN_WINDOW_SIZE (7*288) // For better performance it should
                                // be power of 2 since the value is used for modulus

//#define PREPROCESS_DATA
#define PREPROCESS_DATA_DEV_MULTIPLIER 3

#define USE_JOINT_MATRIX_OP

//#define STD_DEV 0.35355339 // 1/sqrt(DEFAULT_WORKING_TIMEBIN_WINDOW_SIZE)
#define STD_DEV_VERSION2

//#define NORMAL_SUBSPACE_SIZE_FIXED 10
#define NSS_BY_PERCENTAGE 0.80
//#define NSS_BY_DELTA_TEST 5

#define DEFAULT_DETECTION_THRESHOLD 6//stdandard deviation multiplier

#define ALPHA_PERCENTILE_80 0.841621
#define ALPHA_PERCENTILE_85 1.036433
#define ALPHA_PERCENTILE_90 1.281552
#define ALPHA_PERCENTILE_95 1.644854
#define ALPHA_PERCENTILE_99 2.326348

#define REALLY_BIG_REAL_NUMBER 999999.9

#define NORM_AMOUNT_INDETIFICATION_THRESHOLD 1.0
#define IDENTIFICATION_TTL 4 // maximum of how many times could be found same index

#define VERBOSE_MSG
#ifdef VERBOSE_MSG
   #define STATUS_MSG(stream,msg) stream << msg << flush;
#else//VERBOSE_MSG
   #define STATUS_MSG(stream,msg) ;
#endif//VERBOSE_MSG

#define MASK_BIT(selector) (1 << selector)

#define MULTI_TEST
#ifdef MULTI_TEST
	#ifdef NSS_BY_DELTA_TEST
		#define NSS_DEF_CNT 7
	#else//NSS_BY_DELTA_TEST
		#define NSS_DEF_CNT 4
	#endif//NSS_BY_DELTA_TEST

	#define DELTA_TESTNIG_CNT 20

//	#define SPE_TESTING
	#ifdef SPE_TESTING
		#define A_PERCENTILE_DEF_CNT 5
		#define DETECTION_TEST_CNT DELTA_TESTNIG_CNT + A_PERCENTILE_DEF_CNT
	#else//SPE_TESTING
		#define DETECTION_TEST_CNT DELTA_TESTNIG_CNT
	#endif//SPE_TESTING

	#define STARTING_DETECTION_THRESOLD 3
	#define DETECTION_THRESHOLD_INCREMENT 0.2

	#define NSS_BY_PERCT_MULTIPLER(i) (float)(NSS_BY_PERCENTAGE + (i) * 0.05)

	#define DETECTION_THRESHOLD_MULTIPLIER(i) (float)(STARTING_DETECTION_THRESOLD + ((float)(i) * DETECTION_THRESHOLD_INCREMENT))

//	#define DETECTION_SELECTOR ((uint64_t) 0x1ff0000)
//	#define DETECTION_SELECTOR ((uint64_t) 0x00ffC00)
	#define DETECTION_SELECTOR ((uint64_t) 0b11111111110000000000)
//														  12345678901234567890


	#ifdef SPE_TESTING
	float A_PERCENTILES[A_PERCENTILE_DEF_CNT] = {0.841621, 1.036433, 1.281552, 1.644854, 2.326348};
	const char *A_PERC_NAMES [] =
	{
		"80%",
		"85%",
		"90%",
		"95%",
		"99%",
	};
	#endif//SPE_TESTING
#endif//MULTI_TEST


const char *SETTINGS_OPTION [] =
{
	"link count=",
	"links=",
	"agregation=",
	"window size=",
	"xxx=",
};
/**
 * Agregation unit names
 */
const char *AGREG_UNIT_NAME [] =
{
	"flows",
	"packets",
	"bytes",
	"ent_sip",
	"ent_dip",
	"ent_sport",
	"ent_dport",
	"unspecified-error",
};
/**
 * Agregation unit codes
 */
enum agreg_unit_code {
   AU_FLOWS = 0,
   AU_PACKETS,
   AU_BYTES,
   AU_ESIP,
   AU_EDIP,
   AU_ESPORT,
   AU_EDPORT,
};

typedef struct PCA_basic_settings {
   string path_to_settings;
   char *in_unirec_specifier;//used by detector only
   char *out_unirec_specifier;
	uint16_t link_count;
	vector <string> link_names;
	uint16_t agreg_unit_per_link;
	uint16_t agreg_unit_field;
	uint16_t data_matrix_width;//used by detector only
	uint32_t working_timebin_window_size;//used by detector only
} pca_basic_settings_t;



#endif
// END OF PCA_basic.h
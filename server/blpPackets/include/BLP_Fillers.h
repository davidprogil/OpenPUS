/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef BLPF_Fillers_H
#define BLPF_Fillers_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
#include <BLP_FillersUser.h>

/* macros-----------------------------------------------------------------------*/
//packet IDs
#define BLP_SETMODE_PACKETID (0x8001)
#define BLP_SETMODE_SERVICE ((BLP_SETMODE_PACKETID & (0xFF00)) >> 8)
#define BLP_SETMODE_SUBSERVICE (BLP_SETMODE_PACKETID & (0x00FF))

#define BLP_ALLTYPES_PACKETID (0x1780)
#define BLP_ALLTYPES_SERVICE ((BLP_ALLTYPES_PACKETID & (0xFF00)) >> 8)
#define BLP_ALLTYPES_SUBSERVICE (BLP_ALLTYPES_PACKETID & (0x00FF))


#define BLP_ALLRANGES_PACKETID (0x1781)
#define BLP_ALLRANGES_SERVICE ((BLP_ALLRANGES_PACKETID & (0xFF00)) >> 8)
#define BLP_ALLRANGES_SUBSERVICE (BLP_ALLRANGES_PACKETID & (0x00FF))

#define BLP_IMAGESEGMENT_PACKETID (0x8008)
#define BLP_IMAGESEGMENT_SERVICE ((BLP_IMAGESEGMENT_PACKETID & (0xFF00)) >> 8)
#define BLP_IMAGESEGMENT_SUBSERVICE (BLP_IMAGESEGMENT_PACKETID & (0x00FF))

#define BLP_FAILREPORT_PACKETID (0x0102)
#define BLP_FAILREPORT_SERVICE ((BLP_FAILREPORT_PACKETID & (0xFF00)) >> 8)
#define BLP_FAILREPORT_SUBSERVICE (BLP_FAILREPORT_PACKETID & (0x00FF))

/* types------------------------------------------------------------------------*/
//reusable types
typedef enum _BLP_EnumFid_t
{
	BLP_FID_OK=0,
	BLP_FID_BAD_LENGTH=1,
	BLP_FID_NO_PUS=2,
	BLP_FID_BAD_CRC=3,
	BLP_FID_BAD_PACKET_ID=4,
	BLP_FID_INCONSISTENT_SIZE=5,
	BLP_FID_INVALID_PARAMETER_VALUE=6,
	BLP_FID_NB
} BLP_EnumFid_t;

typedef enum _BLP_EnumMode_t
{
	BLP_MODE_SAFE=0,
	BLP_MODE_ALIVENESS=1,
	BLP_MODE_FLYBY=2,
	BLP_MODE_LANDING=3,
	BLP_MODE_NB
} BLP_EnumMode_t;

//auxiliary types

typedef struct __attribute__((packed)) _BLP_UnexpectedValueUint16_t_
{
	uint16_t expectedValue;
	uint16_t foundValue;
} BLP_UnexpectedValueUint16_t;

typedef struct __attribute__((packed)) _BLP_InvalidParameterValue_t_
{
	uint16_t parameterCounter;
} BLP_InvalidParameterValue_t;



//packet types
typedef struct __attribute__((packed)) _BLP_SetMode_t_
{
	CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
	uint8_t mode;
} BLP_SetMode_t;

typedef struct __attribute__((packed)) _BLP_AllTypes_t_
{
	CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
	uint8_t fieldUint8;
	int8_t fieldInt8;
	uint16_t fieldUint16;
	int16_t fieldInt16;
	uint32_t fieldUint32;
	int32_t fieldInt32;
	uint64_t fieldUint64;
	int64_t fieldInt64;
	float32_t fieldFloat32;
	float64_t fieldFloat64;
} BLP_AllTypes_t;

typedef struct __attribute__((packed)) _BLP_AllRanges_t_
{
	CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	PUS_TcSecondaryHeader_t pusTcSecondaryHeader;
	uint32_t maxIncUint32;
	uint32_t maxExcUint32;
	uint32_t minIncUint32;
	uint32_t minExcUint32;
	uint32_t fixedUint32;
	uint32_t minMaxUint32;
} BLP_AllRanges_t;

typedef struct __attribute__((packed)) _BLP_ImageSegment_t_
{
	CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	PUS_TmSecondaryHeader_t pusTmSecondaryHeader;
	uint16_t numberOfPixels;
	uint8_t pixel[20];
} BLP_ImageSegment_t;

typedef struct __attribute__((packed)) _BLP_FailReport_t_
{
	CCSDS_PrimaryHeader_t ccsdsPrimaryHeader;
	PUS_TmSecondaryHeader_t pusTmSecondaryHeader;
	PUS_AcceptanceReport_t pusAcceptanceReport;
	uint16_t failureId;
	union
	{
		BLP_UnexpectedValueUint16_t unexpectedValueUint16;
		BLP_InvalidParameterValue_t invalidParameterValue;
	} failureInfo;
} BLP_FailReport_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void BLPF_FillSetMode(BLP_SetMode_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TcSecondaryHeader_t *pusTcSecondaryHeader,BLP_EnumMode_t mode);
void BLPF_FillAllTypes(BLP_AllTypes_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TcSecondaryHeader_t *pusTcSecondaryHeader,uint8_t fieldUint8,int8_t fieldInt8,uint16_t fieldUint16,int16_t fieldInt16,uint32_t fieldUint32,int32_t fieldInt32,uint64_t fieldUint64,int64_t fieldInt64,float32_t fieldFloat32,float64_t fieldFloat64);
void BLPF_FillAllRanges(BLP_AllRanges_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TcSecondaryHeader_t *pusTcSecondaryHeader,uint32_t maxIncUint32,uint32_t maxExcUint32,uint32_t minIncUint32,uint32_t minExcUint32,uint32_t fixedUint32,uint32_t minMaxUint32);
void BLPF_FillImageSegment(BLP_ImageSegment_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TmSecondaryHeader_t *pusTmSecondaryHeader,uint16_t numberOfPixels,uint8_t *pixel);
void BLPF_FillFailReport(BLP_FailReport_t *target,CCSDS_PrimaryHeader_t *ccsdsPrimaryHeader,PUS_TmSecondaryHeader_t *pusTmSecondaryHeader,PUS_AcceptanceReport_t *pusAcceptanceReport,uint16_t failureId,void *failureInfo,uint16_t failureInfoNb);


/* end */
#endif /* BLPF_Fillers_H */


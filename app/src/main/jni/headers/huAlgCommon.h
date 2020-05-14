/***********************************************************************
* ˵��:�����ṩͳһ�㷨���ýṹ���ö�ٲ�����
*      ��ʹ�ÿɱ��������ʹ��ƽ̨��س�����������
*
* ����:�з���->�㷨��
************************************************************************/

#ifndef HU_ALG_COMMMON_H_
#define HU_ALG_COMMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)  
#ifdef HU_COMPILE_LIBRARY
#define ALG_STD_CALL __declspec(dllexport)
#else
#define ALG_STD_CALL __declspec(dllimport)
#endif
#elif defined(__linux__) || defined(__linux)  
#define ALG_STD_CALL __attribute__((visibility("default")))
#else
#define ALG_STD_CALL
#endif

/**********************ͨ���Դ�������************************/
#define ALG_OK         (0)
#define ALG_PTR_NULL  (-1)
#define ALG_PARAM_ERR (-2)
#define ALG_ERR_OTHER (-3)
/************************************************************/

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MID 
#define MID(a, b, c) ((a)<(b) ? ((b)<(c)?(b):(a)<(c)?(c):(a)) : ((b)>(c)?(b):(a)>(c)?(c):(a)))
#endif

#ifndef ABS
#define ABS(a) ((a) < (0) ? -(a) : (a))
#endif

#ifndef ABS_OPT
#define ABS_OPT(a, b) (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))
#endif

#ifdef NULL
#undef NULL
#endif

#ifdef __cplusplus
#define NULL (0)
#else
#define NULL ((void *)0)
#endif

#ifdef TRUE
#undef TRUE 
#endif
#define TRUE (1)

#ifdef FALSE
#undef FALSE
#endif
#define FALSE (0)

#define SF_PI             (3.14159265359f)
#define DBL_EPSILON_MIN   (2.2204460492503131e-016)
#define FLT_EPSILON_EPS   (1.192092896e-07f)
#define FLT_DIV_EPS       (1.0e-12f)
#define KEY_POINT_NUM	  (5u)
#define IMG_ALIGNMENT_BIT (0x1u)
#define TRACK_EMB_SIZE    (64u)

typedef unsigned long long ulong64;

typedef enum _IMG_TYPE_
{
	IMG_TYPE_YUV420   = 1,//֧��NV12��ʽu��vǰ
	IMG_TYPE_BGRPLANE = 2,//b0,b1...bn, g0,g1...gn, r0 r1...rn ��ɫ���а���opencv��ģʽ
	IMG_TYPE_BGRCUT   = 3,//b0 g0 r0, b1 g1 r1..., bn gn rn
	IMG_TYPE_JPEG_FILE= 4,//ֱ������jpeg�ļ�,�ļ�����INPUT_IMG->data����
	IMG_TYPE_JPEG_MEM = 5,//ֱ������jpeg�ڴ�����
}IMG_TYPE;

typedef struct _INPUT_IMG_
{
	IMG_TYPE       eImgType;//��������
	unsigned int   Ch;		//ʹ�õ�ͨ����1(yuv��������Ϣ)����3(��ɫ)
	unsigned int   Ts;		//����֡��ʱ���
	unsigned int   FrameNum;//����֡��֡��
	unsigned int   ImgW;	//����֡�Ŀ�-Ҫ����뵽 IMG_ALIGNMENT_BIT+1������ֱ�ӷ��ش���
	unsigned int   ImgH;	//����֡�ĸ�-Ҫ����뵽 IMG_ALIGNMENT_BIT+1������ֱ�ӷ��ش���
	unsigned int   ImgSize; //�������ݵ��ֽ��������������洢
	void*          data;	//�����׵�ַ,yuv����bgr��Ҫʹ�������ڴ洫�룬yuv��patch��w��Ҫ����һ�£�Ҫ��16����
}INPUT_IMG;

typedef enum _TRIGGER_TYPE_
{
	TRIGGER_NO = 0,   //û�д�����Ϣ
	TRIGGER_IN = 1,   //��������
	TRIGGER_OUT = 2,  //����ʻ��
}TRIGGER_TYPE;

typedef enum _SIZE_MODE_
{
	MODEL_SMALL  = 1, //Сģʽ
	MODEL_NORMAL = 2, //��ģʽ
	MODEL_BIG    = 3, //��ģʽ
}SIZE_MODE;

typedef struct _point_i32_ //����������-32λ������
{
	int x;
	int y;
}point_i32;

typedef struct _point_f32_ //����������-32λ����
{
	float x;
	float y;
}point_f32;

typedef struct _rect_i32_ //���ϽǼӿ��-32λ������
{
	int x;
	int y;
	int w;
	int h;
}rect_i32;

typedef struct _half_rect_i32_ //�м�Ӱ���-32λ������
{
	int centerX;
	int centerY;
	int halfW;
	int halfH;
}half_rect_i32;

typedef struct _rect_p_u16 //����ָ��-16λ�޷���
{
	unsigned short x0;
	unsigned short y0;
	unsigned short x1;
	unsigned short y1;
}rect_p_u16;

typedef struct _face_rect_ //���ϽǼӿ��-32λ������
{
	rect_i32 rect;
	float Point[KEY_POINT_NUM * 2];//Ŀ��ؼ���
}face_rect;

typedef struct _rect_f32_ //���ϽǼӿ��-32λ����
{
	float x;
	float y;
	float w;
	float h;
}rect_f32;

typedef struct _line_i32_ //�߶�����-32λ������
{
	point_i32 start;
	point_i32 end;
}line_i32;

typedef struct _line_f32_ //�߶�����-32λ����
{
	point_f32 start;
	point_f32 end;
}line_f32;

typedef struct _size_img_ //��С����-32λ�޷���
{
	unsigned int Width;
	unsigned int Height;
}size_img;

typedef struct _target_out_s_ //��׼Ŀ�������ʽ
{
	unsigned int Id;		//Ŀ��id
	unsigned int Ts;		//Ŀ����֡��ʱ���
	unsigned int FrameNum;  //Ŀ����֡
	unsigned int Score;		//Ŀ�����0-100
	unsigned int Update;	//�����Ƿ��֮ǰ��Ŀ����ɿ�-����㷨���1ʱ������score�Ƿ��֮ǰ�Ĵ󣬶����Ը���
	unsigned int Visible;	//Ŀ���Ƿ�ɿ������������������Ϊ�㷨Ԥ��ֵʱ���ñ�־Ϊ0;����ʱ��Ϊ1
	unsigned int EndFlag;	//Ŀ�������־-�и���ʱ��������
	float Point[KEY_POINT_NUM * 2];//Ŀ��ؼ���
	rect_f32     rect;		//Ŀ�����򣬶������ʱʹ�ù�һ��
	float Emb[TRACK_EMB_SIZE];//Ŀ����������λ
	unsigned char Res[8];	//Ԥ��λ
}target_out_s;

#ifdef __cplusplus
};
#endif

#endif // ! HU_ALG_COMMMON_H_

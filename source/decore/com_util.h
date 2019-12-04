/**************************************************************************************
 * Copyright (C) 2018-2019 uavs3d project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Open-Intelligence Open Source License V1.1.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Open-Intelligence Open Source License V1.1 for more details.
 *
 * You should have received a copy of the Open-Intelligence Open Source License V1.1
 * along with this program; if not, you can download it on:
 * http://www.aitisa.org.cn/uploadfile/2018/0910/20180910031548314.pdf
 *
 * For more information, contact us at rgwang@pkusz.edu.cn.
 **************************************************************************************/

#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include "com_type.h"

/* function selection define based on platforms */
#if (defined(__ANDROID__) && defined(__aarch64__)) || (defined(__APPLE__) && defined(__arm64__))
#define ENABLE_FUNCTION_C 1
#define ENABLE_FUNCTION_ARM64 1
#elif (defined(__ANDROID__) && defined(__arm__)) || (defined(__APPLE__) && defined(__ARM_NEON__))
#define ENABLE_FUNCTION_C 1
#define ENABLE_FUNCTION_ARM32 1
#elif (defined(__WIN32__) || defined(_WIN32)) || (defined(__MACOSX__) || defined(macintosh) || defined(__linux__) || defined(__unix__)) && (defined(__i386__) || defined(__x86_64__) || defined(__AMD64__))
#define ENABLE_FUNCTION_X86 1
#define ENABLE_FUNCTION_C 1
#else 
#define ENABLE_FUNCTION_C 1
#endif 

typedef struct uavs3d_funs_handle_t {
    void(*ipcpy[BLOCK_WIDTH_TYPES_NUM]) (const pel *src, int i_src, pel *dst, int i_dst, int width, int height);
    void(*ipflt[NUM_IPFILTER][BLOCK_WIDTH_TYPES_NUM]) (const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff, int max_val);
    void(*ipflt_ext[NUM_IPFILTER_Ext][BLOCK_WIDTH_TYPES_NUM]) (const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coef_x, const s8 *coef_y, int max_val);
    void(*avg_pel[BLOCK_WIDTH_TYPES_NUM])(pel *dst, int i_dst, pel *src1, pel *src2, int width, int height);
    void(*avg_pel_rect)(pel *dst, int i_dst, pel *src1, int i_src1, pel *src2, int i_src2, int width, int height); // for watermark
    void(*recon_luma[BLOCK_WIDTH_TYPES_NUM])(s16 *resi, pel *pred, int i_pred, int width, int height, pel *rec, int i_rec, int cbf, int bit_depth);
    void(*recon_chroma[BLOCK_WIDTH_TYPES_NUM])(s16 *resi_u, s16 *resi_v, pel *pred, int width, int height, pel *rec, int i_rec, u8 cbf[2], int bit_depth);

    void(*itrans_dct2[MAX_TR_LOG2][MAX_TR_LOG2])(s16 *coef, s16 *resi, int bit_depth);
    void(*itrans_dct8[MAX_TR_LOG2 - 2])(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);
    void(*itrans_dst7[MAX_TR_LOG2 - 2])(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);

    void(*deblock_luma[2])(pel *src, int stride, int alpha, int beta, int flag);
    void(*deblock_chroma[2])(pel *srcuv, int stride, int alphau, int betau, int alphav, int betav, int flag);
    void(*sao[2])(pel *src, int i_src, pel *dst, int i_dst, com_sao_param_t *sao_params, int smb_pix_height, int smb_pix_width,
        int smb_available_left, int smb_available_right, int smb_available_up, int smb_available_down, int sample_bit_depth);

    /* alf[3] idx: 0(Y); 1(U or V); 2(U and V) */
    void(*alf[3])(pel *dst, int i_dst, pel *src, int i_src, int lcu_width, int lcu_height, int *coef, int sample_bit_depth);
    void(*alf_fix[2])(pel *dst, int i_dst, pel *src, int i_src, int lcu_width, int lcu_height, int *coef, int sample_bit_depth);

    void(*intra_pred_dc[2])(pel *src, pel *dst, int i_dst, int width, int height, u16 cu_avail, int bit_depth);
    void(*intra_pred_plane[2])(pel *src, pel *dst, int i_dst, int width, int height, int bit_depth);
    void(*intra_pred_bi[2])(pel *src, pel *dst, int i_dst, int width, int height, int bit_depth);
    void(*intra_pred_plane_ipf)(pel *src, s16 *dst, int width, int height);
    void(*intra_pred_bi_ipf)(pel *src, s16 *dst, int width, int height);
    void(*intra_pred_ver[2])(pel *src, pel *dst, int i_dst, int width, int height);
    void(*intra_pred_hor[2])(pel *src, pel *dst, int i_dst, int width, int height);
    void(*intra_pred_ang       [IPD_CNT])(pel *pSrc, pel *dst, int i_dst, int uiDirMode, int iWidth, int iHeight);
    void(*intra_pred_chroma_ang[IPD_CNT])(pel *pSrc, pel *dst, int i_dst, int uiDirMode, int iWidth, int iHeight);
    void(*intra_pred_ipf)(pel *src, pel *dst, int i_dst, int flt_range_hor, int flt_range_ver, const s8* flt_hor_coef, const s8* flt_ver_coef, int w, int h, int bit_depth);
    void(*intra_pred_ipf_s16)(pel *src, pel *dst, int i_dst, s16* pred, int flt_range_hor, int flt_range_ver, const s8* flt_hor_coef, const s8* flt_ver_coef, int w, int h, int bit_depth);

    void(*padding_rows_luma)(pel *src, int i_src, int width, int height, int start, int rows, int padh, int padv);
    void(*padding_rows_chroma)(pel *src, int i_src, int width, int height, int start, int rows, int padh, int padv);

    void(*conv_fmt_8bit)(unsigned char* src_y, unsigned char* src_uv, unsigned char* dst[3], int width, int height, int stride, int stridec, int dst_stride[3], int uv_shift);
    void(*conv_fmt_16bit)(unsigned char* src_y, unsigned char* src_uv, unsigned char* dst[3], int width, int height, int stride, int stridec, int dst_stride[3], int uv_shift);
    void(*conv_fmt_16to8bit)(unsigned char* src_y, unsigned char* src_uv, unsigned char* dst[3], int width, int height, int stride, int stridec, int dst_stride[3], int uv_shift);

    void(*reset_map_scu)(com_scu_t *map_scu, int length);
} uavs3d_funs_handle_t;

extern uavs3d_funs_handle_t uavs3d_funs_handle;

#if ENABLE_FUNCTION_C
void uavs3d_funs_init_mc_c();
void uavs3d_funs_init_intra_pred_c();
void uavs3d_funs_init_itrans_c();
void uavs3d_funs_init_recon_c();
void uavs3d_funs_init_deblock_c();
void uavs3d_funs_init_sao_c();
void uavs3d_funs_init_alf_c();
void uavs3d_funs_init_c();
#endif

#if ENABLE_FUNCTION_X86
int  uavs3d_simd_avx_level(int* phwavx);
void uavs3d_funs_init_sse();
void uavs3d_funs_init_avx2();
#endif

#if ENABLE_FUNCTION_ARM64
void uavs3d_funs_init_arm64();
#endif

#if ENABLE_FUNCTION_ARM32
void uavs3d_funs_init_armv7();
#endif

com_core_t*  com_core_init(com_seqh_t *seqhdr);
void         com_core_free(com_core_t *core);

com_pic_t *   com_pic_alloc(com_pic_param_t * pic_param, int * ret);
void          com_pic_free(com_pic_param_t *pic_param, com_pic_t *pic);
int           com_md5_image(com_pic_t *pic, u8 digest[16]);

void com_lbac_ctx_init(com_lbac_all_ctx_t *sbac_ctx);
void com_dct_coef_init();
void com_dct_coef_destroy();

#ifndef _WIN32
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif

uavs3d_always_inline void uavs3d_check_ref_avaliable(com_pic_t *pic, int line_num)
{
    if (pic->finished_line < line_num) {
        uavs3d_pthread_mutex_lock(&pic->mutex);
        while (pic->finished_line < line_num) {
            uavs3d_pthread_cond_wait(&pic->cond, &pic->mutex);
        }
        uavs3d_pthread_mutex_unlock(&pic->mutex);
    }
}

static uavs3d_always_inline void com_mset_pel(pel * dst, s16 v, int cnt)
{
#if (BIT_DEPTH == 8)
    memset(dst, v, cnt);
#else 
    int i;
    for (i = 0; i < cnt; i++) {
        dst[i] = v;
    }
#endif
}

static uavs3d_always_inline void com_mset_2pel(pel * dst, int v, int cnt)
{
    int i;
#if (BIT_DEPTH == 8)
    s16 *pdst = (s16*)dst;
    for (i = 0; i < cnt; i++) {
        pdst[i] = v;
    }
#else 
    int *pdst = (int*)dst;
    for (i = 0; i < cnt; i++) {
        pdst[i] = v;
    }
#endif
}

static uavs3d_always_inline void com_mcpy_2pel(pel * dst, pel *src)
{
#if (BIT_DEPTH == 8)
    M16(dst) = M16(src);
#else 
    M32(dst) = M32(src);
#endif
}
static uavs3d_always_inline void com_mcpy_4pel(pel * dst, pel *src)
{
#if (BIT_DEPTH == 8)
    M32(dst) = M32(src);
#else 
    //M64(dst) = M64(src);
    M32(dst) = M32(src);
    M32(dst + 2) = M32(src + 2);
#endif
}
void *align_malloc(int i_size);
void align_free(void *p);


#endif /* __COM_UTIL_H__ */

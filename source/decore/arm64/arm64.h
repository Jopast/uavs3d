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

#if defined(__aarch64__) && !defined(__arm64__)
#define __arm64__ 1
#endif

#if defined(__arm64__)
#ifndef __ARM64_H__
#define __ARM64_H__

#include "../com_def.h"
#include "../com_util.h"

void uavs3d_sao_on_lcu_arm64(pel *src, int i_src, pel *dst, int i_dst, com_sao_param_t *sao_params, int smb_pix_height, int smb_pix_width, int smb_available_left, int smb_available_right, int smb_available_up, int smb_available_down, int sample_bit_depth);
void uavs3d_sao_on_lcu_chroma_arm64(pel *src, int i_src, pel *dst, int i_dst, com_sao_param_t *sao_params, int smb_pix_height, int smb_pix_width, int smb_available_left, int smb_available_right, int smb_available_up, int smb_available_down, int sample_bit_depth);
void uavs3d_alf_one_lcu_arm64(pel *dst, int i_dst, pel *src, int i_src, int lcu_width, int lcu_height, int *coef, int sample_bit_depth);
void uavs3d_alf_one_lcu_chroma_arm64(pel *dst, int i_dst, pel *src, int i_src, int lcu_width, int lcu_height, int *coef, int sample_bit_depth);
void uavs3d_alf_one_lcu_one_chroma_arm64(pel *dst, int i_dst, pel *src, int i_src, int lcu_width, int lcu_height, int *coef, int sample_bit_depth);

void uavs3d_deblock_ver_luma_arm64(pel *src, int stride, int Alpha, int Beta, int flt_flag);
void uavs3d_deblock_hor_luma_arm64(pel *src, int stride, int Alpha, int Beta, int flt_flag);
void uavs3d_deblock_ver_chroma_arm64(pel *srcuv, int stride, int alpha_u, int beta_u, int alpha_v, int beta_v, int flt_flag);
void uavs3d_deblock_hor_chroma_arm64(pel *srcuv, int stride, int alpha_u, int beta_u, int alpha_v, int beta_v, int flt_flag);

void uavs3d_if_cpy_w4_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height);
void uavs3d_if_cpy_w8_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height);
void uavs3d_if_cpy_w16_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height);
void uavs3d_if_cpy_w32_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height);
void uavs3d_if_cpy_w64_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height);
void uavs3d_if_cpy_w128_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height);

void uavs3d_if_hor_chroma_w8_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_chroma_w16_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_chroma_w16x_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_chroma_w32_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_chroma_w32x_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_luma_w4_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_luma_w8_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_luma_w16_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_luma_w16x_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_luma_w32_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_hor_luma_w32x_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);

void uavs3d_if_ver_chroma_w8_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_chroma_w16_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_chroma_w32_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_chroma_w32x_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_chroma_w64_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_chroma_w128_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_luma_w4_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_luma_w8_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_luma_w16_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_luma_w16x_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_luma_w32_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);
void uavs3d_if_ver_luma_w32x_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, s8 const *coeff, int max_val);

void uavs3d_if_hor_ver_chroma_w8_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff_h, const s8 *coeff_v, int max_val);
void uavs3d_if_hor_ver_chroma_w16_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff_h, const s8 *coeff_v, int max_val);
void uavs3d_if_hor_ver_chroma_w32_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff_h, const s8 *coeff_v, int max_val);
void uavs3d_if_hor_ver_chroma_w32x_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff_h, const s8 *coeff_v, int max_val);
void uavs3d_if_hor_ver_luma_w4_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff_h, const s8 *coeff_v, int max_val);
void uavs3d_if_hor_ver_luma_w8_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff_h, const s8 *coeff_v, int max_val);
void uavs3d_if_hor_ver_luma_w16_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff_h, const s8 *coeff_v, int max_val);
void uavs3d_if_hor_ver_luma_w32_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff_h, const s8 *coeff_v, int max_val);
void uavs3d_if_hor_ver_luma_w32x_arm64(const pel *src, int i_src, pel *dst, int i_dst, int width, int height, const s8 *coeff_h, const s8 *coeff_v, int max_val);

void uavs3d_itrans_dct2_h4_w4_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h4_w8_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h4_w16_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h4_w32_arm64(s16 *src, s16 *dst, int bit_depth);

void uavs3d_itrans_dct2_h8_w4_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h8_w8_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h8_w16_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h8_w32_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h8_w64_arm64(s16 *src, s16 *dst, int bit_depth);

void uavs3d_itrans_dct2_h16_w4_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h16_w8_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h16_w16_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h16_w32_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h16_w64_arm64(s16 *src, s16 *dst, int bit_depth);

void uavs3d_itrans_dct2_h32_w4_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h32_w8_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h32_w16_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h32_w32_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h32_w64_arm64(s16 *src, s16 *dst, int bit_depth);

void uavs3d_itrans_dct2_h64_w8_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h64_w16_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h64_w32_arm64(s16 *src, s16 *dst, int bit_depth);
void uavs3d_itrans_dct2_h64_w64_arm64(s16 *src, s16 *dst, int bit_depth);

void uavs3d_itrans_dct8_pb4_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);
void uavs3d_itrans_dct8_pb8_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);
void uavs3d_itrans_dct8_pb16_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);
void uavs3d_itrans_dct8_pb32_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);
void uavs3d_itrans_dst7_pb4_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);
void uavs3d_itrans_dst7_pb8_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);
void uavs3d_itrans_dst7_pb16_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);
void uavs3d_itrans_dst7_pb32_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val, s8 *it);

void uavs3d_avg_pel_w4_arm64(pel *dst, int i_dst, pel *src1, pel *src2, int width, int height);
void uavs3d_avg_pel_w8_arm64(pel *dst, int i_dst, pel *src1, pel *src2, int width, int height);
void uavs3d_avg_pel_w16_arm64(pel *dst, int i_dst, pel *src1, pel *src2, int width, int height);
void uavs3d_avg_pel_w32_arm64(pel *dst, int i_dst, pel *src1, pel *src2, int width, int height);
void uavs3d_avg_pel_w64_arm64(pel *dst, int i_dst, pel *src1, pel *src2, int width, int height);
void uavs3d_avg_pel_w128_arm64(pel *dst, int i_dst, pel *src1, pel *src2, int width, int height);

void uavs3d_conv_fmt_8bit_arm64(u8* src_y, u8* src_uv, u8* dst[3], int width, int height, int stride, int stridec, int dst_stride[3], int uv_shift);
void uavs3d_conv_fmt_16bit_arm64(u8* src_y, u8* src_uv, u8* dst[3], int width, int height, int stride, int stridec, int dst_stride[3], int uv_shift);
void uavs3d_padding_rows_lr_arm64(pel *src, int i_src, int width, int height, int pad);
void uavs3d_padding_rows_chroma_lr_arm64(pel *src, int i_src, int width, int height, int pad);

void uavs3d_intra_pred_ver_arm64(pel *src, pel *dst, int i_dst, int w, int h);
void uavs3d_intra_pred_hor_arm64(pel *src, pel *dst, int i_dst, int w, int h);
void uavs3d_intra_pred_hor_uv_arm64(pel *src, pel *dst, int i_dst, int w, int h);
void uavs3d_intra_pred_dc_arm64(pel *src, pel *dst, int i_dst, int w, int h, u16 avail_cu, int bit_depth);
void uavs3d_intra_pred_dc_uv_arm64(pel *src, pel *dst, int i_dst, int w, int h, u16 avail_cu, int bit_depth);
void uavs3d_intra_pred_plane_arm64(pel *src, pel *dst, int i_dst, int w, int h, int bit_depth);
void uavs3d_intra_pred_plane_uv_arm64(pel *src, pel *dst, int i_dst, int w, int h, int bit_depth);
void uavs3d_intra_pred_plane_ipf_arm64(pel *src, s16 *dst, int w, int h);
void uavs3d_intra_pred_bi_arm64(pel *src, pel *dst, int i_dst, int w, int h, int bit_depth);
void uavs3d_intra_pred_bi_ipf_arm64(pel *src, s16 *dst, int w, int h);
void uavs3d_intra_pred_ipf_arm64(pel *src, pel *dst, int i_dst, int flt_range_hor, int flt_range_ver, const s8 *flt_coef_hor, const s8 *flt_coef_ver, int w, int h, int bit_depth);
void uavs3d_intra_pred_ipf_s16_arm64(pel *src, pel *dst, int i_dst, s16 *pred, int flt_range_hor, int flt_range_ver, const s8 *flt_coef_hor, const s8 *flt_coef_ver, int w, int h, int bit_depth);

#endif // #ifndef __NEON_H__
#endif

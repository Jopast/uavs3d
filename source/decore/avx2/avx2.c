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

#include "avx2.h"

#if (BIT_DEPTH == 8)
void uavs3d_funs_init_avx2()
{
    uavs3d_funs_handle.ipcpy[3] = uavs3d_if_cpy_w32_avx2;
    uavs3d_funs_handle.ipcpy[4] = uavs3d_if_cpy_w64_avx2;
    uavs3d_funs_handle.ipcpy[5] = uavs3d_if_cpy_w128_avx2;

    uavs3d_funs_handle.ipflt[IPFILTER_H_4][1] = uavs3d_if_hor_chroma_w8_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_4][2] = uavs3d_if_hor_chroma_w16_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_4][3] = uavs3d_if_hor_chroma_w32_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_4][4] = uavs3d_if_hor_chroma_w32x_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_4][5] = uavs3d_if_hor_chroma_w32x_avx2;

    uavs3d_funs_handle.ipflt[IPFILTER_H_8][0] = uavs3d_if_hor_luma_w4_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_8][1] = uavs3d_if_hor_luma_w8_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_8][2] = uavs3d_if_hor_luma_w16_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_8][3] = uavs3d_if_hor_luma_w32_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_8][4] = uavs3d_if_hor_luma_w32x_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_8][5] = uavs3d_if_hor_luma_w32x_avx2;

    uavs3d_funs_handle.ipflt[IPFILTER_V_4][1] = uavs3d_if_ver_chroma_w8_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_4][2] = uavs3d_if_ver_chroma_w16_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_4][3] = uavs3d_if_ver_chroma_w32_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_4][4] = uavs3d_if_ver_chroma_w64_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_4][5] = uavs3d_if_ver_chroma_w128_avx2;

    uavs3d_funs_handle.ipflt[IPFILTER_V_8][0] = uavs3d_if_ver_luma_w4_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_8][1] = uavs3d_if_ver_luma_w8_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_8][2] = uavs3d_if_ver_luma_w16_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_8][3] = uavs3d_if_ver_luma_w32_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_8][4] = uavs3d_if_ver_luma_w64_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_8][5] = uavs3d_if_ver_luma_w128_avx2;

    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][1] = uavs3d_if_hor_ver_chroma_w8_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][2] = uavs3d_if_hor_ver_chroma_w16_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][3] = uavs3d_if_hor_ver_chroma_w32x_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][4] = uavs3d_if_hor_ver_chroma_w32x_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][5] = uavs3d_if_hor_ver_chroma_w32x_avx2;

    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][0] = uavs3d_if_hor_ver_luma_w4_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][1] = uavs3d_if_hor_ver_luma_w8_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][2] = uavs3d_if_hor_ver_luma_w16_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][3] = uavs3d_if_hor_ver_luma_w32_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][4] = uavs3d_if_hor_ver_luma_w32x_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][5] = uavs3d_if_hor_ver_luma_w32x_avx2;

    uavs3d_funs_handle.avg_pel[1] = uavs3d_avg_pel_w8_avx2;
    uavs3d_funs_handle.avg_pel[2] = uavs3d_avg_pel_w16_avx2;
    uavs3d_funs_handle.avg_pel[3] = uavs3d_avg_pel_w32_avx2;
    uavs3d_funs_handle.avg_pel[4] = uavs3d_avg_pel_w64_avx2;
    uavs3d_funs_handle.avg_pel[5] = uavs3d_avg_pel_w128_avx2;
    uavs3d_funs_handle.conv_fmt_8bit = uavs3d_conv_fmt_8bit_avx2;
    uavs3d_funs_handle.conv_fmt_16bit = uavs3d_conv_fmt_16bit_avx2;
    uavs3d_funs_handle.conv_fmt_16to8bit = uavs3d_conv_fmt_16to8bit_avx2;

    uavs3d_funs_handle.sao[ Y_C] = uavs3d_sao_on_lcu_avx2;
    uavs3d_funs_handle.sao[UV_C] = uavs3d_sao_on_lcu_chroma_avx2;
    uavs3d_funs_handle.alf[ Y_C] = uavs3d_alf_one_lcu_avx2;
    uavs3d_funs_handle.alf[UV_C] = uavs3d_alf_one_lcu_chroma_avx2;
    uavs3d_funs_handle.alf[2] = uavs3d_alf_one_lcu_one_chroma_avx2;

    uavs3d_funs_handle.intra_pred_hor[Y_C] = uavs3d_ipred_hor_avx2;
    uavs3d_funs_handle.intra_pred_ver[Y_C] = uavs3d_ipred_ver_avx2;
    uavs3d_funs_handle.intra_pred_dc [Y_C] = uavs3d_ipred_dc_avx2;

    uavs3d_funs_handle.recon_luma[2] = uavs3d_recon_luma_w16_avx2;
    uavs3d_funs_handle.recon_luma[3] = uavs3d_recon_luma_w32_avx2;
    uavs3d_funs_handle.recon_luma[4] = uavs3d_recon_luma_w64_avx2;

    uavs3d_funs_handle.recon_chroma[2] = uavs3d_recon_chroma_w16_avx2;
    uavs3d_funs_handle.recon_chroma[3] = uavs3d_recon_chroma_w16x_avx2;
    uavs3d_funs_handle.recon_chroma[4] = uavs3d_recon_chroma_w16x_avx2;
    uavs3d_funs_handle.recon_chroma[5] = uavs3d_recon_chroma_w16x_avx2;

    uavs3d_funs_handle.itrans_dct2[1][2] = itrans_dct2_h4_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[1][3] = itrans_dct2_h4_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[1][4] = itrans_dct2_h4_w32_avx2;

    uavs3d_funs_handle.itrans_dct2[2][1] = itrans_dct2_h8_w4_avx2;
    uavs3d_funs_handle.itrans_dct2[2][2] = itrans_dct2_h8_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[2][3] = itrans_dct2_h8_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[2][4] = itrans_dct2_h8_w32_avx2;
    uavs3d_funs_handle.itrans_dct2[2][5] = itrans_dct2_h8_w64_avx2;

    uavs3d_funs_handle.itrans_dct2[3][1] = itrans_dct2_h16_w4_avx2;
    uavs3d_funs_handle.itrans_dct2[3][2] = itrans_dct2_h16_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[3][3] = itrans_dct2_h16_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[3][4] = itrans_dct2_h16_w32_avx2;
    uavs3d_funs_handle.itrans_dct2[3][5] = itrans_dct2_h16_w64_avx2;

    uavs3d_funs_handle.itrans_dct2[4][1] = itrans_dct2_h32_w4_avx2;
    uavs3d_funs_handle.itrans_dct2[4][2] = itrans_dct2_h32_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[4][3] = itrans_dct2_h32_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[4][4] = itrans_dct2_h32_w32_avx2;
    uavs3d_funs_handle.itrans_dct2[4][5] = itrans_dct2_h32_w64_avx2;

    uavs3d_funs_handle.itrans_dct2[5][2] = itrans_dct2_h64_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[5][3] = itrans_dct2_h64_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[5][4] = itrans_dct2_h64_w32_avx2;
    uavs3d_funs_handle.itrans_dct2[5][5] = itrans_dct2_h64_w64_avx2;

    uavs3d_funs_handle.itrans_dct8[0] = itrans_dct8_pb4_avx2;
    uavs3d_funs_handle.itrans_dct8[1] = itrans_dct8_pb8_avx2;
    uavs3d_funs_handle.itrans_dct8[2] = itrans_dct8_pb16_avx2;
    //uavs3d_funs_handle.itrans_dct8[3] = itrans_dct8_pb32_avx2; //��δ�����ã�δ����

    uavs3d_funs_handle.itrans_dst7[0] = itrans_dst7_pb4_avx2;
    uavs3d_funs_handle.itrans_dst7[1] = itrans_dst7_pb8_avx2;
    uavs3d_funs_handle.itrans_dst7[2] = itrans_dst7_pb16_avx2;
    //uavs3d_funs_handle.itrans_dst7[3] = itrans_dst7_pb32_avx2;
}

#else
void uavs3d_funs_init_avx2()
{
    uavs3d_funs_handle.ipcpy[2] = uavs3d_if_cpy_w16_avx2;
    uavs3d_funs_handle.ipcpy[3] = uavs3d_if_cpy_w32_avx2;
    uavs3d_funs_handle.ipcpy[4] = uavs3d_if_cpy_w64_avx2;
    uavs3d_funs_handle.ipcpy[5] = uavs3d_if_cpy_w128_avx2;

    uavs3d_funs_handle.ipflt[IPFILTER_H_4][2] = uavs3d_if_hor_chroma_w16_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_4][3] = uavs3d_if_hor_chroma_w16x_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_4][4] = uavs3d_if_hor_chroma_w16x_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_4][5] = uavs3d_if_hor_chroma_w16x_avx2;

    uavs3d_funs_handle.ipflt[IPFILTER_H_8][2] = uavs3d_if_hor_luma_w16_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_8][3] = uavs3d_if_hor_luma_w16x_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_8][4] = uavs3d_if_hor_luma_w16x_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_H_8][5] = uavs3d_if_hor_luma_w16x_avx2;

    uavs3d_funs_handle.ipflt[IPFILTER_V_4][2] = uavs3d_if_ver_chroma_w16_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_4][3] = uavs3d_if_ver_chroma_w32_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_4][4] = uavs3d_if_ver_chroma_w32x_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_4][5] = uavs3d_if_ver_chroma_w32x_avx2;

    uavs3d_funs_handle.ipflt[IPFILTER_V_8][2] = uavs3d_if_ver_luma_w16_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_8][3] = uavs3d_if_ver_luma_w16x_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_8][4] = uavs3d_if_ver_luma_w16x_avx2;
    uavs3d_funs_handle.ipflt[IPFILTER_V_8][5] = uavs3d_if_ver_luma_w16x_avx2;

    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][1] = uavs3d_if_hor_ver_chroma_w8_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][2] = uavs3d_if_hor_ver_chroma_w16x_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][3] = uavs3d_if_hor_ver_chroma_w16x_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][4] = uavs3d_if_hor_ver_chroma_w16x_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_4][5] = uavs3d_if_hor_ver_chroma_w16x_avx2;

    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][2] = uavs3d_if_hor_ver_luma_w16x_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][3] = uavs3d_if_hor_ver_luma_w16x_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][4] = uavs3d_if_hor_ver_luma_w16x_avx2;
    uavs3d_funs_handle.ipflt_ext[IPFILTER_EXT_8][5] = uavs3d_if_hor_ver_luma_w16x_avx2;

    uavs3d_funs_handle.avg_pel[0] = uavs3d_avg_pel_w4_avx2;
    uavs3d_funs_handle.avg_pel[1] = uavs3d_avg_pel_w8_avx2;
    uavs3d_funs_handle.avg_pel[2] = uavs3d_avg_pel_w16_avx2;
    uavs3d_funs_handle.avg_pel[3] = uavs3d_avg_pel_w32_avx2;
    uavs3d_funs_handle.avg_pel[4] = uavs3d_avg_pel_w64_avx2;
    uavs3d_funs_handle.avg_pel[5] = uavs3d_avg_pel_w128_avx2;
    uavs3d_funs_handle.padding_rows_luma = uavs3d_padding_rows_luma_avx2;
    uavs3d_funs_handle.padding_rows_chroma = uavs3d_padding_rows_chroma_avx2;
    uavs3d_funs_handle.conv_fmt_8bit = uavs3d_conv_fmt_8bit_avx2;
    uavs3d_funs_handle.conv_fmt_16bit = uavs3d_conv_fmt_16bit_avx2;
    uavs3d_funs_handle.conv_fmt_16to8bit = uavs3d_conv_fmt_16to8bit_avx2;

    uavs3d_funs_handle.recon_luma[1] = uavs3d_recon_luma_w8_avx2;
    uavs3d_funs_handle.recon_luma[2] = uavs3d_recon_luma_w16_avx2;
    uavs3d_funs_handle.recon_luma[3] = uavs3d_recon_luma_w32_avx2;
    uavs3d_funs_handle.recon_luma[4] = uavs3d_recon_luma_w64_avx2;

    uavs3d_funs_handle.recon_chroma[2] = uavs3d_recon_chroma_w16_avx2;
    uavs3d_funs_handle.recon_chroma[3] = uavs3d_recon_chroma_w16x_avx2;
    uavs3d_funs_handle.recon_chroma[4] = uavs3d_recon_chroma_w16x_avx2;
    uavs3d_funs_handle.recon_chroma[5] = uavs3d_recon_chroma_w16x_avx2;

    uavs3d_funs_handle.itrans_dct2[1][2] = itrans_dct2_h4_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[1][3] = itrans_dct2_h4_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[1][4] = itrans_dct2_h4_w32_avx2;

    uavs3d_funs_handle.itrans_dct2[2][1] = itrans_dct2_h8_w4_avx2;
    uavs3d_funs_handle.itrans_dct2[2][2] = itrans_dct2_h8_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[2][3] = itrans_dct2_h8_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[2][4] = itrans_dct2_h8_w32_avx2;
    uavs3d_funs_handle.itrans_dct2[2][5] = itrans_dct2_h8_w64_avx2;

    uavs3d_funs_handle.itrans_dct2[3][1] = itrans_dct2_h16_w4_avx2;
    uavs3d_funs_handle.itrans_dct2[3][2] = itrans_dct2_h16_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[3][3] = itrans_dct2_h16_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[3][4] = itrans_dct2_h16_w32_avx2;
    uavs3d_funs_handle.itrans_dct2[3][5] = itrans_dct2_h16_w64_avx2;

    uavs3d_funs_handle.itrans_dct2[4][1] = itrans_dct2_h32_w4_avx2;
    uavs3d_funs_handle.itrans_dct2[4][2] = itrans_dct2_h32_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[4][3] = itrans_dct2_h32_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[4][4] = itrans_dct2_h32_w32_avx2;
    uavs3d_funs_handle.itrans_dct2[4][5] = itrans_dct2_h32_w64_avx2;

    uavs3d_funs_handle.itrans_dct2[5][2] = itrans_dct2_h64_w8_avx2;
    uavs3d_funs_handle.itrans_dct2[5][3] = itrans_dct2_h64_w16_avx2;
    uavs3d_funs_handle.itrans_dct2[5][4] = itrans_dct2_h64_w32_avx2;
    uavs3d_funs_handle.itrans_dct2[5][5] = itrans_dct2_h64_w64_avx2;

    uavs3d_funs_handle.sao[ Y_C] = uavs3d_sao_on_lcu_avx2;
    uavs3d_funs_handle.sao[UV_C] = uavs3d_sao_on_lcu_chroma_avx2;
    uavs3d_funs_handle.alf[ Y_C] = uavs3d_alf_one_lcu_avx2;
    uavs3d_funs_handle.alf[UV_C] = uavs3d_alf_one_lcu_chroma_avx2;
    uavs3d_funs_handle.alf[2] = uavs3d_alf_one_lcu_one_chroma_avx2;

}

#endif